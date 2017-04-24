/*
 * check_dependant.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */
#include "check_dependent.h"
#include "main.h"
#include "Dialog_de.h"
#include "Dialog_Inde.h"

CheckBox::CheckBox(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
	wxPanel *panel = new wxPanel(this, wxID_ANY);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

    wxPanel *hbox1_panel = new wxPanel(panel, -1);
    hbox1->Add(hbox1_panel);
    vbox->Add(hbox1, 1, wxEXPAND);

    if (independent == 1){
    	m_cb = new wxCheckBox(hbox1_panel, ID_CHECKBOX, wxT("Independent"),
                            wxPoint(20, 20));
    	this->SetTitle(wxT("Independent"));
    	m_cb->SetValue(true);
    }
    else{
    	m_cb = new wxCheckBox(hbox1_panel, ID_CHECKBOX, wxT("Independent"),
    	                    wxPoint(20, 20));
    	this->SetTitle(wxT("Dependent"));
    	m_cb->SetValue(false);
    }
    Connect(ID_CHECKBOX, wxEVT_COMMAND_CHECKBOX_CLICKED,
              wxCommandEventHandler(CheckBox::OnToggle));

    //wxPanel *hbox2_panel = new wxPanel(panel, -1);
    wxButton *ok = new wxButton(panel, ID_DEPENDANT_OK, wxT("Ok"));
    wxButton *cancel = new wxButton(panel, ID_DEPENDANT_CANCEL, wxT("Cancel"));
    Connect(ID_DEPENDANT_OK, wxEVT_COMMAND_BUTTON_CLICKED,
                  wxCommandEventHandler(CheckBox::OnOk));
    Connect(ID_DEPENDANT_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
                      wxCommandEventHandler(CheckBox::OnCancel));
    //hbox2->Add(hbox2_panel);
    hbox2->Add(ok);
    hbox2->Add(cancel);

    vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
    panel->SetSizer(vbox);

/*
  m_cb = new wxCheckBox(panel, ID_CHECKBOX, wxT("Independant"),
                        wxPoint(20, 20));
  m_cb->SetValue(true);
  Connect(ID_CHECKBOX, wxEVT_COMMAND_CHECKBOX_CLICKED,
          wxCommandEventHandler(CheckBox::OnToggle));
*/
  Centre();
}

void CheckBox::OnToggle(wxCommandEvent& WXUNUSED(event))
{

  if (m_cb->GetValue()) {
      this->SetTitle(wxT("Independent"));
      independent = 1;
  } else {
      this->SetTitle(wxT("Dependent"));
      independent = 0;
  }
}

void CheckBox::OnOk(wxCommandEvent& WXUNUSED(event)){
	if (independent == 0){
		De *de = new De(wxT("Set Dependent Tuples' Parameters"));
		de->Show(true);
	}
	else{
		Inde *ie = new Inde(wxT("Set Independent Tuples' Parameters"));
		ie->Show(true);
	}
	Close(true);
}

void CheckBox::OnCancel(wxCommandEvent& WXUNUSED(event)){
	Close(true);
}

