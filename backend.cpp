#include "backend.h"

using namespace std;

// Generates a random 5x5 nonogramm using a vector, 0 being empty, 1 being full
vector<vector<int>> generateNonogram() {
    //Define the nonogram as 5x5
    int cols = 5;
    int rows = 5;
    //Create a vector of a vector as a data structure for the nonogram
    vector<vector<int>> matrix(rows, vector<int>(cols));
    random_device rd;
    mt19937 gen(rd());
    int i = 0;
    //Fill all the boxes in the nonogramm randomly with either a 0 or 1
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uniform_int_distribution<int> dis (0, 1);
            int random_number = dis(gen);
            matrix[i][j] = random_number;
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j == 4) {
                cout << matrix[i][j] << '\n';
            }
            else {
                cout << matrix[i][j];
            }
        }
    }   
    return matrix;
}

//Make a user interface for the nonogram
void formatNonogramInterface(const vector<vector<int>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    //Display rows
    cout << "Rows:" << '\n';
    for (int i = 0; i < rows; i++) {
        int counter = 0;
        for (int j = 0; j < cols; j++) {
            //Check if current cell is 1
            if (matrix[i][j] == 1) {
                counter ++;
                //Check if next cell is also 1
                while (j + 1 < cols && matrix[i][j + 1] == 1) {
                    counter += 1;
                    j++; //Move to the next cell
                }
                cout << counter << " ";
                counter = 0; //Reset counter
            }
        }
        cout << '\n';
    }

    // Display columns
    int w = 0;
    cout << setw(w) << "Columns:" << '\n';
    for (int j = 0; j < cols; j++) {
        int counter = 0;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 1) {
                counter++;
                while (i + 1 < rows && matrix[i + 1][j] == 1) {
                    counter++;
                    i++;
                }
                cout << counter;
                if (i + 1 < rows && matrix[i + 1][j] != 1) {
                    cout << setw(w) << '\n';
                }
                counter = 0;
            }
        }
        if (j + 1 < cols) {
            w += 1;
        }
    }

}




int main () {
    vector<vector<int>> matrix = generateNonogram();
    formatNonogramInterface(matrix);
    return 0;
}