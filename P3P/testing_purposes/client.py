import socket
import time
def send_message_to_server(host='127.0.0.1', port=65432):
    i = 0
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((host, port))
        while True:
            message = "hi for the " + str(i) + "time from client 1"
            client_socket.sendall(message.encode('utf-8'))
            response = client_socket.recv(1024)
            print(f"Server response: {response.decode('utf-8')}")
            time.sleep(0.5)
            i += 1

if __name__ == "__main__":
    send_message_to_server()