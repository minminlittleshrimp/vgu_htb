#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hidden() {
    printf("You win! Here is your shell:\n");
    system("/bin/sh");
}

int vulnerable() {
    char buffer[60] = {0};
    printf("Enter some input: ");
    fflush(stdout); // Flush to ensure the prompt is sent immediately
    fgets(buffer, 100, stdin); // Vulnerable function
    printf("You entered: %s\n", buffer);
}

int main() {
    printf("Welcome to the Stack Overflow Challenge!\n");
    vulnerable();
    return 0;
}
