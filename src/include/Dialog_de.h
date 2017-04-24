/*
 * Dialog_de.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */

#ifndef DIALOG_DE_H_
#define DIALOG_DE_H_

#include <wx/wx.h>
#include <vector>
#include <string>
#include "main.h"

extern std::vector<std::vector<std::string>> current_dataset;

class De : public wxFrame
{
public:
  De(const wxString& title);

  void OnCreate(wxCommandEvent& event);
  void OnCancel(wxCommandEvent& event);

private:
  wxTextCtrl *tc1;
  //wxTextCtrl *tc2;
  wxTextCtrl *tc3;
  wxRadioButton *rb1;
  wxRadioButton *rb2;
  wxRadioButton *rb3;

};

	const int ID_DE_CREATE = 21;
	const int ID_DE_CANCEL = 22;

#endif /* DIALOG_DE_H_ */
