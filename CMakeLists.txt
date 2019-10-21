cmake_minimum_required(VERSION  3.12.4)
project(IZ2)

set(CMAKE_C_STANDARD 11)

add_executable(IZ2 source/main.c)
include_directories(include)
find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(IZ2 ${PTHREAD_LIBRARY})
