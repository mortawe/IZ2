//
// Created by master on 21.10.2019.
//

#include <gtest/gtest.h>
extern "C" {
#include "sequential.h"
#include "parallel.h"
};

TEST(test_seq, test_fill_array_seq){
    const size_t memory_size = 100 * 1024 * 1024;
    int * a = (int*)malloc(memory_size);
    if (a == NULL){
        exit(ERROR_MALLOC);
    }
    a = fill_array_seq(a, memory_size / sizeof(int));
    int count = 0;
    for (int i = 0; i < memory_size / sizeof(int); i++){
        ASSERT_EQ(a[i], count);
        count = (count + 1) % 4;
    }
}
TEST(test_seq, test_sequential){
    const size_t memory_size = 100 * 1024 * 1024;
    int status = sequential(memory_size);
    ASSERT_EQ(status, 0);
}

TEST(test_par, test_fill_array_parallel_5_threads){
    const size_t memory_size = 100 * 1024 * 1024;
    int * a = (int*)malloc(memory_size);
    if (a == NULL){
        exit(ERROR_MALLOC);
    }
    a = fill_array_parallel(a, memory_size / sizeof(int), 5);
    int count = 0;
    for (int i = 0; i < memory_size / sizeof(int); i++){
        ASSERT_EQ(a[i], count);
        count = (count + 1) % 4;
    }
}
TEST(test_par, test_fill_array_parallel_25_threads){
    const size_t memory_size = 100 * 1024 * 1024;
    int * a = (int*)malloc(memory_size);
    if (a == NULL){
        exit(ERROR_MALLOC);
    }
    a = fill_array_parallel(a, memory_size / sizeof(int), 25);
    int count = 0;
    for (int i = 0; i < memory_size / sizeof(int); i++){
        ASSERT_EQ(a[i], count);
        count = (count + 1) % 4;
    }
}
TEST(test_par, test_fill_array_parallel_50_threads){
    const size_t memory_size = 100 * 1024 * 1024;
    int * a = (int*)malloc(memory_size);
    if (a == NULL){
        exit(ERROR_MALLOC);
    }
    a = fill_array_parallel(a, memory_size / sizeof(int), 50);
    int count = 0;
    for (int i = 0; i < memory_size / sizeof(int); i++){
        ASSERT_EQ(a[i], count);
        count = (count + 1) % 4;
    }
}

TEST(test_par, test_parallel){
    const size_t memory_size = 100 * 1024 * 1024;
    int status = parallel(memory_size);
    ASSERT_EQ(status, 0);
}
TEST(test_par, test_thread_routine){
    int * a = (int *) malloc(100 * sizeof(int));
    pthr_data *data = (pthr_data *) malloc(sizeof(pthr_data ));
    if (data == NULL) {
            exit(ERROR_MALLOC);
    }
    data->from = 0;
    data->to = 10;
    data->a = a;
    pthread_t thread;
    int status = pthread_create(
                &thread, NULL, thread_routine, data);
    if (status != 0) {
            exit(ERROR_CREATE_PTHREAD);
    }
    status = pthread_join(thread, NULL);
    free(a);
    free(data);
    ASSERT_EQ(status, 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
