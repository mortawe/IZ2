//
// Created by master on 21.10.2019.
//

#include "../include/main.h"

int * fill_array_seq(int * a, int n){
    int count = 0;
    for (int i = 0; i < n; i++) {
        a[i] = count;
        count = (count + 1) % 4;
    }
    return a;
}

void sequential(){
    int * a = (int *) malloc(memory_size);
    if (a == NULL) {
        exit(ERROR_MALLOC);
    }
    size_t array_size = memory_size / sizeof(int);
    fill_array_seq(a, array_size);
    free(a);
}


void * thread_routine(void *  arg){
    pthr_data * data = (pthr_data*) arg;
    int count = 0;
    //printf("thread [%d,%d)\n", a->from, a->to);
    for (int i = data->from; i < data->to; i++) {
        *(data->a + i) = count;
        count = (count + 1) % 4;
    }
}
int * fill_array_parallel(int * a, int array_size, int threads_num){
    int status;
    pthread_t threads[threads_num];
    pthr_data **data = malloc(sizeof(pthr_data * ) * threads_num);
    if (data == NULL) {
        exit(ERROR_MALLOC);
    }
    for (int i = 0; i < threads_num ; i++) {
        data[i] = malloc(sizeof(pthr_data));
        if (data[i] == NULL) {
            exit(ERROR_MALLOC);
        }
        data[i]->from = i * array_size / threads_num;
        data[i]->to = (i+1) * array_size / threads_num;
        data[i]->a = a;
        status = pthread_create(
                &threads[i], NULL, thread_routine, data[i]
        );
        if (status != 0) {
            exit(ERROR_CREATE_PTHREAD);
        }

    }

    for (int i = 0; i < threads_num; i++){
        status = pthread_join(threads[i], NULL);
        if (status != 0) {
            exit(ERROR_JOIN_PTHREAD);
        }
    }
    for (int i = 0; i < threads_num; i++){
        free(data[i]);
    }
    free(data);
}
void parallel(){
    size_t array_size = memory_size / sizeof(int);
    int status;
    int * a = (int *) malloc(memory_size);
    if (a == NULL) {
        exit(ERROR_MALLOC);
    }
    fill_array_parallel(a, array_size, 10);
    free(a);
}

int main(){
    clock_t begin = clock();
    parallel();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("parallel : %f \n", time_spent);

    begin = clock();
    sequential();
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("sequential : %f \n ", time_spent);
    return 0;
}