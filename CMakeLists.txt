cmake_minimum_required(VERSION 3.13.0)
project(ignis)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE ignisHpp "include/*.hpp")
file(GLOB_RECURSE ignisCpp "src/*.cpp")

if("$ENV{VULKAN_SDK}" STREQUAL "")
	set(graphicsApi opengl CACHE STRING "Graphics API")
	message("-- Vulkan SDK not found, falling back to OpenGL")
else()
	set(graphicsApi vulkan CACHE STRING "Graphics API")
endif()

set(graphicsApis vulkan opengl directx)
set_property(CACHE graphicsApi PROPERTY STRINGS ${graphicsApis})

message("-- Enabling ${graphicsApi} support")

# Setup graphics api
	
file(GLOB_RECURSE apiHpp "api/${graphicsApi}/include/*.hpp")
file(GLOB_RECURSE apiCpp "api/${graphicsApi}/src/*.cpp")

# Add ocore

if(TARGET ocore)
	get_target_property(CORE2_SOURCE_DIR ocore SOURCE_DIR)
	message("-- Enabling core2 support (${CORE2_SOURCE_DIR})")
else()
	add_subdirectory(core2)
	set(CORE2_SOURCE_DIR core2)
endif()

# Setup platforms
	
file(GLOB_RECURSE platformHpp "api/${graphicsApi}/platform/${platform}/include/*.hpp")
file(GLOB_RECURSE platformCpp "api/${graphicsApi}/platform/${platform}/src/*.cpp")

# Link library

add_library(
	ignis STATIC
	${ignisHpp}
	${ignisCpp}
	${platformHpp}
	${platformCpp}
	${apiHpp}
	${apiCpp}
	CMakeLists.txt
)

target_include_directories(ignis PRIVATE include)
target_include_directories(ignis PRIVATE ${CORE2_SOURCE_DIR}/include)
target_include_directories(ignis PRIVATE api/${graphicsApi}/include)
target_include_directories(ignis PRIVATE core2/platform/${platform}/include)
target_include_directories(ignis PRIVATE api/${graphicsApi}/platform/${platform}/include)
target_link_libraries(ignis PRIVATE ocore)

if(${graphicsApi} STREQUAL "vulkan")

	message("-- Vulkan SDK found at $ENV{VULKAN_SDK}")
	target_include_directories(ignis PUBLIC $ENV{VULKAN_SDK}/include)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_directories(ignis PUBLIC $ENV{VULKAN_SDK}/Lib)
	else()
		target_link_directories(ignis PUBLIC $ENV{VULKAN_SDK}/Lib32)
	endif()

	target_link_libraries(ignis PUBLIC vulkan-1)

endif()

source_group("Headers" FILES ${ignisHpp})
source_group("Source" FILES ${ignisCpp})
source_group("Platform (${platform}) Headers" FILES ${platformHpp})
source_group("Platform (${platform}) Source" FILES ${platformCpp})
source_group("Graphics (${graphicsApi}) Headers" FILES ${apiHpp})
source_group("Graphics (${graphicsApi}) Source" FILES ${apiCpp})

if(MSVC)
    target_compile_options(ignis PRIVATE /W4 /WX /MD /MP /wd26812 /wd4201 /EHsc /GR)
else()
    target_compile_options(ignis PRIVATE -Wall -fms-extensions -Wextra -Werror)
endif()
