FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    socat && \
    rm -rf /var/lib/apt/lists/*

# Create a non-root user
RUN useradd -m ctfuser && \
    mkdir -p /home/ctfuser/app && \
    chown -R root:ctfuser /home/ctfuser && \
    chmod 750 /home/ctfuser

# Create a flag file, set strict permissions
RUN echo "vgucypher{h34p_0verf0w_t0_rc3}" > /flag.txt && \
    chown root:ctfuser /flag.txt && \
    chmod 440 /flag.txt

# Copy the challenge source code and compile the binary
WORKDIR /home/ctfuser/app
COPY hidden_shell_2.c /home/ctfuser/app/

# Compile the challenge program without RELRO
RUN gcc -Wl,-z,norelro -no-pie -O0 hidden_shell_2.c -o hidden_shell_2 && \
    chown root:ctfuser /home/ctfuser/app/hidden_shell_2 && \
    chmod 750 /home/ctfuser/app/hidden_shell_2 && \
    chmod 550 /home/ctfuser/app

RUN rm /home/ctfuser/app/hidden_shell_2.c

# Switch to the non-root user
USER ctfuser

# Expose port for the challenge
EXPOSE 1337

# Run the challenge with socat to expose it over TCP
ENTRYPOINT ["socat", "TCP-LISTEN:1337,fork", "EXEC:/home/ctfuser/app/hidden_shell_2"]
