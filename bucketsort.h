#include "quicksort.h"
#include <cstddef>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <map>



template <typename T>
void bucketSort(T* tab, int len)
{
    T** bucket = new T* [5]; //tablica kubełków
    int* bucketSize = new int[5] {0}; //ilość elementów w każdym z pięciu kubeczków

    for (int i = 0; i < len; i++) //zliczenie rozmiaru kubełka
    {
        if (tab[i].rating >= 1.0 && tab[i].rating <= 2.0)
        {
            bucketSize[0]++;
        }
        else if (tab[i].rating > 2.0 && tab[i].rating <= 4.0)
        {
            bucketSize[1]++;
        }
        else if (tab[i].rating > 4.0 && tab[i].rating <= 6.0)
        {
            bucketSize[2]++;
        }
        else if (tab[i].rating > 6.0 && tab[i].rating <= 8.0)
        {
            bucketSize[3]++;
        }
        else if (tab[i].rating > 8.0 && tab[i].rating <= 10.0)
        {
            bucketSize[4]++;
        }
    }

    for (int i = 0; i < 5; i++) // tworzenie odpowiednich rozmiarów kubełków
    {
        if (bucketSize[i] > 0)
        {
            bucket[i] = new T[bucketSize[i]];
        }
        else
        {
            bucket[i] = nullptr;
        }
    }

    int* bucketIndex = new int[5] {0}; // który indeks jest aktualnie przetwarzany

    for (int i = 0; i < len; i++) //umieszczanie pozycji w odpowiednim kubełku
    {
        if (tab[i].rating >= 1.0 && tab[i].rating <= 2.0)
        {
            bucket[0][bucketIndex[0]] = tab[i];
            bucketIndex[0]++;
        }
        else if (tab[i].rating > 2.0 && tab[i].rating <= 4.0)
        {
            bucket[1][bucketIndex[1]] = tab[i];
            bucketIndex[1]++;
        }
        else if (tab[i].rating > 4.0 && tab[i].rating <= 6.0)
        {
            bucket[2][bucketIndex[2]] = tab[i];
            bucketIndex[2]++;
        }
        else if (tab[i].rating > 6.0 && tab[i].rating <= 8.0)
        {
            bucket[3][bucketIndex[3]] = tab[i];
            bucketIndex[3]++;
        }
        else if (tab[i].rating > 8.0 && tab[i].rating <= 10.0)
        {
            bucket[4][bucketIndex[4]] = tab[i];
            bucketIndex[4]++;
        }
    }

    for (int i = 0; i < 5; i++) //sortowanie kubełków
    {
        if (bucketSize[i] > 0)
        {
            quickSort(bucket[i], 0, bucketSize[i] - 1);
        }
    }

    int k = 0;
    for (int i = 0; i < 5; i++) //kopia elementów do oryginalnej tablicy w takiej kolejności jak dodane
    {
        if (bucketSize[i] > 0)
        {
            for (int j = 0; j < bucketSize[i]; j++)
            {
                tab[k] = bucket[i][j];
                k++;
            }
        }
        delete[] bucket[i];
    }

    delete[] bucket; // zwalnianie pamięci
    delete[] bucketSize;
    delete[] bucketIndex;
}






