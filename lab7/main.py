import threading
import sys
import time

# Filip Domaszk 197624 [7b]


# funkcja sprawdzająca, czy dana liczba jest pierwsza
def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

# zmienne współdzielone
prime_count = 0
lock = threading.Lock()

# funkcja wykonywana przez każdy wątek na podprzedziale
def check_primes_in_range(start, end):
    global prime_count
    local_count = 0
    for n in range(start, end + 1):
        if is_prime(n):
            print(f"Found prime -> {n}")
            local_count += 1
    # dodanie do globalnego licznika z blokadą
    with lock:
        prime_count += local_count

if __name__ == "__main__":
    limit = 100_000 

    # można sobie zmienić w argumencie programu
    try:
        num_threads = int(sys.argv[1])
        if num_threads < 1:
            raise ValueError
    except (IndexError, ValueError):
        print("usage: python main.py <num_of_threads>")
        print("default = 4")
        num_threads = 4

    threads = []
    step = (limit - 1) // num_threads + 1  # ile liczb przypada na wątek

    start_time = time.time()

    for i in range(num_threads):
        start = 2 + i * step
        end = min(start + step - 1, limit)
        t = threading.Thread(target=check_primes_in_range, args=(start, end))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    elapsed = time.time() - start_time
    print(f"Found {prime_count} primes using {num_threads} threads.")
    print(f"Execution time: {elapsed:.2f} seconds")
