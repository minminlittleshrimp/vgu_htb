#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hidden() {
    system("/bin/bash");
}

struct user {
    char *name;
};

int main(int argc, char *argv[]) {
    // create object user on heap
    struct user *u1 = malloc(sizeof(struct user));
    u1->name = malloc(8);

    struct user *u2 = malloc(sizeof(struct user));
    u2->name = malloc(8);


    printf("Enter your name: ");
    fflush(stdout);
    gets(u1->name);
    printf("Enter your friend's name: ");
    fflush(stdout);
    gets(u2->name);

    printf("Hello %s and %s\n", u1->name, u2->name);
    
    return 0;
}
