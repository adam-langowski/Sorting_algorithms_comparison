#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ns[] = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };

void fill_random(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % n;
    }
}

void fill_increasing(int *A, int n) {
    A[0] = rand() % n;
    for (int i = 1; i<n; i++)
    {
        int k = 1 + rand() % n;
        A[i] = A[i-1] + k;
    }
}

void fill_decreasing(int *A, int n) {
    A[0] = rand() % n;
    for (int i = 1; i<n; i++)
    {
        int k = 1 + rand() % n;
        A[i] = A[i-1] - k;
    }
}

void fill_vshape(int *A, int n) {
    A[0] = rand() % n;
    for (int i=1; i<(n/2); i++)
    {
        int k = 1 + rand() % n;
        A[i] = A[i-1] - k;
    }
    for (int i = (n/2); i<n; i++)
    {
        int k = 1 + rand() % n;
        A[i] = A[i-1] + k;
    }
}

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(int *A, int n) {
    int min;
    for (int i=0; i < n-1; i++)             // zmniejszamy wielkosc tablicy
    {
        min = i;
        for (int j = i+1; j < n; j++)       // znajdowanie najmniejszego elementu i wstawienie go na poczatek
        {
            if (A[j] < A[min])
            min = j;
        }
        swap(&A[min], &A[i]);
    }
}

void insertion_sort(int *A, int n) {        // (jak z talii kart)
    int tmp;
    for (int i=1; i<n; i++)                 // tworzenie tzw. listy uporzadkowanej
    {
        tmp = A[i];
        int j = i-1;
        while (j >= 0 && A[j] > tmp)        // znajdowanie miejsca dla elementu na liscie
        {
            A[j+1] = A[j];
            j = j-1;
        }
        A[j+1] = tmp;
    }
}

void quick_sort(int *A, int l, int p) {         // l,p - przechowuja obrane wartosci, koniec gdy l=p
    int v = A[(l+p)/2];                            // v - obrana os
    int i,j,x;
    i = l;
    j = p;
    do{
        while(A[i] < v) i++;
        while(A[j] > v) j--;
        if(i <= j)
        {
            x = A[i];
            A[i] = A[j];
            A[j] = x;
            i++;
            j--;
        }
    }while(i <= j);

    if(j>l) quick_sort(A, l, j);
    if(i<p) quick_sort(A, i, p);
}

void quick_sort_all(int *A, int n) {
    quick_sort(A, 0, n - 1);
}

int partycja(int A[], int p, int r)
{
    int pivot_index = p + rand()%(r - p + 1); // generowanie losowej osi (pivot)
    int pivot;
    int i = p - 1;
    int j;
    pivot = A[pivot_index];
    swap(&A[pivot_index], &A[r]);            // umieszczamy element 'osi' w posortowanej tablicy
    for (j = p; j < r; j++)                  // wszystkie elementy mniejsze od osi umieszczamy na lewo od osi
    {
        if (A[j] < pivot)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i+1], &A[r]);
    return i + 1;
}

void randomized_quick_sort(int A[], int p, int q) {
    int j;
    if (p < q)
    {
        j = partycja(A, p, q);
        randomized_quick_sort(A, p, j-1);
        randomized_quick_sort(A, j+1, q);
    }
}

void randomized_quick_sort_all(int *A, int n) {
    randomized_quick_sort(A, 0, n - 1);
}

                   // i - korzen; n - rozmiar kopca
void utworz_kopiec(int A[], int n, int i) {
    // ustawiamy lewy i prawy lisc
    int max = i;
    int lewy = 2 * i + 1;
    int prawy = 2 * i + 2;

    if (lewy < n && A[lewy] > A[max])
      max = lewy;

    if (prawy < n && A[prawy] > A[max])
      max = prawy;

    // Kopcujemy do momentu gdy korzen bedzie najwiekszym elementem
    if (max != i) {
      swap(&A[i], &A[max]);
      utworz_kopiec(A, n, max);
    }
}
void heap_sort(int *A, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        utworz_kopiec(A, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
      swap(&A[0], &A[i]);
      utworz_kopiec(A, i, 0);
    }
}

bool is_random(int *A, int n) {
    return true;
}

bool is_increasing(int *A, int n) {
    for (int i = 1; i < n; i++) {
        if (A[i] <= A[i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_decreasing(int *A, int n) {
    for (int i = 1; i < n; i++) {
        if (A[i] >= A[i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_vshape(int *A, int n) {
    if (n % 2 == 0) {
        return is_decreasing(A, n/2) && is_increasing(A + n/2, n/2);
    }
    return is_decreasing(A, n/2 + 1) && is_increasing(A + n/2, n/2 + 1);
}

bool is_sorted(int *A, int n) {
    for (int i = 1; i < n; i++) {
        if (A[i] < A[i - 1]) {
            return false;
        }
    }
    return true;
}

char *bool_to_string(bool b) {
    return b ? "Y" : "N";
}

void (*fill_functions[])(int *, int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
bool (*check_functions[])(int *, int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, int) = { selection_sort, insertion_sort, quick_sort_all, randomized_quick_sort_all, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "RandomizedQuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, int) = fill_functions[j];
            bool (*check)(int *, int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                int n = ns[k];
                int *A = calloc(n, sizeof(*A));

                fill(A, n);
                bool is_filled_ok = check(A, n);

                clock_t begin = clock();
                sort(A, n);
                clock_t end = clock();
                double seconds = (double)(end - begin) / (double) CLOCKS_PER_SEC;

                bool is_sorted_ok = is_sorted(A, n);

                printf("%-20s %-11s %-10d %-4s %-4s %g\n", sort_names[i], fill_names[j], n, bool_to_string(is_filled_ok), bool_to_string(is_sorted_ok), seconds);

                free(A);
            }
        }
    }
    return 0;
}
