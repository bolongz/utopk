/*
 * creategraph.h
 *
 *  Created on: Apr 17, 2017
 *      Author: tao
 */

#ifndef SRC_INCLUDE_CREATEGRAPH_H_
#define SRC_INCLUDE_CREATEGRAPH_H_

#include <wx/wx.h>
#include <vector>
#include <string>
#include "main.h"

class CreateGraph : public wxFrame
{
public:
  CreateGraph(const wxString& title);

  void OnCreate(wxCommandEvent& event);
  void OnCancel(wxCommandEvent& event);
  void PlotMono(std::vector<std::vector<double>> v);

private:
    wxTextCtrl *tc1;
    wxTextCtrl *tc2;
    wxTextCtrl *tc3;
    wxTextCtrl *tc4;
    wxRadioButton *rb1;
    wxRadioButton *rb2;
};

	const int ID_CG_CREATE = 61;
	const int ID_CG_CANCEL = 62;


#endif /* SRC_INCLUDE_CREATEGRAPH_H_ */
