#include <iostream>
#include <pthread.h>

using namespace std;

// Structure to store matrix dimensions and data
struct matrix {
    int rows;
    int columns;
    int* data;
};

// Structure for thread arguments
struct args {
    matrix* matrix1;
    matrix* matrix2;
    matrix* matrix3;
    int row_index;
};

// Function to calculate a single row of the resulting matrix
void* calculate_row(void* arg) {
    args *params = (args*)arg;
    for (int col = 0; col < params->matrix2->columns; col++) {
        int sum = 0;
        for (int inner = 0; inner < params->matrix1->columns; inner++) {
            sum += params->matrix1->data[params->row_index * params->matrix1->columns + inner] *
                   params->matrix2->data[inner * params->matrix2->columns + col];
        }
        params->matrix3->data[params->row_index * params->matrix3->columns + col] = sum;
    }

    pthread_exit(NULL);
}

int main() {
    int Matrix1Row, Matrix1Column, Matrix2Row, Matrix2Column;

    cout << "Enter the dimensions of the first matrix (rows columns): ";
    cin >> Matrix1Row >> Matrix1Column;
    cout << "Enter the dimensions of the second matrix (rows columns): ";
    cin >> Matrix2Row >> Matrix2Column;

    if (Matrix1Column != Matrix2Row) {
        cout << "Error: Invalid matrix dimensions for multiplication." << endl;
        return 1;
    }

    matrix matrix1, matrix2, matrix3;
    matrix1.rows = Matrix1Row;
    matrix1.columns = Matrix1Column;
    matrix1.data = new int[Matrix1Row * Matrix1Column];
    matrix2.rows = Matrix2Row;
    matrix2.columns = Matrix2Column;
    matrix2.data = new int[Matrix2Row * Matrix2Column];
    matrix3.rows = Matrix1Row;
    matrix3.columns = Matrix2Column;
    matrix3.data = new int[Matrix1Row * Matrix2Column];

    cout << "Enter elements of the first matrix:" << endl;
    for (int i = 0; i < Matrix1Row; i++) {
        for (int j = 0; j < Matrix1Column; j++) {
            cin >> matrix1.data[i * Matrix1Column + j];
        }
    }

    cout << "Enter elements of the second matrix:" << endl;
    for (int i = 0; i < Matrix2Row; i++) {
        for (int j = 0; j < Matrix2Column; j++) {
            cin >> matrix2.data[i * Matrix2Column + j];
        }
    }

    int num_threads = min(Matrix1Row, 4);
    pthread_t threads[num_threads];
    args thread_args[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_args[i].matrix1 = &matrix1;
        thread_args[i].matrix2 = &matrix2;
        thread_args[i].matrix3 = &matrix3;
        thread_args[i].row_index = i;

        pthread_create(&threads[i], NULL, calculate_row, &thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    cout << "Resultant matrix:" << endl;
    for (int i = 0; i < Matrix1Row; i++) {
        for (int j = 0; j < Matrix2Column; j++) {
            cout << matrix3.data[i * Matrix2Column + j] << " ";
        }
        cout << endl;
    }

    delete[] matrix1.data;
    delete[] matrix2.data;
    delete[] matrix3.data;

    return 0;
}
