#pragma once
#include "graphics/graphics_object.hpp"
#include "pipeline_layout.hpp"

namespace ignis {

	class GPUResource;
	class GPUBuffer;
	class Sampler;
	class Texture;

	//Describing which range of the resource has to be bound

	struct GPUSubresource {

		GPUResource *resource{};

		struct TextureRange {

			u32 minLevel{}, minLayer{};
			u32 levelCount{}, layerCount{};

			TextureRange() {}
			TextureRange(
				u32 minLevel, u32 minLayer, u32 levelCount, u32 layerCount
			) :
				minLevel(minLevel), minLayer(minLayer), 
				levelCount(levelCount), layerCount(layerCount) {}
		};

		struct SamplerData : TextureRange {

			Texture *texture{};

			SamplerData() {}
			SamplerData(
				Texture *texture,
				u32 minLevel, u32 minLayer, u32 levelCount, u32 layerCount
			): 
				texture(texture), TextureRange(minLevel, minLayer, levelCount, layerCount){}
		};

		struct BufferRange {

			usz offset{}, size{};

			BufferRange() {}
			BufferRange(usz offset, usz size): offset(offset), size(size) {}
		};

		union {
			TextureRange textureRange;
			SamplerData samplerData;
			BufferRange bufferRange;
		};

		GPUSubresource(): samplerData{} {}
		GPUSubresource(GPUBuffer *resource, usz offset = 0, usz size = 0);

		GPUSubresource(
			Sampler *sampler, Texture *texture,
			u32 levelCount = 0, u32 layerCount = 0,
			u32 minLevel = 0, u32 minLayer = 0
		);

		GPUSubresource(Sampler *resource);

		GPUSubresource(
			Texture *resource,
			u32 levelCount = 0, u32 layerCount = 0,
			u32 minLevel = 0, u32 minLayer = 0
		);
	};

	//Which ranges of resources have to be bound

	class Descriptors : public GraphicsObject {

	public:

		using Subresources = HashMap<u32, GPUSubresource>;

		struct Info {

			PipelineLayout pipelineLayout;
			Subresources resources;

			bool shouldFlush{};

			Info(
				const PipelineLayout &pipelineLayout, 
				const Subresources &resources
			);
		};

		apimpl struct Data;

		apimpl Descriptors(Graphics &g, const String &name, const Info &info);
		apimpl ~Descriptors();

		//Flush the updates from the CPU to the GPU
		apimpl void flush(usz offset, usz size);

		//Update the CPU-side resource; requires flush to be called afterwards
		apimpl void bindSubresource(u32 i, const GPUSubresource &range);

		//Check if descriptor slots are compatible (and exist)
		bool isResourceCompatible(u32 i, const GPUSubresource &resource) const;

		//Check if pipeline layout is compatible with a shader
		bool isShaderCompatible(const PipelineLayout &layout) const;

		Data *getData() { return data; }
		const Info &getInfo() const { return info; }

	private:

		Info info;
		Data *data{};
	};

}