/*
 * query.h
 *
 *  Created on: Apr 6, 2017
 *      Author: tao
 */

#ifndef QUERY_H_
#define QUERY_H_

#include <wx/wx.h>

class Query : public wxFrame
{
public:
  Query(const wxString& title);

  void OnOk(wxCommandEvent& event);
  void OnCancel(wxCommandEvent& event);

private:
    wxTextCtrl *tc1;
    wxTextCtrl *tc2;
    wxRadioButton *rb1;
    wxRadioButton *rb2;

};

	const int ID_QUERY_OK = 51;
	const int ID_QUERY_CANCEL = 52;

#endif /* QUERY_H_ */
