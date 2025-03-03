#!/bin/bash

echo "vgucypher{w3lc0m3_t0_th3_h1dd3n_sh3ll}" > /app/flag.txt

# Start the challenge
exec socat TCP-LISTEN:1337,fork EXEC:/app/hidden_shell