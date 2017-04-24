/*
 * Dialog_de.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */
#include "Dialog_de.h"
#include "main.h"
#include "dataset.h"
#include "show_list.h"


De::De(const wxString& title)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(350, 250))
{

	wxPanel *panel = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY,
      wxT("Tuple numbers: "));

	hbox1->Add(st1, 0, wxRIGHT, 60);
	tc1 = new wxTextCtrl(panel, wxID_ANY);
	hbox1->Add(tc1, 1);
	vbox->Add(hbox1, 0, wxLEFT | wxTOP, 10);
	//vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	//wxString str = tc1->GetValue();
	//wxMessageBox(str);

	vbox->Add(-1, 10);
/*
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *st2 = new wxStaticText(panel, wxID_ANY,
      wxT("   Value of k: "));

	hbox2->Add(st2, 0, wxRIGHT, 84);
	tc2 = new wxTextCtrl(panel, wxID_ANY);
	hbox2->Add(tc2, 1);
	vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);

	vbox->Add(-1, 10);
*/
	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText *st3 = new wxStaticText(panel, wxID_ANY,
        wxT("Correlation coefficient: "));

	hbox3->Add(st3, 0, wxRIGHT, 10);
    tc3 = new wxTextCtrl(panel, wxID_ANY);
    hbox3->Add(tc3, 1);
    vbox->Add(hbox3, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st4 = new wxStaticText(panel, wxID_ANY,
        wxT("Generation Rules -- exclusive rules:"));

    hbox4->Add(st4, 0);
    vbox->Add(hbox4, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    rb1 = new wxRadioButton(panel, -1,
        wxT("XOR 2"));
    hbox5->Add(rb1);
    rb2 = new wxRadioButton(panel, -1,
          wxT("XOR 4"));

    hbox5->Add(rb2, 0, wxLEFT, 10);
    rb3 = new wxRadioButton(panel, -1,
          wxT("XOR 8"));

    hbox5->Add(rb3, 0, wxLEFT, 10);
    vbox->Add(hbox5, 0, wxLEFT, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *btn1 = new wxButton(panel, ID_DE_CREATE, wxT("Create"));
    hbox6->Add(btn1, 0);
    wxButton *btn2 = new wxButton(panel, ID_DE_CANCEL, wxT("Cancel"));
    hbox6->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
    vbox->Add(hbox6, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    Connect(ID_DE_CREATE, wxEVT_COMMAND_BUTTON_CLICKED,
		  wxCommandEventHandler(De::OnCreate));
    Connect(ID_DE_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
		  wxCommandEventHandler(De::OnCancel));

    panel->SetSizer(vbox);

    Centre();
}

void De::OnCreate(wxCommandEvent& WXUNUSED(event)){
	Dataset ds;
	//ds.set_independent_value(false);
	wxString num_tuples = tc1->GetValue();
	//wxString str_k = tc2->GetValue();
	wxString co_eff = tc3->GetValue();
	double c_value;
	co_eff.ToDouble(&c_value);
	ds.set_corr_coeff(c_value);

	if (rb1->GetValue()){
		ds.set_gen_rule(2);
	}
	else if (rb2->GetValue()){
		ds.set_gen_rule(4);
	}
	else {
		ds.set_gen_rule(8);
	}

	ds.generate_dataset(wxAtoi(num_tuples));
	ds.get_dataset_value(current_dataset);

	//put dataset function here
	//wxString mystring = wxString::Format(wxT("%i"),gen_rule);
	wxString mystring = wxT("Dataset created.");
	wxMessageBox(wxString(mystring));
	Close(true);
}

void De::OnCancel(wxCommandEvent& WXUNUSED(event)){

	Close(true);
}
