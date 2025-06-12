import threading
import random
import time

# Filip Domaszk 197624 [7b]

# klasyczny model Producent–Konsument z użyciem wielowątkowości w Pythonie. Wątki producentów i konsumentów współdzielą zsynchronizowany magazyn, losowo dodając i pobierając towary różnych typów w ograniczonych ilościach.

# lista produktów
PRODUCT_TYPES = ["apple", "banana", "carrot"]

class Warehouse:
    def __init__(self, capacity):
        self.capacity = capacity  # max total items
        self.storage = {}         # {product_type: quantity}
        self.lock = threading.Lock()
        self.not_full = threading.Condition(self.lock)
        self.not_empty = threading.Condition(self.lock)

    def current_total(self):
        return sum(self.storage.values())

    def add_product(self, product_type, quantity):
        with self.not_full:
            while self.current_total() + quantity > self.capacity:
                self.not_full.wait()

            self.storage[product_type] = self.storage.get(product_type, 0) + quantity
            print(f"[Producer] Added {quantity} {product_type}(s). Total: {self.current_total()}")
            self.not_empty.notify_all()

    def consume_product(self, product_type, quantity):
        with self.not_empty:
            while self.storage.get(product_type, 0) == 0:
                self.not_empty.wait()

            available = self.storage.get(product_type, 0)
            taken = min(available, quantity)
            self.storage[product_type] -= taken
            if self.storage[product_type] == 0:
                del self.storage[product_type]

            print(f"[Consumer] Took {taken} {product_type}(s). Total left: {self.current_total()}")
            self.not_full.notify_all()
            return taken

class Producer(threading.Thread):
    def __init__(self, warehouse, id):
        super().__init__()
        self.warehouse = warehouse
        self.id = id

    def run(self):
        while True:
            product_type = random.choice(PRODUCT_TYPES)
            quantity = random.randint(1, 5)
            time.sleep(random.uniform(0.5, 2.0))  # simulate delay
            print(f"Producer-{self.id} wants to add {quantity} {product_type}(s)")
            self.warehouse.add_product(product_type, quantity)

class Consumer(threading.Thread):
    def __init__(self, warehouse, id):
        super().__init__()
        self.warehouse = warehouse
        self.id = id

    def run(self):
        while True:
            product_type = random.choice(PRODUCT_TYPES)
            quantity = random.randint(1, 5)
            time.sleep(random.uniform(0.5, 2.5))  # simulate delay
            print(f"Consumer-{self.id} wants to take {quantity} {product_type}(s)")
            taken = self.warehouse.consume_product(product_type, quantity)

if __name__ == "__main__":
    warehouse = Warehouse(capacity=20)

    # start producentów
    producers = [Producer(warehouse, i) for i in range(3)]
    for p in producers:
        p.start()

    # start konsumentów
    consumers = [Consumer(warehouse, i) for i in range(4)]
    for c in consumers:
        c.start()
