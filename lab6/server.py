import socket
import threading
from math import sqrt
from vars import *

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)


def is_prime(x):
    if x <= 1:
        return False
    
    if x == 2:
        return True
    
    if x % 2 == 0:
        return False

    for i in range(3, int(sqrt(x)+1)):
        if x % i == 0:
            return False
    
    return True


def handle_client(conn, addr):
    print(f"<server> {addr} connected!")

    while True:
        msg = conn.recv(SIZE).decode(FORMAT)
        
        if not msg:
            print(f"<{addr[0]}:{addr[1]}> disconnected")
            break
        
        if msg:            
            if msg == DISCONNECT:
                print(f"<{addr[0]}:{addr[1]}> disconnected")
                break
                
            try:
                msg = int(msg)
            except ValueError or TypeError:
                conn.send(f"<server> says {msg} is not int!".encode(FORMAT))
            else:
                print(f"<{addr[0]}:{addr[1]}> sends: {msg}")
                conn.send(f"<server> says {msg} is prime!".encode(FORMAT) if is_prime(msg) 
                      else f"<server> says {msg} is not prime!".encode(FORMAT))
        
    conn.close()
    return
    

def start():
    server.listen()
    print(f"<server> is listening on {HOST}:{PORT}")
    try:
        while True:
            conn, addr = server.accept()
            thread = threading.Thread(target=handle_client, args=(conn, addr))
            thread.start()
            
            print(f"<server> active connections: {threading.active_count() - 1}")
    except KeyboardInterrupt:
        print("<server> shutting down...")
    finally:
        server.close()
        

print("<server> is starting...")
start()