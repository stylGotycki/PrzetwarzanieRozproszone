// Filip Domaszk 197624 [7B] lab4
#include <windows.h>
#include <stdio.h>

// Program uruchamia podproces notepad.exe; w nim próbuje stworzyć nowy plik "podproces.txt".
// Po uruchomieniu, oczekuje na zakończenie podprocesu notepad.exe.

int main() {
    STARTUPINFO si; // startowe informacje o tworzonym procesie 
    PROCESS_INFORMATION pi; // informacje o procesie w trakcie jego życia

    // si i pi bardzo prawdopodobnie dostają jakiś "śmietnik" z pamięci po inicjalizacji
    // przed użyciem należy je wyczyścić
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));

    // nazwa programu do uruchomienia
    LPCSTR command = "notepad.exe podproces.txt";

    // tworzenie procesu
    if (!CreateProcess(
            NULL,           // ścieżka do pliku 
            (LPSTR)command, // komenda do uruchomienia
            NULL,           // atrybuty procesu
            NULL,           // atrybuty wątku
            FALSE,          // nie dziedziczy deskryptorów
            0,              // flagi tworzenia
            NULL,           // zmienne środowiskowa
            NULL,           // katalog roboczy
            &si,            // informacje o uruchamianiu
            &pi))           // informacje o procesie
    {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    // proces main.c oczekuje na koniec podprocesu notepad.exe w nieskończoność
    WaitForSingleObject(pi.hProcess, INFINITE);

    // zwolnienie uchwytów w celu uniknięcia wycieku danych
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Proces ended.\n");
    return 0;
}