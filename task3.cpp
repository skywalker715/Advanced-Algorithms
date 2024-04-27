#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

int bubble_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            count++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return count;
}

int selection_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            count++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap(arr[i], arr[min_index]);
    }
    return count;
}

int insertion_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            count++;
            arr[j + 1] = arr[j];
            j--;
        }
        if (j >= 0) count++; 
        arr[j + 1] = key;
    }
    return count;
}

void heapify(int arr[], int n, int i, int &count) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n) {
        count++;
        if (arr[l] > arr[largest]) {
            largest = l;
        }
    }

    if (r < n) {
        count++;
        if (arr[r] > arr[largest]) {
            largest = r;
        }
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, count);
    }
}

int heap_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, count);
    
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, count);
    }
    return count;
}
vector<int> generate_sorted_array(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1); 
    return arr;
}

vector<int> generate_inversely_sorted_array(int size) {
    vector<int> arr(size);
    iota(arr.rbegin(), arr.rend(), 1); 
    return arr;
}

void test_comparisons() {
    ofstream compFile("comparisonfile.csv"), timeFile("timesfile.csv");

    compFile << "Array Type,Array Size,Bubble Sort,Selection Sort,Insertion,Heap\n";
    timeFile << "Array Type,Array Size,Bubble Sort,Selection Sort,Insertion,Heap\n";

    for (int size = 1; size <= 30; ++size) {
        vector<int> comparisons(4, 0);
        vector<double> times(4, 0.0);

        vector<int> arr(size);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 100);
        for (int i = 0; i < size; i++) {
            arr[i] = distrib(gen);
        }

        vector<int> temp = arr;
        auto start = high_resolution_clock::now();
        int comp = bubble_sort_count(temp.data(), size);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        comparisons[0] = comp;
        times[0] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = selection_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[1] = comp;
        times[1] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = insertion_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[2] = comp;
        times[2] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = heap_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[3] = comp;
        times[3] = duration.count() * 1e-6;

        compFile << "Random Arrays Comparisons," << size << "," << comparisons[0] << "," << comparisons[1] << "," << comparisons[2] << "," << comparisons[3] << endl;
        timeFile << "Random Arrays Times," << size << "," << times[0] << "," << times[1] << "," << times[2] << "," << times[3] << endl;
    }

    for (int size = 1; size <= 30; ++size) {
        vector<int> comparisons(4, 0);
        vector<double> times(4, 0.0);

        vector<int> arr(size);
        iota(arr.begin(), arr.end(), 1); 

        vector<int> temp = arr;
        auto start = high_resolution_clock::now();
        int comp = bubble_sort_count(temp.data(), size);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        comparisons[0] = comp;
        times[0] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = selection_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[1] = comp;
        times[1] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = insertion_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[2] = comp;
        times[2] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = heap_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[3] = comp;
        times[3] = duration.count() * 1e-6;

        compFile << "Sorted Arrays Comparisons," << size << "," << comparisons[0] << "," << comparisons[1] << "," << comparisons[2] << "," << comparisons[3] << endl;
        timeFile << "Sorted Arrays Times," << size << "," << times[0] << "," << times[1] << "," << times[2] << "," << times[3] << endl;
    }

    for (int size = 1; size <= 30; ++size) {
        vector<int> comparisons(4, 0);
        vector<double> times(4, 0.0);

        vector<int> arr(size);
        iota(arr.rbegin(), arr.rend(), 1); 

        vector<int> temp = arr;
        auto start = high_resolution_clock::now();
        int comp = bubble_sort_count(temp.data(), size);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        comparisons[0] = comp;
        times[0] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = selection_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[1] = comp;
        times[1] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = insertion_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[2] = comp;
        times[2] = duration.count() * 1e-6;

        temp = arr;
        start = high_resolution_clock::now();
        comp = heap_sort_count(temp.data(), size);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        comparisons[3] = comp;
        times[3] = duration.count() * 1e-6;

        compFile << "Inversely Sorted Arrays Comparisons," << size << "," << comparisons[0] << "," << comparisons[1] << "," << comparisons[2] << "," << comparisons[3] << endl;
        timeFile << "Inversely Sorted Arrays Times," << size << "," << times[0] << "," << times[1] << "," << times[2] << "," << times[3] << endl;
    }

    compFile.close();
    timeFile.close();
}

int main() {
    test_comparisons();
    return 0;
}