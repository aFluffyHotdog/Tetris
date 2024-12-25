import socket
import threading
import sys
import select
from protocols import handle_received_message, send_protocol_message
from game_logic import update_game_state
from Cython.Build import cythonize

# Client setup
SERVER_IP = '127.0.0.1'
SEND_PORT = 8080
RECV_PORT = 8081

# Socket to send
send_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
send_socket.connect((SERVER_IP, SEND_PORT))
print(f"Connected to Player 1 at {SERVER_IP}:{SEND_PORT} (for sending)...")

# Socket to receive 
recv_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
recv_socket.connect((SERVER_IP, RECV_PORT))
print(f"Connected to Player 1 at {SERVER_IP}:{RECV_PORT} (for receiving)...")

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
            game_state = update_game_state(key, "2")
            send_protocol_message(send_socket, "hi")

# Receive func
def receive_messages():
    while True:
        data = recv_socket.recv(1024).decode()
        print(type(data))
        if data:
            print(data)
            handle_received_message(data)
            # print("Enter: ", end='', flush=True)  # Reprint the "Enter: " prompt

send_messages()
