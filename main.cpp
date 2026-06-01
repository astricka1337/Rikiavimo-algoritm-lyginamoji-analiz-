#ifndef SORTING_H
#define SORTING_H

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