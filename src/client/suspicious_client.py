# suspicious client code
import socket
import time
from config import HOST, BUFFER_SIZE, SUS_CLIENT_MESSAGES

# Forbidden ports that will trigger IDS rules
SUSPICIOUS_PORTS = [8080, 12345, 2222, 9999]

def suspicious_client():
    for port in SUSPICIOUS_PORTS:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(2)  # short timeout
        print(f"Attempting connection to forbidden port {port}...")
        try:
            sock.connect((HOST, port))
            # If connection succeeds (unexpected), send a message
            for msg in SUS_CLIENT_MESSAGES:
                sock.sendall(msg.encode("utf-8"))
                print(f"Sent to {port}: {msg.rstrip()}")
                time.sleep(0.5)
        except socket.timeout:
            print(f"Timeout on port {port} (expected - connection refused)")
        except ConnectionRefusedError:
            print(f"Connection refused on port {port} (expected - suspicious traffic generated)")
        except Exception as e:
            print(f"Error on port {port}: {e}")
        finally:
            sock.close()
        time.sleep(3) #short delay

if __name__ == "__main__":
    print("Starting suspicious client - generating traffic on forbidden ports")
    suspicious_client()