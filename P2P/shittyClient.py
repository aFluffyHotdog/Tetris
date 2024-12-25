import asyncio
import websockets
import time
import os
async def client():
    uri = "ws://localhost:8080"  # URL of the WebSocket server
    async with websockets.connect(uri) as websocket:
        # Send a message to the server
        while True:
            print("sending from server " + str(os.getpid()))
            websocket.send("sending from server " + str(os.getpid()))
            time.sleep(1)
            # Wait for a message from the server
            try:
                response =  websocket.recv()
                print(f"Received from server: {response}")
            except :
                pass

# Run the client
asyncio.run(client())
