cmake_minimum_required(VERSION 3.21.0)
project(protobuf_learn VERSION 0.1.0)


set(CMAKE_CXX_STANDARD 17)
include(FindProtobuf)
#find_package(Protobuf REQUIRED)

if ( Protobuf_FOUND )
    message( STATUS "Protobuf version : ${Protobuf_VERSION}" )
    message( STATUS "Protobuf include path : ${Protobuf_INCLUDE_DIRS}" )
    message( STATUS "Protobuf libraries : ${Protobuf_LIBRARIES}" )
    message( STATUS "Protobuf compiler libraries : ${Protobuf_PROTOC_LIBRARIES}")
    message( STATUS "Protobuf lite libraries : ${Protobuf_LITE_LIBRARIES}")
else()
    message( WARNING "Protobuf package not found -> specify search path via PROTOBUF_ROOT variable")
endif()

SET(CMAKE_OSX_ARCHITECTURES "arm64")
set(Protobuf_LIBRARIES "/opt/homebrew/lib")
set(Protobuf_INCLUDE_DIRS "/opt/homebrew/include")
set(CMAKE_EXE_LINKER_FLAGS "-lprotobuf")
#set(LINKER_FLAGS "-lprotobuf")
#set(LD_FLAGS ${LINKER_FLAGS})

include_directories(${Protobuf_INCLUDE_DIRS})
add_executable(writer src/write_address.cpp)
#target_link_libraries(writer ${Protobuf_LIBRARIES})

target_link_libraries(writer -L/usr/local/lib/)
#target_link_libraries(writer -lprotobuf)
target_link_libraries(writer libprotobuf.a)
target_link_libraries(writer libprotoc.a)

