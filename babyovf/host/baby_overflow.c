#include <stdio.h>
#include <string.h>

int main() {
    char str[10];
    int flag = 0;  // False

    while (1==1)
    {
        printf("Hint: the secret code is only 10 character. Can you guess it?\n");
        printf("Enter the secret code: ");
        scanf("%s", str); 

        // Check if the input matches the secret code to set the flag
        if (strcmp(str, "secret123") == 0) {
            flag = 1;  // True
        }

        if (flag) {
            printf("Congratulations! You've found the flag: vgu_eth_hacking{bAb3_bAb3_ov3rfl0w}\n");
        } else {
            printf("Access denied! Try again.\n");
        }

    };
    

    return 0;
}
