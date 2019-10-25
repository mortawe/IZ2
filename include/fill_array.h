//
// Created by master on 25.10.2019.
//

#ifndef IZ2_FILL_ARRAY_H
#define IZ2_FILL_ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
enum{SUCCESS = 0, FAILURE = -1, ERROR_MALLOC = -11};
//parallel
typedef struct{
    int * a; //array_to_fill
    int * ref; //ref array
    char * used;
    int from; //start filling index
    int  to; //worst case end position

} pthr_data;
void * thread_routine(void * arg);
int threads_creation(int * ref_array, int * array_to_fill, char * used_index, int array_size);

//sequential


int fill_array(int * ref_array, int * array_to_fill, size_t array_size);

#endif //IZ2_FILL_ARRAY_H
