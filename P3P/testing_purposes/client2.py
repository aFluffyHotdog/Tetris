import socket
import threading

def listen_to_server(client_socket):
    """Continuously listen for and print messages from the server."""
    while True:
        response = client_socket.recv(1024)  # Buffer size of 1024 bytes
        if response:
            print(f"Server response: {response.decode('utf-8')}")
        else:
            break  # Server has likely disconnected
    print("Disconnected from server.")

def send_message_to_server(host='127.0.0.1', port=65432):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((host, port))
        print("Connected to server.")

        # Start a thread to listen to server messages
        threading.Thread(target=listen_to_server, args=(client_socket,), daemon=True).start()

        while True:
            user_input = input("Press 'x' to send a message, or wait to receive messages: ").strip().lower()
            if user_input == 'x':
                message = input("Enter your message: ")
                client_socket.sendall(message.encode('utf-8'))

if __name__ == "__main__":
    send_message_to_server()
