#pragma once
#include <wx/wx.h>
#include <wx/calctrl.h>
#include "bankfunctions.h"

class ATMFrame : public wxFrame
{
public:
	transaction Transaction; // class caller
	ATMFrame(const wxString& title);
private: // event handlers
	
	void LogIn();
	void OnEnterClicked(wxCommandEvent& evt); // Event Handler, it should have reference as a parameter
	void OnButtonAnyClicked(wxCommandEvent& evt); // Event Handler, it should have reference as a parameter
	void OnClose(wxCloseEvent& evt);

	void Creation();
	void OnSubmitClicked(wxCommandEvent& evt);

	void BankFunctions();

	// log-in panel buttons
};
