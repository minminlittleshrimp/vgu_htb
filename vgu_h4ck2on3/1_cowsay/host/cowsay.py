import sys
import subprocess

def cowsay_message(message):
    try:
        # Execute the message in the shell
        result = subprocess.run(
            ["bash", "-c", f"cowsay {message}"], capture_output=True, text=True
        )
        return result.stdout
    except Exception as e:
        return f"Error: {e}"

def main():
    sys.stdout.write("Give me a message to say!\n")
    sys.stdout.flush()  # Ensure prompt is sent immediately

    message = sys.stdin.readline().strip()
    if message:
        response = cowsay_message(message)
    else:
        response = "No message received."

    sys.stdout.write(response + "\n")
    sys.stdout.flush()

if __name__ == "__main__":
    main()
