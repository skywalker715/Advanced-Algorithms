#include <iostream> // This line includes the iostream library for input/output operations
using namespace std; // This line uses the std namespace to avoid repeatedly qualifying std:: before standard library elements

int removeDuplicates(char arrayWithDuplicates[], int size) {
    if (size <= 1) { // Check if the array size is less than or equal to 1
        return size;  // If the array size is 1 or less, return the size as there are no duplicates
    }

    int p1 = 0; // Initialize a pointer p1 to keep track of the unique elements position in the array
    for (int nextNonDuplicate = 1; nextNonDuplicate < size; nextNonDuplicate++) {
        if (arrayWithDuplicates[p1] != arrayWithDuplicates[nextNonDuplicate]) {  // Compare the element at p1 with the next element
            arrayWithDuplicates[++p1] = arrayWithDuplicates[nextNonDuplicate];  // If different, copy the next element to the position pointed to by p1 and increment p1
        }
    }
    return p1 + 1; // Return the new size of the array without duplicates (p1 points to the last unique element + 1)
}

int main() {
    char input[] = {'a', 'b', 'b', 'c', 'e'}; // Character array with duplicates
    int size = sizeof(input) / sizeof(input[0]); // Get the size of the array

    cout << "Array with duplicates: ";
    for (int i = 0; i < size; i++) {
        cout << input[i] << " "; // Print the array elements
    }
    cout << endl;

    int newsize = removeDuplicates(input, size); // Call the removeDuplicates function to remove duplicates and get the new size
    cout << "Array without duplicates: ";
    for (int i = 0; i < newsize; i++) {
        cout << input[i] << " "; // Print the array elements without duplicates
    }
    cout << endl;

    return 0; // Indicate successful program termination
}
