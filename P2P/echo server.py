import socket

def start_server(host='127.0.0.1', port=65432):
    # Create a socket object
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))  # Bind the socket to the address and port
        server_socket.listen()  # Start listening for connections
        print(f"Server listening on {host}:{port}")
        
        while True:
            # Accept a client connection
            client_socket, client_address = server_socket.accept()
            with client_socket:
                print(f"Connected by {client_address}")
                # Receive the data from the client
                data = client_socket.recv(1024)  # Buffer size of 1024 bytes
                if data:
                    # Decode and process the message
                    received_message = data.decode('utf-8')
                    print(f"Received message: {received_message}")
                    
                    # Create the response message
                    response_message = f"Hi, you sent: {received_message}"
                    
                    # Send the response back to the client
                    client_socket.sendall(response_message.encode('utf-8'))

if __name__ == "__main__":
    start_server()
