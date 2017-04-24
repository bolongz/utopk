/*
 * menu.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */
#include "menu.h"
#include "main.h"
#include "check_dependent.h"
#include "Dialog_de.h"
#include "Dialog_Inde.h"
#include "show_list.h"
#include "dataset.h"
#include "db.h"
#include "query.h"
#include "loadgraph.h"
#include "creategraph.h"
#include "createg6to9.h"

SimpleMenu::SimpleMenu(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300))
{

	menubar = new wxMenuBar;
	file = new wxMenu;

	quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
	file->Append(quit);
	menubar->Append(file, wxT("&File"));

	result = new wxMenu;
	result->Append(ID_QUERY, wxT("&New Top-k query"));
	menubar->Append(result, wxT("&Result"));

	dataset = new wxMenu;
	dataset->Append(ID_NEW_DATASET, wxT("&New Dataset "));
	dataset->Append(ID_SHOW_DATASET, wxT("&Show Dataset"));
	dataset->Append(ID_DATASET_INTO_MYSQL, wxT("&Dataset into MYSQL"));
	dataset->Append(ID_DATASET_RANKED, wxT("&Show Score-ranked Dataset"));
	dataset->Append(ID_SAVE_RANKED, wxT("&Save Score_ranked data"));
	menubar->Append(dataset, wxT("&Dataset"));

	graph = new wxMenu;
	menubar->Append(graph, wxT("&Graph"));

	creategraph = new wxMenu;
	creategraph->Append(ID_GRAPH_TIME, wxT("Create single dataset time-k graph ..."));
	creategraph->Append(ID_GRAPH_DEPTH, wxT("Create single dataset depth-k graph ..."));
	creategraph->Append(ID_CREATE_6, wxT("Create Comparation Independent U-Topk/U-kRank time/depth graph..."));
	graph->AppendSubMenu(creategraph, wxT("&Create Graph according the selected dataset"));

	loadgraph = new wxMenu;
	loadgraph->Append(ID_LOAD_6, wxT("Load Independent U-Topk time graph..."));
	loadgraph->Append(ID_LOAD_7, wxT("Load Independent U-Topk depth graph..."));
	loadgraph->Append(ID_LOAD_8, wxT("Load Independent U-kRanks time graph..."));
	loadgraph->Append(ID_LOAD_9, wxT("Load Independent U-kRanks depth graph..."));
	loadgraph->Append(ID_LOAD_10, wxT("Load Independent U-Topk correlations graph..."));
	loadgraph->Append(ID_LOAD_11, wxT("Load Independent U-kRanks correlations graph..."));
	loadgraph->Append(ID_LOAD_12, wxT("Load OPTU-Topk depth graph..."));
	loadgraph->Append(ID_LOAD_13, wxT("Load OPTU-Topk time graph..."));
	loadgraph->Append(ID_LOAD_14, wxT("Load Rule set complexity graph..."));
	graph->AppendSubMenu(loadgraph, wxT("&Load graph..."));

	SetMenuBar(menubar);

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SimpleMenu::OnQuit));
	Connect(ID_NEW_DATASET, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SimpleMenu::OnNewDataset));
	Connect(ID_SHOW_DATASET, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SimpleMenu::OnShowDataset));
	Connect(ID_DATASET_RANKED, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnDatasetRanked));
	Connect(ID_SAVE_RANKED, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnSaveRanked));
	Connect(ID_DATASET_INTO_MYSQL, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SimpleMenu::OnIntoMysql));
	Connect(ID_QUERY, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SimpleMenu::OnQuery));

	//submenu
	Connect(ID_GRAPH_TIME, wxEVT_COMMAND_MENU_SELECTED,
	    wxCommandEventHandler(SimpleMenu::OnGraphTime));
	Connect(ID_GRAPH_DEPTH, wxEVT_COMMAND_MENU_SELECTED,
		    wxCommandEventHandler(SimpleMenu::OnGraphDepth));
	Connect(ID_CREATE_6, wxEVT_COMMAND_MENU_SELECTED,
		    wxCommandEventHandler(SimpleMenu::OnCreate6));

	Connect(ID_LOAD_6, wxEVT_COMMAND_MENU_SELECTED,
		    wxCommandEventHandler(SimpleMenu::OnLoad6));
	Connect(ID_LOAD_7, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad7));
	Connect(ID_LOAD_8, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad8));
	Connect(ID_LOAD_9, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad9));
	Connect(ID_LOAD_10, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad10));
	Connect(ID_LOAD_11, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad11));
	Connect(ID_LOAD_12, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad12));
	Connect(ID_LOAD_13, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad13));
	Connect(ID_LOAD_14, wxEVT_COMMAND_MENU_SELECTED,
			wxCommandEventHandler(SimpleMenu::OnLoad14));

	Centre();

}

void SimpleMenu::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

void SimpleMenu::OnNewDataset(wxCommandEvent& WXUNUSED(event))
{
	CheckBox *cb = new CheckBox(wxT("Independant"));
	cb->Show(true);
	//std::cout << "size: " << current_dataset.size() << std::endl;
}

void SimpleMenu::OnShowDataset(wxCommandEvent& WXUNUSED(event))
{
	Show_list *sl = new Show_list(wxT("Top-k Dataset"),current_dataset);
	sl->Show(true);
}

void SimpleMenu::OnIntoMysql(wxCommandEvent& WXUNUSED(event))
{
	Db db;
	if (db.dataset_into_mysql(current_dataset)){
		wxString mystring = wxT("Put into mysql successfully.");
		wxMessageBox(wxString(mystring));
	}
	else{
		wxString mystring = wxT("Put into mysql failed.");
		wxMessageBox(wxString(mystring));
	}
}

void SimpleMenu::OnDatasetRanked(wxCommandEvent& WXUNUSED(event))
{
	Db db;
	if (db.get_score_ranked_data(ranked_dataset)){
		Show_list *sl = new Show_list(wxT("Score-Ranked Dataset"),ranked_dataset);
		sl->Show(true);
	}
	else{
		wxString mystring = wxT("Display Score-randed Dataset failed.");
		wxMessageBox(wxString(mystring));
	}
}

void SimpleMenu::OnSaveRanked(wxCommandEvent& WXUNUSED(event))
{
	Db db;
	wxString mystring;
	if (db.get_score_ranked_data(ranked_dataset)){
		if (db.save_into_file(ranked_dataset, "ranked_data"))
			mystring = wxT("Ranked data save into file 'ranked_data'.");
		else
			mystring = wxT("Ranked data save failed.");
		wxMessageBox(wxString(mystring));
	}
	else{
		mystring = wxT("Getting ranked data failed.");
		wxMessageBox(wxString(mystring));
	}
}

void SimpleMenu::OnQuery(wxCommandEvent& WXUNUSED(event))
{
	Query *qr = new Query(wxT("Input k value: "));
	qr->Show(true);
}

void SimpleMenu::OnGraphTime(wxCommandEvent& WXUNUSED(event)){
	y_axis = 0;
	CreateGraph *cg = new CreateGraph("Creating Graph: ");
	cg->Show(true);
}

void SimpleMenu::OnGraphDepth(wxCommandEvent& WXUNUSED(event)){
	y_axis = 1;
	CreateGraph *cg = new CreateGraph(wxT("Creating Graph: "));
	cg->Show(true);
}

void SimpleMenu::OnCreate6(wxCommandEvent& WXUNUSED(event)){
	CreateG6to9 *c6 = new CreateG6to9(wxT("Creating Graph: "));
	c6->Show(true);
}

void SimpleMenu::OnLoad6(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 6;
	LoadGraph *la = new LoadGraph(wxT("Independent U-Topk time:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad7(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 7;
	LoadGraph *la = new LoadGraph(wxT("Independent U-Topk depth:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad8(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 8;
	LoadGraph *la = new LoadGraph(wxT("Independent U-kRanks time:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad9(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 9;
	LoadGraph *la = new LoadGraph(wxT("Independent U-kRanks depth:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad10(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 10;
	LoadGraph *la = new LoadGraph(wxT("Independent U-Topk correlations:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad11(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 11;
	LoadGraph *la = new LoadGraph(wxT("Independent U-kRanks correlations:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad12(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 12;
	LoadGraph *la = new LoadGraph(wxT("OPTU-Topk depth:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad13(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 13;
	LoadGraph *la = new LoadGraph(wxT("OPTU-Topk time:  "));
	la->Show(true);
}

void SimpleMenu::OnLoad14(wxCommandEvent& WXUNUSED(event)){
	graph_seq = 14;
	LoadGraph *la = new LoadGraph(wxT("Rule set complexity:  "));
	la->Show(true);
}


