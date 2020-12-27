#include "plik1.h"

int pobierz_liczbe(int poczatek, int koniec)
{
    cout << endl;
    int liczba = 1;
    for (;;)
    {

        char znak;
        cout << "Podaj cyfre od " << poczatek << " do " << koniec << endl << ">>";
        znak = _getch();
        if (znak >= poczatek + 48 and znak <= koniec + 48)
        {
            liczba = znak - 48;
            break;
        }
        else
        {
            cout << "Wprowadz poprawna liczbe!" << endl;
        }

    }
    cout << "Wybrales " << liczba << " liczbe!";
    return liczba;
}

void wiadomosc(string wiadomosc, bool czy_przerwa)
{
    if (czy_przerwa)
    {
        cout << "|                                        |" << endl;
    }
    cout << "|";
    bool przod = true;
    for (int i = wiadomosc.length(); i < 40; i++)
    {
        if (przod)
        {
            wiadomosc = " " + wiadomosc;
        }
        else
        {
            wiadomosc = wiadomosc + " ";
        }
        przod = !przod;
    }
    cout << wiadomosc.c_str();
    cout << "|" << endl;
}
string wybor_kategori(string plik, bool czy_losowo)
{
    int kosmos, licznik = 0, n = 0, ile = 0, wybor = 0;
    char w;
    string linia, kategoria, wybrana, haslo;
    ifstream kat(plik);
    if (!kat) { cout << endl << "Blad otwarcia pliku!" << endl;  exit(0); }
    while (!kat.eof())
    {
        getline(kat, linia);
        if (linia.find("-") != string::npos)
        {
            n++;
            kategoria = linia;
            if (!czy_losowo) cout << n << ". kategoria: " << kategoria.erase(0, 1) << endl;
        }
        licznik += 1;
    }
    if (licznik == 1) { cout << "Pusty plik!" << endl; exit(0); }
    if (czy_losowo)
    {
        srand(time(NULL));
        kosmos = rand();
        wybor = (rand() % n) + 1;
    }
    else
    {
        wybor = pobierz_liczbe(1, n);
    }

    kat.close();
    ifstream ada(plik);
    while (!ada.eof())
    {
        getline(ada, linia);
        if (linia.find("-") != string::npos)
        {
            ile++;
            if (ile == wybor)
            {
                wybrana = linia.erase(0, 1);
                ada.close();
                return wybrana;
            }
        }
    }
    return "Blad!";
}

int ile_prob_do_konca(string slowo, string strzal)
{
    int bledne_proby = 0;
    for (int i = 0; i < strzal.length(); i++)
    {
        if (slowo.find(strzal[i]) == string::npos)
            bledne_proby++;
    }
    return bledne_proby;
}

void wisielec(int bledne_proby)
{
    if (bledne_proby >= 1)
        wiadomosc("|");
    else
        wiadomosc("");

    if (bledne_proby >= 2)
        wiadomosc("|");
    else
        wiadomosc("");

    if (bledne_proby >= 3)
        wiadomosc("|");
    else
        wiadomosc("");

    if (bledne_proby >= 4)
        wiadomosc("O");
    else
        wiadomosc("");

    if (bledne_proby >= 5)
        wiadomosc("/|\\");
    else
        wiadomosc("");

    if (bledne_proby == 6)
        wiadomosc("/ \\");
    else
        wiadomosc("");
}

bool zgadywanie(string slowo, string strzal)
{
    bool wygrana = true;
    string z;
    for (int i = 0; i < slowo.length(); i++)
    {
        if (strzal.find(slowo[i]) == string::npos)
        {
            wygrana = false;
            z += "_ ";
        }
        else
        {
            z += slowo[i];
            z += " ";
        }
    }
    wiadomosc(z, true);
    return wygrana;
}
void rysuj_litery(string dane_litery, char poczatek, char koniec)
{
    string z;
    for (char i = poczatek; i <= koniec; i++)
    {
        if (dane_litery.find(i) == string::npos)
        {
            z += i;
            z += " ";
        }
        else
            z += "_ ";
    }
    wiadomosc(z);
}
void dostepne_litery(string wszystkie_strzaly)
{
    wiadomosc("Dostepne litery:", true);
    rysuj_litery(wszystkie_strzaly, 'a', 'p');
    rysuj_litery(wszystkie_strzaly, 'q', 'z');
}

string losuj_slowo(string plik, string kategoria)
{
    bool znaleziono = false;
    int ile = 0, ile_hasel = 0, ktora_linia = 0;
    string linia, slowo;
    ifstream piesek(plik);
    while (!piesek.eof())
    {
        getline(piesek, linia);
        if (linia.find("-" + kategoria) != string::npos)
        {
            znaleziono = true;
            ile = -1;
        }
        ile++;
        if (znaleziono)
        {
            if (linia.find("-") != string::npos or linia.find("!KONIEC!") != string::npos)
            {
                if (linia.find("-" + kategoria) != string::npos)
                {
                    1 == 1;
                }
                else
                {
                    ile_hasel = ile - 1;
                    break;
                }
            }
        }
    }
    ktora_linia = (rand() % ile_hasel) + 1;
    ifstream kot(plik);
    while (!kot.eof())
    {
        getline(kot, linia);
        ile++;
        if (linia.find("-" + kategoria) != string::npos)
        {
            ile = 0;
        }
        if (ile == ktora_linia)
        {
            slowo = linia;
            kot.close();
            return slowo;
        }
    }
    return "blad";
}

void statystyki(string plik,int nr_gracza, bool czy_wygral, bool rysuj)
{
    string linia, pomoc;
    if (rysuj) system("cls");
    const int n = 9;
    bool pelen = true;
    int licznik = 0, i = 1, x = 1, wygrane[n] = { 0 }, przegrane[n] = { 0 };

    i = 1;
    ifstream otworz(plik);
    if (!otworz) { cout << endl << "Blad otwarcia pliku!" << endl;  exit(0); }
    while (!otworz.eof())
    {
        getline(otworz, linia);
        if ((i + 1) % 3 == 0)
        {
            if (rysuj) cout << "Gracz " << x << ":" << endl;
            linia.erase(0, 9);
            wygrane[x] = stoi(linia);
            if (rysuj) cout << "Wygrane: " << wygrane[x] << endl;
        }
        if (i % 3 == 0)
        {
            linia.erase(0, 11);
            przegrane[x] = stoi(linia);
            if (rysuj) cout << "Przegrane: " << przegrane[x] << endl;
            x++;
        }
        i++;
    }

    if (czy_wygral) wygrane[nr_gracza] += 1;
    else przegrane[nr_gracza] += 1;
    otworz.close();
    ofstream zapisz("plik");

    i = 1;
    while (i <= 8)
    {
        zapisz << "gracz " << i << ":" << endl << "Wygrane: " << wygrane[i] << endl << "Przegrane: " << przegrane[i] << endl;
        i++;
    }
    zapisz.close();
}