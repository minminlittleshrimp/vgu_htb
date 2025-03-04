#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hidden() {
    system("/bin/bash");
}

void vulnerable() {
    char buffer[32]; // Small buffer on the stack

    printf("Enter your input: ");
    fflush(stdout);
    gets(buffer); // Unsafe function, vulnerable to buffer overflow

    printf("You entered: %s\n", buffer);
}

int main() {
    vulnerable();
    return 0;
}
