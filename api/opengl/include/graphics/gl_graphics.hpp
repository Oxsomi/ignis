#pragma once 
#include "types/types.hpp"
#include "graphics/graphics.hpp"

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
	#include <gl/GL.h>
	#include "graphics/wglext.h"
#endif

#include "glext.h"

namespace ignis {

	class Surface;
	class Swapchain;

	//Graphics data

	struct Graphics::Data {

		Surface *currentSurface{};
		Swapchain *swapchain{};

		f32 depth{};
		u32 stencil{};

		GLuint readFramebuffer{}, drawFramebuffer{};

		Vec4u viewport{}, scissor{};

		Vec4f clearColor{};

		u32 maxSamples;

		u32 minor, major;
		bool isES{}, scissorEnable{};

	};

}

#include "gl_header.hpp"