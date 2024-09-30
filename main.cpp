#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include "mergesort.h"
#include "bucketsort.h"
#include "quicksort.h"
#include "movie.h"
#include "bin.h"
#include "tytuly.h"








int main() {

    

    // pliki
    std::ifstream plik_baza;  // baza filmow (wczytywany plik)
    std::string baza_nazwa = "data.tsv";
    std::ofstream posortowana_baza_zapis;  // posortowana baza (zapisywany plik)
    std::string posortowana_baza_zapis_nazwa;
    std::string line;  // pojedynczy wpis w bazie
    std::ifstream file2("referencyjne.tsv");

    // sortowania
    std::string sorts[3] = { "merge", "quick","bucket" };

    // testy
    unsigned int test = 0;    // numer testu
    unsigned int nlimit = 0;  // limit n dla zapisu na posortowana_baza_zapis
    unsigned int ile_poz_do_sortowania[] = { 10000, 100000, 500000, 1000000, 1295778 };
    unsigned int nieocenione, mediana;  // ilosc nieocenionych filmow, mediana ocen
    float srednia;               // srednia ocen
    int liczba_linii = 0;
    std::string linia, line1, temp,temp1;

    std::cout<<"Podaj ile pozycji zapisac do posortowania-(10000, 100000, 500000, 1000000, 1295778)"<<std::endl;
    std::cin>>nlimit;
    std::cout << std::fixed << std::setprecision(3); 


    //wczytanie pliku referencyjnego
    if (!file2.is_open()) {
    std::cout << "Nie udalo sie otworzyc pliku ";
    exit(1);
    }
    // zliczanie liczby linii w pliku referencyjnym
    while (getline(file2, linia)) {
        liczba_linii++;
    }

    tytuly* baza_nazwy = new tytuly[liczba_linii];
    
    file2.clear(); // reset flagów strumienia
    file2.seekg(0, std::ios::beg);
    std::getline(file2, line1);  // pominiecie headera
    for (unsigned int i = 0; i < liczba_linii-1; i++) {
        // format pliku: id;type;tytul;tytul;...
        std::getline(file2, line1);  // dzielenie pliku na linie
        std::stringstream split(line1);
        // wczytywanie nazwy
        std::getline(split, baza_nazwy[i].tconst, '\t');
        temp=baza_nazwy[i].tconst;
        temp.erase(std::remove(temp.begin(),temp.end(),'t'),temp.end());
        baza_nazwy[i].id=std::stoi(temp);
        std::getline(split, line1, '\t');
        std::getline(split, line1, '\t');
        std::getline(split, baza_nazwy[i].tytul, '\t');
    }
    file2.close();

    for (unsigned int n : ile_poz_do_sortowania)  // #include <iterator>
    {
        test++;
        std::cout << "TEST " << test << "/" << std::size (ile_poz_do_sortowania) << ": n = " << n << '\n';
        movie* parsowana_baza = new movie[n];

// wczytywanie pliku
nieocenione = 0;
plik_baza.open(baza_nazwa);

if (!plik_baza.is_open()) {
    std::cout << "Nie udalo sie otworzyc pliku " + baza_nazwa;
    exit(1);
}

std::getline(plik_baza, line);  // pominiecie headera
for (unsigned int i = 0; i < n; i++) {
    // format pliku: nazwa;ocena;glosy
    std::getline(plik_baza, line);  // dzielenie pliku na linie
    std::stringstream split(line);
    // wczytywanie nazwy
    std::getline(split, parsowana_baza[i].name, '\t');
        temp1=parsowana_baza[i].name;
        temp1.erase(std::remove(temp1.begin(),temp1.end(),'t'),temp1.end());
        parsowana_baza[i].id1=std::stoi(temp1);

    // wczytywanie oceny
    if (!(split >> parsowana_baza[i].rating)) {
        nieocenione++;
        parsowana_baza[i].rating = -1;
    }
    // wczytywanie liczby glosow
    if (!(split >> parsowana_baza[i].votes)) {
        parsowana_baza[i].votes = -1;
    }

    // koniec pliku - zmiana n do liczby wczytanych filmow
    if (plik_baza.eof()) {
        std::cout << "Plik zawiera za malo danych - wczytane filmy: " << i << " / " << n << '\n';
        n = i + 1;
    }
}
plik_baza.close();



    
        auto czas_start = std::chrono::high_resolution_clock::now();  // mierzenie czasu
        auto czas_koniec = std::chrono::high_resolution_clock::now();  // koniec mierzenia
        auto czas = std::chrono::duration<double, std::milli>(czas_koniec - czas_start).count();






        // sortowania
            std::cout << "Sortowanie ";
     
                /*std::cout << "przez scalanie (mergesort)\n";
                czas_start = std::chrono::high_resolution_clock::now();
                mergeSort(parsowana_baza, 0, n - nieocenione - 1);
                czas_koniec = std::chrono::high_resolution_clock::now();*/

                /*std::cout << "kubełkowe (bucketsort)\n";
                czas_start = std::chrono::high_resolution_clock::now();
                bucketSort(parsowana_baza, 0, n - nieocenione - 1);
                czas_koniec = std::chrono::high_resolution_clock::now();*/

                std::cout << "przez szybkie (quicksort)\n";
                czas_start = std::chrono::high_resolution_clock::now();
                quickSort(parsowana_baza, 0, n - nieocenione - 1);
                czas_koniec = std::chrono::high_resolution_clock::now();


            czas = std::chrono::duration<double, std::milli>(czas_koniec - czas_start).count();
            std::cout << "> Czas sortowania: " << czas << " ms\n";

            // srednia ocen
            srednia = 0;
            for (unsigned int j = 0; j < n - nieocenione; ++j)
                srednia += parsowana_baza[j].rating;  // srednia jako suma
            srednia /= n - nieocenione;
            std::cout << "> Srednia ocen:    " << srednia << '\n';

            // mediana;
            mediana= 0;
            if ((n - nieocenione) % 2 != 0)
                mediana= parsowana_baza[(n - nieocenione) / 2].rating;
            else
                mediana= (parsowana_baza[(n - nieocenione - 1) / 2].rating + parsowana_baza[(n - nieocenione) / 2].rating) / 2;
            std::cout << "> mediana ocen:    " << mediana<< "\n\n";
                if (nlimit > 0 && nlimit >= n) {
        // zapisywanie plikow
            std::cout << "Zapisywanie posortowanych baz...\n";
            posortowana_baza_zapis_nazwa =
                baza_nazwa.substr(0, baza_nazwa.length() - 4) + "_" +
                std::to_string(n);
            
                posortowana_baza_zapis.open(posortowana_baza_zapis_nazwa + "_"  +
                    "sort.tsv");
                if (posortowana_baza_zapis.is_open()) {
                    posortowana_baza_zapis << "lp.\t id \t rating \t title\n";  // header
                    czas_start = std::chrono::high_resolution_clock::now();
                    for (unsigned int j = 0; j < n - nieocenione ; ++j)
                    {
                       int indeks=binary_search(baza_nazwy,liczba_linii,parsowana_baza[j].id1);
                        //std::string title=baza_nazwy[indeks].tytul;
                        posortowana_baza_zapis<<j+1<<". \t"<<parsowana_baza[j].id1 << "\t"<< parsowana_baza[j].rating<<"\t"<<baza_nazwy[indeks].tytul<<"\n";
                    }
                    czas_koniec = std::chrono::high_resolution_clock::now();
                    czas = std::chrono::duration<double, std::milli>(czas_koniec - czas_start).count();
                    std::cout << "> Czas zapisu z wyszukiwaniem binarnym: " << czas << " ms\n";

                    posortowana_baza_zapis.close(); 
                }
                else
                    std::cout << "[Blad] ";
                std::cout << posortowana_baza_zapis_nazwa + "_"  +
                    "sort.tsv\n";
                delete[] parsowana_baza;
            std::cout << '\n';
                }

        


        std::cout << "KONIEC TESTU " << test << "/" << std::size (ile_poz_do_sortowania) << '\n';

}



    return 0;
}

