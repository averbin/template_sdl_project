cmake_minimum_required(VERSION 3.5)

project(
	TemplateOpenGLProject
	LANGUAGES C CXX
)

message("_-_-_ Project Name: ${CMAKE_PROJECT_NAME}")

# --== Find OpenGL ==--
# Prevent warning about policy CMP0072
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
# --== ==--

include(FetchContent)
include(CMakePrintHelpers)

# --== Find SDL3 ==--
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/external")
set(SDL3_LOCAL_DIR "${FETCHCONTENT_BASE_DIR}/SDL3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin")

if(EXISTS "${SDL3_LOCAL_DIR}/CMakeLists.txt")
	message(STATUS "Using existing SDL3 at ${SDL3_LOCAL_DIR}")
	set(SDL3_SOURCE_DIR "${SDL3_LOCAL_DIR}")
else()
	message(STATUS "Fetching SDL3 from GitHub into ${SDL3_LOCAL_DIR}")
	FetchContent_Declare(
		SDL3
		GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
		GIT_TAG a96677bdf6b4acb84af4ec294e5f60a4e8cbbe03
		SOURCE_DIR ${SDL3_LOCAL_DIR}
	)
	FetchContent_Populate(SDL3)
	set(SDL3_SOURCE_DIR "${SDL3_LOCAL_DIR}")
endif()

set(SDL_TEST OFF CACHE INTERNAL "")
set(SDL_SHARED OFF CACHE INTERNAL "")
set(SDL_STATIC ON CACHE INTERNAL "")

#FetchContent_GetProperties(SDL3)
#if(NOT sdl3_POPULATED)
#	FetchContent_Populate(SDL3)
	add_subdirectory(${SDL3_SOURCE_DIR} ${CMAKE_BINARY_DIR}/_deps/sdl3-build)
#endif()

# --== ==--
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} 
		PRIVATE 
			SDL3::SDL3
			OpenGL::GL
)
