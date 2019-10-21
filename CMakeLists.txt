cmake_minimum_required(VERSION  3.12.4)
project(IZ2)

set(CMAKE_C_STANDARD 11)
set(LIB_SOURCE_FILES source/main.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

enable_testing()

add_library(IZ2_lib STATIC ${LIB_SOURCE_FILES})

add_executable(IZ2 source/main.c)
add_executable(unit_test test/unit_test.cpp)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           master
        SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
        BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND     ""
        INSTALL_COMMAND   ""
        TEST_COMMAND      ""
        )
find_package(GTest REQUIRED)
include_directories(include)
include_directories(${GTEST_INCLUDE_DIRS})


find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(IZ2 ${PTHREAD_LIBRARY})
target_link_libraries(unit_test ${GTEST_LIBRARIES})
target_link_libraries(IZ2 IZ2_lib)
target_link_libraries(unit_test IZ2_lib)


add_test(NAME test COMMAND unit_test)