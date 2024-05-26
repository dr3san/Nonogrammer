#include "backend.h"
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

// Generates a random 5x5 nonogram using a vector, 0 being empty, 1 being full
vector<vector<int>> generateNonogram() {
    // Define the nonogram as 5x5
    int cols = 5;
    int rows = 5;
    // Create a vector of a vector as a data structure for the nonogram
    vector<vector<int>> matrix(rows, vector<int>(cols));
    random_device rd;
    mt19937 gen(rd());
    // Fill all the boxes in the nonogram randomly with either a 0 or 1
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uniform_int_distribution<int> dis(0, 1);
            matrix[i][j] = dis(gen);
        }
    }
    // Print the matrix for debugging purposes
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == cols - 1) {
                cout << matrix[i][j] << '\n';
            } else {
                cout << matrix[i][j];
            }
        }
    }
    return matrix;
}

// Make a user interface for the nonogram
void formatNonogramInterface(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // First, create row hints
    vector<vector<int>> rowHints(rows);
    for (int i = 0; i < rows; i++) {
        int counter = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                counter++;
                if (j == cols - 1 || matrix[i][j + 1] == 0) {
                    rowHints[i].push_back(counter);
                    counter = 0;
                }
            }
        }
    }

    // Create column hints
    vector<vector<int>> colHints(cols);
    for (int j = 0; j < cols; j++) {
        int counter = 0;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 1) {
                counter++;
                if (i == rows - 1 || matrix[i + 1][j] == 0) {
                    colHints[j].push_back(counter);
                    counter = 0;
                }
            }
        }
    }

    // Determine the maximum number of hints for rows and columns to format properly
    int maxRowHints = 0;
    int maxColHints = 0;
    for (const auto& hints : rowHints) {
        maxRowHints = max(maxRowHints, (int)hints.size());
    }
    for (const auto& hints : colHints) {
        maxColHints = max(maxColHints, (int)hints.size());
    }

    // Print the column hints
    for (int hintRow = 0; hintRow < maxColHints; hintRow++) {
        // Print spacing for row hints
        for (int i = 0; i < maxRowHints; i++) {
            cout << "   ";
        }
        for (int j = 0; j < cols; j++) {
            if (hintRow < colHints[j].size()) {
                cout << setw(3) << colHints[j][hintRow];
            } else {
                cout << "   ";
            }
        }
        cout << '\n';
    }

    // Print the row hints and the nonogram matrix
    for (int i = 0; i < rows; i++) {
        // Print row hints
        for (int hintIdx = 0; hintIdx < maxRowHints; hintIdx++) {
            if (hintIdx < rowHints[i].size()) {
                cout << setw(3) << rowHints[i][hintIdx];
            } else {
                cout << "   ";
            }
        }
        // Print the matrix row
        for (int j = 0; j < cols; j++) {
            cout << setw(3) << (matrix[i][j] == 1 ? "X" : ".");
        }
        cout << '\n';
    }
}

int main() {
    vector<vector<int>> matrix = generateNonogram();
    formatNonogramInterface(matrix);
    return 0;
}
