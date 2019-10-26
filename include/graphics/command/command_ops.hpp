#pragma once
#include "types/types.hpp"

namespace ignis {

	//Command op codes

	//Techniques (FT or EXT)
	//	_FT: Feature (Requires a certain API)
	//	_EXT: Extension (Requires a certain GPU)
	//Their availability can be queried from the Graphics class
	//When a FT or EXT is requested, it should return how available it is
	//	Supported: It is fully supported by hardware
	//	Performance: It runs slower but still works
	//	Unsupported: It won't be able to run
	//Suffixes:
	//	none: Core standard
	//	_0: Rarely unavailable, often available either by hardware or software (performance impact when software)
	//  _1: Often available on desktop
	//  _2: Rarely available on desktop
	//  _3: Only available for certain vendors

	//TODO: Refactor into bitset; so you can immediately query important flags
	enum CommandOp : u32 {

		//Core commands

		CMD_BIND_PIPELINE,
		CMD_BIND_DESCRIPTORS,
		CMD_BIND_PRIMITIVE_BUFFER,

		CMD_BEGIN_SURFACE,
		CMD_END_SURFACE,
		CMD_BEGIN_QUERY,					//TODO:
		CMD_END_QUERY,						//TODO:

		CMD_PRESENT,

		CMD_SET_CLEAR_COLOR,
		CMD_SET_CLEAR_DEPTH,
		CMD_SET_CLEAR_STENCIL,
		CMD_SET_BLEND_CONSTANTS,			//TODO:
		CMD_SET_LINE_WIDTH,					//TODO:
		CMD_SET_STENCIL_COMPARE_MASK,		//TODO:
		CMD_SET_STENCIL_REFERENCE,			//TODO:
		CMD_SET_STENCIL_WRITE_MASK,			//TODO:

		CMD_DRAW_INSTANCED,
		CMD_DRAW_INDIRECT,					//TODO:
		CMD_DISPATCH,						//TODO:
		CMD_DISPATCH_INDIRECT,				//TODO:

		CMD_CLEAR_SURFACE,					//TODO:
		CMD_CLEAR_IMAGE,					//TODO:
		CMD_CLEAR_QUERY_POOL,				//TODO:

		CMD_BLIT_SURFACE,
		CMD_COPY_BUFFER,					//TODO:
		CMD_COPY_IMAGE_TO_BUFFER,			//TODO:
		CMD_COPY_BUFFER_TO_IMAGE,			//TODO:
		CMD_COPY_QUERY_POOL,				//TODO:

		CMD_DEBUG_START_REGION,
		CMD_DEBUG_INSERT_MARKER,
		CMD_DEBUG_END_REGION,

		//Software or hardware backed commands
		//TODO:

		CMD_BEGIN_QUERY_INDIRECT_EXT_0,
		CMD_END_QUERY_INDIRECT_EXT_0,
		CMD_BEGIN_CONDITIONAL_EXT_0,
		CMD_END_CONDITIONAL_EXT_0,

		//Common commands
		//TODO:

		CMD_DRAW_INDIRECT_COUNT_EXT_2,
		CMD_DRAW_INDEXED_INDIRECT_COUNT_EXT_2,

		//Vendor commands
		//TODO:

		CMD_TRACE_RAYS_FT_3,
		CMD_BUILD_ACCELERATION_STRUCTURE_FT_3,
		CMD_COPY_ACCELERATION_STRUCTURE_FT_3,
		CMD_WRITE_ACCELERATION_STRUCTURE_PROPERTIES_FT_3,
		CMD_DRAW_MESH_TASKS_FT_3,
		CMD_DRAW_MESH_TASKS_INDIRECT_FT_3,
		CMD_DRAW_MESH_TASKS_INDIRECT_COUNT_FT_3,
		//TODO: Variable rate shading

		//End of enum

		CMD_ENUM_NEXT
	};

}