#!/bin/bash

# Run the C program with socat to expose it over port 1338
socat -b 8192 TCP-LISTEN:1338,reuseaddr,fork EXEC:"./baby_overflow",pty,stderr