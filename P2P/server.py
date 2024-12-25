import socket
import threading
import sys
import select
from protocols import handle_received_message, send_protocol_message
from game_logic import update_game_state

# Server setup
SERVER_IP = '127.0.0.1'
SEND_PORT = 8081
RECV_PORT = 8080

# 1) SET UP SOCKETS, LISTEN, ACCEPT
# Socket to send messages
send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# BIND
send_socket.bind((SERVER_IP, SEND_PORT))
# LISTEN
send_socket.listen(1)
print(f"Waiting for Player 2 to connect on {SERVER_IP}:{SEND_PORT} (for sending)...")

# Socket to receive messages
recv_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
recv_socket.bind((SERVER_IP, RECV_PORT))
recv_socket.listen(1)
print(f"Waiting for Player 2 to connect on {SERVER_IP}:{RECV_PORT} (for receiving)...")

# Accept connections from the client
send_conn, send_address = send_socket.accept()
recv_conn, recv_address = recv_socket.accept()
print(f"Player 2 connected from {send_address} and {recv_address}!")

# Non-blocking input to handle user input and receiving at the same time
def non_blocking_input(prompt):
    print(prompt, end='', flush=True)
    ready, _, _ = select.select([sys.stdin], [], [], 0.1)  # 0.1 sec timeout
    if ready:
        return sys.stdin.readline().strip()
    return None

# Send func
def send_messages():
    while True:
        # Update game state and send a message
        key = non_blocking_input("Enter: ")  # Prompting for input non-blockingly
        if key:
            game_state = update_game_state(key, "1")
            send_protocol_message(send_conn, game_state)

# Receive func
def receive_messages():
    while True:
        data = recv_conn.recv(1024).decode()
        if data:
            handle_received_message(data)
            print(data, flush=True)  # Reprint the "Enter: " prompt


receive_messages()