#include "klasy.h"


// ---------------------------------------------------------------------------------------------------------------------

Lista_Skladnikow Wczytywanie_skladnikow(Lista_Skladnikow & lista, bool & powrot_do_menu)	
{
	Skladnik skladnik;
	string nazwa_skladnika;
	int gramatura_skladnika;
	bool znaleziono;
	int decyzja =2 ;
	while (decyzja!=4)
	{
		system("cls");
		cout << "                   KREATOR LISTY SKLADNIKOW" << endl << endl;
		cout << "Twoje skladniki:" << endl;
		lista.Wypisz_skladniki();
		cout << endl << endl;
		Kontrola_decyzji(decyzja, lista);

		switch (decyzja)
		{
		case 4:
			break;
		case 3: 
			system("cls");
			Wyswietl(decyzja);
			continue;
		case 2:
			Kontrola_skladnika(lista, nazwa_skladnika, znaleziono, decyzja);	// Koltrola poprawnosci nazwy skladnika
			if (nazwa_skladnika == "anuluj") break;								// Anulowanie wprowadzania skladnika
			Kontrola_gramatury(lista, nazwa_skladnika, gramatura_skladnika);	// Kontrola poprawnosci gramatury skladnika
			skladnik.Definiuj_skladnik(nazwa_skladnika, gramatura_skladnika);	// Utworzenie skladnika
			lista.Dodaj_skladnik(skladnik);										// Dodanie skladnika
			break;
		case 1:
			if (lista.Rozmiar() == 0)
			{
				cout << "Brak skladnikow do usuniecia." << endl;
				Sleep(1000);
			}
			else 
				lista.Usun_skladnik();
			break;
		case 0:
			powrot_do_menu = true;
			return lista;
		default:
			cout << "Nieznana opcja." << endl;
			Sleep(500);
			break;
		}
	}
	return lista;
}

// ---------------------------------------------------------------------------------------------------------------------

void Kontrola_skladnika(Lista_Skladnikow & lista, string & nazwa_skladnika, bool & znaleziono, int & decyzja)
{
	bool pomocnicza = false; // zmienna pomocnicza przy wyswietlaniu KREATORA
	string bufor;
	ifstream plik1;
	do
	{
		if (pomocnicza) Kreator_pomocnicza(lista);
		if(!pomocnicza) pomocnicza = true;
		try
		{
			plik1.open("Dane\\Baza skladnikow.txt", ios::out);
			if (!plik1.good()) {
				string wyjatek = "Nie udalo sie otworzyc bazy skladnikow.";
				throw wyjatek; }
		}
		catch (string wyjatek)
		{
			cout << wyjatek << endl;
			Sleep(1000);
			exit(0);
		}
		znaleziono = false;
		Dodawanie_skladnika_menu();
		getline(cin, nazwa_skladnika);
		if(nazwa_skladnika == "") getline(cin, nazwa_skladnika);
		if (nazwa_skladnika == "anuluj")
		{
			plik1.close();
			return;
		}
		while (getline(plik1, bufor) && !plik1.fail())
		{
			if (nazwa_skladnika == bufor)
			{
				znaleziono = true;
				break;
			}
		}
		if (znaleziono == false)
		{
			cout << "Podany skladnik nie wystepuje w bazie." << endl;
			cout << "Czy na pewno chodzilo Ci o : " << nazwa_skladnika << "?" << endl << endl;
			Sleep(2000);
		}
		plik1.close();
		if (!lista.Czy_unikatowy(nazwa_skladnika))
		{
			cout << "Skladnik o podanej nazwie juz istnieje." << endl;
			Sleep(1000);
			znaleziono = false;
		}

	} while (znaleziono == false);
}


// ---------------------------------------------------------------------------------------------------------------------

void Kontrola_gramatury(Lista_Skladnikow & lista, string & nazwa_skladnika, int & gramatura_skladnika)
{
	string gram;
	regex wzor_gramatury("^[1-9]([0-9]*g$)");		// Wzor wyrazenia regularnego.
	do
	{
		Kreator_pomocnicza(lista);					// Podtrzymanie widoku kreatora.
		Dodawanie_skladnika_menu();
		cout << nazwa_skladnika << endl;

		cout << "Podaj gramature: ";
		getline(cin, gram);
		if (!regex_match(gram, wzor_gramatury))									
		{
			cout << endl << "Blad: Niepoprawny format gramatury."	<< endl;
			cout << "Gramatura powinna zostac podana w gramach.\n"	<< endl;
			cout << "Poprawny format gramatury to np.: 300g";
			Sleep(3500);
		}
	} while (!regex_match(gram, wzor_gramatury));
	gramatura_skladnika = stoi(gram);
}

// ---------------------------------------------------------------------------------------------------------------------

void Kontrola_decyzji(int & x, Lista_Skladnikow & lista) // Pobranie i kontrola poprawnosci zmiennej nawigacyjnej od uzytkownika.
{
	ostringstream tmp;
	tmp << x;
	string decyzja = tmp.str();
	regex cyfra("[0-4]");
	do
	{
		Decyzja();
		getline(cin, decyzja);
		
		if (!regex_match(decyzja, cyfra))
		{
			cout << "Nieznana opcja." << endl;
			Sleep(1000);
			system("cls");
			cout << "                   KREATOR LISTY SKLADNIKOW" << endl << endl;
			cout << "Twoje skladniki:" << endl;
			lista.Wypisz_skladniki();
			cout << endl << endl;
		}
	} while (!regex_match(decyzja, cyfra));
	x = stoi(decyzja);
}

// ---------------------------------------------------------------------------------------------------------------------

void Wybierz_kategorie(string & kategoria)		// Funkcja odpowiadajaca za pobranie od uzytkownika nazwy wybranej przed niego kategorii.
{
	fstream plik;
	string bufor;
	do
	{
		system("cls");
		cout << "Wybierz kategorie dan z dostepnych w bazie:" << endl;
		Otworz_spis_kategorii(plik);
		while (getline(plik, bufor) && !plik.fail())
			cout << bufor << endl;
		plik.close();
		cout << endl <<  "Podaj nazwe wybranej kategorii: ";
		cin.clear();
		cin.sync();
		getline(cin, kategoria);
		if (kategoria == "")
			getline(cin, kategoria);
		try										// Sprawdzenie poprawnosci wybranej kategorii.
		{
			plik.open("kategorie\\" + kategoria + ".txt", ios::in);
			if (!plik.good())
			{
				string wyjatek = "Nie znaleziono podanej kategorii. Sprobuj jeszcze raz.";
				throw wyjatek;
			}
			else
				break;
		}

		catch (string wyjatek)
		{
			cout << wyjatek << endl;
			Sleep(1000);
		}
	} while (!plik.good());
	plik.close();
	cout << endl << "Wybrana kategoria: " << kategoria << endl;
	Sleep(700);
	cout << endl <<  "Uruchamianie kreatora listy skladnikow .";
	Animacja();
}

// ---------------------------------------------------------------------------------------------------------------------

void Znajdz_Propozycje(string & kategoria, Lista_Skladnikow & lista_skladnikow, Propozycja & propozycja, Lista_Propozycji & lista_propozycji)
{
	Zmienne zmienna;								// Struktura z danymi wykorzystywanymi w funkcji.
	Otworz_kategorie(kategoria, zmienna.plik);		// Otwarcie odpowiedniego pliku.

	while (getline(zmienna.plik, zmienna.bufor) && !zmienna.plik.eof())		// Przeszukiwanie pliku w celu znalezienia pasujacych dan.
	{
		Pobierz_zmienne(zmienna);											// Pobieranie wartosci zmiennych z pliku.

		for (int i = 0; i < zmienna.liczba_skladnikow; i++)					// Szukanie do momentu znalezienia wszystkich podanych skladnikow.
		{
			zmienna.znaleziono = false;
			if (zmienna.trafione_skladniki == lista_skladnikow.Rozmiar())
				break;
			getline(zmienna.plik, zmienna.bufor);
			if (zmienna.bufor == "") getline(zmienna.plik, zmienna.bufor);	// Pobranie pustego znaku.
			for (vector<Skladnik>::iterator it = lista_skladnikow.skladniki.begin(); it != lista_skladnikow.skladniki.end(); ++it)
			{																
				if (zmienna.bufor == it->Pobierz_nazwe())
				{
					zmienna.trafione_skladniki++;
					zmienna.znaleziono = true;
					zmienna.plik >> zmienna.gram;
					zmienna.liczba_porcji = it->Pobierz_gramature() / zmienna.gram; // Obliczanie liczby porcji w oparciu o podane gramatury.
					if (zmienna.pierwsze_trafienie)
					{
						zmienna.ostateczna_liczba_porcji = zmienna.liczba_porcji;
						zmienna.pierwsze_trafienie = false;
					}
					else if (zmienna.liczba_porcji < zmienna.ostateczna_liczba_porcji)
						zmienna.ostateczna_liczba_porcji = zmienna.liczba_porcji;
					break;
				}
			} if (!zmienna.znaleziono)
				getline(zmienna.plik, zmienna.bufor);
		}

		while (zmienna.plik >> zmienna.znak && zmienna.znak != ':');				// Pobieranie po znaku az znaleziony zostanie dwukropek.
		getline(zmienna.plik, zmienna.bufor);
		if (zmienna.trafione_skladniki == lista_skladnikow.Rozmiar() && zmienna.ostateczna_liczba_porcji != 0)
		{																			//Jesli wszystkie skladniki zostana odnalezione, propozycja jest dodawana do listy propozycji.
			propozycja.Definiuj_Propozycje(zmienna.bufor, zmienna.czas_przygotowania, zmienna.ostateczna_liczba_porcji);
			lista_propozycji.Dodaj_propozycje(propozycja);
		}
	}
	zmienna.plik.close();
}

// ---------------------------------------------------------------------------------------------------------------------

void Pobierz_zmienne(struct Zmienne & zmienna)
{
	if (zmienna.bufor == "") getline(zmienna.plik, zmienna.bufor);		// Pobieranie wartosci zmiennych z pliku.
	zmienna.trafione_skladniki = 0;
	zmienna.plik >> zmienna.bufor;
	zmienna.plik >> zmienna.czas_przygotowania;
	zmienna.plik >> zmienna.bufor;
	zmienna.plik >> zmienna.liczba_skladnikow;
	zmienna.pierwsze_trafienie = true;
}

// ---------------------------------------------------------------------------------------------------------------------




void Wyczysc_listy(Lista_Propozycji & lista_propozycji, Lista_Skladnikow & lista_skladnikow)
{																		// Zwalnianie pamieci.
	lista_propozycji.Czysc_liste();
	lista_skladnikow.Czysc_liste();
}

// ---------------------------------------------------------------------------------------------------------------------

void Wyswietl_Propozycje(Lista_Propozycji & lista_propozycji, fstream & plik, string & danie_do_otwarcia)
{
	do
	{
		system("cls");													// Wyswietlanie znalezionych propozycji.
		cout << "Wyszukane propozycje dan :" << endl << endl;
		lista_propozycji.Wypisz_propozycje();
		cout << endl << "Aby wyswietlic przepis konkretnego dania, podaj jego nazwe." << endl;
		cout << "Jesli chcesz wrocic do menu, wpisz menu. " << endl << endl;
		cin.clear();
		cout << "Nazwa dania: ";
		getline(cin, danie_do_otwarcia);
		if (danie_do_otwarcia == "") getline(cin, danie_do_otwarcia);

		if (danie_do_otwarcia == "menu")
			break;
																		// Otwieranie odpowiedniego pliku z przepisem pozadanym przez uzytkownika.
		try
		{
			plik.open("Przepisy\\" + danie_do_otwarcia + ".txt", ios::in);
			if (!plik.good())
			{
				string wyjatek = "Podane danie nie wystepuje w bazie.\nUpewnij sie, ze nazwa zostala wpisana poprawnie.";
				throw wyjatek;
			}
		}

		catch (string wyjatek)
		{
			cout << wyjatek << endl;
			Sleep(2100);
		}

	} while (!plik.good());
}

// ---------------------------------------------------------------------------------------------------------------------

void Brak_wynikow()											// Informacja o nieznalezieniu pasujacych dan.
{
	system("cls");
	cout << "Brak wynikow dla podanej kombinacji skladnikow.\n" << endl;
	cout << "Wcisnij dowolny klawisz aby wrocic do menu."		<< endl;
	_getch();
}

// ---------------------------------------------------------------------------------------------------------------------

void Wyniki(Lista_Propozycji & lista_propozycji)			// Wyswietlanie wynikow wyszukiwania i decyzja w sprawie wyboru dania.
{
	Lista_Ostatnich lista_ostatnich;						// Zmienna do pracy z lista ostatnio wybranych dan.
	string danie_do_otwarcia;								// Zmienna przechowujaca nazwe dania wybranego przez uzytkownika.
	fstream plik;
	int wybor = 1;											// Zmienna determinujaca dzialania na wynikach.
	do
	{
		switch (wybor)
		{
		case 1:
			Wyswietl_Propozycje(lista_propozycji, plik, danie_do_otwarcia);
			if (danie_do_otwarcia == "menu")				// Opcja powrotu do menu glownego.
				break;
			Wypisz_przepis(plik, danie_do_otwarcia);		// Wypisuje przepis
			Decyzja_propozycje(wybor);						// Decyzja w sprawie wybranej propozycji.
			break;
		case 2:												// Zapisywanie wyboru do listy ostatnio wybranych dan.
			system("cls");
			cout << "ZAPISYWANIE WYBORU.";
			Animacja();
			lista_ostatnich.Wczytaj_liste();
			lista_ostatnich.Dodaj(danie_do_otwarcia);
			lista_ostatnich.Zapisz();
			lista_ostatnich.Czysc_liste();
			cout << endl << "ZAPISANO!" << endl;
			cout << "Wcisnij dowolny klawisz aby wrocic do menu." << endl;
			wybor = 0;
			_getch();
			break;
		case 0:												// Powrot do menu glownego.
			cout << "Powrot do menu" << endl;
			Sleep(1000);
			break;
		default:
			cout << "Nieznana opcja" << endl;
			break;
		};
	} while (wybor != 0 && danie_do_otwarcia != "menu");
}

// ---------------------------------------------------------------------------------------------------------------------

void Decyzja_propozycje(int & wybor)				// Pobranie decyzji od uzytkownika w sprawie wyswietlonego dania.
{
	cout << "\nWprowadz: "						<< endl;
	cout << "-> 2 aby wybrac danie"				<< endl;
	cout << "-> 1 aby wrocic do propozycji dan" << endl;
	cout << "-> 0 aby wrocic do menu glownego"	<< endl;
	cout << "-->";
	do
	{
		cin.clear();
		cin >> wybor;
	} while (wybor != 2 && wybor != 1 && wybor != 0);
}

// ---------------------------------------------------------------------------------------------------------------------

void Wypisz_przepis(fstream & plik, string danie_do_otwarcia)		
{													// Wypisanie przepisu.
	system("cls");
	while (getline(plik, danie_do_otwarcia) && !plik.fail())
		cout << danie_do_otwarcia << endl;
	plik.close();
}

// ---------------------------------------------------------------------------------------------------------------------

void Pobierz_zmienna_nawigacyjna(int & x)			// Pobranie i kontrola poprawnosci zmiennej nawigacyjnej od uzytkownika.
{
	do
	{
		menu_glowne();
		cin >> x;
		if (x != 1 && x != 2 && x != 3 && x != 4 && x != 5)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Nieznana opcja." << endl;
			Sleep(1000);
		}
		system("cls");
	} while (x != 1 && x != 2 && x != 3 && x != 4 && x != 5);
}

// ---------------------------------------------------------------------------------------------------------------------

void Ostatnie_dania(int & wybor_menu)				// Zarzadzanie lista ostatnich dan.
{
	Ostatnie_dania_menu(wybor_menu);				// Wyswietlenie ostatnich dan z nawigacja.
	string polecenie;
	getline(cin, polecenie);						// Pobranie polecenia od uzytkownika.
	if(polecenie == "") getline(cin, polecenie);
	if (polecenie == "menu");						// Realizacja polecenia uzytkownika.
	else if (polecenie == "reset")
	{
		fstream plik;
		plik.open("Dane\\Ostatnie.txt", ios::out | ios::trunc);
		if (!plik.good())
		{
			cout << "Blad odczytu pliku Ostatnie.txt." << endl;
			Sleep(1500);
			exit(EXIT_FAILURE);
		}
		else
		{
			plik << "    10 ostatnio wybranych dan:" << endl;
			plik.close();
		}
		cout << "Usuwanie pozycji.";
		Animacja();
		wybor_menu = 10;
	}
	else if (polecenie == "wyswietl")
	{
		string nazwa;
		fstream plik1;
		cout << "Podaj nazwe dania: ";
		getline(cin, nazwa);
		if (nazwa == "") getline(cin, nazwa);
		Otworz_przepis(plik1, nazwa);
		wybor_menu = 10;
	}
	else
	{
		cout << "Polecenie nieznane." << endl;
		Sleep(700);
		wybor_menu = 10;
	}
}

// ---------------------------------------------------------------------------------------------------------------------