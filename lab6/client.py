import socket
import random
from vars import *

# Klient wysyła liczbę do serwera, otrzymuje komunikat czy podana liczba była pierwsza.
# Jeżeli nie wysłał liczby dostaje komunikat o błędzie.
# Jeżeli wpisze polecenie `exit` zakończy komunikację.

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)

def send(x):
    print(f"<client> sending {x}!")
    client.send(str(x).encode(FORMAT))
    print(client.recv(SIZE).decode(FORMAT))
    
def send_disconnect():
    print("<client> disconnects!")
    client.send(DISCONNECT.encode(FORMAT))


print("Type exit to stop the program!")
while True:
    x = input("<client> Enter a number: ")
    if x == 'exit':
        send_disconnect()
        break
    
    try:
        x = int(x)
    except ValueError:
        print("Wrong value provided!")
    else:    
        send(x)
        
client.close()