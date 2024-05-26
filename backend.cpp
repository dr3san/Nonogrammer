#include "backend.h"
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <string>

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

// Format the nonogram hints and return the hints data structure
vector<string> formatNonogramInterface(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // First, create row hints
    vector<string> hints(10, "   "); // Initialize with empty strings
    for (int i = 0; i < rows; i++) {
        string rowHint = "";
        int counter = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                counter++;
                if (j == cols - 1 || matrix[i][j + 1] == 0) {
                    rowHint += to_string(counter);
                    counter = 0;
                }
            }
        }
        // Ensure the row hint is exactly 3 characters long
        while (rowHint.length() < 3) {
            rowHint = " " + rowHint;
        }
        hints[i] = rowHint.substr(0, 3);
    }

    // Create column hints
    for (int j = 0; j < cols; j++) {
        string colHint = "";
        int counter = 0;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 1) {
                counter++;
                if (i == rows - 1 || matrix[i + 1][j] == 0) {
                    colHint += to_string(counter);
                    counter = 0;
                }
            }
        }
        // Ensure the column hint is exactly 3 characters long
        while (colHint.length() < 3) {
            colHint = " " + colHint;
        }
        hints[5 + j] = colHint.substr(0, 3);
    }

    // Print the hints for debugging purposes
    cout << "\nFormatted Nonogram Hints:\n";
    cout << "Row Hints:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Row " << i + 1 << ": " << hints[i] << '\n';
    }

    cout << "Column Hints:\n";
    for (int i = 5; i < 10; i++) {
        cout << "Column " << i - 4 << ": " << hints[i] << '\n';
    }

    return hints;
}

int main() {
    vector<vector<int>> matrix = generateNonogram();
    vector<string> hints = formatNonogramInterface(matrix);

    // Print the nonogram matrix with hints
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Determine the maximum number of hints for rows and columns to format properly
    int maxRowHints = 3;
    int maxColHints = 3;

    // Print the column hints
    for (int hintRow = 0; hintRow < maxColHints; hintRow++) {
        // Print spacing for row hints
        for (int i = 0; i < maxRowHints; i++) {
            cout << "   ";
        }
        for (int j = 0; j < cols; j++) {
            if (hintRow < hints[5 + j].length()) {
                cout << setw(3) << hints[5 + j][hintRow];
            } else {
                cout << "   ";
            }
        }
        cout << '\n';
    }

    // Print the row hints and the nonogram matrix
    for (int i = 0; i < rows; i++) {
        // Print row hints
        cout << setw(3) << hints[i];
        // Print the matrix row
        for (int j = 0; j < cols; j++) {
            cout << setw(3) << (matrix[i][j] == 1 ? "X" : ".");
        }
        cout << '\n';
    }

    return 0;
}
