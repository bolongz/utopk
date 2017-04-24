/*
 * query.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: tao
 */
#include "query.h"
#include "main.h"
#include "show_list.h"
#include "db.h"
#include "utopk.h"
#include "ukrank.h"
#include "indenputopk.h"
#include "indenpukrank.h"
#include "caller.h"
#include <string>
#include <sstream>
#include <vector>


Query::Query(const wxString& title)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 200))
{

	wxPanel *panel = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY,
        wxT("k value: "));

    hbox1->Add(st1, 0, wxRIGHT, 62);
    tc1 = new wxTextCtrl(panel, wxID_ANY);
    hbox1->Add(tc1, 1);
    vbox->Add(hbox1, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    rb1 = new wxRadioButton(panel, -1,
                wxT("IndepU-Topk/OPTU-Topk"));
    hbox2->Add(rb1);
    rb2 = new wxRadioButton(panel, -1,
                wxT("IndepU-kRanks/OPTU-kRanks"));
    hbox2->Add(rb2, 0, wxLEFT, 10);
    vbox->Add(hbox2, 0, wxLEFT, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *btn1 = new wxButton(panel, ID_QUERY_OK, wxT("OK"));
    hbox3->Add(btn1, 0);
    wxButton *btn2 = new wxButton(panel, ID_QUERY_CANCEL, wxT("Cancel"));
    hbox3->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
    vbox->Add(hbox3, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    Connect(ID_QUERY_OK, wxEVT_COMMAND_BUTTON_CLICKED,
    		  wxCommandEventHandler(Query::OnOk));
    Connect(ID_QUERY_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
    		  wxCommandEventHandler(Query::OnCancel));

    panel->SetSizer(vbox);

    Centre();
}

void Query::OnOk(wxCommandEvent& WXUNUSED(event)){
	wxString k_str = tc1->GetValue();

	long k_value;
	k_str.ToLong(&k_value);

	Launch::Source source;
	Launch::Rules r;
	Caller caller;
	double process_time;
	int process_depth;

	Db db;
	if (!db.get_score_ranked_data(ranked_dataset)){
		wxString mystring = wxT("Get Score-randed Dataset failed.");
		wxMessageBox(wxString(mystring));
	}

	caller.db_to_source(ranked_dataset, source);
	caller.start(source, r);
	current_result.clear();

	if (independent == 1){
		if (rb1->GetValue()){
			caller.processing_indenputopk((int) k_value, current_result);
		}
		else if (rb2->GetValue()){
			caller.processing_indenpukrank((int) k_value, current_result);
		}
	}
	else if (independent == 0){
		if (rb1->GetValue()){
			caller.processing_utopk((int) k_value, current_result);
		}
		else if (rb2->GetValue()){
			caller.processing_ukrank((int) k_value, current_result);
		}
	}
	process_time = caller.run_time();
	process_depth = caller.scan_depth();

	std::string str_title;
	str_title = "Time: " + std::to_string(process_time) + "   Depth: "
			+ std::to_string(process_depth);
	wxString mystring(str_title);

	Show_list *sl = new Show_list(mystring,current_result);
	sl->Show(true);

	Close(true);
}

void Query::OnCancel(wxCommandEvent& WXUNUSED(event)){

	Close(true);
}





