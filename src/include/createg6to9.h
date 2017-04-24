/*
 * createg6to9.h
 *
 *  Created on: Apr 18, 2017
 *      Author: tao
 */

#ifndef SRC_INCLUDE_CREATEG6TO9_H_
#define SRC_INCLUDE_CREATEG6TO9_H_
#include <wx/wx.h>
#include "main.h"

class CreateG6to9 : public wxFrame
{
public:
  CreateG6to9(const wxString& title);

  void OnCreate(wxCommandEvent& event);
  void OnCancel(wxCommandEvent& event);
  void PlotPoly(double arr[5][15]);

private:
    wxTextCtrl *tc1;
    wxTextCtrl *tc2;
    wxTextCtrl *tc3;
    wxTextCtrl *tc4;
    wxTextCtrl *tc7;

    wxRadioButton *rb1;
    wxRadioButton *rb2;
    wxRadioButton *rb3;
    wxRadioButton *rb4;

    //store 5 datasets' time and depth and extra information;
    //each row: time: 0/2/4/6 cell, depth:1/3/5/7 cell
    //cell 10: Y-axis, time:0, depth: 1
    //cell 11: distribution, uu: 1, un: 2, ue:3
    //cell 12: mean value(if un or ue); cell 13: tuple number
    //cell 14: u_semantics, U-Topk: 0, U-kRanks: 1
    double Time_depth[5][15];
};

	const int ID_6TO9_CREATE = 71;
	const int ID_6TO9_CANCEL = 72;




#endif /* SRC_INCLUDE_CREATEG6TO9_H_ */
