###############################################################################
# NAME:             CMakeLists.txt
#
# AUTHOR:           Ethan D. Twardy <edtwardy@mtu.edu>
#
# DESCRIPTION:      Build script for the ReachCodec.
#
# CREATED:          09/12/2020
#
# LAST EDITED:      09/17/2020
###

cmake_minimum_required(VERSION 3.15.1)
project(ReachCodec DESCRIPTION "Codec Library for the Reach Media Server")

include(conanbuildinfo.cmake)
conan_basic_setup()

list(APPEND PROJECT_FLAGS "--bind" "-Wall" "-Wextra" "-Os" "-s FILESYSTEM=0"
  "-s ENVIRONMENT=web" "-s MODULARIZE=1" "-s EXPORT_NAME=ReachCodec"
  "-s ASYNCIFY=1" "-std=c++17")
list(JOIN PROJECT_FLAGS " " PROJECT_FLAGS)
string(CONCAT CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_FLAGS}")

set(REACH_CODEC_SOURCES
  src/AudioStreamDecoder.cpp
  src/DecoderFactory.cpp
  src/FlacDecoder.cpp)

add_executable(ReachCodec ${REACH_CODEC_SOURCES})
set_target_properties(ReachCodec PROPERTIES
  OUTPUT_NAME "ReachCodec"
  SUFFIX ".js")
target_link_libraries(ReachCodec ${CONAN_LIBS})
target_include_directories(ReachCodec PRIVATE include ${CONAN_INCLUDE_DIRS})

###############################################################################
