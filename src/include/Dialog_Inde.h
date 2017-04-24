/*
 * Dialog_Inde.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */

#ifndef DIALOG_INDE_H_
#define DIALOG_INDE_H_

#include <wx/wx.h>
#include <vector>
#include <string>
#include "main.h"

extern std::vector<std::vector<std::string>> current_dataset;

class Inde : public wxFrame
{
public:
  Inde(const wxString& title);

  void OnCreate(wxCommandEvent& event);
  void OnCancel(wxCommandEvent& event);

private:
    wxTextCtrl *tc1;
    wxTextCtrl *tc2;
    wxTextCtrl *tc3;
    wxRadioButton *rb1;
    wxRadioButton *rb2;
    wxRadioButton *rb3;
};

	const int ID_INDE_CREATE = 31;
	const int ID_INDE_CANCEL = 32;


#endif /* DIALOG_INDE_H_ */
