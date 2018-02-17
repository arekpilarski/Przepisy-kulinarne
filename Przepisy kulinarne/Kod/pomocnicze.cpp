#include "klasy.h"

// ---------------------------------------------------------------------------------------------------------------------

void menu_glowne()
{
	cout << "  Witaj w programie kucharskim!\n" << endl;
	cout << "             MENU"					<< endl;
	cout << "1. Wyszukaj dania"					<< endl;
	cout << "2. Pokaz ostatnio wybrane dania"	<< endl;
	cout << "3. Wyswietl instrukcje uzytkowania"<< endl;
	cout << "4. Pokaz przelicznik gramatur"		<< endl;
	cout << "5. Zakoncz program\n"				<< endl;
	cout << "Podaj numer operacji, ktora chcesz";
	cout << " wykonac i zatwierdz enterem."		<< endl;
	cout << "-->";
}

// ---------------------------------------------------------------------------------------------------------------------

void Wyswietl(int & name)		// Wypisuje z pliku liste ostatnich 10 dan lub wyswietla przelicznik gramatur
{
	ifstream plik;
	{
		if (name == 2)
			plik.open("Dane\\Ostatnie.txt", ios::in);
		else
			plik.open("Dane\\Tabelka.txt", ios::in);

		if (!plik.good())
		{
			string wyjatek = "Nie znaleziono pliku.";
			throw wyjatek;
		}
	}

	catch (string wyjatek)
	{
		cout << wyjatek << endl;
		Sleep(1500);
		exit(EXIT_FAILURE);
	}

	string bufor;
	while (getline(plik, bufor) && !plik.fail())
		cout << bufor << endl;
	plik.close();

	if (name != 2)
	{
		cout << endl << "Wcisnij dowolny klawisz, by wrocic." << endl;
		_getch();
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void Dodawanie_skladnika_menu()						// Menu dodawania skladnika.
{
	cout << "                     DODAWANIE SKLADNIKA\n"<< endl;
	cout << "W celu dodania skladnika wpisz ";
	cout << "jego nazwe i zatwierdz enterem."			<< endl;
	cout << "Jesli chcesz anulowac dodawanie ";
	cout << "skladnika, wpisz 'anuluj'.\n"				<< endl;
	cout << "Nazwa skladnika: ";
}

// ---------------------------------------------------------------------------------------------------------------------

void Kreator_pomocnicza(Lista_Skladnikow & lista)	// Funkcja pomocnicza podtrzymujaca widok kreatora
{
	system("cls");
	cout << "                   KREATOR LISTY SKLADNIKOW" << endl << endl;
	cout << "Twoje skladniki:" << endl;
	lista.Wypisz_skladniki();
	cout << endl << endl;
	Decyzja();
	cout << "2\n";
}

// ---------------------------------------------------------------------------------------------------------------------

void Decyzja()											// Menu kreatora
{
	cout << "\n\nDostepne operacje: "				<< endl;
	cout << "4 -> wyszukaj propozycji dan"			<< endl;
	cout << "3 -> przelicznik gramatur"				<< endl;
	cout << "2 -> dodaj skladnik do listy"			<< endl;
	cout << "1 -> usun ostatnio dodany skladnik"	<< endl;
	cout << "0 -> wroc do menu glownego programu\n"	<< endl;
	cout << "Wprowadz numer operacji, ktora chcesz wykonac i zatwierdz enterem." << endl;
	cout << "-->";
}

// ---------------------------------------------------------------------------------------------------------------------

void Otworz_spis_kategorii(fstream & plik)			// Otwarcie pliku z kategoriami.
{
	try
	{
		plik.open("dane\\spis kategorii.txt", ios::in);
		if (!plik.good())
		{
			string wyjatek = "Nie udalo sie otworzyc pliku: Spis kategorii.";
			throw wyjatek;
		}
	}
	catch (string wyjatek)
	{
		cout << wyjatek << endl;
		Sleep(1000);
		exit(EXIT_FAILURE);
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void Otworz_kategorie(string & kategoria, fstream & plik)				// Otwieranie odpowiedniego pliku z kategoria.
{
	try
	{
		plik.open("kategorie\\" + kategoria + ".txt", ios::in);
		if (!plik.good())
		{
			string wyjatek = "Blad otwarcia pliku kategorii.";
			throw wyjatek;
		}
	}

	catch (string wyjatek)
	{
		cout << wyjatek << endl;
		Sleep(1000);
		exit(EXIT_FAILURE);
	}

	system("cls");
	cout << "Szukanie propozycji dan.";
	Animacja();
}

// ---------------------------------------------------------------------------------------------------------------------

void Ostatnie_dania_menu(int & wybor_menu)						// Wyswietlenie ostatnich wybranych 10 dan.
{
	Wyswietl(wybor_menu);
	cout << "\n\nWpisz: "						<< endl;
	cout << "'reset'    - aby wyczyscic liste"	<< endl;
	cout << "'menu'     - aby wrocic do menu"	<< endl;
	cout << "'wyswietl' - aby wyswietlic wybrany przepis" << endl;
	cout << "-->";
}

// ---------------------------------------------------------------------------------------------------------------------

void Otworz_przepis(fstream & plik1, string & nazwa)			// Otwieranie pliku z przepisem.
{
	try
	{
		plik1.open("Przepisy\\" + nazwa + ".txt", ios::in);
		if (!plik1.good())
		{
			string wyjatek = "Danie " + nazwa + " nie zostalo odnalezione.\n";
			throw wyjatek;
		}
		else
		{
			Wypisz_przepis(plik1, nazwa);
			cout << endl << "Wcisnij dowolny klawisz by wrocic." << endl;
			_getch();
		}
	}

	catch (string wyjatek)
	{
		cout << wyjatek << endl;
		Sleep(1200);
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void Animacja()					// Animacja pracy programu.
{
	Sleep(400);
	cout << ".";
	Sleep(400);
	cout << ".";
	Sleep(400);
	cout << ".";
	Sleep(400);
}

// ---------------------------------------------------------------------------------------------------------------------

void Otworz_instrukcje()
{
	fstream plik;
	string bufor;

	try
	{
		plik.open("Dane\\Instrukcja.txt", ios::in);
		if (!plik.good())
		{
			string wyjatek = "Nie znaleziono instrukcji.\n";
			throw wyjatek;
		}
		else
		{
			Wypisz_przepis(plik, bufor);
			cout << endl << "Wcisnij dowolny klawisz by wrocic." << endl;
			_getch();
		}
	}

	catch (string wyjatek)
	{
		cout << wyjatek << endl;
		Sleep(1200);
	}

}

// ------------------------------------------------------------------------------------------------------------------- -