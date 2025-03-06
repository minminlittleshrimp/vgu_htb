# Baby Level of HEAP Exploitation

## Introduction
Welcome to the baby level of heap exploitation! This challenge introduces you to fundamental heap vulnerabilities, particularly focusing on memory corruption through unsafe input handling.

## Challenge Overview
In this challenge, you are given a program that dynamically allocates memory for user input but lacks proper bounds checking. The goal is to exploit this behavior to gain unintended control over program execution.

## Key Concepts
- **Heap Chunk:** A block of memory allocated on the heap via `malloc()`. It consists of metadata and user data.
- **GOT (Global Offset Table):** A table used by dynamically linked binaries to resolve function addresses at runtime. Overwriting GOT entries can redirect execution flow and execute arbitrary functions.
- **Heap Overflow:** Writing more data than allocated in a heap chunk, potentially corrupting adjacent memory structures.
- **Function Pointer Overwrite:** If a structure contains a function pointer, overflowing into it can allow arbitrary code execution.

## Hint for Exploitation
- The program uses `gets()`, which **does not** check input length, leading to **buffer overflow**.
- **Heap chunk corruption** can allow modification of function pointers.
- **GOT Overwrite:** If you can overwrite a function pointer (e.g., `printf@GOT`), you may be able to redirect execution to `hidden()`.
- Overwriting `u2->name` or its pointer structure could allow redirection to `hidden()`.

## Conclusion
This challenge provides an entry point into heap-based vulnerabilities. Understanding heap memory structures and unsafe input functions is essential for both offensive and defensive security research.

Happy hacking!
