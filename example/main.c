//
// Created by master on 21.10.2019.
//

#include "../source/main.c"

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