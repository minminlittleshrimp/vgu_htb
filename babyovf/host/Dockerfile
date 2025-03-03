FROM ubuntu:20.04

# Install required packages for 32-bit compilation
RUN dpkg --add-architecture i386 && apt-get update && apt-get install -y \
    build-essential \
    gcc-multilib \
    libc6-dev-i386 \
    socat && \
    rm -rf /var/lib/apt/lists/*

# Create a non-root user
RUN useradd -m ctfuser && \
    mkdir -p /home/ctfuser/app && \
    chown -R root:ctfuser /home/ctfuser && \
    chmod 750 /home/ctfuser

# Copy the challenge source code and compile the binary
WORKDIR /home/ctfuser/app
COPY . .

# Compile the challenge program without RELRO
RUN gcc baby_overflow.c -no-pie -fno-pie -fno-stack-protector -z execstack -Wl,-z,norelro -o baby_overflow && \
    chown root:ctfuser /home/ctfuser/app/baby_overflow && \
    chmod 750 /home/ctfuser/app/baby_overflow && \
    chmod 550 /home/ctfuser/app && \
    chmod +x entrypoint.sh

RUN rm /home/ctfuser/app/baby_overflow.c

# Switch to the non-root user
USER ctfuser

# Expose port for the challenge
EXPOSE 1338

# Run the challenge with socat to expose it over TCP
# ENTRYPOINT ["socat", "TCP-LISTEN:1338,fork", "EXEC:/home/ctfuser/app/baby_overflow"]
CMD ["./entrypoint.sh"]
