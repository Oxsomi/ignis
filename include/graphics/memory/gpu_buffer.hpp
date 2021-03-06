#pragma once
#include "graphics/gpu_resource.hpp"
#include "graphics/command/command_list.hpp"
#include "types/vec.hpp"

namespace ignis {

	namespace cmd {
		class FlushBuffer;
	}

	enum class GPUBufferUsage : u32;
	enum class GPUMemoryUsage : u8;

	class GPUBuffer : public GPUObject, public GPUResource {

		friend class CommandList;
		friend class UploadBuffer;
		friend class cmd::FlushBuffer;

	public:

		struct Info {

			Buffer initData;
			u64 size;

			GPUBufferUsage type;
			GPUMemoryUsage usage;

			List<Vec2u64> pending;	//offset, size
			bool markedPending{};

			Info(u64 bufferSize, GPUBufferUsage type, GPUMemoryUsage usage);
			Info(GPUBufferUsage type, GPUMemoryUsage usage, const Buffer &initData);
		};

		apimpl struct Data;

		GPUBuffer(Graphics &g, const String &name, const Info &info):
			GPUBuffer(g, name, info, GPUObjectType::BUFFER) {}

		static bool isCompatible(GPUBufferType type, GPUBufferUsage usage);

		bool isCompatible(const RegisterLayout &reg, const GPUSubresource &resource) const final override;

		inline u64 size() const { return info.size; }

		Data *getExtendedData() { return data; }
		const Info &getInfo() const { return info; }

		template<typename T = u8>
		T *getBuffer() const { return (T*) info.initData.data(); }

		void flush(u64 offset, u64 size);

		//Only valid if the GPU memory is present on the CPU (e.g. it's shared memory)
		apimpl Buffer readback(u64 offset, u64 size);

	protected:

		void mergePending();

		apimpl GPUBuffer(Graphics &g, const String &name, const Info &info, GPUObjectType type);

		//Prepare for any data to be allocated that's needed
		//Returns { 0, u64_MAX } if an upload buffer is not needed
		apimpl Pair<u64, u64> prepare(CommandList::Data*, UploadBuffer*);

		//Copy allocation from GPU to CPU
		apimpl void flush(CommandList::Data*, UploadBuffer*, const Pair<u64, u64>&);

		apimpl ~GPUBuffer();

	private:

		Info info;
		Data *data;
	};

	using GPUBufferRef = GraphicsObjectRef<GPUBuffer>;
}