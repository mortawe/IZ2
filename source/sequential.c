//
// Created by master on 21.10.2019.
//
#include "fill_array.h"
int fill_array(int * ref_array, int * array_to_fill, size_t array_size) {
    if (ref_array == NULL || array_to_fill == NULL) return FAILURE;
    for (int i = 0; i < array_size; i++) {
        array_to_fill[i] = ref_array[i];
    }
    return SUCCESS;
}




