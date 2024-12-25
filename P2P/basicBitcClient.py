import asyncio
import websockets

async def send_message():
    uri = "ws://127.0.0.1:8080"
    async with websockets.connect(uri) as websocket:
        message = "Hello, WebSocket server!"
        await websocket.send(message)
        print(f"Sent message: {message}")

# Run client
if __name__ == "__main__":
    asyncio.run(send_message())
