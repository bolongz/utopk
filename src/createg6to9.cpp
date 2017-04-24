/*
 * createg6to9.cpp
 *
 *  Created on: Apr 18, 2017
 *      Author: tao
 */
#include "createg6to9.h"
#include "main.h"
#include "dataset.h"
#include "engine.h"
#include "show_list.h"
#include "db.h"
#include "utopk.h"
#include "ukrank.h"
#include "indenputopk.h"
#include "indenpukrank.h"
#include "caller.h"
#include "loadgraph.h"
#include <string>
#include <sstream>
#include <vector>

CreateG6to9::CreateG6to9(const wxString& title)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(550, 450))
{

	wxPanel *panel = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY,
        wxT("  Mean value of 1st dataset(un)'s confidence: "));

    hbox1->Add(st1, 0, wxRIGHT, 61);
    tc1 = new wxTextCtrl(panel, wxID_ANY);
    hbox1->Add(tc1, 1);
    vbox->Add(hbox1, 0, wxLEFT | wxTOP, 10);
    //vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st2 = new wxStaticText(panel, wxID_ANY,
            wxT("  Mean value of 2nd dataset(un)'s confidence: "));

    hbox2->Add(st2, 0, wxRIGHT, 59);
    tc2 = new wxTextCtrl(panel, wxID_ANY);
    hbox2->Add(tc2, 1);
    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);



    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st3 = new wxStaticText(panel, wxID_ANY,
            wxT("  Mean value of 3rd dataset(ue)'s confidence: "));

    hbox3->Add(st3, 0, wxRIGHT, 60);
    tc3 = new wxTextCtrl(panel, wxID_ANY);
    hbox3->Add(tc3, 1);
    vbox->Add(hbox3, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st4 = new wxStaticText(panel, wxID_ANY,
            wxT("  Mean value of 4th dataset(ue)'s confidence: "));

    hbox4->Add(st4, 0, wxRIGHT, 60);
    tc4 = new wxTextCtrl(panel, wxID_ANY);
    hbox4->Add(tc4, 1);
    vbox->Add(hbox4, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st5 = new wxStaticText(panel, wxID_ANY,
           wxT("  The 5th dataset(uu)'s confidence is normally distributed. "));
    hbox5->Add(st5, 0, wxRIGHT, 60);
    vbox->Add(hbox5, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox7 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st7 = new wxStaticText(panel, wxID_ANY,
                wxT("  Input tuple number( > 1000): "));

    hbox7->Add(st7, 0, wxRIGHT, 60);
    tc7 = new wxTextCtrl(panel, wxID_ANY);
    hbox7->Add(tc7, 1);
    vbox->Add(hbox7, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox8 = new wxBoxSizer(wxHORIZONTAL);
    rb1 = new wxRadioButton(panel, -1, wxT("IndeU-Topk/Time "));
    hbox8->Add(rb1);
    rb2 = new wxRadioButton(panel, -1, wxT("IndepeU-kRanks/Time "));
    hbox8->Add(rb2, 0, wxLEFT, 10);
    vbox->Add(hbox8, 0, wxLEFT, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox9 = new wxBoxSizer(wxHORIZONTAL);
    rb3 = new wxRadioButton(panel, -1, wxT("IndeU-Topk/Depth"));
    hbox9->Add(rb3);
    rb4 = new wxRadioButton(panel, -1,wxT("IndepeU-kRanks/Depth "));
    hbox9->Add(rb4, 0, wxLEFT, 10);
    vbox->Add(hbox9, 0, wxLEFT, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *btn1 = new wxButton(panel, ID_6TO9_CREATE, wxT("Create"));
    hbox6->Add(btn1, 0);
    wxButton *btn2 = new wxButton(panel, ID_6TO9_CANCEL, wxT("Cancel"));
    hbox6->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
    vbox->Add(hbox6, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    Connect(ID_6TO9_CREATE, wxEVT_COMMAND_BUTTON_CLICKED,
    		  	wxCommandEventHandler(CreateG6to9::OnCreate));
    Connect(ID_6TO9_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
    		  	wxCommandEventHandler(CreateG6to9::OnCancel));

    panel->SetSizer(vbox);

    Centre();
}

void CreateG6to9::PlotPoly(double cArray[5][15]){
	int M = 5;
	int N = 15;

	Engine *ep;
	if (!(ep=engOpen("\0"))) {//if start successfully, the pointer ep will not be NULL.
		std::cout<< "Can't start MATLAB engine!"<<std::endl;
		return;
	}

	//define mxArray，as array of N rows, M columns (reverse of C array)
	mxArray *xx = mxCreateDoubleMatrix(N, M, mxREAL);
	//copy cArray value into mxArray
	memcpy(mxGetPr(xx), cArray, M*N*sizeof(double));
	//write into MATLAB's work space
	engPutVariable(ep, "input_data", xx);
	// call MATLAB function "plot_mono"
	engEvalString(ep, "RESULT=plot_poly(input_data);"); // 1. the computation result is set to RESULT
	//mxArray *result = engGetVariable(ep, "RESULT");  // 2. get the result

	//release memory
	mxDestroyArray(xx);
	//mxDestroyArray(result);
	engClose(ep); //close MATLAB engine
}

void CreateG6to9::OnCreate(wxCommandEvent& WXUNUSED(event)){
	std::vector<double> mean_values;
	wxString mean1 = tc1->GetValue();
	wxString mean2 = tc2->GetValue();
	wxString mean3 = tc3->GetValue();
	wxString mean4 = tc4->GetValue();
	wxString tup_num = tc7->GetValue();
	long tup_num_value;
	tup_num.ToLong(&tup_num_value);
	double mean_value;
	mean1.ToDouble(&mean_value);
	mean_values.push_back(mean_value);
	mean2.ToDouble(&mean_value);
	mean_values.push_back(mean_value);
	mean3.ToDouble(&mean_value);
	mean_values.push_back(mean_value);
	mean4.ToDouble(&mean_value);
	mean_values.push_back(mean_value);
	if (rb1->GetValue()){
		u_semantics = 0;
		y_axis = 0;
	}
	else if (rb2->GetValue()){
		u_semantics = 1;
		y_axis = 0;
	}
	else if (rb3->GetValue()){
		u_semantics = 0;
		y_axis = 1;
	}
	else if (rb4->GetValue()){
		u_semantics = 1;
		y_axis = 1;
	}
	int k_values[4] = {1,10,100,1000};

	/*Generate time/depth pairs of distribution: un/un/ue/ue/uu respectively,
	 * using k vale of 1/10/100/1000
	 */
	independent = 1;
	for (int i = 0; i < 5; i++){

		/*----------------------------generate dataset---------------------*/
		Dataset ds;
		if (i < 4){
			ds.set_mean(mean_values[i]);
		}
		std::cout << "g_mean: " << g_mean << std::endl;
		ds.set_corr_coeff(0);		//fig 6 to 9, rho = 0
		if (i == 4){
				ds.set_confi_distr(1);
		}
		else if ((i == 0) || (i == 1)){
				ds.set_confi_distr(2);
		}
		else {
			ds.set_confi_distr(3);
		}
		ds.generate_dataset(wxAtoi(tup_num));
		ds.get_dataset_value(current_dataset);

		/*-----put dataset into MYSQL, get score-randed data------------------*/
		Db db;
		db.dataset_into_mysql(current_dataset);
		db.get_score_ranked_data(ranked_dataset);

		/*-------------launch corresponding algorithm------------------------*/
		Launch::Source source;
		Launch::Rules r;
		Caller caller;
		caller.db_to_source(ranked_dataset, source);
		caller.start(source, r);
		current_result.clear();
		if (u_semantics == 0){
			for (int j = 0; j < 4; j++){
				caller.processing_indenputopk(k_values[j], current_result);
				Time_depth[i][j*2] = caller.run_time();
				Time_depth[i][j*2 + 1] = caller.scan_depth();
			}
		}
		else if (u_semantics == 1){
			for (int j = 0; j < 4; j++){
				caller.processing_indenpukrank(k_values[j], current_result);
				Time_depth[i][j*2] = caller.run_time();
				Time_depth[i][j*2 + 1] = caller.scan_depth();
			}
		}
		Time_depth[i][10] = y_axis;
		Time_depth[i][11] = g_confi_distr;
		Time_depth[i][12] = g_mean;
		Time_depth[i][13] = (int) tup_num_value;
		Time_depth[i][14] = u_semantics;
		std::cout << "mean value: " << Time_depth[i][12] << std::endl;
	}

	PlotPoly(Time_depth);

	graph_seq = 1;

	wxString mystring(wxT("Created Comparison Graph"));
	LoadGraph *la = new LoadGraph(mystring);
	la->Show(true);
	Close(true);
}

void CreateG6to9::OnCancel(wxCommandEvent& WXUNUSED(event)){
	Close(true);
}





