/*
 * Dialog_Inde.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */
#include "Dialog_Inde.h"
#include "main.h"
#include "dataset.h"

Inde::Inde(const wxString& title)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(600, 300))
{

	wxPanel *panel = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY,
        wxT("Tuple numbers: "));

    hbox1->Add(st1, 0, wxRIGHT, 62);
    tc1 = new wxTextCtrl(panel, wxID_ANY);
    hbox1->Add(tc1, 1);
    vbox->Add(hbox1, 0, wxLEFT | wxTOP, 10);
    //vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    vbox->Add(-1, 10);


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
          wxT("If score and confidence are un-correlated, confidence is: "));

    hbox4->Add(st4, 0);
    vbox->Add(hbox4, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    rb1 = new wxRadioButton(panel, -1,
            wxT("uniformly distributed"));
    hbox5->Add(rb1);
    rb2 = new wxRadioButton(panel, -1,
              wxT("normally distributed"));

    hbox5->Add(rb2, 0, wxLEFT, 10);
    rb3 = new wxRadioButton(panel, -1,
              wxT("exponetially distributed"));

    hbox5->Add(rb3, 0, wxLEFT, 10);
    vbox->Add(hbox5, 0, wxLEFT, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st2 = new wxStaticText(panel, wxID_ANY,
            wxT("mean value: "));

    hbox2->Add(st2, 0, wxRIGHT, 84);
    tc2 = new wxTextCtrl(panel, wxID_ANY);
    hbox2->Add(tc2, 1);
    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 20);


    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *btn1 = new wxButton(panel, ID_INDE_CREATE, wxT("Create"));
    hbox6->Add(btn1, 0);
    wxButton *btn2 = new wxButton(panel, ID_INDE_CANCEL, wxT("Cancel"));
    hbox6->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
    vbox->Add(hbox6, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    Connect(ID_INDE_CREATE, wxEVT_COMMAND_BUTTON_CLICKED,
    		  wxCommandEventHandler(Inde::OnCreate));
    Connect(ID_INDE_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
    		  wxCommandEventHandler(Inde::OnCancel));

    panel->SetSizer(vbox);

    Centre();
}

void Inde::OnCreate(wxCommandEvent& WXUNUSED(event)){
	wxString num_tuples = tc1->GetValue();
	wxString mean_value = tc2->GetValue();
	wxString co_eff = tc3->GetValue();
	Dataset ds;
	//ds.set_independent_value(true);
	double m_value;
	mean_value.ToDouble(&m_value);
	ds.set_mean(m_value);
	double c_value;
	co_eff.ToDouble(&c_value);
	ds.set_corr_coeff(c_value);

	if (rb1->GetValue()){
		ds.set_confi_distr(1);
	}
	else if (rb2->GetValue()){
		ds.set_confi_distr(2);
	}
	else {
		ds.set_confi_distr(3);
	}
	ds.generate_dataset(wxAtoi(num_tuples));
	ds.get_dataset_value(current_dataset);

	//put dataset function here
	//wxString mystring = wxString::Format(wxT("%i"),gen_rule);
	wxString mystring = wxT("Dataset created.");
	wxMessageBox(wxString(mystring));
	Close(true);
}

void Inde::OnCancel(wxCommandEvent& WXUNUSED(event)){

	Close(true);
}



