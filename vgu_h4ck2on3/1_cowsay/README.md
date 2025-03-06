## Cowsay CTF Challenge

### Overview
---
Welcome to the **Cowsay CTF Challenge**! This challenge involves exploiting a **command injection vulnerability** in a Python-based server that runs a **cowsay** service. The server is inside a Docker container, and it listens on port **13400**.

Your task is to exploit this vulnerability, execute shell commands on the server, and retrieve the **flag** from the server's filesystem.

### Flag Format
---
The flag will be in the following format: vgucypher{Ca7ch_m3_1F_U_Can}

### Setup Instructions
---
Follow the steps below to set up and run the CTF challenge:

#### 1. Run bash script for container generation:
```
./cowsay.sh
```
#### 2. Run netcat to connect to container for hacking:
```
nc localhost 13400
```
#### Example:
```
[*]─[LocalMachine]─[~/work/vgu-cypher-ctf-2024/pwned/cowsay]
└──> nc localhost 13400

Give me a message to say!
Hello VGUCypher
 _________________
< Hello VGUCypher >
 -----------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```
---
#### Now, it's time to HACK!
```
"When the cybercow coming to town it says Mooooo
"The cow listens closely, but what if it could do more than just talk?
Sometimes, input can carry hidden surprises that the shell might execute.
Think about how Bash handles unexpected substitutions. In Bash, certain
characters aren't just for decoration. They might allow you to substitute
one thing for another, like output for input. Look for ways to turn a
simple message into something... actionable."
```
Cow Master Moolenium once said:
```
"Much like how a simple droid can hide advanced programming, input can
conceal powerful commands. In Bash, what appears harmless might invoke
something unexpected. Think carefully! Substitution can lead to execution."
```