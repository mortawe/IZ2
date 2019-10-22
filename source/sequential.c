//
// Created by master on 21.10.2019.
//

#include "sequential.h"

int * fill_array_seq(int * a, int n){
    int count = 0;
    for (int i = 0; i < n; i++) {
        a[i] = count;
        count = (count + 1) % 4;
    }
    return a;
}

int sequential(size_t memory_size){
    int * a = (int *) malloc(memory_size);
    if (a == NULL) {
        exit(ERROR_MALLOC);
    }
    size_t array_size = memory_size / sizeof(int);
    fill_array_seq(a, array_size);
    free(a);
    return SUCCESS;
}



