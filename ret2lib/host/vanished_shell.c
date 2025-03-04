#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sorry this time :))
void win() {
    //system("/bin/bash");
    //find &system,+9999999,"/bin/sh"
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
    printf("checksec for you babe:\n");
    printf("Arch:     i386-32-little\n");
    printf("RELRO:    Full RELRO\n");
    printf("Stack:    Canary found\n");
    printf("NX:       NX enabled\n");
    printf("PIE:      PIE enabled\n");
    prtinf("ASLR      Disabled\n");
    printf("You lose! Bye noob! (~o~)\n");
    return 0;
}
