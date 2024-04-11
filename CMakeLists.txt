cmake_minimum_required(VERSION 3.16.3)
project(Mandelbrot
	VERSION 1.0
	DESCRIPTION "A program for displaying the Mandelbrot set"
	LANGUAGES CXX)

#C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#custom find modules:
#I did not make these
#https://github.com/aminosbh/sdl2-cmake-modules/tree/master
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#SDL packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Mandelbrot
	src/eventHandler.cpp
	src/eventHandler.hpp
	src/globals.hpp
	src/headers.hpp
	src/main.cpp
	src/mandelbrot.cpp
	src/mandelbrot.hpp
	src/renderer.cpp
	src/renderer.hpp
	src/utils.cpp
	src/utils.hpp
)

target_link_libraries(Mandelbrot ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})