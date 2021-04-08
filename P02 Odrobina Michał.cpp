/* Zaimplementuj sortowanie przez wybieranie oraz sortowanie metoda quicksort. */

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <algorithm>

using namespace std;
using namespace std::chrono;


// Funkcja losujaca ciag liczb "pseudolosowych"
vector<int> Losuj_Ciag(int min, int max, int n);

// Funkcja wypisujaca ciag na ekranie
void Wypisz_Ciag(vector<int> ciag);

// Funkcja zapisujaca ciag do pliku tekstowego
void Zapisz_Ciag_Do_Pliku(string nazwa_pliku, vector<int> ciag);

// Funkcja odczytujaca ciag z pliku tekstowego
vector<int> Odczytaj_Ciag_Z_Pliku(string nazwa_pliku);

// Funkcja wypisujaca ciag z pliku tekstowego na ekranie
void Wypisz_Ciag_Z_Pliku(string nazwa_pliku);

// Funkcja wypisujaca posortwany ciag na ekranie
void Wypisz_Wynik(vector<int> wynik, int n);

// Algorytm sortujacy Quicksort
vector<int> Quick_Sort(int pierwszy, int ostatni);

// Algorytm sortujacy Sortowanie przez wybieranie
vector<int> Sortowanie_Przez_Wybor(int n);

// Funkcja zapisujaca posortowany ciag do pliku
void Zapisz_Wynik_Do_Pliku(const string nazwa_pliku, vector<int> wynik, int n);

// Funkcja zapisujaca ciag do pliku tekstowego z funkcji: testy()
void Zapisz_Ciag_Do_Pliku_Testy(string nazwa_pliku_ciag, vector<int> ciag_testowy);

// Funkcja zapisujaca czasy wykonywania kazdego z algorytmow do pliku
void Zapisz_Czasy_Do_Pliku(string nazwa_pliku_czas, vector<double> czasy, string litera);

// Funkcja generujaca ciag optymistyczny dla algorytmu Quicksort
vector<int> Ciag_Optymistyczny(vector<int> mediana, int poczatek, int n);

// Funkcja bedaca ciagiem pesymistycznym dla algorytmu Quicksort
// Funkcja bedaca ciagiem optymistycznym dla algorytmu Sortowanie przez wybieranie
vector<int> Posortowany_Ciag(int n);

// Funkcja szukajaca median dla funkcji: Posortowany_Ciag(int n);
vector<int> Szukaj_Median(int poczatek, int n);

// Funkcja bedaca ciagiem pesymistycznym dla algorytmu Sortowanie przez wybieranie
vector<int> Posortowany_Ciag_Malejacy(int n);

// Funkcja wykonujaca testy dla zwiekszajacych sie probek danych 'n'
void testy();


// Licznik czasu wykonywanych funkcji
high_resolution_clock::time_point start;
high_resolution_clock::time_point stop;
duration<double> czas;


vector<int> ciag_quick_sort; // Ciag ktory ma zostac posortowany przez: Quick_Sort
vector<int> ciag_select;     // Ciag ktory ma zostac posortowany przez: Sortowanie_Przez_Wybor
vector<int> ciag_sort;       // Ciag w ktorym maja zostac odnaleziony mediany
vector<int> ciag_opt;        // Ciag optymistyczny ktory ma zostac posortowany przez: Quick_Sort
vector<int> ciag_pes;        // Ciag pesymistyczny ktory ma zostac posortowany przez: Quick_Sort
vector<int> ciag_opt_select; // Ciag optymistyczny ktory ma zostac posortowany przez: Sortowanie_Przez_Wybor
vector<int> ciag_pes_select; // Ciag pesymistyczny ktory ma zostac posortowany przez: Sortowanie_Przez_Wybor

int main()
{
    int n = 20;     // ciag wylosuje 20 liczb
    vector<int> wynik;
    vector<int> ciag;

    //////////////////////////
    /* Odczyt ciagu z pliku */
    //////////////////////////

//    string nazwa_pliku =  "Plik.txt" ;
//    ciag = Odczytaj_Ciag_Z_Pliku(nazwa_pliku);
//    Wypisz_Ciag_Z_Pliku(nazwa_pliku);
//    n = ciag.size();


    ciag = Losuj_Ciag(0, 100, n);
    ciag_quick_sort = ciag;
    ciag_select = ciag;
    Wypisz_Ciag(ciag);
    cout << "-------------------------------------------------------------" << endl << endl;
    Zapisz_Ciag_Do_Pliku("Wylosowany ciag.txt", ciag);

    ////////////////////////////////////////

    // Quicksort //

    // Sortowanie oraz czas wykonania algorytmu dla wybranej liczby 'n' wartości ciagu losowego

    start = high_resolution_clock::now();
    wynik = Quick_Sort(0, n-1);
    stop = high_resolution_clock::now();
    czas = stop-start;



    cout << "Posortowany ciag (Quick_Sort): " << endl << endl;
    Wypisz_Wynik(wynik, n);
    cout << endl << "Czas wykonania algorytmu: " << czas.count() << " s." << endl;
    cout << "-------------------------------------------------------------" << endl;
    Zapisz_Wynik_Do_Pliku("Posortowany ciag (Quick_Sort).txt", wynik, n);

    ////////////////////////////////////////

    // Sortowanie Przez Wybor //

    // Sortowanie oraz czas wykonania algorytmu dla wybranej liczby 'n' wartości ciagu losowego

    start = high_resolution_clock::now();
    wynik = Sortowanie_Przez_Wybor(n);
    stop = high_resolution_clock::now();
    czas = stop-start;



    cout << "Posortowany ciag (Sortowanie_Przez_Wybor): " << endl << endl;
    Wypisz_Wynik(wynik, n);
    cout << endl << "Czas wykonania algorytmu: " << czas.count() << " s." << endl;
    Zapisz_Wynik_Do_Pliku("Posortowany ciag (Sortowanie_Przez_Wybor).txt", wynik, n);


    testy();



    return 0;

}



////////////////////////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////






void testy()
{
    int n = 200;
    int ilosc_testow = 10;
    vector<int> wynik_test;
    vector<int> ciag_testowy;
    vector<int> mediana;
    vector<double> czas_quick_sort(ilosc_testow);
    vector<double> czas_select(ilosc_testow);

    cout << "_____________________________________________________" << endl;
    cout << "Testy:" << endl << endl;


    for(int i=0; i<ilosc_testow; i++)
    {

        string nazwa_pliku_ciag_opt = ("Wylosowany ciag OPTYMISTYCZNY TESTY (Quick_Sort) " + to_string(i) +".txt");
        string nazwa_pliku_ciag_pes = ("Wylosowany ciag PESYMISTYCZNY TESTY (Quick_Sort) " + to_string(i) +".txt");
        string nazwa_pliku_ciag = ("Wylosowany ciag LOSOWY TESTY " + to_string(i) +".txt");
        string nazwa_pliku_ciag_opt_select = ("Wylosowany ciag OPTYMISTYCZNY TESTY (Sortowanie_Przez_Wybor) " + to_string(i) +".txt");
        string nazwa_pliku_ciag_pes_select = ("Wylosowany ciag PESYMISTYCZNY TESTY (Sortowanie_Przez_Wybor) " + to_string(i) +".txt");
        string nazwa_pliku_wynik1 = ("Posortowany ciag TESTY (Quick_Sort) " + to_string(i) +".txt");
        string nazwa_pliku_wynik2 = ("Posortowany ciag TESTY (Sortowanie_Przez_Wybor) " + to_string(i) +".txt");

        cout << "n: " << n << endl;

        // Ciag optymistyczny //

        ciag_sort = Posortowany_Ciag(n);
        mediana = Szukaj_Median(0, n-1);


        // Losowanie ciagu //

        ciag_testowy = Losuj_Ciag(0, 100, n);

        ciag_opt = Ciag_Optymistyczny(mediana, 0, n-1);
        ciag_pes = Posortowany_Ciag(n);

        ciag_opt_select = Posortowany_Ciag(n);
        ciag_pes_select = Posortowany_Ciag_Malejacy(n);


        /////////////////////////////////
        /* WYBOR CIAGU DO POSORTOWANIA */   /* Moze byc zaznaczona tylko jedna opcja, dla jednego algorytmu */
        /////////////////////////////////



        // Quicksort //

        /* LOSOWY */

//        ciag_quick_sort = ciag_testowy;
//        Zapisz_Ciag_Do_Pliku_Testy(nazwa_pliku_ciag, ciag_testowy);

        /* OPTYMISTYCZNY */
        ciag_quick_sort = ciag_opt;
        Zapisz_Ciag_Do_Pliku_Testy(nazwa_pliku_ciag_opt, ciag_opt);

        /* PESYMISTYCZNY */
//        ciag_quick_sort = ciag_pes;
//        Zapisz_Ciag_Do_Pliku_Testy(nazwa_pliku_ciag_pes, ciag_pes);



        // Sortowanie Przez Wybor //

        /* LOSOWY */

//        ciag_select = ciag_testowy;
//        Zapisz_Ciag_Do_Pliku_Testy(nazwa_pliku_ciag, ciag_testowy);

        /* OPTYMISTYCZNY */
//        ciag_select = ciag_opt_select;
//        Zapisz_Ciag_Do_Pliku_Testy(nazwa_pliku_ciag_opt_select, ciag_opt_select);

        /* PESYMISTYCZNY */
        ciag_select = ciag_pes_select;
        Zapisz_Ciag_Do_Pliku_Testy(nazwa_pliku_ciag_pes_select, ciag_pes_select);

        /////////////////////////////////
        /////////////////////////////////

        // Licznik czasu dla: Quick Sort //

        start = high_resolution_clock::now();
        wynik_test = Quick_Sort(0, n-1);
        stop = high_resolution_clock::now();
        czas = stop-start;
        czas_quick_sort[i] = czas.count();
        cout << "CzasA (Quick_Sort) " << i+1 << ": ";
        cout << czas_quick_sort[i] << " s." << endl;



        Zapisz_Wynik_Do_Pliku(nazwa_pliku_wynik1, wynik_test, n);


        // Licznik czasu dla: Sortowanie Przez Wybor //

        start = high_resolution_clock::now();
        wynik_test = Sortowanie_Przez_Wybor(n);
        stop = high_resolution_clock::now();
        czas = stop-start;
        czas_select[i] = czas.count();
        cout << "CzasB (Sortowanie_Przez_Wybor) " << i+1 << ": ";
        cout << czas_select[i] << " s." << endl << endl;
        cout << "-------------------------------------" << endl;


        Zapisz_Wynik_Do_Pliku(nazwa_pliku_wynik2, wynik_test, n);




        n*=2;
    }


    Zapisz_Czasy_Do_Pliku("Czasy Quick Sort.txt", czas_quick_sort, "A");
    Zapisz_Czasy_Do_Pliku("Czasy Sortowanie Przez Wybor.txt", czas_select, "B");


}



//--------------------------------------------------------------------------------------



vector<int> Losuj_Ciag(int min, int max, int n)
{
    srand(time(NULL));  // Pobiera aktualny czas z komputera

    vector<int> tab;

    for(int i=0; i<n; i++)    // losuje z liczby przedzialu od 'min=1' do 'max=100' i zapisuje je w tablicy 'tab'
    {
        tab.push_back( (rand()%max) + min + 1 );
    }


    return tab;


}



//--------------------------------------------------------------------------------------



void Wypisz_Ciag(vector<int> ciag)
{

    cout << "Wylosowany ciag: " << endl;

    for(int i=0; i<ciag.size(); i++)
    {
        cout << setw(5) << ciag[i];
    }

    cout << endl << endl;

}



//--------------------------------------------------------------------------------------



void Zapisz_Ciag_Do_Pliku(string nazwa_pliku, vector<int> ciag)
{

    ofstream out(nazwa_pliku);

    for(int i=0; i<ciag.size(); i++)
    {
        out << setw(5) << ciag[i];
    }


}



//--------------------------------------------------------------------------------------



vector<int> Odczytaj_Ciag_Z_Pliku(string nazwa_pliku)
{
    ifstream in(nazwa_pliku);
    vector<int> tab;
    int liczba_ciagu;

    while(!in.eof())
    {
        in >> liczba_ciagu;
        tab.push_back(liczba_ciagu);

    }


    return tab;

}



//--------------------------------------------------------------------------------------



void Wypisz_Ciag_Z_Pliku(string nazwa_pliku)
{
    ifstream in(nazwa_pliku);
    int liczba_ciagu;

    while(!in.eof())
    {
        in >> liczba_ciagu;
        cout << setw(6) << liczba_ciagu;

    }




}



//--------------------------------------------------------------------------------------



vector<int> Quick_Sort(int pierwszy, int ostatni)
{

    int piwot, i, j;


    i = (pierwszy + ostatni) / 2;                             // Ustalamy indeks elementu srodkowego

    piwot = ciag_quick_sort[i];                               // Element srodkowy przypisujemy jako piwot

    ciag_quick_sort[i] = ciag_quick_sort[ostatni];            // Element srodkowy zamieniamy z elementem ostatnim

    j = pierwszy;                                             // j - wskazuje na indeks 0
    i = pierwszy;                                             // i - wskazuje na indeks 0

    while(i < ostatni)                                        // Sprawdzamy wszystkie wartosci w ciagu do ostatniej liczby
    {
        if(ciag_quick_sort[i] < piwot)                        // Jezeli liczba 'ciag_quick_sort[i]' jest mniejsza od piwota...
        {
            swap(ciag_quick_sort[i], ciag_quick_sort[j]);     // Zamien liczbe 'ciag_quick_sort[i]' z liczba 'ciag_quick_sort[j]'
            j++;                                              // Wskaznik 'j' przechodzi o jedno miejsce dalej

        }

        i++;                                                  // Wskaznik 'i' przechodzi o jedno miejsce dalej
    }

    ciag_quick_sort[ostatni] = ciag_quick_sort[j];            // Ostatnia liczbe przypisujemy do liczby, na ktorej zatrzymal sie wskaznik 'j'
    ciag_quick_sort[j] = piwot;                               // Liczba, na ktora wskazuje wskaznij 'j', staje sie piwotem


    if(pierwszy < j-1)                                        // Jezeli pierwsza liczba jest mniejsza od piwotu
    {
        Quick_Sort(pierwszy, j-1);                            // Wykonaj ponownie algorytm sortujacy dla liczb mniejszych od piwota, gdzie liczba stojaca przed piwotem jest ostatnia liczba
    }

    if(j+1 < ostatni)                                         // Jezeli ostatnia liczba jest wieksza od piwotu
    {
        Quick_Sort(j+1, ostatni);                             // Wykonaj ponownie algorytm sortujacy dla liczb wiekszych od piwota, gdzie liczba stojaca za piwotem jest pierwsza liczba

    }




    return ciag_quick_sort;                                   // Zwroc posortowany ciag

}



//--------------------------------------------------------------------------------------



vector<int> Sortowanie_Przez_Wybor(int n)
{
    int i, j, minim;

    j = 0;                                                  // 'j' wskazuje na 0 indeks

    while(j < n)                                            // Wykonuje petle do momentu, w ktorym wskaznik 'j' bedzie wskazywal ostatnia liczbe
    {
        minim = j;                                          // Przypisuje liczbe o indeksie 'j' jako minimalna liczbe
        i = j + 1;                                          // Miejsce od ktorego zaczyna sie sprawdzanie kazdej liczby. Co petle zwieksza sie o 1

        while(i < n)                                        // Sprawdzenie kazdej liczby od indeksu 'i' az do ostatniej liczby
        {
            if(ciag_select[i] < ciag_select[minim])         // Jezeli wybrana liczba bedzie mniejsza od aktualnej liczby minimalnej...
            {
                minim = i;                                  // Wskaz wybrana liczbe jako minimalna
            }

            i++;                                            // Przesuwa wskaznik 'i' o jedno miejsce dalej

        }

        swap(ciag_select[minim], ciag_select[j]);           // Zamienia aktualnie wskazana liczbe na nowa, jako minimalna

        j++;                                                // Przesuniêcie o jedno miejsce wskaznika, ktory bedzie wskazywal liczbe jako minimalna

    }


    return ciag_select;                                     // Zwroc posortowany ciag

}



//--------------------------------------------------------------------------------------



void Wypisz_Wynik(vector<int> wynik, int n)
{


    for(int i=0; i<n; i++)
    {
        cout << setw(5) << wynik[i];
    }

    cout << endl;

}



//--------------------------------------------------------------------------------------



void Zapisz_Wynik_Do_Pliku(string nazwa_pliku, vector<int> wynik, int n)
{
    ofstream out(nazwa_pliku);


    for(int i=0; i<n; i++)
    {
        out << setw(5) << wynik[i];
    }

    cout << endl;



}



//--------------------------------------------------------------------------------------



void Zapisz_Ciag_Do_Pliku_Testy(string nazwa_pliku_ciag, vector<int> ciag_testowy)
{
    ofstream out(nazwa_pliku_ciag);

    for(int i=0; i<ciag_testowy.size(); i++)
    {
        out << setw(5) << ciag_testowy[i];
    }




}



//--------------------------------------------------------------------------------------



void Zapisz_Czasy_Do_Pliku(string nazwa_pliku_czas, vector<double> czasy, string litera)
{
    ofstream out(nazwa_pliku_czas);

    for(int i=0; i<czasy.size(); i++)
    {
        out << "Czas" << litera << " " << i << ": ";
        out << czasy[i] << " s." << endl;

    }



}



//--------------------------------------------------------------------------------------



vector<int> Ciag_Optymistyczny(vector<int> mediana, int poczatek, int n)
{
    int srodek;
    int p, i;

    // Porownuje wartosci ciagu z liczbami ktore zostaly wybrane jako mediany

    for(p=0;p<ciag_opt.size(); p++)
    {

        if(ciag_opt[p]==mediana[0])
        {

            // Wyznacza srodek
            srodek =  (poczatek + n ) / 2;

            // Liczbe ktora zostala uznana za mediane umieszcza na srodku ciagu
            swap(ciag_opt[p], ciag_opt[srodek]);

        }

    }

    i=1;
    p=0;

    // Poprzednie czynnosci zostaja wykonane dla lewej strony ciagu
    while(poczatek < srodek-5)
    {

        if(ciag_opt[p]==mediana[i])
        {
            srodek =  (poczatek + srodek-1) / 2;

            swap( ciag_opt[srodek], ciag_opt[p] );

            i++;
            p=0;
        }
        else
        {

            p++;
        }

    }


    srodek =  (poczatek + n ) / 2;

    // Poprzednie czynnosci zostaja wykonane dla prawej strony ciagu
    while(srodek+5 < n)
    {

        if(ciag_opt[p]==mediana[i])
        {
            srodek =  (srodek+1 + n ) / 2; // wyznacza srodki w czesciach

            swap( ciag_opt[srodek], ciag_opt[p] );

            i++;
            p=0;
        }
        else
        {

            p++;
        }

    }

    return ciag_opt;


}



//--------------------------------------------------------------------------------------



vector<int> Posortowany_Ciag(int n)
{
    vector<int> ciag;


    ciag = Losuj_Ciag(0, 100, n);   // Losuje ciag
    ciag_opt = ciag;



    sort( ciag.begin(), ciag.end() ); // Sortuje ciag


    return ciag;


}



//--------------------------------------------------------------------------------------



vector<int> Szukaj_Median(int poczatek, int n)
{

    vector<int> mediana;



    int ind_mediana =  (poczatek + n ) / 2;  // Wyszukuje indeks mediany

    mediana.push_back( ciag_sort[ind_mediana] ); // Szufladkuje mediane

    // Dla lewej strony ciagu
    while(poczatek < ind_mediana-5)
    {
        ind_mediana =  (poczatek + ind_mediana-1) / 2;

        mediana.push_back( ciag_sort[ind_mediana] );
    }

    ind_mediana =  (poczatek + n ) / 2;

    // Dla prawej strony ciagu
    while(ind_mediana+5 < n)
    {
        ind_mediana =  (ind_mediana+1 + n ) / 2;
        mediana.push_back( ciag_sort[ind_mediana] );
    }


    return mediana;


}



//--------------------------------------------------------------------------------------



vector<int> Posortowany_Ciag_Malejacy(int n)
{
    vector<int> ciag;


    ciag = Losuj_Ciag(0, 100, n);   // Losuje ciag


    sort( ciag.begin(), ciag.end(), greater<int>() ); // Sortuje ciag malejaco


    return ciag;


}


