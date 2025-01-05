import socket
import threading

def handle_client(client_socket, other_client_socket, client_id):
    try:
        while True:
            # Receive data from this client
            data = client_socket.recv(1024)
            if not data:  # If no data, client disconnected
                print(f"Client {client_id} disconnected.")
                break
            received_message = data.decode('utf-8')
            print(f"Client {client_id} sent: {received_message}")
            
            # Forward the message to the other client
            other_client_socket.sendall(received_message.encode('utf-8'))
    except ConnectionResetError:
        print(f"Client {client_id} connection reset.")
    finally:
        client_socket.close()

def start_server(host='127.0.0.1', port=65432):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))
        server_socket.listen(2)  # Allow up to 2 connections
        print(f"Server listening on {host}:{port}")
        
        # Accept two client connections
        client1_socket, client1_address = server_socket.accept()
        print(f"Client 1 connected from {client1_address}")
        
        client2_socket, client2_address = server_socket.accept()
        print(f"Client 2 connected from {client2_address}")
        client1_socket.send("Client 2 connected".encode('utf-8'))

        #TODO: send message to client1 that client2 is ready to start running
        
        # Start threads to handle each client
        threading.Thread(target=handle_client, args=(client1_socket, client2_socket, 1), daemon=True).start()
        threading.Thread(target=handle_client, args=(client2_socket, client1_socket, 2), daemon=True).start()

        # Keep the server running
        while True:
            pass

if __name__ == "__main__":
    start_server()
