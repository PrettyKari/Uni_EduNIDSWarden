import socket
import threading
from datetime import datetime
from config import HOST, ALLOWED_PORTS, BUFFER_SIZE, SERVER_TEST_MESSAGES
import os


os.makedirs("logs", exist_ok = (True))
log_file = None
cnsl_logging = True
def logger(message, cnsl = False):
	timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
	line = f"[{timestamp}] {message}"
	if cnsl:
		print(line)
	if log_file is not None:
		log_file.write(line + "\n")
		log_file.flush()


def handle_client(conn_socket, cli_address):
	logger(f"Accepted connection from {cli_address}", cnsl_logging)
	try:
		while True:
			data = conn_socket.recv(BUFFER_SIZE)
			if not data:
				break
			message = data.decode("utf-8")
			logger(f"Received from {cli_address}: {message.rstrip()}", cnsl_logging)
			
			response = SERVER_TEST_MESSAGES[4]
			conn_socket.sendall(response.encode("utf-8"))
			logger(f"Sent to {cli_address}: {response.rstrip()}")
	except Exception as e:
		logger(f"Error with client {cli_address}: {e}", cnsl_logging)
	finally:
		conn_socket.close()
		logger(f"Connection with {cli_address} closed", cnsl_logging)


def listen_on_port(port):
	server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	try:
		server_sock.bind((HOST, port))
		server_sock.listen(5)
		logger(f"Server listening on port {port}", cnsl_logging)
	except Exception as e:
		logger(f"Failed to bind/listen on port {port}: {e}", cnsl_logging)
		return
	while True:
		try:
			conn, cli_address = server_sock.accept()
			threading.Thread(target = handle_client, args = (conn, cli_address),daemon = True).start()
		except Exception as e:
			logger(f"Error accepting connection on port {port}: {e}", cnsl_logging)


if __name__ == "__main__":
	global log_file
	log_file = open("logs/server.log", "a", encoding="utf-8")
	logger(f"Starting server on {HOST} ports {sorted(ALLOWED_PORTS)}", cnsl_logging)
	
	threads = []
	for port in ALLOWED_PORTS:
		t = threading.Thread(target = listen_on_port, args = (port,), daemon = True)
		t.start()
		threads.append(t)
	try:
		threading.Event().wait()
	except KeyboardInterrupt:
		logger(f"Server shutting down by user request", True)
	finally:
		if log_file is not None:
			log_file.close()