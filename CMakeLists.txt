cmake_minimum_required(VERSION 3.5)
project(VortexModel_linux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/include/root" )

set(SOURCE_FILES main.cpp Vortex.cpp Vortex.h VortexModel.cpp VortexModel.h Agent.cpp Agent.h Bond.cpp Bond.h Pole.cpp Pole.h)
add_executable(VortexModel_linux ${SOURCE_FILES})
#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(ROOT_DIR /usr/include/root/)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
#find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)


#include(${ROOT_USE_FILE})
add_definitions(${ROOT_CXX_FLAGS})

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})

target_link_libraries(VortexModel_linux ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${ROOT_LIBRARIES})