# Stack Overflow Challenge (Medium Level)

## Overview

This challenge is designed to test your skills in exploiting a **stack-based buffer overflow** vulnerability. The program asks for your favorite food and stores it in a buffer that is smaller than the input size allowed. By exploiting this vulnerability, you can overwrite the return address of the function and gain control of the program's execution flow.

The goal is to call the `win()` function, which spawns a shell, by carefully crafting your input to exploit the buffer overflow.

---

## Challenge Description

The program has a function called `get_favorite_food()` that reads up to 100 bytes of input into a buffer (`food`) that is only 64 bytes long. This creates a classic **stack-based buffer overflow** vulnerability. By providing carefully crafted input, you can overwrite the return address of the function and redirect execution to the `win()` function, which spawns a shell.

### Protections:
- **No Stack Canary**: There is no stack canary to detect stack corruption.
- **NX (No-Execute)**: The stack is non-executable, so you cannot directly execute shellcode on the stack.
- **ASLR (Address Space Layout Randomization)**: The addresses of the stack, heap, and libraries are randomized, making it harder to predict memory addresses.

---

## Objective

Your goal is to exploit the buffer overflow vulnerability to call the `win()` function and spawn a shell. To do this, you will need to:
1. Overwrite the return address of `get_favorite_food()` with the address of `win()`.
2. Ensure that the program does not crash before reaching the `win()` function.

---

## Hints

### 1. **Buffer Overflow**
   - The `food` buffer is only 64 bytes long, but the program reads up to 100 bytes using `fgets()`. This allows you to overwrite the return address of the function.
   - Use a debugger (e.g., `gdb`) to determine the exact offset required to overwrite the return address.

### 2. **Find the Address of `win()`**
   - Use a debugger or tools like `objdump` to find the address of the `win()` function in the binary.
   - Example command: `objdump -d ./binary_name | grep win`

### 3. **Craft the Payload**
   - Your payload should consist of:
     1. **Padding**: Fill the buffer with 64 bytes of junk data.
     2. **Return Address**: Overwrite the return address with the address of `win()`.
   - Example payload structure:
     ```
     [64 bytes of padding][Address of win()]
     ```

### 4. **ASLR Considerations**
   - ASLR randomizes the addresses of the stack, heap, and libraries. However, the address of the `win()` function is within the binary itself, so it is not affected by ASLR.
   - You can reliably use the address of `win()` in your exploit.

### 5. **Testing the Exploit**
   - Use a debugger to test your payload and ensure that the return address is correctly overwritten.
   - Example command to run the program with input:
     ```
     python3 -c 'print("A"*64 + "\xef\xbe\xad\xde")' | ./binary_name
     ```
     Replace `\xef\xbe\xad\xde` with the address of `win()` in little-endian format.

---

## Tools

- **gdb**: Use `gdb` to debug the program, inspect memory, and find the address of `win()`.
- **objdump**: Use `objdump` to disassemble the binary and find the address of `win()`.
- **Python**: Use Python to generate the exploit payload.
- **Pwntools**: A Python library for exploit development that can help automate the process.

---

## Example Exploit

### Step 1: Find the Address of `win()`
Use `objdump` to find the address of `win()`:
```bash
objdump -d ./binary_name | grep win
```
Example output:
```
080491b6 <win>:
```
The address of `win()` is `0x080491b6`.

### Step 2: Craft the Payload
The payload should consist of:
- 64 bytes of padding (e.g., `"A" * 64`).
- The address of `win()` in little-endian format (e.g., `\xb6\x91\x04\x08`).

### Step 3: Run the Exploit
Use Python to generate the payload and pipe it into the program:
```bash
python3 -c 'print("A"*64 + "\xb6\x91\x04\x08")' | ./binary_name
```

If successful, the program will execute the `win()` function and spawn a shell.

---

## Conclusion

This challenge demonstrates how to exploit a stack-based buffer overflow vulnerability to gain control of a program's execution flow. By carefully crafting your input, you can overwrite the return address and redirect execution to the `win()` function, bypassing protections like NX and ASLR. Good luck, and happy hacking!