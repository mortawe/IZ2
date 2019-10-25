//
// Created by master on 25.10.2019.
//
#include <gtest/gtest.h>
extern "C" {
#include "fill_array.h"
};
TEST(test_par, test_correct_input){
    const size_t memory_size = 100 * 1024 * 1024;
    int * array_to_fill = (int*)malloc(memory_size);
    if (array_to_fill == NULL){
        exit(ERROR_MALLOC);
    }
    int * ref_array = (int*)malloc(memory_size);
    if (ref_array == NULL){
        free(array_to_fill);
        exit(ERROR_MALLOC);
    }
    for (int i = 0; i < memory_size/sizeof(int); i++){
        ref_array[i] = i;
    }
    fill_array(ref_array, array_to_fill, memory_size/sizeof(int));
    for (int i = 0; i < memory_size/sizeof(int); i++){
        ASSERT_EQ(array_to_fill[i], ref_array[i]);
    }
    free(array_to_fill);
    free(ref_array);
}
TEST(test_par, test_thread_routine){
    int * array_to_fill = (int*)malloc(1000*sizeof(int));
    if (array_to_fill == NULL){
        exit(ERROR_MALLOC);
    }
    int * ref_array = (int*)malloc(1000*sizeof(int));
    if (ref_array == NULL){
        free(array_to_fill);
        exit(ERROR_MALLOC);
    }
    for (int i = 0; i < 1000; i++){
        ref_array[i] = i;
    }
    pthr_data * data1 = (pthr_data *)malloc(sizeof(pthr_data));
    if (data1 == NULL) {
        free(array_to_fill);
        free(ref_array);
        exit(ERROR_MALLOC);
    }
    char * used_index1 = (char * ) calloc(sizeof(char), 1000);
    data1->from = 0;
    data1->to = 1000;
    data1->a = array_to_fill;
    data1->ref = ref_array;
    data1->used = used_index1;
    pthr_data * data2 = (pthr_data *)malloc(sizeof(pthr_data));
    if (data2 == NULL) {
        free(array_to_fill);
        free(ref_array);
        exit(ERROR_MALLOC);
    }
    data2->from = 500;
    data2->to = 1000;
    data2->a = array_to_fill;
    data2->ref = ref_array;
    data2->used = used_index1;
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_routine, data1);
    pthread_create(&thread2, NULL, thread_routine, data2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    for (int i = 0; i < 1000; i++){
        ASSERT_EQ(array_to_fill[i], ref_array[i]);
    }
    free(array_to_fill);
    free(ref_array);
    free(used_index1);
    free(data1);
    free(data2);
}
TEST(test_par, test_wrong_input){
    int *a = NULL;
    int *b = NULL;
    ASSERT_EQ(fill_array(a,b, 10), FAILURE);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
