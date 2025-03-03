#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hidden() {
    system("/bin/bash");
}

void vulnerable() {
    char buffer[60];
    printf("Enter some input: ");
    fflush(stdout); // Flush to ensure the prompt is sent immediately
    gets(buffer); // Vulnerable function
    printf("You entered: %s\n", buffer);
    fflush(stdout); // Flush to ensure the output is sent immediately
}

int main() {
    printf("Welcome to the Stack Overflow Challenge!\n");
    fflush(stdout); // Flush to ensure the message is sent immediately
    vulnerable();
    return 0;
}
