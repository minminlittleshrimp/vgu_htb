#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sorry this time :))
void win() {
    //system("/bin/bash");
    printf("You lose! No shell here (T.T)!\n");
}

void get_input() {
    char something[60]= {0};

    printf("What do you want to solve?\n");
    fflush(stdout);
    fgets(something, 101, stdin);
    printf("Hmmm..... %s...", something);
}

int main(int argc, char *argv[]) {
    printf("Hello noob, welcome to ret2lib chall!!!\n");
    get_input();
    printf("You lose! Bye noob! (~o~)\n");
    return 0;
}
