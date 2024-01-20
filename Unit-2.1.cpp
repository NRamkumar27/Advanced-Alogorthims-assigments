#include <iostream>

class SparseMatrix {
private:
    int rows, cols, numNonZero;
    int* rowIndices;
    int* colIndices;
    int* values;

public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols), numNonZero(0) {
        // Assuming a maximum of 100 non-zero elements for simplicity
        rowIndices = new int[100];
        colIndices = new int[100];
        values = new int[100];
    }

    ~SparseMatrix() {
        delete[] rowIndices;
        delete[] colIndices;
        delete[] values;
    }

    void insert(int row, int col, int value) {
        // Only store non-zero elements
        if (value != 0) {
            rowIndices[numNonZero] = row;
            colIndices[numNonZero] = col;
            values[numNonZero] = value;
            numNonZero++;
        }
    }

    int get(int row, int col) const {
        // Check if there is a non-zero element at the given row and column
        for (int i = 0; i < numNonZero; ++i) {
            if (rowIndices[i] == row && colIndices[i] == col) {
                return values[i]; // Return the value
            }
        }
        return 0; // Default value for zero elements
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << get(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows and columns: ";
    std::cin >> rows >> cols;

    SparseMatrix sparseMat(rows, cols);

    std::cout << "Enter non-zero elements (row, column, value) - terminate with (-1, -1, -1):" << std::endl;

    int row, col, value;
    while (true) {
        std::cin >> row;
        if (row == -1) {
            break;
        }
        std::cin >> col >> value;
        sparseMat.insert(row, col, value);
    }

    std::cout << "Sparse Matrix:" << std::endl;
    sparseMat.print();

    return 0;
}
