cmake_minimum_required(VERSION 3.20)

project(DatabaseServer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g -fPIC")
IF(APPLE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF()

include(./common.cmake)

# Protos
get_filename_component(db_proto "protos/dbserver.proto" ABSOLUTE)
get_filename_component(db_proto_path "${db_proto}" PATH)

# Generated sources
set(db_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/dbserver.pb.cc")
set(db_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/dbserver.pb.h")
set(db_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/dbserver.grpc.pb.cc")
set(db_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/dbserver.grpc.pb.h")
add_custom_command(
	OUTPUT "${db_proto_srcs}" "${db_proto_hdrs}" "${db_grpc_srcs}" "${db_grpc_hdrs}"
	COMMAND ${_PROTOBUF_PROTOC}
	ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
	  --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
	  -I "${db_proto_path}"
	  --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
	  "${db_proto}"
	DEPENDS "${db_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# db_grpc_proto
add_library(db_grpc_proto
	${db_grpc_srcs}
	${db_grpc_hdrs}
	${db_grpc_srcs}
	${db_grpc_hdrs})
target_link_libraries(db_grpc_proto
	absl::check
	${_REFLECTION}
	${_GRPC_GRPCPP}
	${_PROTOBUG_LIBPROTOBUF})

# Target server
add_executable(server serverMain.cpp)
target_link_libraries(server
	db_grpc_proto
	absl::check
	absl::flags
	absl::flags_parse
	absl::log
	${_REFLECTION}
	${_GRPC_GRPCPP}
        ${_PROTOBUG_LIBPROTOBUF})

# Target client
add_executable(client clientMain.cpp)
target_link_libraries(client
        db_grpc_proto
        absl::check
        absl::flags
        absl::flags_parse
        absl::log
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUG_LIBPROTOBUF})
