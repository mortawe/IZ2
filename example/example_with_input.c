//
// Created by master on 25.10.2019.
//

#include <unistd.h>
#include "fill_array.h"
typedef struct {
    int s;
    int p;
} flags;


int main() {

    printf("Введите размер массива: ");
    int array_size;
    scanf("%d", &array_size);
    int * ref_array = malloc(array_size * sizeof(int));

    printf("\n Введите значения %d элементов массива: ", array_size);
    for (int i = 0; i < array_size; i++) {
        scanf("%d", &ref_array[i]);
    }

    struct timespec start, finish;
    double elapsed;
    int * array_to_fill = malloc(array_size * sizeof(int));

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
    free( array_to_fill);
    free(ref_array);


    return 0;
}
