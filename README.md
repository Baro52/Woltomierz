# Woltomierz
Program napisany na Atmega 128
Cele:
- zaprogramować porty C i D jako wyjściowe
- zaprogramować przetwornik analogowo cyfrowy, m.in. wybrać pin (gdzieś na nóżce portu A) do którego podłączone będzie mierzone napięcie
- a dalej główna pętla programu
- kopiować wynik przetwarzania do zmiennej lokalnej 
- w zmiennej lokalnej jest liczba w zakresie 0-255, trzeba ją przetworzyć na liczbę 0.00-5.00   
- (a może od razu na 3 cyfry ???)
- wyciągnąć ze zmiennej po przetworzeniu, ile to jest całych woltów ...
- ile to jest dziesiątych części volta ..
- ile setnych 
- 3 cyfry wysłać przez konwerter na port podłączony do wyświetlacza, stosując multipleksowanie jak w przykładzie

Do poprawienia:
- optymalizacja - operowanie na 4 bajtach na 8 bitowej Atmedze jest niepożądane
