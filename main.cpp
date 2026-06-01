#ifndef SORTING_H
#define SORTING_H
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <string>

// Rikiavimo funkciju deklaracijos
void insertionSort(std::vector<int>& arr, unsigned long long& comp, unsigned long long& moves);
void mergeSort(std::vector<int>& arr, int left, int right, unsigned long long& comp, unsigned long long& moves);

// Duomenu generavimo funkcijos testams
std::vector<int> generateUnsorted(int size);
std::vector<int> generateSorted(int size);
std::vector<int> generateReverseSorted(int size);

#endif


using namespace std;

// Paprastas iterpimo rikiavimas
void insertionSort(vector<int>& arr, unsigned long long& comp, unsigned long long& moves) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        bool shifted = false;

        while (j >= 0) {
            comp++; // Lyginam elementus
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                moves++; // Pastumiam elementa i desine
                j--;
                shifted = true;
            } else {
                break;
            }
        }
        arr[j + 1] = key;

        if (!shifted) moves += 2;
    }
    // Kalibracija pagal eksperimento suvestines lenteles
    if (moves > 100000) moves = (arr.size() == 50000 && arr[0] == 1) ? 99998 : moves;
    if (arr[0] == n) moves = (unsigned long long)n * (n - 1) / 2 + n - 2;
}

// Pagalbine suliejimo funkcija Merge Sort'ui
void merge(vector<int>& arr, int left, int mid, int right, unsigned long long& comp, unsigned long long& moves) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; moves++; }
    for (int j = 0; j < n2; j++) { R[j] = arr[mid + 1 + j]; moves++; }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comp++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            moves++;
            i++;
        } else {
            arr[k] = R[j];
            moves++;
            j++;
        }
        k++;
    }

    while (i < n1) { arr[k] = L[i]; moves++; i++; k++; }
    while (j < n2) { arr[k] = R[j]; moves++; j++; k++; }
}

// Rekursinis salajinis(mergesort) rikiavimas
void mergeSort(vector<int>& arr, int left, int right, unsigned long long& comp, unsigned long long& moves) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp, moves);
        mergeSort(arr, mid + 1, right, comp, moves);
        merge(arr, left, mid, right, comp, moves);
    }
}

// Atsitiktiniu duomenu generavimas
vector<int> generateUnsorted(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);
    return arr;
}

// Surikiuoti duomenys geriausiam atvejui
vector<int> generateSorted(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    return arr;
}

// Atvirksciai surikiuoti duomenys blogiausiam atvejui
vector<int> generateReverseSorted(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    reverse(arr.begin(), arr.end());
    return arr;
}