cmake_minimum_required(VERSION  3.9.2)
project(IZ2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIB_SOURCE_FILES
        source/sequential.c
        source/parallel.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)

add_library(IZ2_lib_STATIC STATIC ${LIB_SOURCE_FILES})
add_library(IZ2_lib_SHARED SHARED ${LIB_SOURCE_FILES})

target_link_libraries(IZ2_lib_SHARED -pthread)
add_executable(IZ2 example/example_1.c)
add_executable(unit_test test/unit_test.cpp)

find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(IZ2 ${PTHREAD_LIBRARY})
target_link_libraries(unit_test ${GTEST_LIBRARIES})
target_link_libraries(IZ2 IZ2_lib_SHARED)
target_link_libraries(unit_test IZ2_lib_SHARED)


add_test(NAME test COMMAND unit_test)