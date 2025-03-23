# Problem głodujących filozofów
![alt text](https://www.prismmodelchecker.org/tutorial/images/dining-phil.png)
## Opis problemu
Problem głodujących filozofów pokazuje wzajemne blokowanie się wątków w oczekiwaniu na współdzielone zasoby. Prowadzi to do zakleszczenia (deadlocka). Problem filozofów został przedstawiony następująco. N liczba filozofów siedzi przy okrągłym stole i jedzą spaghetti. Jest N liczba widelców dokłądnie 1 widelec między każdą parą filozofów. Filozof by zjeść musi użyć do tego obu widelców przez co nie pozwala w momęcie jedzenia na spożycie dla sąsiednich filzofów. Filozofowie myślą i jedzą w nieskończoność. Naszym celem jest takie rozdielenie widelców między filozofów aby nie doszło do zakleszczenia oraz by żaden z filozofów nie czekał w niekończoność na możliwość zjedzenia.
## Jak uruchomić program
Wystarczy pobrać najnowszy plik .exe z zakładki releases i go uruchomić. Należy potem podawać w okienku konsoli wartości dla symulacji. Ilość filozofów, czas jedzenia i czas myślenia.  Program jest kompilowany w cmake i działa na windowsie. 
## Kompilacja programu
Wygeneruj pliki do budowy projektu.
```shell
cmake .. -DCMAKE_BUILD_TYPE=Release
```
Następnie skompiluj program
```shell
cmake --build . --config Release
```
Potem wystarczy uruchomić plik .exe
## Wątki
Każdy filozof to osobny wątek. Wypisywanie jest zabezpieczone współdzielonym mutexem. Pętla działana wątku filozofa jest wykonywana w funkcji run
```c++
void Philosopher::Run() {
    while (true) {
        think();
        pickForks();
        eat();
        releaseForks();
    }
}
```
Filozof wiecznie próbuje podnieść widelce i jeść. W momęcie gdy skończy odstawia widelce i zaczyna myśleć, pozwalając innym filozofom na jedzenie.
## Sekcje krytyczne
Sekcje krytyczne to dostęp do widelców. Widelce są mutexami dzięki czemu tylko jeden wątek na raz może zablokować widelce. By zapobiec zakleszczeniu każdy filozof bierze pierwsze widelec o mniejszym numerze a potem drugi widelec o większym numerze. Dzięki czemu nigdy nie dojdzie do sytuacji w której wszyscy filozofowie mają jeden widelec i czekają na drugi. Można to porównać do sytuacji gdy każdy filozof bierze pierwsze wideleć swoją reką dominującą ,ale tylko jeden z nich jest leworęczny. W takiej sytuacji jeden filozof zawszę będzie zmuszony do czekania zanim drugi zakończy jedzenie. By dopilnować by filozof nie czekał w nieskończoność dodałem także kolejke piorytetową bazująca na ostatnim cazsie posiłku.