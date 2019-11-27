#pragma once
#include "graphics/gpu_resource.hpp"
#include "graphics/graphics_object.hpp"
#include "graphics/enums.hpp"

namespace ignis {

	class Sampler : public GraphicsObject, public GPUResource {

	public:

		struct Info {

			Vec4f borderColor{};

			f32 anisotropy, minLod, maxLod;

			SamplerMin minFilter;
			SamplerMag magFilter;

			SamplerMode s, t, r;

			Info(
				SamplerMin min = SamplerMin::LINEAR_MIPS,
				SamplerMag mag = SamplerMag::LINEAR,
				SamplerMode srtFilterMode = SamplerMode::REPEAT,
				f32 anisotropy = 8,
				f32 minLod = -f32_MAX,
				f32 maxLod = f32_MAX
			);

			Info(
				Vec4f borderColor,
				SamplerMin min = SamplerMin::LINEAR_MIPS,
				SamplerMag mag = SamplerMag::LINEAR,
				f32 anisotropy = 8,
				f32 minLod = -f32_MAX,
				f32 maxLod = f32_MAX
			);

			Info(
				SamplerMode sFilter,
				SamplerMode rFilter,
				SamplerMode tFilter,
				SamplerMin min = SamplerMin::LINEAR_MIPS,
				SamplerMag mag = SamplerMag::LINEAR,
				f32 anisotropy = 8,
				f32 minLod = -f32_MAX,
				f32 maxLod = f32_MAX
			);

			Info(
				Vec4f borderColor,
				SamplerMode sFilter,
				SamplerMode rFilter,
				SamplerMode tFilter,
				SamplerMin min = SamplerMin::LINEAR_MIPS,
				SamplerMag mag = SamplerMag::LINEAR,
				f32 anisotropy = 8,
				f32 minLod = -f32_MAX,
				f32 maxLod = f32_MAX
			);
		};

		apimpl struct Data;

		apimpl Sampler(Graphics &g, const String &name, const Info &info);

		bool isCompatible(
			const RegisterLayout &reg, const GPUSubresource &resource
		) const final override;

		Data *getData() { return data; }
		const Info &getInfo() const { return info; }

	private:

		apimpl ~Sampler();

		Info info;
		Data *data;
	};

}