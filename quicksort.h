#pragma once

template <typename T>
int podzial_tablic(T* tablica, int poczatek, int koniec) {
    T temp, srodek = tablica[(poczatek + koniec) / 2];  // element srodkowy
    int l = poczatek, r = koniec;                    // iteratory dla podtablic lewej i prawej
    while (true) {
        while (tablica[l] < srodek) {
            ++l;  // dopóki po lewej są mniejsze od środkowego
        }
        while (tablica[r] > srodek) {
            --r;  // dopóki po prawej są większe od środkowego
        }

        if (l >= r) {
            return r;  // element osiowy
        }

        // zamień elementy - mniejszy na lewo, większy na prawo
        temp = tablica[l];
        tablica[l++] = tablica[r];
        tablica[r--] = temp;
    }
}

template <typename T>
void quickSort(T* tablica, int poczatek, int koniec) {
    // rekurencyjne dzielenie na 2 podtablice aż do uzyskania jednoelementowych
    if (poczatek >= 0 && poczatek < koniec) {
        int srodek = podzial_tablic(tablica, poczatek, koniec);  // element osiowy
        quickSort(tablica, poczatek, srodek);              // lewa podtablica
        quickSort(tablica, srodek + 1, koniec);            // prawa podtablica
    }
}
