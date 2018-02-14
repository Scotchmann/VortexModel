cmake_minimum_required(VERSION 3.5)
project(VortexModel_linux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Dlinux" )
set(SOURCE_FILES main.cpp Vortex.cpp Vortex.h VortexModel.cpp VortexModel.h Agent.cpp Agent.h Bond.cpp Bond.h Pole.cpp Pole.h InertialVector.cpp InertialVector.h DifferentialSet.h)

add_executable(VortexModel_linux ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenCL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS}  ${Boost_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS} /usr/local/include/ )

link_directories(${OpenCL_LIBRARY})

target_link_libraries(VortexModel_linux -lm -lpthread ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}  ${Boost_LIBRARIES} ${OpenCL_LIBRARY})
