/*
Сравните и выведите в консоль время работы последовательного
и параллельного с использованием нескольких потоков алгоритмов,
каждый из которых выделяет в динамической памяти числовой
массив размером 100 Мб и инициализирует его значениями по
следующему шаблону: 0, 1, 2, 3, 0, 1, 2, 3, … */

#include<unistd.h>
#include <stdio.h>
int main(  ) {
    int pid = fork();
    if ( pid == 0 ) {
        printf("parallel and sequential \n");
        execl("./ex1", " ", NULL);
    } else {
        execl("./ex2", " ", NULL);
    }

    return 0;
}