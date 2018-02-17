#include "klasy.h"

int main()
{
	int wybor_menu = 0;					// Zmienna nawigacyjna.
	bool powrot_do_menu = false;		// Zmienna zawierajaca informacje o woli powrotu do menu.
	string kategoria;					// Zmienna przechowujaca nazwe wybranej kategorii, podawana miedzy funkcjami.
	Lista_Skladnikow lista_skladnikow;	// Zmienna do przechowywania skladnikow wprowadzanych przez uzytkownika.
	Propozycja propozycja;				// Zmienna obrazujaca propozycje dania wynaleziona przez program.
	Lista_Propozycji lista_propozycji;	// Zmienna do przechowywania znalezionych propozycji.
	do
	{
		if (wybor_menu != 10)							// wybor_menu = 10 sluzy przy wyswietlaniu 10 ostatnich dan.							
			Pobierz_zmienna_nawigacyjna(wybor_menu);	// Pobranie od uzytkownika wartosci zmiennej nawigacyjnej
		else
			wybor_menu = 2;								// Determinuje wyswietlenie listy odtatnich 10 dan

		switch (wybor_menu)
		{
		case 1:															// Interakcja programu z uzytkownikiem.
			Wybierz_kategorie(kategoria);								// Wybor rodzaju dania do przyszykowania.
			Wczytywanie_skladnikow(lista_skladnikow, powrot_do_menu);	// Pobranie danych o skladnikach od uzytkownika.
			if (powrot_do_menu)											// Opcja powrotu do menu glownego z kreatora skladnikow.
			{
				powrot_do_menu = false;
				cout << "Zamykanie kreatora";
				Animacja();
				Wyczysc_listy(lista_propozycji, lista_skladnikow);
				break;
			}
			Znajdz_Propozycje(kategoria, lista_skladnikow, propozycja, lista_propozycji);	// Wyszukanie propozycji dan na podstawie podanych skladnikow.
			
			if (lista_propozycji.Rozmiar() == 0)											// Jesli nie znaleziono dan pasujacych do podanych skladnikow.
			{
				Brak_wynikow();
				Wyczysc_listy(lista_propozycji, lista_skladnikow);							// Usuwa wszystkie elementy list.
				break;
			}
			else
				Wyniki(lista_propozycji);													// Przedstawione wyniki poszukiwan oraz podjecie decyzji w zwiazku z nimi.
			Wyczysc_listy(lista_propozycji, lista_skladnikow);
			break;
		case 2:									// Wyswietla ostatnio wybrane dania.
			Ostatnie_dania(wybor_menu);
			break;
		case 5:									// Wyjscie z programu.
			cout << "Zamykanie programu.";
			Animacja();
			break;
		case 4:									// Wyswietla przelicznik.
			Wyswietl(wybor_menu);
			break;
		case 3:									// Wyswietla instrukcje uzytkowania.
			Otworz_instrukcje();
			break;
		default:
			cout << "Nieznana opcja." << endl;
			wybor_menu = 0;
			Sleep(1000);
			break;
		}
		system("cls");
	} while (wybor_menu != 5);
	return 0;
}

