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