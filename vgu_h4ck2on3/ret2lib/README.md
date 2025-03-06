# Return-to-libc Challenge

## Overview

This challenge is designed to introduce you to the concept of a **return-to-libc** attack, a common technique used in binary exploitation when the stack is non-executable (NX bit is enabled). The goal is to exploit a buffer overflow vulnerability to execute arbitrary code by leveraging functions from the C standard library (libc).

## Challenge Description

The provided C program is vulnerable to a buffer overflow attack. The `get_input()` function reads up to 100 bytes of input into a buffer that is only 64 bytes long. This allows an attacker to overwrite the return address of the function and control the program's execution flow.

However, the program has several security mechanisms in place:
- **NX (No-Execute) bit**: The stack is non-executable, so you cannot directly execute shellcode on the stack.
- **PIE (Position Independent Executable)**: The binary is compiled with PIE, meaning the base address of the binary is randomized.
- **Full RELRO**: The Global Offset Table (GOT) is read-only, preventing GOT overwrite attacks.
- **No Canary**: There is no stack canary to detect stack corruption.

Despite these protections, the program is still vulnerable to a **return-to-libc** attack because ASLR is disabled, meaning the addresses of libc functions are predictable.

## Objective

Your goal is to exploit the buffer overflow vulnerability to call the `win()` function, which will print a message. However, the `win()` function does not provide a shell. Instead, you need to use a **return-to-libc** attack to spawn a shell by calling `system("/bin/sh")`.

## Hints

1. **Buffer Overflow**: The buffer `something` in the `get_input()` function is only 64 bytes long, but the program reads up to 100 bytes. This allows you to overwrite the return address of the function.

2. **Return Address**: Overwrite the return address of `get_input()` to redirect execution to a function of your choice. Since the stack is non-executable, you cannot directly execute shellcode. Instead, you need to use functions from libc.

3. **Libc Functions**: Use the `system()` function from libc to execute `/bin/sh`. You will need to find the address of `system()` and the string `/bin/sh` in memory.

4. **ASLR Disabled**: Since ASLR is disabled, the addresses of libc functions are predictable. You can find the base address of libc and calculate the addresses of `system()` and `/bin/sh`.

5. **Exploit Construction**: Construct a payload that:
   - Overwrites the return address with the address of `system()`.
   - Provides the address of `/bin/sh` as an argument to `system()`.

6. **Finding Addresses**: Use tools like `gdb` or `objdump` to find the addresses of `system()` and `/bin/sh` in libc. You can also use the `ldd` command to find the base address of libc.

7. **Payload Structure**: Your payload should look something like this:
   ```
   [Padding to overwrite the buffer][Address of system()][Address of exit()][Address of "/bin/sh"]
   ```

## Example Exploit

Here’s a rough outline of how you might construct the exploit:

1. **Find the offset**: Determine the exact number of bytes needed to overwrite the return address. This can be done by analyzing the stack layout or using a debugger.

2. **Find libc addresses**:
   - Use `gdb` to find the address of `system()` in libc.
   - Find the address of the string `/bin/sh` in libc.

3. **Construct the payload**:
   - Pad the input to overwrite the buffer and the return address.
   - Replace the return address with the address of `system()`.
   - Provide the address of `/bin/sh` as an argument to `system()`.

4. **Execute the exploit**:
   - Run the program with the crafted input to spawn a shell.

## Tools

- **gdb**: Use `gdb` to debug the program and find memory addresses.
- **objdump**: Use `objdump` to disassemble the binary and find function addresses.
- **python**: Use a python script to generate the exploit payload.

## Conclusion

This challenge demonstrates how to exploit a buffer overflow vulnerability in a binary with non-executable stack and other protections. By using a **return-to-libc** attack, you can bypass the NX bit and execute arbitrary code by leveraging functions from libc. Good luck, and happy hacking!