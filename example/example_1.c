//
// Created by master on 21.10.2019.
//
/*
Сравните и выведите в консоль время работы последовательного 
и параллельного с использованием нескольких потоков алгоритмов,
каждый из которых выделяет в динамической памяти числовой 
массив размером 100 Мб и инициализирует его значениями по 
следующему шаблону: 0, 1, 2, 3, 0, 1, 2, 3, … */

#include "../include/sequential.h"
#include "../include/parallel.h"

int main(){
    const size_t memory_size = 100 * 1024 * 1024;
    struct timespec start, finish;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);
    parallel(memory_size);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("parallel : %f \n", elapsed);

    clock_gettime(CLOCK_MONOTONIC, &start);
    sequential(memory_size);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("sequential : %f \n ", elapsed);
    return 0;
}
