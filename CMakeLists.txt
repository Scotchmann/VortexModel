cmake_minimum_required(VERSION 3.5)
project(VortexModel_linux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vortex.cpp Vortex.h VortexModel.cpp VortexModel.h Agent.cpp Agent.h Bond.cpp Bond.h Pole.cpp Pole.h)
add_executable(VortexModel_linux ${SOURCE_FILES})