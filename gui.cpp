// wxWidgets "Hello World" Program
 
#include <wx/wx.h>
#include <vector>
#include "backend.h"
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <string>

using namespace std;

#define ID_CHECK 1001
#define ID_REGEN 1002
 
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};
 
class MyFrame : public wxFrame {
public:
    MyFrame();

    wxGridSizer *m_gridSizer;
    std::vector<std::vector<wxStaticText*>> m_gridCells;

    vector<vector<int>> nonogram = generateNonogram();
    vector<string> hints = formatNonogramInterface(nonogram);
 
private:
    void OnButtonClick(wxCommandEvent& event);
    // void OnButtonRightClick(wxCommandEvent& event);
    void OnCellClick(wxMouseEvent& event);

    void CreateGrid(int rows, int cols);

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Nonogram", wxPoint(30, 30), wxSize(800, 600)) {
    // MENU BAR
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    // LAYOUT

    // Create the grid
    m_gridSizer = new wxFlexGridSizer(6, 6, 3, 3);
    CreateGrid(6, 6);


    // Create a button
    wxButton *check_button = new wxButton(this, ID_CHECK, "Check solution");
    // wxButton *regenerate_button = new wxButton(this, ID_REGEN, "Regenerate puzzle");

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(check_button, 1, wxALL | wxEXPAND, 5);
    // buttonSizer->Add(regenerate_button, 1, wxALL | wxEXPAND, 5);

    // Create the main sizer
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_gridSizer, 1, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    // Set sizer
    SetSizerAndFit(mainSizer);

    // BIND EVENTS
    check_button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    // regenerate_button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
}
 
void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event){
    wxMessageBox("Nonogramm on keeruline m6istatus.", "Nonogrammidest", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnButtonClick(wxCommandEvent& event) {
    // if (event.GetId() == ID_REGEN) {
    //     wxMessageBox("regen");
    // }
    if (event.GetId() == ID_CHECK) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (this->nonogram[i][j] == 1) {
                    if (this->m_gridCells[i+1][j+1]->GetBackgroundColour() == *wxWHITE) {
                        wxMessageBox("Solution is wrong!");
                        return;
                    }
                }
                
                else if (this->nonogram[i][j] == 0) {
                    if (this->m_gridCells[i+1][j+1]->GetBackgroundColour() == *wxBLACK) {
                        wxMessageBox("Solution is wrong!");
                        return;
                    } 
                }
            }
        }            
        wxMessageBox("Solution is correct!");
    }
}

void MyFrame::OnCellClick(wxMouseEvent& event) {
    wxStaticText* cell = dynamic_cast<wxStaticText*>(event.GetEventObject());
    if (cell) {
        if (event.LeftIsDown()) {
            // Toggle cell color
            if (cell->GetBackgroundColour() == *wxWHITE) {
                cell->SetBackgroundColour(*wxBLACK);
            }
            else {
                cell->SetBackgroundColour(*wxWHITE);
            }
            cell->Refresh();
        }
    }
    event.Skip();
}

void MyFrame::CreateGrid(int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        std::vector<wxStaticText*> row;
        for (int j = 0; j < cols; ++j) {
            if (i == 0 && j == 0) {
                wxStaticText* cell = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(20, 20), wxALIGN_BOTTOM);
                row.push_back(cell);
                m_gridSizer->Add(cell, 0, wxEXPAND);
            }
            // COLUMN
            else if (i == 0) {
                wxStaticText* cell = new wxStaticText(this, wxID_ANY, wxString::Format("%c\n%c\n%c", this->hints[4+j][0], this->hints[4+j][1], this->hints[4+j][2]));
                cell->Wrap(-1);
                cell->Fit();
                row.push_back(cell);
                m_gridSizer->Add(cell, 0, wxEXPAND);
            }
            // ROW
            else if (j == 0) {
                wxStaticText* cell = new wxStaticText(this, wxID_ANY, wxString::Format("%c %c %c", this->hints[i-1][0], this->hints[i-1][1], this->hints[i-1][2]));
                cell->Wrap(-1);
                cell->Fit();
                row.push_back(cell);
                m_gridSizer->Add(cell, 0, wxEXPAND);
            }

            else {
                wxStaticText* cell = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(20, 20), wxALIGN_CENTRE);
                cell->SetBackgroundColour(*wxWHITE);
                cell->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnCellClick, this);
                row.push_back(cell);
                m_gridSizer->Add(cell, 0, wxEXPAND);
            }
        }
        m_gridCells.push_back(row);
    }
}

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