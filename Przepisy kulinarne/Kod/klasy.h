#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include <list>
#include <regex>
#include <sstream>

using namespace std;

class Nazwa									// Klasa Nazwa przechowujaca zmienna string zawierajaca nazwe.
{
	string nazwa;
public:
	Nazwa() : nazwa("brak") {}
	Nazwa(string name) : nazwa(name) {}
	~Nazwa() {}

	string Pobierz_nazwe()
	{
		return nazwa;
	}

	void Ustaw_nazwe(string name)
	{
		nazwa = name;
	}
};

// ---------------------------------------------------------------------------------------------------------------------


class Skladnik : public Nazwa				// Klasa Skladnik reprezentuje dane pojedynczego skladnika.
{
	int gramatura;
public:
	Skladnik() : Nazwa(), gramatura(0) {}
	Skladnik(string name, int gram) : Nazwa(name), gramatura(gram) {}
	~Skladnik() {}

	void Wypisz_skladnik()
	{
		cout << Pobierz_nazwe() << " " << gramatura << "g" << endl;
	}

	void Definiuj_skladnik(string name, int gram)
	{
		Ustaw_nazwe(name);
		gramatura = gram;
	}

	int Pobierz_gramature()
	{
		return gramatura;
	}

};

// ---------------------------------------------------------------------------------------------------------------------


class Lista_Skladnikow						// Klasa przechowujaca kontener Skladnikow, dostarczajaca operacje na nim.
{
public:
	vector <Skladnik> skladniki;
	Lista_Skladnikow() {}
	Lista_Skladnikow(vector <Skladnik> skl) : skladniki(skl) {}
	~Lista_Skladnikow() {}

	void Dodaj_skladnik(Skladnik & skl)
	{
		skladniki.push_back(skl);
	}

	void Usun_skladnik()
	{
		skladniki.pop_back();
	}

	void Wypisz_skladniki()
	{
		for (vector<Skladnik>::iterator it = skladniki.begin(); it != skladniki.end(); ++it)
		{
			it->Wypisz_skladnik();
		}
	}

	int Rozmiar()
	{
		return skladniki.size();
	}

	void Czysc_liste()
	{
		for (int i = skladniki.size(); i > 0 ; i--)
			skladniki.pop_back();
	}

	bool Czy_unikatowy(string & name)		// Funkcja sprawdza czy skladnik nie zostal juz wczesniej podany.
	{
		for (vector<Skladnik>::iterator it = skladniki.begin(); it != skladniki.end(); ++it)
		{
			if (name == it->Pobierz_nazwe())
				return false;
		}
		return true;
	}


};

// ---------------------------------------------------------------------------------------------------------------------


class Propozycja :public Nazwa				// Klasa reprezentujaca pojedyncza propozycje dania, wyszukana w bazie.
{
	int czas;
	int liczba_porcji;
public:
	Propozycja() : Nazwa("brak"), czas(0), liczba_porcji(0) {}
	Propozycja(string name, int x, int y) : Nazwa(name), czas(x), liczba_porcji(y) {}
	~Propozycja() {}

	int Czas_Przygotowania()
	{
		return czas;
	}

	int Liczba_Porcji()
	{
		return liczba_porcji;
	}

	void Wypisz_Propozycje()
	{
		cout << "Nazwa: " << Pobierz_nazwe() << endl;
		cout << "Czas przygotowania: " << czas << "min" << endl;
		cout << "Mozliwa liczba porcji: " << liczba_porcji << endl;
		cout << endl;
	}

	void Definiuj_Propozycje(string name, int time, int lporcji)
	{
		Ustaw_nazwe(name);
		czas = time;
		liczba_porcji = lporcji;
	}
};

// ---------------------------------------------------------------------------------------------------------------------


class Lista_Propozycji						// Klasa przechowujaca kontener Propozycji, dostarczajaca operacje na nim.
{
	vector<Propozycja> propozycje_dan;
public:
	Lista_Propozycji() {}
	Lista_Propozycji(vector<Propozycja> danie) : propozycje_dan(danie) {}
	~Lista_Propozycji() {}

	void Dodaj_propozycje(Propozycja & prop)
	{
		propozycje_dan.push_back(prop);
	}

	void Wypisz_propozycje()
	{
		int licznik = 0;
		for (vector<Propozycja>::iterator it = propozycje_dan.begin(); it != propozycje_dan.end(); ++it)
		{
			cout << "Propozycja " << ++licznik << ":" << endl;
			it->Wypisz_Propozycje();
		}
	}

	void Czysc_liste()
	{
		for (int i = propozycje_dan.size(); i > 0; i--)
			propozycje_dan.pop_back();
	}

	int Rozmiar()
	{
		return propozycje_dan.size();
	}
};

// ---------------------------------------------------------------------------------------------------------------------

class Lista_Ostatnich : public Nazwa		// Klasa do obslugi listy ostatnio wybieranych dan.
{
	list<Nazwa> ostatnie;
	string tytul;
public:
	Lista_Ostatnich()  {}
	~Lista_Ostatnich() {}
	void Wczytaj_liste()					// Wczytanie listy z pliku.
	{
		ifstream plik;
		plik.open("Dane\\Ostatnie.txt", ios::in);
		if (!plik.good())
		{
			cout << "Nie udalo sie otworzyc pliku z lista." << endl;
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
		string bufor;
		Nazwa danie;
		char znak;
		getline(plik, tytul);
		while (plik >> znak && !plik.fail())// Obsluga pliku.
		{
			plik.seekg(3, ios_base::cur);
			getline(plik, bufor);
			danie.Ustaw_nazwe(bufor);
			ostatnie.push_back(danie);
		}
		plik.close();
	}
	void Zapisz()							// Zapisywanie zaktualizowanej listy.
	{
		ofstream plik;
		plik.open("Dane\\Ostatnie.txt", ios::out);
		if (!plik.good())
		{
			cout << "Nie udalo sie otworzyc pliku z lista." << endl;
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
		plik << tytul << endl;
		int i = 1;
		if (ostatnie.size() == 0)
			plik << "Lista jest pusta." << endl;

		else
		{
			for (list<Nazwa>::iterator it = ostatnie.begin(); it != ostatnie.end(); it++)
			{
				if (i < 10)
					plik << i++ << ".  " << it->Pobierz_nazwe() << endl;
				else
					plik << i++ << ". " << it->Pobierz_nazwe() << endl;
			}	
		}
	}
	void Dodaj(string & nazwa)				// Dodanie pozycji do listy
	{
		Nazwa danie(nazwa);
		if (ostatnie.size() >= 10) ostatnie.pop_back();
		ostatnie.push_front(danie);
	}
	void Czysc_liste()
	{
		ostatnie.clear();
	}
};

// ---------------------------------------------------------------------------------------------------------------------

struct Zmienne							// Struktura przechowujaca zmienne uzywane w funkcji.
{
	string bufor;						// Bufor pobierajacy dane z pliku.
	int liczba_skladnikow;				// Okresla liczbe skladnikow potrzebnych do przygotowania dania.
	int czas_przygotowania;				// Czas przygotowania dania.
	int trafione_skladniki;				// Okresla ile skladnikow, z tych podanych przez uzytkownika, znajduje sie w danym przepisie.
	int liczba_porcji = 0;				// Tymczasowa liczba porcji na podstawie podanego skladnika.
	int ostateczna_liczba_porcji = 0;	// Liczba mozliwych porcji na podstawie podanych skladnikow.
	int gram;							// Przechowuje gramature pobrana z pliku.
	bool znaleziono = false;			// Zmienna pomocnicza przy czytaniu pliku.
	char znak;							// Bufor dla znakow.
	bool pierwsze_trafienie;			// Zmienna pomocnicza - gramatura pierwszego trafionego skladnika okresla koncowa liczbe porcji, kolejne trafienia moga ja zmodyfikowac.
	fstream plik;
};

// ---------------------------------------------------------------------------------------------------------------------
// Funkcje glowne programu.

Lista_Skladnikow Wczytywanie_skladnikow(Lista_Skladnikow & lista, bool & powrot_do_menu);
void Znajdz_Propozycje(string & kategoria, Lista_Skladnikow & lista_skladnikow, Propozycja & propozycja, Lista_Propozycji & lista_propozycji);
void Wyczysc_listy(Lista_Propozycji & lista_propozycji, Lista_Skladnikow & lista_skladnikow);

// ---------------------------------------------------------------------------------------------------------------------
// Funkcje wypisujace dane.

void Wyswietl_Propozycje(Lista_Propozycji & lista_propozycji, fstream & plik, string & danie_do_otwarcia);
void Wypisz_przepis(fstream & plik, string danie_do_otwarcia);
void Wyniki(Lista_Propozycji & lista_propozycji);
void Wyswietl(int & name);

// ---------------------------------------------------------------------------------------------------------------------
// Funkcje pobierania i kontroli poprawnosci wprowadzanych danych.

void Kontrola_skladnika(Lista_Skladnikow & lista, string & nazwa_skladnika, bool & znaleziono, int & decyzja);
void Kontrola_gramatury(Lista_Skladnikow & lista, string & nazwa_skladnika, int & gramatura_skladnika);
void Kontrola_decyzji(int & x, Lista_Skladnikow & lista_skladnikow);

// ---------------------------------------------------------------------------------------------------------------------
// Funkcje pobierania zmiennych.

void Pobierz_zmienne(struct Zmienne & zmienna);
void Wybierz_kategorie(string & kategoria);
void Pobierz_zmienna_nawigacyjna(int & x);
void Decyzja_propozycje(int & wybor);

// ---------------------------------------------------------------------------------------------------------------------
// Funkcje pomocnicze, tekstowe

void Kreator_pomocnicza(Lista_Skladnikow & lista);
void Ostatnie_dania_menu(int & wybor_menu);
void Ostatnie_dania(int & wybor_menu);
void Dodawanie_skladnika_menu();
void Brak_wynikow();
void menu_glowne();
void Animacja();
void Decyzja();

// ---------------------------------------------------------------------------------------------------------------------
// Funkcje odpowiadajace za poprawne otwieranie plikow.

void Otworz_kategorie(string & kategoria, fstream & plik);
void Otworz_przepis(fstream & plik1, string & nazwa);
void Otworz_spis_kategorii(fstream & plik);
void Otworz_instrukcje();
