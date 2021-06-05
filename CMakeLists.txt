cmake_minimum_required(VERSION 3.19)
project(Linux_Net)

set(CMAKE_CXX_STANDARD 14)

add_executable(server utils.cpp wrap.cpp server.cpp server_main.cpp )
#add_executable(client utils.cpp wrap.cpp client.cpp client_main.cpp)
target_link_libraries(server pthread)
#target_link_libraries(client pthread)
