#include <iostream>
using namespace std;

int Divide(int items[], int low, int high) {
    int pivot = items[high];
    int index = low - 1;

    for (int current = low; current < high; current++) {
        if (items[current] <= pivot) {
            index++;
            swap(items[index], items[current]);
        }
    }
    swap(items[index + 1], items[high]);
    return index + 1;
}

void QuickOrganize(int items[], int low, int high, int key) {
    int keyIndex = -1;
    for (int i = low; i <= high; i++) {
        if (items[i] == key) {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex != -1) {
        swap(items[keyIndex], items[high]);
        if (low < high) {
            int divIndex = Divide(items, low, high);
            QuickOrganize(items, low, divIndex - 1, key);
            QuickOrganize(items, divIndex + 1, high, key);
        }
    }
}

int main() {
    int sequence[] = {12, 4, 6, 7, 2, 5, 8, 9, 10, 99, 8, 64, 12, 12};
    int length = sizeof(sequence) / sizeof(sequence[0]);
    int key = 7;

    bool found = false;
    for (int i = 0; i < length; i++) {
        if (sequence[i] == key) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Key not found in the sequence." << endl;
        return 0;
    }

    bool isSmallest = true, isLargest = true;
    for (int i = 0; i < length; i++) {
        if (sequence[i] < key) isSmallest = false;
        if (sequence[i] > key) isLargest = false;
    }

    if (isSmallest || isLargest) {
        cout << "Choose another key." << endl;
        return 0;
    }

    QuickOrganize(sequence, 0, length - 1, key);
    cout << "Organized Sequence\n";
    for (int i = 0; i < length; i++) {
        cout << sequence[i] << " ";
    }
    return 0;
}
