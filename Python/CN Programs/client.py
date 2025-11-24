# Implementing TCP Client
import socket

def run_client():
    TARGET_IP = '127.0.0.1'
    TARGET_PORT = 5000
    
    # Creating socket
    sock_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Connecting to server
    try:
        sock_client.connect((TARGET_IP, TARGET_PORT))
        print(f"[Client] Connecting to {TARGET_IP}:{TARGET_PORT}")
        
        # Sending a message
        my_msg = "Requesting data packet #42."
        sock_client.send(my_msg.encode())
        
        # Waiting for response
        server_reply = sock_client.recv(1024).decode()
        print(f"[Server Reply]: {server_reply}")
        
    except ConnectionRefusedError:
        print("[Error] Could not connect. Is the server running?")
    finally:
        sock_client.close()

if __name__ == "__main__":
    run_client()
