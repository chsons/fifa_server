cmake_minimum_required(VERSION 3.1)
project(nserver)

ADD_DEFINITIONS(
	-std=c++14
	-O2
	-g -rdynamic
	-Wno-write-strings
	-c
	-Wno-long-long
	-Wpointer-arith
	-DLINUX2
	-D_REENTRANT
	-D_POSIX_PTHREAD_SEMANTICS
)

set(
	SOURECE
	${CMAKE_CURRENT_SOURCE_DIR}/src/http.cc
	
)


add_library(interfacelib STATIC ${SOURECE})


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/inc
	${CMAKE_CURRENT_SOURCE_DIR}/../jsoncpp/include
	${CMAKE_CURRENT_SOURCE_DIR}/../vsys/inc
	${CMAKE_CURRENT_SOURCE_DIR}/../redisdb/inc
)


ADD_EXECUTABLE(EXE_SERVER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc
)

target_link_libraries(
  EXE_SERVER
	${CMAKE_CURRENT_SOURCE_DIR}/../jsoncpp/build/lib/libjsoncpp.a
	interfacelib
	${CMAKE_CURRENT_SOURCE_DIR}/../redisdb/lib/libredisdb.a
	${CMAKE_CURRENT_SOURCE_DIR}/../vsys/lib/libvsys.a
	${CMAKE_CURRENT_SOURCE_DIR}/../acl/lib_acl_cpp/lib/lib_acl_cpp.a
	${CMAKE_CURRENT_SOURCE_DIR}/../acl/lib_protocol/lib/lib_protocol.a
	${CMAKE_CURRENT_SOURCE_DIR}/../acl/lib_acl/lib/lib_acl.a
  pthread
  dlib
	gflags
	glog
	dl
  ach
    
)
