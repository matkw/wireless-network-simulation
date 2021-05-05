# wireless-network-simulation
Object oriented computer simulation of discrete event

Treść zadania:
W sieci bezprzewodowej stacje nadawcze konkurują o dostęp do łącza. W losowych odstępach czasu CGPk k-ta stacja nadawcza generuje pakiety gotowe do
wysłania. Po uzyskaniu dostępu do łącza zgodnie z algorytmem A, k-ty terminal podejmuje próbę transmisji najstarszego pakietu ze swojego bufora. Czas
transmisji wiadomości z k-tej stacji nadawczej do k-tej stacji odbiorczej wynosi CTPk. Jeśli transmisja pakietu zakończyła się sukcesem, stacja odbiorcza przesyła
potwierdzenie ACK (ang. Acknowledgment) poprawnego odebrania wiadomości. Czas transmisji ACK wynosi CTIZ. Jeśli transmisja pakietu nie powiodła się, stacja
odbiorcza nie przesyła ACK. Odbiór pakietu uznajemy za niepoprawny, jeśli w kanale transmisyjnym wystąpiła kolizja lub błąd. Przez kolizję rozumiemy nałożenie
się jakiejkolwiek części jednego pakietu na inny pakiet (pochodzący z innego nadajnika). Dodatkowo każda transmisja pakietu może zakończyć się błędem TER.
Brak wiadomości ACK po czasie (CTPk+ CTIZ) od wysłania pakietu jest dla stacji nadawczej sygnałem o konieczności retransmisji pakietu. Każdy pakiet może być
retransmitowany maksymalnie LR razy. Dostęp do łącza w przypadku retransmisji opiera się na tych samych zasadach co transmisja pierwotna. Jeśli mimo LR-
krotnej próby retransmisji pakietu nie udało się poprawnie odebrać, wówczas stacja nadawcza odrzuca pakiet i – jeśli jej bufor nie jest pusty – przystępuje do
próby transmisji kolejnego pakietu. Opracuj symulator sieci bezprzewodowej zgodnie z metodą M.
Za pomocą symulacji wyznacz:
● Wartość parametru L, która zapewni średnią pakietową stopę błędów (uśrednioną po K odbiornikach) nie większą niż 0.1, a następnie:
o pakietową stopę błędów w każdym z odbiorników mierzoną jako iloraz liczby pakietów straconych do liczby przesłanych pakietów,
o średnią liczbę retransmisji pakietów, o przepływność systemu mierzoną liczbą poprawnie odebranych pakietów w jednostce czas u,
o średnie opóźnienie pakietu, tzn. czas jaki upływa między pojawieniem się pakietu w buforze, a jego poprawnym odebraniem,
o średni czas oczekiwania, tzn. czas między pojawieniem się pakietu w buforze, a jego opuszczeniem
o Sporządź wykres zależności średniej liczby retransmisji pakietów od parametru P Sporządź wykres zależności przepływności systemu oraz średniej i
maksymalnej pakietowej stopy błędów w zależności od wartości L.

Wykorzystany protokół:
Protokół CSMA (ang. Carrier Sense Multiple Access) z wymuszaniem transmizji z prawdopodobieństwem 1 (ang. 1-persistent) - po wygenerowaniu nowego pakietu, stacja nadawcza sprawdza zajętość kanału transmisyjnego. Jeśli kanał jest zajęty, to czeka aż się zwolni sprawdzając zajętość co 0.5 ms. Jeśli kanał jest wolny, to stacja natychmiast podejmuje próbę przesłania swojego pakietu.
W przypadku retransmisji, stacja nadawcza sprawdza stan kanału po losowym czasie CRP równym R*CTP_k,gdzie R jest losową liczbą z przedziału <0, (2^r - 1), a r jest numerem aktualnej retransmisji (przy każdej retransmisji czas ten jest losowany ponownnie). Jeśli kanał jest zajęty, to czeka aż się zwolni, sprawdzając zajętość co 0.5 ms. Jeśli kanał jest wolny, to stacja natychmiast podejmuje próbę retransmisji swojego pakietu.
