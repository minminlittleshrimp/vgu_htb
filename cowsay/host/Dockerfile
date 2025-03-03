FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    python3 \
    cowsay \
    socat && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -m ctfuser && \
    mkdir -p /home/ctfuser/app && \
    chown -R root:ctfuser /home/ctfuser && \
    chmod 750 /home/ctfuser

WORKDIR /app
COPY cowsay.py /home/ctfuser/app

RUN echo "vgucypher{th3_C0w_5@Y:Moo0oo}" > /flag.txt && \
    chown root:ctfuser /flag.txt && \
    chmod 440 /flag.txt

RUN ln -s /usr/games/cowsay /usr/local/bin/cowsay

USER ctfuser

EXPOSE 13400

ENTRYPOINT ["socat", "TCP-LISTEN:13400,fork", "EXEC:python3 /home/ctfuser/app/cowsay.py"]
