//
// Created by master on 21.10.2019.
//

#include <gtest/gtest.h>
extern "C" {
#include "fill_array.h"
};
TEST(test_seq, test_correct_input){
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
    for (size_t i = 0; i < memory_size/sizeof(int); i++){
        ref_array[i] = i;
    }
    fill_array(ref_array, array_to_fill, memory_size/sizeof(int));
    for (size_t i = 0; i < memory_size/sizeof(int); i++){
        ASSERT_EQ(array_to_fill[i], ref_array[i]);
    }
    free(array_to_fill);
    free(ref_array);
}

TEST(test_seq, test_wrong_input){
    int *a = NULL;
    int *b = NULL;
    ASSERT_EQ(fill_array(a,b, 10), FAILURE);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
