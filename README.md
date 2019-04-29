# maraton-filmowy
Program umożliwiający grupom fanów kina wybieranie filmow do maratonu.
Każdy kinomaniak (użytkownik) może wprowadzać preferowane filmy, które chciałby obejrzeć w trakcie maratonu, może je także usuwać. Użytkownik identyfikowany jest za pomocą identyfikatora liczbowego. Identyfikatory użytkowników są unikalne. Film identyfikowany jest za pomocą identyfikatora liczbowego. Identyfikatory filmów są unikalne. Użytkownicy tworzą drzewo. Każdy już zapisany użytkownik może dopisywać nowych użytkowników, jako potomków swojego wierzchołka drzewa. Na początku istnieje użytkownik o identyfikatorze 0 (korzeń drzewa), niemający żadnych preferencji filmowych. Każdy użytkownik z wyjątkiem użytkownika o identyfikatorze 0 może siebie wypisać. Identyfikator filmu jest też jego arbitralnie ustaloną oceną.

Program wykonuje następujące operacje:

- addUser <parentUserId> <userId> – Użytkownik o identyfikatorze parentUserId dodaje użytkownika o identyfikatorze userId. Operacja wykonuje się w czasie stałym.
  
- delUser <userId> – Użytkownik o identyfikatorze userId wypisuje się. Dodane przez niego preferencje filmowe są zapominane. Użytkownicy uprzednio dodani przez użytkownika userId stają się potomkami rodzica użytkownika userId. Usunięcie wykonuje się w czasie stałym.

- addMovie <userId> <movieRating> – Użytkownik o identyfikatorze userId dodaje film o identyfikatorze movieRating do swoich preferencji filmowych. Operacja wykonuje się w czasie liniowym względem liczby preferencji użytkownika, który dodaje film.

- delMovie <userId> <movieRating> – Użytkownik o identyfikatorze userId usuwa film o identyfikatorze movieRating ze swoich preferencji filmowych. Operacja wykonuje się w czasie liniowym względem liczby preferencji użytkownika, który usuwa film.

- marathon <userId> <k> – Wyznacza co najwyżej k identyfikatorów filmów o najwyższych ocenach spośród:
  * własnych preferencji filmowych użytkownika o identyfikatorze userId;

  * preferencji filmowych wyodrębnionych w wyniku przeprowadzenia operacji marathon dla każdego z potomków użytkownika userId, przy czym w wynikowej grupie k filmów znajdą się tylko takie, które mają ocenę większą od maksymalnej oceny filmu spośród preferencji użytkownika  userId.
  
Program wypisuje na standardowe wyjście:

- Dla każdej operacji innej niż marathon wiersz ze słowem OK.

- Dla operacji marathon wiersz zawierający posortowane malejąco wyznaczone oceny, a w przypadku braku filmów spełniających warunki       maratonu wiersz zawierający jedynie słowo NONE.      

- Każdy wiersz wyjścia kończy się linuksowym znakiem końca linii.

Obsługa błędów:

- Program wypisuje informacje o błędach na standardowe wyjście diagnostyczne.

- Puste wiersze są ignorowane.

- Wiersze rozpoczynające się znakiem # są ignorowane.

- Dla każdego błędnego wiersza i dla każdej operacji, która nie może być wykonana np. z powodu błędnej wartości parametru, wypisywany jest wiersz ze słowem ERROR.
