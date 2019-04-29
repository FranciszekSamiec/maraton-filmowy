#include <stdio.h>
#include <stdbool.h>


char tab[5000]; // Tablica przechowująca interpretowany kod.
int stos[4000]; // Tablica stos jest stosem powrotu.
int dlugosc_wejscia = 0; 
int tab_adresow[10000]; // Indeksami tablicy adresów sa adresy a wartościamy tablicy są wartośći adresów maszyny.
char tab_etykiet[3000]; // Tablica etykiet zawiera wszystkie etykiety interpretowanego kodu oddzielone znakiem ':'.
int tab_indeksow_powrotu[1000]; //Jest to tablica zawierająca indeksy do których program przechodzi po skoku.
int stos_powrotu[4000]; 
int indeks_tab_etykiet = 0; // Aktualny indeks tablicy etykiet.
int indeks_tab_indeksow_powrotu = 0; // Aktualny indeks tablicy indeksów powrotu.
int top_stosu_powrotu = 0; // Wierzchołek stosu powrotu.

// Funkcja czytająca interpretowany kod i zapisująca do tablicy tab.

void czytaj()
{    
    int c;
    int i=0;
    while ((c = getchar()) != EOF && c != '&')
    {
        if (tab[i] != '+')
        {
            *(tab + i) = c;
            i++;
            dlugosc_wejscia++;
        }
    }
}

void inicjuj_tablice_adresow()
{
    for (int i = 0; i < 10000; i++)
    {
        *(tab_adresow + i) = -1 - (i - 5000);
    }
}

// Funkcja licząca potęgę liczby 10.

int potega(int wykladnik)  // podstawa będzie zawsze równa 10
{
    int wynik = 1;
    while (wykladnik != 0)
    {
        wynik = wynik * 10;
        wykladnik--;
    }
    return wynik;
}

// Funkcja wykonująca instrukcję pisania.

void pisanie(int pocz_adres1, int i, int koniec_adresu1, bool ujemny1)
{
    i = koniec_adresu1;
    int adres1 = 0;
    int wykladnik_potegi = 0;
    while (i != pocz_adres1)
    {
        i--;
        adres1 = adres1 + potega(wykladnik_potegi) * (tab[i] - '0');
        wykladnik_potegi++;
    } 
    if (ujemny1 == true)
        adres1 = (-1) * adres1;
    putchar(tab_adresow[tab_adresow[adres1 + 5000] + 5000]);
}    

// Funkcja wykonująca instrukcje czytania.

void czytanie(int pocz_adres, int i, bool ujemny1)
{
    int wejscie;
    int adres = 0;
    int wykladnik_potegi = 0;
    while (i != pocz_adres)
    {
        i--;
        adres = adres + potega(wykladnik_potegi) * (tab[i] - '0');
        wykladnik_potegi++;
    }
    if (ujemny1 == true)
        adres = (-1) * adres;
    wejscie = getchar();
    if (wejscie != EOF)
    {
        *(tab_adresow + tab_adresow[adres + 5000] + 5000) = wejscie;
    }
    else
    {
        *(tab_adresow + tab_adresow[adres + 5000] + 5000) = -1;
    }
}
    
// Funkcja wykonująca instrukcje odejmowania.
    
void odejmowanie(int pocz_adres1, int koniec_adresu1, int pocz_adres2, int i, bool ujemny1, bool ujemny2)
{
    int adres1 = 0;
    int adres2 = 0;
    int wykladnik_potegi = 0;
    while (i != pocz_adres2)
    {
        i--;
        adres2 = adres2 + potega(wykladnik_potegi) * (tab[i] - '0');
        wykladnik_potegi++;
    } 
    i = koniec_adresu1;
    wykladnik_potegi = 0;
    while (i != pocz_adres1)
    {
        i--;
        adres1 = adres1 + potega(wykladnik_potegi) * (tab[i] - '0');
        wykladnik_potegi++;
    } 
    if (ujemny1 == true)
        adres1 = (-1) * adres1;
    if (ujemny2 == true)
        adres2 = (-1) * adres2;
    *(tab_adresow + tab_adresow[adres1 + 5000] + 5000) = 
    tab_adresow[tab_adresow[adres1 + 5000] + 5000] - tab_adresow[tab_adresow[adres2 + 5000] + 5000];
}

// Funkcja wykonująca instrukcje skoku.

void skok(int pocz_adres1,int koniec_adresu1, int* i, int i_pomocnicze, bool ujemny1)
{
    
    (*i) = koniec_adresu1;
    int adres1 = 0;
    int wykladnik_potegi = 0;
    
    while (*i != pocz_adres1)
    {
        (*i)--;
        adres1 = adres1 + potega(wykladnik_potegi) * (tab[*i] - '0');
        wykladnik_potegi++;
    } 
    if (ujemny1 == true)
        adres1 = (-1) * adres1;
    if (tab_adresow[tab_adresow[adres1 + 5000] + 5000] > 0)
    {
        (*i) = i_pomocnicze;
        int j = 1;
        int licznik_etykiet = 0;
        bool znalazl = false;
        
        while (znalazl == false && j<3000)
        {
            if (tab_etykiet[j] == tab[*i])
            {
                while (tab_etykiet[j] == tab[*i])
                {
                    j++;
                    (*i)++;
                }
                if (((tab[*i] > 'Z' || tab[*i] < 'A') && (tab[*i] < 'a' || tab[*i] > 'z')
                    && tab[*i] != '_' && (tab[*i]>'9' || tab[*i] < '0')) && ((tab_etykiet[j]
                    > 'Z' || tab_etykiet[j] < 'A') && (tab_etykiet[j] < 'a' || tab_etykiet[j]
                    > 'z') && tab_etykiet[j] != '_' && (tab_etykiet[j]>'9' || tab_etykiet[j] < '0')))
                {
                    znalazl = true;
                    (*i) = tab_indeksow_powrotu[licznik_etykiet];
                }
                else
                {
                    (*i) = i_pomocnicze;
                }
            }
            while (tab_etykiet[j] != ':')
            {
                j++;
            }
            licznik_etykiet++;
            j++;
        }
    }
    else
    {
        while ((tab[i_pomocnicze] <= 'Z' && tab[i_pomocnicze] >= 'A') || (tab[i_pomocnicze] 
            >= 'a' && tab[i_pomocnicze] <= 'z') || tab[i_pomocnicze] == '_' || 
            (tab[i_pomocnicze]<='9' && tab[i_pomocnicze] >= '0'))
        {
            i_pomocnicze++;
        }
        (*i) = i_pomocnicze - 1;
    }
}

// Funkcja wykonująca instrukcje wywołania.
   
void wywolanie(int* i, int i_pomocnicze2)
{
    int j = 1;
    int licznik_etykiet = 0; 
    bool znalazl = false;
    
    while (znalazl == false && j<3000)
    {
        if (tab_etykiet[j] == tab[*i])
        {
            while (tab_etykiet[j] == tab[*i])
            {
                j++;
                (*i)++;
            }
            if (((tab[*i] > 'Z' || tab[*i] < 'A') && (tab[*i] < 'a' || tab[*i] > 'z') 
                && tab[*i] != '_' && (tab[*i]>'9' || tab[*i] < '0')) && ((tab_etykiet[j]
                > 'Z' || tab_etykiet[j] < 'A') && (tab_etykiet[j] < 'a' || tab_etykiet[j]
                > 'z') && tab_etykiet[j] != '_' && (tab_etykiet[j]>'9' || tab_etykiet[j] < '0')))
            {
                znalazl = true;
                *i = tab_indeksow_powrotu[licznik_etykiet];
            }
            else
            {
                *i = i_pomocnicze2;
            }
        }
        while (tab_etykiet[j] != ':')
        {
            j++;
        }
        licznik_etykiet++;
        j++;
    }
    while ((tab[i_pomocnicze2] <= 'Z' && tab[i_pomocnicze2] >= 'A') || (tab[i_pomocnicze2] >= 'a'
        && tab[i_pomocnicze2] <= 'z') || tab[i_pomocnicze2] == '_' || (tab[i_pomocnicze2]<='9' 
        && tab[i_pomocnicze2] >= '0'))
    {
        i_pomocnicze2++;
    }
    i_pomocnicze2--;
    *(stos_powrotu + top_stosu_powrotu) = i_pomocnicze2;
    top_stosu_powrotu++;
}

// Funkcja wykonująca instrukcje powrotu.

void powrot(int* i)
{
    if (top_stosu_powrotu > 0)
    {
        *i = stos_powrotu[top_stosu_powrotu - 1];
        top_stosu_powrotu--;
    }
    else
    {
        *i = dlugosc_wejscia;
    }
}

// Funkcja tworząca tablice etykiet.

void utworz_tab_etykiet()    
{
    for (int j = 0; j < dlugosc_wejscia; j++)
    {
        if (tab[j] == ':')
        {
            *(tab_etykiet + indeks_tab_etykiet) = tab[j];
            indeks_tab_etykiet++;
            j++;
            while ((tab[j] <= 'Z' && tab[j] >= 'A') || (tab[j] >= 'a' && tab[j] <= 'z') ||
                tab[j] == '_' || (tab[j]<='9' && tab[j] >= '0'))
            {
                *(tab_etykiet + indeks_tab_etykiet) = tab[j];
                indeks_tab_etykiet++;
                j++;
            }
            *(tab_indeksow_powrotu + indeks_tab_indeksow_powrotu) = j;
            indeks_tab_indeksow_powrotu++;
            j--;
        }
    }
}
        
void przesun(int* i)
{
    while (tab[*i] <= '9' && tab[*i] >= '0')
    {
        (*i)++;
    }
}

void przesun2(int*i)
{
    while (tab[*i] == '|' || tab[*i] == ' ' || tab[*i] == '\t' || tab[*i] == '\n')
    {
        (*i)++;
    }
}


int main()
{   
    inicjuj_tablice_adresow();
    czytaj();
    utworz_tab_etykiet();
    bool ujemny1 = false; // Zmienne ujemny1 oraz ujemny2 określają 
    bool ujemny2 = false; // czy przed odpowiednimi adresami są znaki '-'.
    
    for (int i=0; i < dlugosc_wejscia; i++)
    {
        if (tab[i] <= '9' && tab[i] >= '0')
        {
            int pocz_adres1 = i;
            if (i > 0 && tab[i - 1] == '-')
                ujemny1 = true;
            przesun(&i);
            int koniec_adresu1 = i;
            przesun2(&i);
            if (tab[i] == '^')
            {
                // Teraz wykona się instrukcja pisania.
                pisanie(pocz_adres1, i, koniec_adresu1, ujemny1);
            }
            else if ((tab[i] <= '9' && tab[i] >= '0') || tab[i] == '-')
            {
                // Teraz wykona się instrukcja odejmowania.
                if (tab[i] == '-')
                {
                    ujemny2 = true;
                    i++;
                }
                int pocz_adres2 = i;
                przesun(&i);
                odejmowanie(pocz_adres1,koniec_adresu1, pocz_adres2, i, ujemny1, ujemny2);
                i--;
            }
            else if ((tab[i] <= 'Z' && tab[i] >= 'A') || (tab[i] >= 'a' && tab[i] <= 'z') || tab[i] == '_')
            {
                // Teraz wykona się instrukcja skoku.
                int i_pomocnicze = i;
                skok(pocz_adres1, koniec_adresu1, &i, i_pomocnicze, ujemny1);
            }
            ujemny1 = false;
            ujemny2 = false;
        }
        else if ((tab[i] <= 'Z' && tab[i] >= 'A') || (tab[i] >= 'a' && tab[i] <= 'z') || tab[i] == '_')
        {
            // Teraz nastąpi instrukcja wywołania.
            int i_pomocnicze2 = i;
            wywolanie(&i, i_pomocnicze2);
        }
        else if (tab[i] == ':')
        {
            // Teraz nastąpi pominięcie etykiety.
            i++;
            while ((tab[i] <= 'Z' && tab[i] >= 'A') || (tab[i] >= 'a' && tab[i] <= 'z')
                || tab[i] == '_' || (tab[i]<='9' && tab[i] >= '0'))
            {
                i++;
            }
            i--;
        }
        else if (tab[i] == ';')
        {
            // Teraz wykona się instrukcja powrotu.
            powrot(&i);
        }
        else if (tab[i] == '^')
        {
            // Teraz wykona się instrukcja czytania
            i++;
            przesun2(&i);
            if (tab[i] == '-')
            {
                i++;
                ujemny1 = true;
            }
            int pocz_adres = i;
            przesun(&i);
            czytanie(pocz_adres, i, ujemny1);
            ujemny1 = false;
            i--;
        }
    }
    return 0;
}