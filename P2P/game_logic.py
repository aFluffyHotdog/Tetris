# This module contains game logic functions

def update_game_state(key, num):
    """
    Handles the update of the game state. For example, moving blocks,
    checking for line clears, and updating the game grid.
    """
    # Perform game logic (move, rotate, etc.)    

    # Placeholder example
    game_state = {
        #"grid": [[0, 0, 0, 0], [1, 1, 0, 0]],  # A simple grid example
        "player_num": num,
        "player_move": f"MOVE {input_key(key)}"
    }

    return game_state

def input_key(key):
    if key == '\x1b[C':
        return "right"
    elif key == '\x1b[D':
        return "left"
        
    
def move_piece(direction):
    """
    Handle the movement of the Tetris piece (left, right, rotate).
    """
    if direction == "left":
        # Code to move piece left
        pass
    elif direction == "right":
        # Code to move piece right
        pass
