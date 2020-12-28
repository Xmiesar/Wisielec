#include "plik1.h"

int main(int argc, char* argv[])
{ 
    int gracz = 0, ilosc_graczy = 4;
    string kategoria;
    string nazwa_pliku_wejciowego, nazwa_pliku; 
    
        if (argc == 5) {
            for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i - 1], "-i") == 0) nazwa_pliku_wejciowego = argv[i];
                if (strcmp(argv[i - 1], "-w") == 0) nazwa_pliku = argv[i];
            }
        }
        else {
            cout << "Zly format!" << endl << "Prawidlowy format to: nazwa_pliku.exe  -i  plik z kategoriami i haslami  -w  plik z statystykami" << endl;
            exit(0);
        }

    cout << "Podana nazwa pliku wejsciowego: " << nazwa_pliku_wejciowego << endl;
    cout << "Podana nazwa pliku wejsciowego i wyjsciowego: " << "   " << nazwa_pliku << endl;

    char wybor='1';
    while(wybor!='5')
    { 
        string kosmos, wszystkie_strzaly, slowo;
        int bledne_proby = 0;
        bool wygrana = false;
    
         wiadomosc("MENU");
         wiadomosc("      1.Rozpocznij rozgrywke   ");
         wiadomosc("  2.Wybor kategorii   ");
         wiadomosc("   3.Statystyki graczy   ");
         wiadomosc("        4.Wybierz ilosc graczy(1-8)");
         wiadomosc("         (Domyslna ilosc graczy to 4)");
         wiadomosc("5.Wyjdz z gry     ");
         wybor = _getch();
      switch (wybor)
      {
         case '1': 
         { 
            gracz = (gracz % ilosc_graczy) + 1;
            if (kategoria.empty())
            { 
                kategoria = wybor_kategori(nazwa_pliku_wejciowego,true);
            }
            slowo = losuj_slowo(nazwa_pliku_wejciowego, kategoria);
            system("cls");
            wisielec(bledne_proby);
            do
            {   
                wiadomosc("Gracz " + to_string(gracz) , true);
                wiadomosc("Kategoria: "+kategoria);
                dostepne_litery(wszystkie_strzaly);
                wiadomosc("Zgadnij slowo: ", true);
                wygrana=zgadywanie(slowo, wszystkie_strzaly);

                if (wygrana) break;                    
                char literka;
                while(true)
                { 
                wiadomosc("Wprowadz litere: ",true);
                literka = _getch();
                literka=tolower(literka);
                if (literka < 'a' or literka>'z')
                {
                    wiadomosc("To nie litera!",true);

                }
                else break;
                }
                system("cls");
                if (wszystkie_strzaly.find(literka) == string::npos)
                wszystkie_strzaly += literka;
                bledne_proby = ile_prob_do_konca(slowo, wszystkie_strzaly);  
                wisielec(bledne_proby);
            } while (bledne_proby < 6);
            if (wygrana)    
            {
                statystyki(nazwa_pliku,gracz, true);
                wiadomosc(""); 
                wiadomosc("WYGRANA!"); 
            }
           else
            { 
                wiadomosc("Gracz " + to_string(gracz),true);
                statystyki(nazwa_pliku,gracz, false);
                wiadomosc("Kategoria: " + kategoria);
                dostepne_litery(wszystkie_strzaly);
                wiadomosc("Zgadnij slowo: ", true);
                wygrana = zgadywanie(slowo, slowo); 
                wiadomosc("PRZEGRANA!",true);
            }
            kategoria.clear();
            break;
         }
        case '2': 
        {   
            system("cls");
            kategoria = wybor_kategori(nazwa_pliku_wejciowego);
            wiadomosc(kategoria);
            break;
        }
        case '3': 
        {
            statystyki(nazwa_pliku,0, false, true);
            break;
        }
        case '4':
        {
            ilosc_graczy = pobierz_liczbe(1, 8);
            break;
        }
        case '5':
        {
            exit(0);
        }
        default: system("cls");
            cout << "Podana opcja nie istnieje\n";
            break;
        
      }
      kosmos=_getch();
      system("cls");
    }
}
