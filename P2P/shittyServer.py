import asyncio
import websockets

# List to keep track of connected clients
connected_clients = set()

async def handler(websocket, path):
    # Add the new client to the list of connected clients
    connected_clients.add(websocket)
    print(f"New client connected: {websocket.remote_address}")
    
    try:
        async for message in websocket:
            print(f"Message received: {message}")
            
            # Relay the message to all other connected clients
            for client in connected_clients:
                if client != websocket:  # Avoid sending the message back to the sender
                    await client.send("hi")
    except websockets.exceptions.ConnectionClosed as e:
        print(f"Client disconnected: {websocket.remote_address}")
    finally:
        # Remove the client from the list upon disconnection
        connected_clients.remove(websocket)

# Start the WebSocket server
async def main():
    server = await websockets.serve(handler, "localhost", 8080)
    print("WebSocket server is running on ws://localhost:8080")
    await server.wait_closed()

# Run the server
asyncio.run(main())
