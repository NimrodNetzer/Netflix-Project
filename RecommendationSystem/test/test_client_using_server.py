import subprocess
import time
import pytest


# Test for client-server communication
def test_client_using_server():
    # Start the server in a separate process
    server_process = subprocess.Popen(['python', 'test_helper_server.py'])
    time.sleep(1)  # Give the server some time to start

    try:
        # Start the client process
        client_process = subprocess.Popen(['python', 'client.py', '127.0.0.1', '12345'])

        # Wait for the client process to complete
        client_process.communicate()

        # Optionally assert server or client logs if needed
        # For example, check if the server received and responded to the client

    finally:
        # Terminate the server after the test
        server_process.terminate()
        server_process.wait()  # Wait for the server process to terminate
