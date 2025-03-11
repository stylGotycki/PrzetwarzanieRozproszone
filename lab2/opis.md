Filip Domaszk
197624
[7B]
lab2
---
Główna rożnica pomiędzy dwoma podejściami dotyczy etapu na jakim odbywa się załączanie biblioteki. Dla bibliotek statycznych jest to faza linkowania, dla dynamicznych - faza wykonywania. Obydwa podejścia mają swoje konsekwencje.

### Konsekwencje korzystania z bibliotek statycznych:
- Plik wykonywalny jest większy, ponieważ jest połączeniem półskompilowanego programu i biblioteki, 
- Wykonuje się szybciej, ponieważ program nie szuka odwołań do funkcji w pamięci - ma je w swoim kodzie,
- Większe zużycie pamięci - każdy program ma swoją kopię biblioteki.
- Jest to mniej elastyczne rozwiązanie - trzeba "podlinkować" za każdym razem gdy zmienia się biblioteka,
- Programy korzystające z bibliotek statycznych są prostsze w dystrybucji - wszystko co potrzebne siedzi razem z programem.
- O wiele łatwiej zachować kompatybilność wsteczną.

### Konsekwencją korzystania z bibliotek dynamicznych:
- Plik wykonywalny jest mniejszy, ponieważ zawiera referencje do funkcji z biblioteki,
- Wykonuje się nieznacznie wolniej - program szuka odwołań do biblioteki w czasie wykonywania.
- Mniejsze zużycie pamięci - każdy program "podłącza" się do wspólnej biblioteki.
- Całkiem elastyczne, ponieważ aktualizacja biblioteki nie wymaga rekompilacji programu.
- Programy korzystające z bibliotek dynamicznych są trudniejsze w dystrybucji - trzeba zapewnić posiadanie biblioteki w systemie.

---
Ostatnia kwestia to wykorzystanie tych podejść w różnych systemach. Aplikacje na system Windows mają tendencję do korzystania z bibliotek statycznych, podczas gdy Linux na ogół wykorzystuje biblioteki dynamiczne. 
