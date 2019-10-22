//
// Created by master on 21.10.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define ERROR_MALLOC -11
#define ERROR_CREATE_PTHREAD -12
#define ERROR_JOIN_PTHREAD -13
#define SUCCESS 0
const size_t memory_size = 100 * 1024 * 1024;
#ifndef T2_SEQUENTIAL_H
#define T2_SEQUENTIAL_H
int sequential(size_t);

int * fill_array_seq(int *, int);
#endif //IZ2_MAIN_H
