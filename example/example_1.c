//
// Created by master on 21.10.2019.
//


#include "fill_array.h"


int main() {
    srand(clock());
    const size_t memory_size = 100 * 1024 * 1024;
    size_t array_size = memory_size / sizeof(int);
    int * const ref_array = calloc(array_size, sizeof(int));
    for (int i = 0; i < array_size; i++){
        ref_array[i] = rand() % sizeof(int) + 1;
    }

    struct timespec start, finish;
    double elapsed;
    int * array_to_fill = malloc(memory_size);
    clock_gettime(CLOCK_MONOTONIC, &start);
    int status = fill_array(ref_array, array_to_fill, array_size);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    if (status == SUCCESS) {
        printf("time : %f \n", elapsed);
    } else {
        printf("error");
    }
    free(ref_array);
    free(array_to_fill);
    return 0;
}
