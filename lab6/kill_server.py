# Filip Domaszk 197624 [7B] lab6
import socket
from vars import *

# Wysłanie sygnału zamknięcia do serwera.

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)
print("<kill_server> sent end message!")
client.send(KILL.encode(FORMAT))
