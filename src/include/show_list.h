/*
 * show_list.h
 *
 *  Created on: Mar 31, 2017
 *      Author: tao
 */

#ifndef SHOW_LIST_H_
#define SHOW_LIST_H_

#include <wx/wx.h>
#include "wx/listctrl.h"
#include <vector>
#include <string>

class Show_list : public wxFrame
{
public:
	Show_list(const wxString& title, std::vector<std::vector<std::string>> v);
	//Show_list(const wxString& title);

	void OnOk(wxCommandEvent& event);

private:
  wxListCtrl *m_listCtrl;
};

	const int ID_SHOW_LIST_OK = 41;

#endif /* SHOW_LIST_H_ */
