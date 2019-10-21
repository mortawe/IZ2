//
// Created by master on 21.10.2019.
//

#include <gtest/gtest.h>
extern "C" {
#include "main.h"
};

TEST(test_seq, test_seq_test_fill_Test){
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}