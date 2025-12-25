# normal client code
import socket
import time
from config import HOST, ALLOWED_PORTS, BUFFER_SIZE, CLIENT_MESSAGES
from random import choice

# Chooses randomly one allowed port
TARGET_PORT = choice(ALLOWED_PORTS)

def normal_client():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((HOST, TARGET_PORT))
        print(f"Connected to server on port {TARGET_PORT}")

        for msg in CLIENT_MESSAGES:
            sock.sendall(msg.encode("utf-8"))
            print(f"Sent: {msg.rstrip()}")

            data = sock.recv(BUFFER_SIZE)
            if data:
                response = data.decode("utf-8")
                print(f"Received: {response.rstrip()}")
            time.sleep(2)  # small delay between messages
    except Exception as e:
        print(f"Connection error: {e}")
    finally:
        sock.close()
        print("Client closed")

if __name__ == "__main__":
    normal_client()