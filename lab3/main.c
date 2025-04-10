// Filip Domaszk 197624 [7B] lab3
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int pcounter = 0;

// Głównym celem tego "redundantego" kodu jest pokazanie jak tworzy się "potok" podprocesów.
// Procesy mają oddzielne przestrzenie adresowe, dlatego do komunikacji między nimi użyłem
// kanału pipe(). Program jest opisany dosyć skrupulatnie ze względu na to, że robię coś takiego 
// pierwszy raz :p
int factorial(int n) {
    // base case
    if (n <= 1) {
        pid_t pid = fork();
        if (pid == 0) {
            pcounter++;
            execlp("ps", "- u stylgotycki", "-l", "--forest", NULL);
            return 0;   // ten return zwraca kod wyjścia
        }
        else {
            waitpid(pid, NULL, 0);
            printf("n = %d, wynik = %d\n", n, 1);
            return 1;   // a ten return zwraca wynik funkcji 
            
            // opisuje te returny, bo za długo zajęło mi domyślenie się, że to tak działa...
        }
    }

    // File Descriptor i pipe()
    // fd[0] - czytanie z potoku
    // fd[1] - pisanie do potoku
    // pipe() - kanał komunikacji (linuxowy "|")
    int fd[2]; 
    pipe(fd);

    pid_t pid = fork();
    if (pid == 0) {  // proces potomny
        pcounter++;
        close(fd[0]); // proces potomny niczego nie czyta, zamyka fd[0]
        
        int result = factorial(n - 1);   // krok rekurencyjny
        write(fd[1], &result, sizeof(result));   // zapis wyniku w fd[1]

        close(fd[1]); // skończono zapis, zamyka fd[1]

        sleep(1);   // zupełnie niepotrzebne, ale pokazuje, że proces trwa jakiś czas
        _exit(0);   // zakończenie podprocesu, nie będzie kontynuować procesu macierzystego
    } 
    else {
        close(fd[1]);   // proces macierzysty niczego nie pisze, zamyka fd[1]

        int child_result;   // pojemnik na wartość otrzymaną z pipe()
        waitpid(pid, NULL, 0);  // oczekiwanie na zakończenie procesu potomnego
        
        read(fd[0], &child_result, sizeof(child_result)); // zapisanie rezultatu
        close(fd[0]); // skończono odczyt, zamyka fd[0]

        int result = n * child_result; // obliczanie silnii
        printf("n = %d, wynik = %d\n", n, result); // wypisywanie wartości pośredniej
        return result;  // kolejna wartość silnii
    }
}

int main(int argc, char** argv) {
    int n = 10;
    
    printf("factorial(%d) = %d\n", n, factorial(n));
    
    // bloki danych poszczególnych procesów nie są dzielone!, stąd zliczanie w globalnej zmiennej nie ma sensu!
    printf("process counter: %d\n", pcounter);
    
    return 0;
}