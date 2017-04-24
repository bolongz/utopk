/*
 * menu.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */

#ifndef MENU_H_
#define MENU_H_

#include <wx/wx.h>
#include <wx/menu.h>
#include "main.h"

extern std::vector<std::vector<std::string>> current_dataset;

class SimpleMenu : public wxFrame
{
public:
    SimpleMenu(const wxString& title);

    void OnQuit(wxCommandEvent& event);
    void OnNewDataset(wxCommandEvent& event);
    void OnShowDataset(wxCommandEvent& event);
    void OnDatasetRanked(wxCommandEvent& event);
    void OnSaveRanked(wxCommandEvent& event);
    void OnIntoMysql(wxCommandEvent& event);
    void OnQuery(wxCommandEvent& event);

    //submenu
    void OnGraphTime(wxCommandEvent& event);
    void OnGraphDepth(wxCommandEvent& event);

    void OnLoad6(wxCommandEvent& event);
    void OnLoad7(wxCommandEvent& event);
    void OnLoad8(wxCommandEvent& event);
    void OnLoad9(wxCommandEvent& event);
    void OnLoad10(wxCommandEvent& event);
    void OnLoad11(wxCommandEvent& event);
    void OnLoad12(wxCommandEvent& event);
    void OnLoad13(wxCommandEvent& event);
    void OnLoad14(wxCommandEvent& event);

    void OnCreate6(wxCommandEvent& event);
    void OnCreate7(wxCommandEvent& event);
    void OnCreate8(wxCommandEvent& event);
    void OnCreate9(wxCommandEvent& event);

    wxMenuBar *menubar;
    wxMenu *file;
    wxMenu *dataset;
    wxMenu *result;
    wxMenu *graph;
    wxMenuItem *quit;
    wxMenu *creategraph;
    wxMenu *loadgraph;


};

	const int ID_NEW_DATASET = 1;
	const int ID_DATASET_INTO_MYSQL = 2;
	const int ID_SHOW_DATASET = 3;
	const int ID_DATASET_RANKED = 4;
	const int ID_SAVE_RANKED = 5;
	const int ID_QUERY = 6;

	//submenu
	const int ID_GRAPH_TIME = 101;
	const int ID_GRAPH_DEPTH = 102;
	//const int ID_GRAPH_RULE = 103;

	const int ID_LOAD_6 = 111;
	const int ID_LOAD_7 = 112;
	const int ID_LOAD_8 = 113;
	const int ID_LOAD_9 = 114;
	const int ID_LOAD_10 = 115;
	const int ID_LOAD_11 = 116;
	const int ID_LOAD_12 = 117;
	const int ID_LOAD_13 = 118;
	const int ID_LOAD_14 = 119;

	const int ID_CREATE_6 = 121;
	const int ID_CREATE_7 = 122;
	const int ID_CREATE_8 = 123;
	const int ID_CREATE_9 = 124;


#endif /* MENU_H_ */
