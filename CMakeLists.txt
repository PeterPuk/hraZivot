cmake_minimum_required(VERSION 3.18)
project(hraZivot C)

set(CMAKE_C_STANDARD 99)

add_executable(hraZivot main.c klient.h server.h server.c klient.c)
target_link_libraries(hraZivot pthread)