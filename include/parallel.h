//
// Created by master on 22.10.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define ERROR_MALLOC -11
#define ERROR_CREATE_PTHREAD -12
#define ERROR_JOIN_PTHREAD -13
#define SUCCESS 0

#ifndef IZ2_PARALLEL_H
#define IZ2_PARALLEL_H
typedef struct{
    int * a;
    int from;
    int  to;
} pthr_data;
void * thread_routine(void *);
int parallel(size_t);
int * fill_array_parallel(int *, int, int );
#endif //IZ2_PARALLEL_H
