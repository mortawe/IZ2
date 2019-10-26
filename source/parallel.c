//
// Created by master on 22.10.2019.
//
#include <unistd.h>
#include "fill_array.h"


int threads_creation(int * ref_array, int * array_to_fill, char * used_index, size_t array_size){
    int step = array_size >> 1;
    int threads_num = 0, max_threads_num = sysconf(_SC_NPROCESSORS_ONLN)*128;
    pthr_data ** data =  (pthr_data **) malloc(sizeof( pthr_data *) * max_threads_num);
    if (data == NULL || ref_array == NULL || array_to_fill == NULL) {
        free(data);
        return FAILURE;
    }
    pthread_t thread[max_threads_num];
    while (step > 1 && threads_num < max_threads_num){
        int is_array_full = 1;
        for (size_t i = 0; i < array_size; i+= step) {
            if (!used_index[i]){
                data[threads_num] = (pthr_data * ) malloc(sizeof(pthr_data));
                if (data[threads_num] == NULL) {
                    break;
                }
                data[threads_num]->from = i;
                data[threads_num]->a = array_to_fill;
                data[threads_num]->ref = ref_array;
                data[threads_num]->to = array_size;
                data[threads_num]->used = used_index;
                if (pthread_create(&thread[threads_num], NULL, thread_routine, data[threads_num]) == 0) {
                    threads_num++;
                    is_array_full = 0;
                } else {
                    break;
                }
            }
        }
        if (is_array_full == 1) break;
        step = step >> 1;
    }
    for (int i = 0; i < threads_num; i++){
        pthread_join(thread[i], NULL);
        free(data[i]);
    }
    free(data);
    return threads_num;
}

void * thread_routine(void *  arg){
    pthr_data * data = (pthr_data*) arg;
    if (data == NULL){
        return NULL;
    }
    for (size_t i = data->from; i < data->to; i++) {
        if (data->used[i]) {
            break;
        }
        data->used[i] = 1;
        *(data->a+i) = *(data->ref+i);
    }
    return NULL;
}
int  fill_array(int * ref_array, int * array_to_fill, size_t array_size) {
    if (ref_array == NULL || array_to_fill == NULL) return FAILURE;
    char * used_index = (char *) calloc(sizeof(char), array_size);
    threads_creation(ref_array, array_to_fill, used_index, array_size);
    free(used_index);
    return SUCCESS;
}
