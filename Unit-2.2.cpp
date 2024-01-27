#include <iostream>

class Node {
public:
    int row, col, value;
    Node* next;

    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    int rows, cols;
    Node** rowsArray;

public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols) {
        rowsArray = new Node*[rows];
        for (int i = 0; i < rows; ++i) {
            rowsArray[i] = nullptr;
        }
    }

    ~SparseMatrix() {
        for (int i = 0; i < rows; ++i) {
            Node* current = rowsArray[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] rowsArray;
    }

    void insert(int row, int col, int value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cout << "Invalid row or column index." << std::endl;
            return;
        }

        Node* newNode = new Node(row, col, value);
        newNode->next = rowsArray[row];
        rowsArray[row] = newNode;
    }

    void printLinkedList() const {
        std::cout << "\nLinked List Representation:\n";
        for (int i = 0; i < rows; ++i) {
            Node* current = rowsArray[i];
            while (current) {
                std::cout << "(" << current->row << ", " << current->col << ", " << current->value << ") -> ";
                current = current->next;
            }
            std::cout << "nullptr\n";
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
        std::cin >> row >> col >> value;
        if (row == -1 || col == -1 || value == -1) {
            break;
        }
        sparseMat.insert(row, col, value);
    }

    sparseMat.printLinkedList();

    return 0;
}
