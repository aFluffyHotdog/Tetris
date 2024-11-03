import json

def send_protocol_message(socket, game_state):
    """
    Encodes and sends the protocol message over the socket.
    game_state: The current state of the game to be sent (dict).
    """
    serialized_data = json.dumps(game_state)
    socket.send(serialized_data.encode())
    print(f"\n---- SENT ----")
    print(f"Sent: {serialized_data}\n")



def handle_received_message(data):
    """
    Decodes and handles the received protocol message.
    data: The message received from the socket (string).
    """
    print(f"\n---- RECEIVED ----")

    game_state = json.loads(data)
    print(f"Received: {game_state}")
    
    # Process the game state, e.g., update player position, sync grid, etc.
    if "player_move" in game_state:
        move = game_state["player_move"]
        player_num = game_state["player_num"]
        print(f"Player {player_num} move received: {move}")
        # Call game_logic functions based on the move
    print("\n")
