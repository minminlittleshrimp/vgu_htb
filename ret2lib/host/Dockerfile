FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-multilib \
    libc6-dev-i386 \
    python3-pip \
    python3-pwntools \
    vim \
    gdb \
    socat && \
    rm -rf /var/lib/apt/lists/*

# Create a non-root user
RUN useradd -m ctfuser && \
    mkdir -p /home/ctfuser/app && \
    chown -R root:ctfuser /home/ctfuser && \
    chmod 750 /home/ctfuser

# Create a flag file, set strict permissions
RUN echo "vgucypher{r3t21i6_0verf0w_t0_rc3}" > /flag.txt && \
    chown root:ctfuser /flag.txt && \
    chmod 440 /flag.txt

# Copy the challenge source code and compile the binary
WORKDIR /home/ctfuser/app
COPY pwn_r2l.py /home/ctfuser/app/
COPY vanished_shell.c /home/ctfuser/app/

# Compile the challenge program without RELRO
RUN gcc -m32 -z relro -fno-stack-protector -z noexecstack -no-pie -g -o vanished_shell vanished_shell.c && \
    chown root:ctfuser /home/ctfuser/app/vanished_shell && \
    chmod 750 /home/ctfuser/app/vanished_shell && \
    chmod 550 /home/ctfuser/app

# RUN rm /home/ctfuser/app/vanished_shell.c
# Switch to the non-root user
USER ctfuser

# Expose port for the challenge
EXPOSE 1335

# Run the challenge with socat to expose it over TCP
ENTRYPOINT ["socat", "TCP-LISTEN:1335,fork", "EXEC:/home/ctfuser/app/vanished_shell"]
