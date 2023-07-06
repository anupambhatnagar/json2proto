project(protobuf_learn)
cmake_minimum_required(VERSION 3.21.0)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11")

find_package(Protobuf REQUIRED)

if ( Protobuf_FOUND )
    message( STATUS "Protobuf version : ${Protobuf_VERSION}" )
    message( STATUS "Protobuf include path : ${Protobuf_INCLUDE_DIRS}" )
    message( STATUS "Protobuf libraries : ${Protobuf_LIBRARIES}" )
    message( STATUS "Protobuf compiler libraries : ${Protobuf_PROTOC_LIBRARIES}")
    message( STATUS "Protobuf lite libraries : ${Protobuf_LITE_LIBRARIES}")
else()
    message( WARNING "Protobuf package not found -> specify search path via PROTOBUF_ROOT variable")
endif()

add_subdirectory(src)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Protobuf_INCLUDE_DIRS})
add_executable(writer write_address.cpp ${Protobuf_LIBRARIES})
target_link_libraries(writer proto ${Protobuf_LIBRARIES})

