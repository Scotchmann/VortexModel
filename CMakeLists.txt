cmake_minimum_required(VERSION 3.5)
project(VortexModel_linux)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/include/root" )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 " )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
#set(CMAKE_CXX_FLAGS " -I/path/to/compute/include main.cpp ")
find_package(Boost 1.61.0 COMPONENTS compute)




set(SOURCE_FILES main.cpp Vortex.cpp Vortex.h VortexModel.cpp VortexModel.h Agent.cpp Agent.h Bond.cpp Bond.h Pole.cpp Pole.h InertialVector.cpp InertialVector.h )
add_executable(VortexModel_linux ${SOURCE_FILES})
#list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
#set(ROOT_DIR /usr/include/root/)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenCL REQUIRED)
#find_package(BoostCompute REQUIRED)
#find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)


#include(${ROOT_USE_FILE})
#add_definitions(${ROOT_CXX_FLAGS})

#include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${ROOT_INCLUDE_DIRS})
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS}  ${Boost_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS} /usr/local/include/ )

link_directories(${OpenCL_LIBRARY})

target_link_libraries(VortexModel_linux ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}  ${Boost_LIBRARIES} ${OpenCL_LIBRARY})

