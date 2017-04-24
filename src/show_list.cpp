/*
 * show_list.cpp
 *
 *  Created on: Mar 31, 2017
 *      Author: tao
 */
#include "show_list.h"
#include "main.h"
#include <vector>
#include <string>
#include <sstream>


Show_list::Show_list(const wxString& title, std::vector<std::vector<std::string>> v)
       : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(600, 500))
{

	wxPanel *panel = new wxPanel(this, -1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

	m_listCtrl = new wxListCtrl(panel, wxID_ANY,
                                     wxDefaultPosition, wxDefaultSize,wxLC_REPORT
									 | wxBORDER_THEME | wxLC_EDIT_LABELS);

	int num_cols, num_rows;
 //Initial With Report Items
	if (v.empty()){
		num_cols = 2;
		num_rows = 100;
		//std::vector<std::vector<std::string>>	v;
		std::vector<std::string> v_temp;

		for (int i = 0; i < num_rows; i++){
 			 std::stringstream ss,ss1;
 			 ss << "row" << i;
 			 std::string str;
 			 ss >> str;
 			 v_temp.push_back(str);
 			 str.clear();

 			 ss1 << i;
 			 ss1 >> str;
 			 v_temp.push_back(str);
 			 v.push_back(v_temp);
		}
	}
	else{
		num_cols = v[0].size();
		num_rows = v.size();
	}


     // to speed up inserting we hide the control temporarily
	for (int i = 0; i < num_cols; i++){
		m_listCtrl->InsertColumn(i,wxString::Format(wxT("Column %d"), i + 1),2);
		m_listCtrl->SetColumnWidth(i, 200);
	}

     m_listCtrl->Hide();

     for (long i = 0; i < num_rows; i++){
    	 wxString firstString(v[i][0].c_str(), wxConvUTF8);
    	 long index = m_listCtrl->InsertItem(i,firstString);
    	 for (int j = 1; j < num_cols; j++){
    		 wxString followingString(v[i][j].c_str(), wxConvUTF8);
    		 m_listCtrl->SetItem(index,j,followingString);
    	 }
     }

     m_listCtrl->Show();

 //set list display size and area
     /*
 	 wxSize size = GetClientSize();
     wxCoord y = (2*size.y)/3;
     m_listCtrl->SetSize(0, 0, size.x, y);
     */

     hbox1->Add(m_listCtrl, 1, wxEXPAND, wxALL);
     vbox->Add(hbox1, 1, wxBOTTOM | wxLEFT | wxRIGHT | wxEXPAND, 10);

     wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
     wxButton *btn1 = new wxButton(panel, ID_SHOW_LIST_OK, wxT("OK"));
     hbox2->Add(btn1, 0);

     vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

     Connect(ID_SHOW_LIST_OK, wxEVT_COMMAND_BUTTON_CLICKED,
         		  wxCommandEventHandler(Show_list::OnOk));
     panel->SetSizer(vbox);

     Centre();
}

void Show_list::OnOk(wxCommandEvent& WXUNUSED(event)){

	Close(true);
}

