// wxWidgets "Hello World" Program
 
#include <wx/wx.h>
#include <vector>

#define ID_CHECK 1001
#define ID_REGEN 1002
 
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
 
class MyFrame : public wxFrame
{
public:
    MyFrame();

    wxGridSizer *m_gridSizer;
    std::vector<std::vector<wxStaticText*>> m_gridCells;
 
private:
    void OnButtonClick(wxCommandEvent& event);
    // void OnButtonRightClick(wxCommandEvent& event);
    void OnCellClick(wxMouseEvent& event);

    void CreateGrid(int rows, int cols);


    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
 
wxIMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Nonogram", wxPoint(30, 30), wxSize(800, 600))
{
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
    wxButton *regenerate_button = new wxButton(this, ID_REGEN, "Regenerate puzzle");

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(check_button, 1, wxALL | wxEXPAND, 5);
    buttonSizer->Add(regenerate_button, 1, wxALL | wxEXPAND, 5);

    // Create the main sizer
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(m_gridSizer, 1, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);

    // Set sizer
    SetSizerAndFit(mainSizer);

    // BIND EVENTS
    check_button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    regenerate_button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
}
 
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnButtonClick(wxCommandEvent& event)
{
    if (event.GetId() == ID_REGEN) {
        wxMessageBox("regen");
    }
    if (event.GetId() == ID_CHECK) {
        wxMessageBox("check");
    }
}

// void MyFrame::OnButtonRightClick(wxCommandEvent& event)
// {
//     wxMessageBox("Button R clicked!");
// }

void MyFrame::OnCellClick(wxMouseEvent& event)
    {
        wxStaticText* cell = dynamic_cast<wxStaticText*>(event.GetEventObject());
        if (cell)
        {
            if (event.LeftIsDown())
            {
                // Toggle cell color
                if (cell->GetBackgroundColour() == *wxWHITE)
                    cell->SetBackgroundColour(*wxBLACK);
                else
                    cell->SetBackgroundColour(*wxWHITE);
                cell->Refresh();
            }
        }
        event.Skip();
    }

void MyFrame::CreateGrid(int rows, int cols)
    {
        for (int i = 0; i < rows; ++i)
        {
            std::vector<wxStaticText*> row;
            for (int j = 0; j < cols; ++j)
            {
                if (i == 0 && j == 0) {
                    wxStaticText* cell = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(20, 20), wxALIGN_BOTTOM);
                    row.push_back(cell);
                    m_gridSizer->Add(cell, 0, wxEXPAND);
                }
                else if (i == 0) {
                    wxStaticText* cell = new wxStaticText(this, wxID_ANY, wxString::Format("%s\n%s", std::to_string(i), std::to_string(j)));
                    cell->Wrap(-1);
                    cell->Fit();
                    row.push_back(cell);
                    m_gridSizer->Add(cell, 0, wxEXPAND);
                }

                else if (j == 0) {
                    wxStaticText* cell = new wxStaticText(this, wxID_ANY, wxString::Format("%d %d", i, j));
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