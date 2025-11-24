# Implementing TCP Server
import socket

def run_server():
    SERVER_IP = '127.0.0.1'
    SERVER_PORT = 5000 
    
    # Creating the socket object
    sock_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Binding and Listening
    sock_server.bind((SERVER_IP, SERVER_PORT))
    sock_server.listen(1) # Setting backlog to 1
    
    print(f"[Server] Listening on port {SERVER_PORT}...")
    
    while True:
        # Accepting incoming connection
        conn_obj, client_addr = sock_server.accept()
        print(f"[Server] Connection establishing with {client_addr}")
        
        # Reading data
        data_received = conn_obj.recv(1024).decode()
        if not data_received:
            break
            
        print(f"[Client says]: {data_received}")
        
        # Sending response
        reply = "Server confirms receipt. Over."
        conn_obj.send(reply.encode())
        
        # Cleaning up
        conn_obj.close()
        break

if __name__ == "__main__":
    run_server()
