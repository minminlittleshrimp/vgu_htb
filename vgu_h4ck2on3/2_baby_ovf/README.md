# B4BY Level to Overflow

## Introduction
Welcome to the "B4BY Level to Overflow" challenge! This is an introductory challenge designed to help you understand the basics of string buffer overflow vulnerabilities, particularly in relation to the `strcmp` function.

## Challenge Overview
In this challenge, you are given a program that takes user input and processes it using the `strcmp` function. Your goal is to exploit the program by leveraging a buffer overflow vulnerability.

## Understanding the Vulnerability
The challenge revolves around a simple buffer overflow scenario where user input is handled improperly. Specifically, it involves the `strcmp` function, which compares two strings without checking the length of the input buffer.

### Key Concepts to Keep in Mind:
- **Buffer Overflow:** This occurs when data exceeds the allocated buffer size and overwrites adjacent memory.
- **`strcmp` Usage:** The `strcmp` function compares two strings and returns 0 if they are equal. However, if you control the input buffer and its contents, you can manipulate program execution.
- **Exploitation:** By carefully crafting your input, you may be able to overwrite memory or manipulate the program’s logic.

## Hint for Exploitation
1. **Identify the Buffer Size:** The buffer is only **10 bytes**, but `scanf("%s", str);` does not enforce size restrictions.
2. **Overflow the Buffer:** Inputting more than **10 characters** will start overwriting adjacent memory, including the `flag` variable.
3. **Set `flag = 1` by Overflow:** Since `flag` is stored right after the buffer, overflowing with extra characters can change it from `0` to `1`.
4. **Bypass the `strcmp` Check:** Instead of guessing the correct secret, simply exploit the overflow to manipulate `flag`.

### Example Input for Overflow:
```bash
AAAAAAAAAAA  # (11+ characters to modify `flag`)
```

## Tools and Techniques
- **GDB (GNU Debugger):** To analyze the binary and check memory layout.
- **Manual Input Testing:** Since pwntools isn’t required, you can manually input a long string to observe behavior.

## Mitigations
In real-world applications, developers can prevent such vulnerabilities using:
- **Bounds Checking:** Using `fgets` instead of `scanf` to limit input size.
- **Stack Canaries:** Protecting the stack from being overwritten.
- **ASLR (Address Space Layout Randomization):** Randomizing memory addresses to make exploitation harder.
- **DEP/NX (Data Execution Prevention):** Preventing execution of injected shellcode in writable memory regions.

## Conclusion
This challenge is a great introduction to buffer overflow attacks, specifically when exploiting `strcmp` usage. Understanding how buffer overflows work is crucial for both offensive security (penetration testing) and defensive security (secure coding practices).

Happy hacking!
