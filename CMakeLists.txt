cmake_minimum_required(VERSION  3.9.2)
project(IZ2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIB_SOURCE_FILES_STATIC_SEQ source/sequential.c)
set(LIB_SOURCE_FILES_SHARED_PAR source/parallel.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pthread -g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include)

add_library(IZ2_lib_STATIC_SEQ STATIC ${LIB_SOURCE_FILES_STATIC_SEQ})
add_library(IZ2_lib_SHARED_PAR SHARED ${LIB_SOURCE_FILES_SHARED_PAR})
#target_link_libraries(IZ2_lib_STATIC_SEQ  gcov)
#target_link_libraries(IZ2_lib_SHARED_PAR gcov)

target_link_libraries(IZ2_lib_STATIC_SEQ  -pthread)
target_link_libraries(IZ2_lib_SHARED_PAR  -pthread)
add_executable(ex1 example/example_1.c)
add_executable(ex2 example/example_2.c)
add_executable(unit_test_par test/unit_test_par.cpp)
add_executable(unit_test_seq test/unit_test_seq.cpp)
add_executable(ex example/example_with_both_libs.cpp)

find_library(PTHREAD_LIBRARY pthread)
target_link_libraries(ex1 ${PTHREAD_LIBRARY})
target_link_libraries(unit_test_par ${GTEST_LIBRARIES})
target_link_libraries(unit_test_seq ${GTEST_LIBRARIES})
target_link_libraries(ex1 IZ2_lib_SHARED_PAR)
target_link_libraries(ex2 IZ2_lib_STATIC_SEQ)
target_link_libraries(unit_test_par IZ2_lib_SHARED_PAR)
target_link_libraries(unit_test_seq IZ2_lib_STATIC_SEQ)

add_test(NAME ex1 COMMAND ex1)
add_test(NAME ex2 COMMAND ex2)
add_test(NAME test1 COMMAND unit_test_par)
add_test(NAME test2 COMMAND unit_test_seq)
add_test(NAME ex COMMAND ex)

add_executable(main example/example_with_input.c)
target_link_libraries(main IZ2_lib_SHARED_PAR)


