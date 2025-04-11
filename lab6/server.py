# Filip Domaszk 197624 [7B] lab6
import socket
import threading
from math import sqrt
from vars import *

# Serwer nasłuchuje na porcie zdefiniowanym porcie. Reaguje na następujące wiadomości:
# - liczba -> zwraca wiadomość o tym czy liczba była pierwsza.
# - DISCONNECT -> nie zwraca niczego; kończy połączenie z klientem.
# - KILL -> nie zwraca niczego; kończy działanie serwera.

# Zdecydowałem się na KILL ze względu na to, że nie do końca wiedziałem jak inaczej zakończyć 
# połączenie, kiedy serwer jest w trakcie oczekiwania na klienta. Tzn. Serwer "zapętla" się w tym
# oczekiwaniu i inne akcje (ctrl+C) nie są możliwe. Prawdopodobnie to kwestia implementacji 
# oczekiwania jako osobny wątek.

# A propos wątków - serwer wydziela wątek dla każdego klienta. Dzięki temu możliwe jest nadsyłanie
# wiadomości przez n klientów jednocześnie.


# utworzenie gniazdka o adresie IPv4 działającego na protokole TCP
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)


# O(sqrt(n))
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


# obsługa klienta
def handle_client(conn, addr):
    print(f"<server> {addr} connected!")

    while True:
        msg = conn.recv(SIZE).decode(FORMAT) # odebranie wiadomości, dekodowanie 
        
        # klient wysyła pustą wiadomość, jeżeli nagle się wyłączy
        if not msg:
            print(f"<{addr[0]}:{addr[1]}> disconnected")
            break
        
        if msg:
            if msg == DISCONNECT:
                print(f"<{addr[0]}:{addr[1]}> disconnected")
                break
            
            if msg == KILL:
                print(f"<{addr[0]}:{addr[1]}> disconnected")
                server.close()
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