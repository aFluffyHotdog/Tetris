import json

def serialize_grid(grid):
    """
    Converts a 2D grid (list of lists) into a JSON string.
    """
    return json.dumps(grid)

def deserialize_grid(grid_string):
    """
    Converts a JSON string back into a 2D grid (list of lists).
    """
    return json.loads(grid_string)
