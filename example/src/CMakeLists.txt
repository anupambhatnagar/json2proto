INCLUDE(FindProtobuf)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER addressbook.proto)
ADD_LIBRARY(proto ${PROTO_HEADER} ${PROTO_SRC})
