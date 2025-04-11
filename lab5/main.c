// Filip Domaszk 197624 [7B] lab5
#include <windows.h>
#include <stdio.h>
#define NUM_PROCESSES 5
#define START_VALUE 123
#define TRUE 1
#define END_VALUE -10000

// Komunikacja między procesami w systemie Windows może odbywać się poprzez:
// - Clipboard -> działa dokładnie tak samo jak operacje Kopiuj, Wklej itd.
// - Potoki -> proces ma swoje wejście i wyjście. Przyjmuje dane, modyfikuje je i wysyła dalej.
// - Shared Memory -> grupa procesów ma dostęp do tego samego fragmentu pamięci.

// Prosty program, który wykorzystuje pipe'y do przekazywania wartości.
// Program to gra w ziemniaka między procesami. Każdy odejmuje swoją wartość id od otrzymanej wartości i przekazuje ją
// dalej. Proces, który otrzyma wartość x <= 0 przegrywa. Wysyła wtedy wartość końcową x = -10000, która jest sygnałem do zakończenia
// działania dla reszty "wygranych" procesów.
// Program ma bardzo dużo komentarzy - jest to swego rodzaju notatka.

int main(int argc, char* argv[]) { 
#pragma region CHILD_PROCESS
    if (argc == 5 && strcmp(argv[1], "child") == 0) {
        // child <id> <read_handle> <write_handle>
        int id = atoi(argv[2]); // id podprocesu
        HANDLE readPipe = (HANDLE)atoi(argv[3]); // strumień wejściowy
        HANDLE writePipe = (HANDLE)atoi(argv[4]); // strumień wyjściowy

        int x; // wartość "krążąca"
        DWORD bytes; // realna liczba bajtów(?)
        while (TRUE) {
            if (!ReadFile(readPipe, &x, sizeof(int), &bytes, NULL) || bytes == 0)
                break;

            if (x == END_VALUE) {  // ogólny warunek końcowy
                printf("proces %d WYGRAŁ\n", id);
                WriteFile(writePipe, &x, sizeof(int), &bytes, NULL);
                break;
            }

            if (x <= 0) {   // warunek przegranej 
                printf("proces %d PRZEGRAŁ\n", id);
                x = END_VALUE; // wartość końcowa dla reszty procesów
                WriteFile(writePipe, &x, sizeof(int), &bytes, NULL);
                break;
            }
            
            // ogólny warunek
            Sleep(50);
            printf("proces %d otrzymał %d\n", id, x);
            x -= id;
            WriteFile(writePipe, &x, sizeof(int), &bytes, NULL);
        }
        
        // koniec komunikacji -> zamknięcie strumieni
        CloseHandle(readPipe);
        CloseHandle(writePipe);
        return 0;
    }
#pragma endregion CHILD_PROCESS

#pragma region MAIN_PROCESS
    HANDLE pipes[NUM_PROCESSES][2]; // [i][0] - read, [i][1] - write
    PROCESS_INFORMATION pi[NUM_PROCESSES];
    STARTUPINFO si[NUM_PROCESSES];
    
    // utworzenie pierścienia strumieni
    for (int i = 0; i < NUM_PROCESSES; i++) {
        SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
        CreatePipe(&pipes[i][0], &pipes[i][1], &sa, 0);
    }

    // tworzenie procesów potomnych 
    for (int i = 0; i < NUM_PROCESSES; i++) {
        // zerowanie si i pi -> możliwe, że coś było pod tym adresem
        memset(&pi[i], 0, sizeof(pi[i]));
        memset(&si[i], 0, sizeof(si[i]));
        si[i].cb = sizeof(si[i]);           
        
        // argumenty do wywołania podprocesu
        char cmd[256];
        int read_fd = (int)pipes[i][0];
        int write_fd = (int)pipes[(i + 1) % NUM_PROCESSES][1];

        sprintf(cmd, "\"%s\" child %d %d %d", argv[0], i, read_fd, write_fd);
        printf("%s\n", cmd);

        CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si[i], &pi[i]);
    }

    // start gry
    int value = START_VALUE;
    DWORD bytes;
    WriteFile(pipes[0][1], &value, sizeof(int), &bytes, NULL);

    // oczekiwanie na koniec gry
    for (int i = 0; i < NUM_PROCESSES; i++) {
        WaitForSingleObject(pi[i].hProcess, INFINITE);
        // zwolnienie uchwytów w celu uniknięcia wycieku danych
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    // zwolnienie strumieni w celu uniknięcia wycieku danych
    for (int i = 0; i < NUM_PROCESSES; i++) {
        CloseHandle(pipes[i][0]);
        CloseHandle(pipes[i][1]);
    }

    printf("proces główny kończy działanie!\n");
    return 0;
#pragma endregion MAIN_PROCESS
}