/*
 * check_dependant.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */

#ifndef CHECK_DEPENDENT_H_
#define CHECK_DEPENDENT_H_

#include <wx/wx.h>
#include "main.h"

extern int independent;

class CheckBox : public wxFrame
{
public:
    CheckBox(const wxString& title);

    void OnToggle(wxCommandEvent& event);
    void OnOk(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    wxCheckBox *m_cb;

};

const int ID_CHECKBOX = 11;
const int ID_DEPENDANT_OK = 12;
const int ID_DEPENDANT_CANCEL = 13;



#endif /* CHECK_DEPENDENT_H_ */
