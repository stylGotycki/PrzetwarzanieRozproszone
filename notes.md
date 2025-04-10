# procesy
- wykonywane w izolowanej (własnej) przestrzeni adresowej
- komunikacja za pomocą określonych strumieni


# wątki
- wykonywane w przestrzeni jednego procesu
- wspólna przestrzeń adresowa
    - wynika z tego zagrożenie "kłótni o dane"

# przetwarzanie wielowątkowe:
- wydzielenie różnych funkcji programu i przypisanie im oddzielnych wątków
- np.
    - wątek 1: obsługa GUI
    - wątek 2: komunikacja z serwerem/bazą danych
- często przypisuje się wątkowi pewną funkcję blokująca -> taką która blokuje program do czasu wykonania
- wątki mogą być uruchamiane w miarę potrzeb
- na ogół wątków nie powinno być więcej niż 16

- cykl życia wątku:
- #todo
