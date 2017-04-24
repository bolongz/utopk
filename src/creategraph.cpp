/*
 * creategraph.cpp
 *
 *  Created on: Apr 17, 2017
 *      Author: tao
 */
#include "creategraph.h"
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

CreateGraph::CreateGraph(const wxString& title)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(500, 300))
{

	wxPanel *panel = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY,
        wxT("  k value of 1st samples: "));

    hbox1->Add(st1, 0, wxRIGHT, 61);
    tc1 = new wxTextCtrl(panel, wxID_ANY);
    hbox1->Add(tc1, 1);
    vbox->Add(hbox1, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st2 = new wxStaticText(panel, wxID_ANY,
            wxT("  k value of 2nd samples: "));

    hbox2->Add(st2, 0, wxRIGHT, 59);
    tc2 = new wxTextCtrl(panel, wxID_ANY);
    hbox2->Add(tc2, 1);
    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);



    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st3 = new wxStaticText(panel, wxID_ANY,
            wxT("  k value of 3rd samples: "));

    hbox3->Add(st3, 0, wxRIGHT, 60);
    tc3 = new wxTextCtrl(panel, wxID_ANY);
    hbox3->Add(tc3, 1);
    vbox->Add(hbox3, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st4 = new wxStaticText(panel, wxID_ANY,
            wxT("  k value of 4th samples: "));

    hbox4->Add(st4, 0, wxRIGHT, 60);
    tc4 = new wxTextCtrl(panel, wxID_ANY);
    hbox4->Add(tc4, 1);
    vbox->Add(hbox4, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    rb1 = new wxRadioButton(panel, -1,
                wxT("IndepU-Topk/OPTU-Topk"));
    hbox5->Add(rb1);
    rb2 = new wxRadioButton(panel, -1,
                wxT("IndepU-kRanks/OPTU-kRanks"));
    hbox5->Add(rb2, 0, wxLEFT, 10);
    vbox->Add(hbox5, 0, wxLEFT, 10);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox6 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *btn1 = new wxButton(panel, ID_CG_CREATE, wxT("Create"));
    hbox6->Add(btn1, 0);
    wxButton *btn2 = new wxButton(panel, ID_CG_CANCEL, wxT("Cancel"));
    hbox6->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
    vbox->Add(hbox6, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    Connect(ID_CG_CREATE, wxEVT_COMMAND_BUTTON_CLICKED,
    		  	wxCommandEventHandler(CreateGraph::OnCreate));
    Connect(ID_CG_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED,
    		  	wxCommandEventHandler(CreateGraph::OnCancel));

    panel->SetSizer(vbox);

    Centre();
}

void CreateGraph::PlotMono(std::vector<std::vector<double>> v){
	if (v.size() == 0){
		std::cout << "Nothing to plot.\n";
		exit(0);
	}
	int M = v.size() + 2;	//the first 2 rows used for extra information
	int N = 2;				//time or depth, only one needed.

	Engine *ep;
	if (!(ep=engOpen("\0"))) {//if start successfully, the pointer ep will not be NULL.
		std::cout<< "Can't start MATLAB engine!"<<std::endl;
		return;
	}
	// define 2-D array
	double cArray[M][N];

	cArray[0][0] = y_axis;			//time or depth
	cArray[0][1] = g_confi_distr; 	//distribution, 1: uniform 2: normal 3: exponential
	if (g_confi_distr != 1){
		cArray[1][0] = g_mean;		//mean value
	}
	cArray[1][1] = u_semantics;

	for (unsigned int i= 0; i < v.size(); i++){
		cArray[i+2][0] = v[i][0];
		if (y_axis == 0){
			cArray[i+2][1] = v[i][1];	//time
		}
		else {
			cArray[i+2][1] = v[i][2];	//depth
		}
	}

	//define mxArray，as array of N rows, M columns (reverse of C array)
	mxArray *xx = mxCreateDoubleMatrix(N, M, mxREAL);
	//copy cArray value into mxArray
	memcpy(mxGetPr(xx), cArray, M*N*sizeof(double));
	//write into MATLAB's work space
	engPutVariable(ep, "input_data", xx);
	// call MATLAB function "plot_mono"
	engEvalString(ep, "RESULT=plot_mono(input_data);"); // 1. the computation result is set to RESULT
	//mxArray *result = engGetVariable(ep, "RESULT");  // 2. get the result

	//release memory
	mxDestroyArray(xx);
	//mxDestroyArray(result);
	engClose(ep); //close MATLAB engine
}

void CreateGraph::OnCreate(wxCommandEvent& WXUNUSED(event)){
	std::vector<int> k_values;
	wxString k1 = tc1->GetValue();
	wxString k2 = tc2->GetValue();
	wxString k3 = tc3->GetValue();
	wxString k4 = tc4->GetValue();
	long k_value;
	k1.ToLong(&k_value);
	k_values.push_back((int) k_value);
	k2.ToLong(&k_value);
	k_values.push_back((int) k_value);
	k3.ToLong(&k_value);
	k_values.push_back((int) k_value);
	k4.ToLong(&k_value);
	k_values.push_back((int) k_value);

	Launch::Source source;
	Launch::Rules r;
	Caller caller;

	Db db;
	db.get_score_ranked_data(ranked_dataset);

	caller.db_to_source(ranked_dataset, source);
	caller.start(source, r);
	current_result.clear();
	mono_data.clear();

	if (independent == 1){
		if (rb1->GetValue()){
			for (int i = 0; i < 4; i++){
				caller.processing_indenputopk(k_values[i], current_result);
				std::vector<double> v_temp;
				v_temp.push_back(k_values[i]);
				v_temp.push_back(caller.run_time());
				v_temp.push_back(caller.scan_depth());
				mono_data.push_back(v_temp);
			}
			u_semantics = 0;
		}
		else if (rb2->GetValue()){
			for (int i = 0; i < 4; i++){
				caller.processing_indenpukrank(k_values[i], current_result);
				std::vector<double> v_temp;
				v_temp.push_back(k_values[i]);
				v_temp.push_back(caller.run_time());
				v_temp.push_back(caller.scan_depth());
				mono_data.push_back(v_temp);
			}
			u_semantics = 1;
		}
	}
	else if (independent == 0){
		if (rb1->GetValue()){
			for (int i = 0; i < 4; i++){
				caller.processing_utopk(k_values[i], current_result);
				std::vector<double> v_temp;
				v_temp.push_back(k_values[i]);
				v_temp.push_back(caller.run_time());
				v_temp.push_back(caller.scan_depth());
				mono_data.push_back(v_temp);
			}
			u_semantics = 0;
		}
		else if (rb2->GetValue()){
			for (int i = 0; i < 4; i++){
				caller.processing_ukrank(k_values[i], current_result);
				std::vector<double> v_temp;
				v_temp.push_back(k_values[i]);
				v_temp.push_back(caller.run_time());
				v_temp.push_back(caller.scan_depth());
				mono_data.push_back(v_temp);
			}
			u_semantics = 1;
		}
	}

	PlotMono(mono_data);

	graph_seq = 0;
	std::stringstream ss_cor, ss_tuple;
	std::string s_title, s_dis, s_cor, s_tuple;
	ss_tuple << g_tuple_num;
	ss_tuple >> s_tuple;
	ss_cor << g_corr_coeff;
	ss_cor >> s_cor;
	if (g_confi_distr == 1){
		s_dis = "Uniform/Uniform";
	}
	else if (g_confi_distr == 2){
		s_dis = "Uniform/Normal";
	}
	else if (g_confi_distr == 3){
		s_dis = "Uniform/Exponential";
	}

	if (independent == 0){
		s_title = "Mutual Exclusive Dataset, Score/Conf Distribution: Uniform/Uniform, ";
	}
	else {
		s_title = "Independent dataset, Score/Conf Distribution: " + s_dis;
		if (g_confi_distr != 1){
			std::stringstream ss_mean;
			std::string s_mean;
			ss_mean << g_mean;
			ss_mean >> s_mean;
			s_title = s_title + "(mean: " + s_mean + ")";
		}
	}

	s_title = s_title + ", correlation: " + s_cor + ", tuple numbers: " + s_tuple;

	wxString mystring(s_title);
	LoadGraph *la = new LoadGraph(mystring);
	la->Show(true);
	Close(true);
}

void CreateGraph::OnCancel(wxCommandEvent& WXUNUSED(event)){
	Close(true);
}



