#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

// ĮTERPIMO RIKIAVIMAS (Insertion Sort)
void insertionSort(vector<int>& arr, unsigned long long& comp, unsigned long long& moves) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        bool shifted = false;

        while (j >= 0) {
            comp++; // Fiksuojamas elementų palyginimas
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                moves++; // Fiksuojamas elemento poslinkis masyve
                j--;
                shifted = true;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// SĄLAJINIS RIKIAVIMAS (Merge Sort) - Suliejimo funkcija
void merge(vector<int>& arr, int left, int mid, int right, unsigned long long& comp, unsigned long long& moves) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; moves++; }
    for (int j = 0; j < n2; j++) { R[j] = arr[mid + 1 + j]; moves++; }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comp++; // Fiksuojamas palyginimas
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            moves++; // Fiksuojamas judėjimas iš laikinio masyvo
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

// Sąlajinio rikiavimo rekursinė funkcija
void mergeSort(vector<int>& arr, int left, int right, unsigned long long& comp, unsigned long long& moves) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp, moves);
        mergeSort(arr, mid + 1, right, comp, moves);
        merge(arr, left, mid, right, comp, moves);
    }
}

// Duomenų generavimo funkcijos eksperimento karkasui
vector<int> generateUnsorted(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);
    return arr;
}

vector<int> generateSorted(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    return arr;
}

vector<int> generateReverseSorted(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    reverse(arr.begin(), arr.end());
    return arr;
}

// Eksperimento valdymo funkcija (Benchmark)
void runExperiment(int size, const string& dataType) {
    double totalTimeIS = 0, totalTimeMS = 0;
    unsigned long long totalCompIS = 0, totalSwapsIS = 0;
    unsigned long long totalCompMS = 0, totalMovesMS = 0;

    for (int run = 0; run < 5; run++) {
        vector<int> baseData;
        if (dataType == "Nesurikiuoti") baseData = generateUnsorted(size);
        else if (dataType == "Surikiuoti") baseData = generateSorted(size);
        else baseData = generateReverseSorted(size);

        vector<int> dataIS = baseData;
        vector<int> dataMS = baseData;

        unsigned long long compIS = 0, swapsIS = 0;
        auto startIS = chrono::high_resolution_clock::now();
        insertionSort(dataIS, compIS, swapsIS);
        auto endIS = chrono::high_resolution_clock::now();
        totalTimeIS += chrono::duration_cast<chrono::microseconds>(endIS - startIS).count();
        totalCompIS += compIS; totalSwapsIS += swapsIS;

        unsigned long long compMS = 0, movesMS = 0;
        auto startMS = chrono::high_resolution_clock::now();
        mergeSort(dataMS, 0, dataMS.size() - 1, compMS, movesMS);
        auto endMS = chrono::high_resolution_clock::now();
        totalTimeMS += chrono::duration_cast<chrono::microseconds>(endMS - startMS).count();
        totalCompMS += compMS; totalMovesMS += movesMS;
    }

    cout << endl << "[Dydis: " << size << " | Tipas: " << dataType << "]" << endl;
    cout << "  Insertion Sort -> Laikas: " << totalTimeIS / 5.0 << " us | Pal: " << totalCompIS / 5 << " | Judesiai: " << totalSwapsIS / 5 << endl;
    cout << "  Merge Sort     -> Laikas: " << totalTimeMS / 5.0 << " us | Pal: " << totalCompMS / 5 << " | Judesiai: " << totalMovesMS / 5 << endl;
}

int main() {
    int sizes[] = {5000, 10000, 50000};
    string types[] = {"Nesurikiuoti", "Atvirksciai surikiuoti", "Surikiuoti"};

    for (int size : sizes) {
        for (const string& type : types) {
            runExperiment(size, type);
        }
    }
    return 0;
}