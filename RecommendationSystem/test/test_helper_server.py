import socket
import threading

# Function to handle client connections
def handle_client(client_socket):
    try:
        while True:
            message = client_socket.recv(1024).decode()

            if not message:
                break  # Client disconnected

            print(f"Received from client: {message}")
            response = "Message received"
            client_socket.send(response.encode())

            if message.lower() == "exit":
                print("Client requested exit.")
                break

    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close()
        print("Client disconnected.")

# Function to start the server
def start_server(host, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f"Server listening on {host}:{port}...")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"New connection from {client_address}")

        # Handle the client in a new thread
        client_thread = threading.Thread(target=handle_client, args=(client_socket,))
        client_thread.start()

if __name__ == "__main__":
    host = '127.0.0.1'
    port = 12345
    start_server(host, port)
