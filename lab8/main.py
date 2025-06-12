import os

# Filip Domaszk 197624 [7b]

# funkcja pomocnicza do czytania z deskryptora (do końca)
def read_all(fd):
    data = b''
    while True:
        chunk = os.read(fd, 1024)
        if not chunk:
            break
        data += chunk
    return data

if __name__ == "__main__":
    # p1 (dla proces 1 -> proces 2), p2 (proces 2 -> proces 3)
    p1_read, p1_write = os.pipe()
    p2_read, p2_write = os.pipe()

    pid1 = os.fork()

    if pid1 == 0:
        # proces 2: dziecko 1
        # zamienia małe litery na duże
        os.close(p1_write)  # zamyka nieużywany koniec zapisu potoku 1
        os.close(p2_read)   # zamyka nieużywany koniec odczytu potoku 2

        data = read_all(p1_read).decode()
        os.close(p1_read)

        upper_data = data.upper().encode()
        os.write(p2_write, upper_data)
        os.close(p2_write)

        os._exit(0)

    else:
        pid2 = os.fork()
        if pid2 == 0:
            # proces 3: dziecko 2
            # wyświetla dane
            os.close(p2_write)  # zamyka nieużywany koniec zapisu potoku 2
            os.close(p1_write)
            os.close(p1_read)

            result = read_all(p2_read).decode()
            os.close(p2_read)

            print("Capslocked text:", result)
            os._exit(0)

        else:
            # proces 1: rodzic
            # wczytuje dane i wysyła do procesu 2
            os.close(p1_read)   # zamyka nieużywany koniec odczytu potoku 1
            os.close(p2_read)
            os.close(p2_write)

            user_input = input("Enter text: ")
            os.write(p1_write, user_input.encode())
            os.close(p1_write)

            # waits for chidren processes
            os.wait()
            os.wait()
