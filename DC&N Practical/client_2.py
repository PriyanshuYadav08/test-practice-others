import socket
import threading
import sys

HOST = '127.0.0.1'
PORT = 12345

def receive_message(client):
    while True:
        try:
            message = client.recv(1024)
            if not message:
                break
            print(message.decode())
        except:
            break
    
def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    threading.Thread(target = receive_message, args = (sock,), daemon = True).start()
    
    while True:
        try:
            message = input()
            if message.lower() == "/quit":
                sock.close()
                sys.exit()
            sock.sendall(message.encode())
        except:
            break
        
if __name__ == "__main__":
    main()