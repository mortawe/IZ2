//
// Created by master on 21.10.2019.
//

#include "../include/sequential.h"
#include "../include/parallel.h"

int main(){
    const size_t memory_size = 100 * 1024 * 1024;
    clock_t begin = clock();
    parallel(memory_size);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("parallel : %f \n", time_spent);

    begin = clock();
    sequential(memory_size);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("sequential : %f \n ", time_spent);
    return 0;
}