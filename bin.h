#pragma once

#include "tytuly.h"
#include <iostream>

// funkcja wyszukująca indeks elementu w posortowanej tablicy przy użyciu algorytmu wyszukiwania binarnego
int binary_search(tytuly* arr, int n, int ID) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].id == ID) {
            return mid; //zwraca miejsce czego szukam
        } else if (arr[mid].id < ID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
