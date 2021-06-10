cmake_minimum_required(VERSION 3.19)
project(Linux_Net)

set(CMAKE_CXX_STANDARD 14)

include_directories("lib")
include_directories("src")

#add_executable(test test/test.cpp src/Work.cpp)
add_executable(server src/utils.cpp src/wrap.cpp src/server.cpp src/server_main.cpp src/Work.cpp )
#add_executable(client utils.cpp wrap.cpp client.cpp client_main.cpp)
target_link_libraries(server pthread)
#target_link_libraries(client pthread)
