import socket
import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: python client.py <server_ip> <port>")
        sys.exit(1)

    server_ip = sys.argv[1]
    server_port = int(sys.argv[2])

    # Create socket
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_ip, server_port))

    print(f"Connected to server at {server_ip}:{server_port}")

    while True:
        # Get user input
        command = input("Enter a command: ")

        if command.lower() == 'exit':
            print("Exiting...")
            break
        if len(command) == 0:
            command = '\n'
        # Send the command to the server
        client_socket.send(command.encode())

        # Receive the response from the server
        response = client_socket.recv(1024).decode()
        print("Server response:", response)

    # Close the connection
    client_socket.close()

if __name__ == "__main__":
    main()
