#pragma once

#ifndef plik1_h
#define plik1_h

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

int pobierz_liczbe(int poczatek, int koniec);
void wiadomosc(string wiadomosc, bool czy_przerwa = false);
string wybor_kategori(string plik, bool czy_losowo = false);
int ile_prob_do_konca(string slowo, string strzal);
void wisielec(int bledne_proby);
bool zgadywanie(string slowo, string strzal);
void rysuj_litery(string dane_litery, char poczatek, char koniec);
void dostepne_litery(string wszystkie_strzaly);
string losuj_slowo(string plik, string kategoria);
void statystyki(string plik,int nr_gracza, bool czy_wygral = true, bool rysuj = false);

#endif 