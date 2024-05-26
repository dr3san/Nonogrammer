#include "wx/wx.h"

class gui : public wxApp {
public:
    virtual bool OnInit();
};

class Nono : public wxFrame {
public:
    Nono();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};