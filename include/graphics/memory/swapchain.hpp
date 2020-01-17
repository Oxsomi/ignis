#pragma once
#include "../graphics_object.hpp"
#include "../enums.hpp"
#include "types/vec.hpp"

namespace oic {
	struct ViewportInfo;
}

namespace ignis {

	class SwapchainImage;

	class Swapchain : public GraphicsObject {

	public:

		struct Info {

			oic::ViewportInfo *vi;

			Vec2u16 size;

			GPUFormat format;
			bool useVSync;

			Info(oic::ViewportInfo *vi, bool useVSync): 
				vi(vi), size(), format(GPUFormat::NONE), useVSync(useVSync) {}
		};

		plimpl struct Data;

		plimpl apimpl Swapchain(Graphics &g, const String &name, const Info &info);
		plimpl apimpl void present();
		plimpl apimpl void bind();

		apimpl void onResize(const Vec2u32 &size);

		apimpl void begin();
		apimpl void end();

		inline const Info &getInfo() const  { return info; }
		inline Data *getData() const { return data; }

	private:

		plimpl apimpl ~Swapchain();

		Info info;
		Data *data;
	};

}