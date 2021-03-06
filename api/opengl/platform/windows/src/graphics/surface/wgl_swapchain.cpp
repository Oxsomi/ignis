#include "system/windows_viewport_manager.hpp"
#include "system/system.hpp"
#include "system/log.hpp"
#include "graphics/format.hpp"
#include "graphics/wgl_graphics.hpp"
#include "graphics/surface/wgl_swapchain.hpp"

#pragma comment(lib, "opengl32.lib")

using namespace oic;
using namespace windows;

namespace ignis {

	//Create a swapchain
	Swapchain::Swapchain(Graphics &g, const String &name, const Info &inf):
		GPUObject(g, name, GPUObjectType::SWAPCHAIN), info(inf)
	{

		data = new Swapchain::Data{};
		info.size = info.vi->size.cast<Vec2u16>();

		//Create context

		WWindow *win = ((WViewportManager*) System::viewportManager())->get(info.vi);
		data->dc = GetDC(win->hwnd);

		GLint pixelFormatId{};
		GLuint numFormats{};

		//Get a non core context

		const int pixelAttribs[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 0,
			WGL_STENCIL_BITS_ARB, 0,
			0
		};

		wglChoosePixelFormatARB(data->dc, pixelAttribs, NULL, 1, &pixelFormatId, &numFormats);

		if (!numFormats)
			oic::System::log()->fatal("The OpenGL Swapchain's context couldn't be chosen");

		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));

		if (!DescribePixelFormat(data->dc, pixelFormatId, sizeof(pfd), &pfd))
			oic::System::log()->fatal("The OpenGL Swapchain's context couldn't described");

		if (!SetPixelFormat(data->dc, pixelFormatId, &pfd))
			oic::System::log()->fatal("The OpenGL Swapchain's context couldn't be set");

		info.format = GPUFormat::rgba8;

		#ifndef NO_DEBUG
			constexpr int enableDebug = WGL_CONTEXT_DEBUG_BIT_ARB;
		#else
			constexpr int enableDebug{};
		#endif

		int contextAttribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, int(g.getData()->major),
			WGL_CONTEXT_MINOR_VERSION_ARB, int(g.getData()->minor),
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			WGL_CONTEXT_FLAGS_ARB, enableDebug,
			0
		};

		wglSwapIntervalEXT(info.useVSync);
		data->rc = wglCreateContextAttribsARB(data->dc, g.getData()->platform->rc, contextAttribs);

		if (!data->rc || !wglMakeCurrent(data->dc, data->rc))
			oic::System::log()->fatal("The OpenGL Swapchain's context couldn't be made current");

		//Enable debug callbacks

		#ifndef NO_DEBUG
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glxDebugMessage, nullptr);
		#endif

		onResize(info.vi->size);

		//Set it identical to D3D depth system (1 = near, 0 = far), it has better precision
		//The coordinate system is still flipped, so the final blit should inverse height

		glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
		glDepthRange(1, 0);
	}

	Swapchain::~Swapchain() {

		//Finish the thread
		getGraphics().wait();

		//Destroy all FBOs and VAOs

		getGraphics().getData()->destroyContext();

		//Destroy context

		wglMakeCurrent(data->dc, NULL);
		wglDeleteContext(data->rc);

		WWindow *win = ((WViewportManager*)System::viewportManager())->get(info.vi);
		ReleaseDC(win->hwnd, data->dc);

		destroy(data);
	}

	void Swapchain::present() {
		SwapBuffers(data->dc);
	}
}