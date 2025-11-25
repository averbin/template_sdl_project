cmake_minimum_required(VERSION 3.20)
project(TemplateOpenGLProject LANGUAGES C CXX)

message(STATUS "_-_-_ Project Name: ${CMAKE_PROJECT_NAME}")

# --- OpenGL ---
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# --- SDL Download, Build and Find ---
set(SDL3_ROOT ${CMAKE_SOURCE_DIR}/external/SDL3)
set(SDL3_SRC  ${SDL3_ROOT}/output)
set(SDL3_BUILD ${SDL3_ROOT}/build)
set(SDL3_INSTALL ${SDL3_ROOT}/install)

# --- SDL Configuration ---
set(SDL_TEST OFF CACHE INTERNAL "")
set(SDL_SHARED OFF CACHE INTERNAL "")
set(SDL_STATIC ON CACHE INTERNAL "")

# --- Download SDL---
include(FetchContent)

set(FETCHCONTENT_BASE_DIR ${SDL3_INSTALL})
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG a8589a84226a6202831a3d49ff4edda4acab9acd
    SOURCE_DIR ${SDL3_SRC}
	BINARY_DIR ${SDL_BUILD}
)

FetchContent_GetProperties(SDL3)
FetchContent_MakeAvailable(SDL3)

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
	PRIVATE
		SDL3::SDL3
		OpenGL::GL	
)
