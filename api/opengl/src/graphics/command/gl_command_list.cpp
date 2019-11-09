#include "graphics/command/command_list.hpp"
#include "graphics/command/command_ops.hpp"
#include "graphics/command/commands.hpp"
#include "graphics/memory/primitive_buffer.hpp"
#include "graphics/surface/swapchain.hpp"
#include "graphics/surface/gl_framebuffer.hpp"
#include "graphics/shader/descriptors.hpp"
#include "graphics/shader/pipeline.hpp"
#include "graphics/gl_context.hpp"

namespace ignis {

	void CommandList::execute(Command *c) {

		using namespace cmd;

		auto &ctx = getGraphics().getData()->getContext();

		//TODO: Instead of doing validation here; 
		//do it whenever a command enters the command buffer!
		//Also make the arguments invalid so they can pass through
		//Also things like begin/end without a framebuffer set

		switch (c->op) {

			case CMD_BEGIN_FRAMEBUFFER:
				{
					auto *bs = (BeginFramebuffer*)c;

					auto size = bs->bindObject->getInfo().size;

					if(!size[0] || !size[1])
						oic::System::log()->fatal("Please specify an initialized framebuffer");

					bs->bindObject->begin(bs->renderArea);
					ctx.currentFramebuffer = bs->bindObject;
				}
				break;

			case CMD_END_FRAMEBUFFER:

				ctx.currentFramebuffer->end();
				break;

			case CMD_SET_CLEAR_COLOR:

				{
					SetClearColor *cc = (SetClearColor*)c;
					Vec4f color = cc->rgbaf;

					if (cc->type == SetClearColor::Type::UNSIGNED_INT)
						color = Vec4f{ 
							f32(cc->rgbau[0]), 
							f32(cc->rgbau[1]),
							f32(cc->rgbau[2]),
							f32(cc->rgbau[3]) 
						};

					else if(cc->type == SetClearColor::Type::SIGNED_INT)
						color = Vec4f {
							f32(cc->rgbai[0]),
							f32(cc->rgbai[1]),
							f32(cc->rgbai[2]),
							f32(cc->rgbai[3])
						};

					if (color != ctx.clearColor) {
						glClearColor(color[0], color[1], color[2], color[3]);
						ctx.clearColor = color;
					}
				}
				break;

			case CMD_SET_CLEAR_DEPTH:

				{
					SetClearDepth *cd = (SetClearDepth*)c;

					if (cd->dataObject != ctx.depth)
						glClearDepth(ctx.depth = cd->dataObject);
				}
				break;

			case CMD_SET_CLEAR_STENCIL:

				{
					SetClearStencil *cd = (SetClearStencil*)c;

					if (cd->dataObject != ctx.stencil)
						glClearStencil(ctx.stencil = cd->dataObject);
				}
				break;

			case CMD_BLIT_FRAMEBUFFER:

				{
					BlitFramebuffer *bf = (BlitFramebuffer*) c;

					GLenum mask{};
					GLenum filter = 
						bf->filter == BlitFramebuffer::BlitFilter::NEAREST ? GL_NEAREST : 
						GL_LINEAR;

					if (bf->mask & BlitFramebuffer::COLOR)
						mask |= GL_COLOR_BUFFER_BIT;
					else if (bf->mask & BlitFramebuffer::DEPTH)
						mask |= GL_DEPTH_BUFFER_BIT;
					else
						mask |= GL_STENCIL_BUFFER_BIT;

					GLuint read = ((Framebuffer*) bf->src)->getData()->index;
					GLuint write = ((Framebuffer*) bf->dst)->getData()->index;

					Vec4u srcArea = bf->srcArea, dstArea = bf->dstArea;

					if (!srcArea[2]) srcArea[2] = bf->src->getInfo().size[0];
					if (!srcArea[3]) srcArea[3] = bf->src->getInfo().size[1];
					if (!dstArea[2]) dstArea[2] = bf->dst->getInfo().size[0];
					if (!dstArea[3]) dstArea[3] = bf->dst->getInfo().size[1];

					glBlitNamedFramebuffer(
						ctx.bound[GL_READ_FRAMEBUFFER] = read,
						ctx.bound[GL_DRAW_FRAMEBUFFER] = write,
						srcArea[0], srcArea[1], srcArea[2], srcArea[3],
						dstArea[0], dstArea[1], dstArea[2], dstArea[3],
						mask,
						filter
					);

				}
				break;

			case CMD_BIND_PRIMITIVE_BUFFER:
				
				{
					auto *pbuffer = ((BindPrimitiveBuffer*) c)->bindObject;

					if (pbuffer != ctx.primitiveBuffer) {
						ctx.primitiveBuffer = pbuffer;

						if (ctx.vaos.find(pbuffer) == ctx.vaos.end())
							ctx.vaos[pbuffer] = glxGenerateVao(pbuffer);

						glBindVertexArray(ctx.vaos[pbuffer]);
					}
				}
				break;

			case CMD_BIND_PIPELINE:
				
				{
					auto *pipeline = ((BindPipeline*) c)->bindObject;

					if (pipeline != ctx.pipeline) {
						ctx.pipeline = pipeline;
						glxBindPipeline(ctx, pipeline);
					}
				}
				break;

			case CMD_BIND_DESCRIPTORS:

				{
					auto *descriptors = ((BindDescriptors*) c)->bindObject;

					if (descriptors != ctx.descriptors) {

						ctx.descriptors = descriptors;

						if(descriptors)
							glxBindDescriptors(ctx, descriptors);
					}

				}

				break;

			case CMD_DRAW_INSTANCED:

				if (!ctx.primitiveBuffer)
					oic::System::log()->fatal("No primitive buffer bound!");

				if (!ctx.pipeline)
					oic::System::log()->fatal("No pipeline bound!");

				if(!ctx.primitiveBuffer->matchLayout(
					ctx.pipeline->getInfo().attributeLayout
				))
					oic::System::log()->fatal("Pipeline vertex layout doesn't match primitive buffer!");

				if (ctx.descriptors && 
					!ctx.descriptors->isShaderCompatible(
						ctx.pipeline->getInfo().pipelineLayout
					)
				)
					oic::System::log()->fatal("Pipeline layout doesn't match descriptors!");

				if(!ctx.currentFramebuffer)
					oic::System::log()->fatal("No surface bound");

				if(
					ctx.currentFramebuffer->getInfo().samples != 
					ctx.pipeline->getInfo().msaa.samples
				)
					oic::System::log()->fatal("Surface didn't have the same number of samples as pipeline");

				{
					auto topo = glxTopologyMode(ctx.pipeline->getInfo().topology);
					auto *di = (DrawInstanced*) c;

					if (ctx.primitiveBuffer->indices())
						glDrawElementsInstancedBaseVertexBaseInstance(
							topo,
							di->count,
							glxGpuFormatType(ctx.primitiveBuffer->getIndexFormat()),
							(void*) (
										usz(di->start) * 
										FormatHelper::getSizeBytes(
											ctx.primitiveBuffer->getIndexFormat()
										)
									 ),
							di->instanceCount,
							di->vertexStart,
							di->instanceStart
						);
					else
						glDrawArraysInstancedBaseInstance(
							topo,
							di->start,
							di->count,
							di->instanceCount,
							di->instanceStart
						);
				}

				break;


			#ifndef NDEBUG

				case CMD_DEBUG_START_REGION:

					{

						auto *sr = (DebugStartRegion*)c;

						glPushDebugGroup(
							GL_DEBUG_SOURCE_APPLICATION,
							0,
							GLsizei(sr->size()),
							sr->string
						);
					}

					break;

				case CMD_DEBUG_END_REGION:

					glPopDebugGroup();
					break;

				case CMD_DEBUG_INSERT_MARKER:

					{

						auto *im = (DebugInsertMarker*)c;

						glDebugMessageInsert(
							GL_DEBUG_SOURCE_APPLICATION,
							GL_DEBUG_TYPE_MARKER,
							0,
							GL_DEBUG_SEVERITY_NOTIFICATION,
							GLsizei(im->size()),
							im->string
						);
					}

					break;

			#else

				case CMD_DEBUG_START_REGION:
				case CMD_DEBUG_END_REGION:
				case CMD_DEBUG_INSERT_MARKER:
					break;

			#endif

			default:
				oic::System::log()->fatal("Unsupported operation");

		}

	}

}