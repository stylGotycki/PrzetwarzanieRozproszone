import threading
import queue
import time
import random

# Filip Domaszk 197624 [7b]

class BinarySemaphore:
    def __init__(self):
        # kanał (kolejka) o maksymalnym rozmiarze 1, przechowujący "token" semafora
        self.channel = queue.Queue(maxsize=1)
        self.channel.put(1)  # semafor jest początkowo dostępny (wartość = 1)

    def acquire(self):
        # pobranie tokenu z kanału - jeśli brak tokenu, wątek czeka (blokuje się)
        self.channel.get()

    def release(self):
        try:
            # zwrot tokenu do kanału - jeśli kanał jest pełny, błąd jest ignorowany
            self.channel.put_nowait(1)
        except queue.Full:
            pass  # zapobiega wielokrotnemu zwracaniu tokenów


# funkcja reprezentująca sekcję krytyczną chronioną semaforem
def critical_section(thread_id, semaphore):
    for i in range(3):
        time.sleep(random.uniform(0.2, 0.8))  # symulacja pracy przed sekcją krytyczną
        print(f"Thread {thread_id} waiting to enter critical section...")
        semaphore.acquire()
        print(f"Thread {thread_id} ENTERED critical section")
        time.sleep(random.uniform(0.5, 1.0))  # sekcja krytyczna
        print(f"Thread {thread_id} LEAVING critical section")
        semaphore.release()

if __name__ == "__main__":
    sem = BinarySemaphore()
    threads = []

    # 4 wątki próbujące uzyskać dostęp do sekcji krytycznej
    for i in range(4):
        t = threading.Thread(target=critical_section, args=(i, sem))
        threads.append(t)
        t.start()

    # zakończenie wszystkich wątków
    for t in threads:
        t.join()
