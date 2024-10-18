#include "ATMFrame.h"
#include "bankfunctions.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/calctrl.h>
#include <wx/datetime.h>
#include <vector>

wxPanel* log_in;
wxPanel* bank_functions;
wxPanel* create;

wxFont titleFont(80, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD);
wxFont brandFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);
wxFont textFont(32, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
wxFont createFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
wxFont fieldFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont passFont(40, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

// LOG-IN PANEL
wxButton* button1;
wxStaticText* title1;
wxTextCtrl* textbox;
wxBoxSizer* sizer;

// CREATION PANEL
wxStaticText* branding;
wxStaticText* name;
wxStaticText* birthday;
wxStaticText* month;
wxStaticText* day;
wxStaticText* year;
wxStaticText* contact;
wxStaticText* deposit;
wxStaticText* pin;
wxStaticText* minimum;
wxStaticText* colon;
wxStaticText* brand;

wxTextCtrl* nameField;
wxTextCtrl* contactField;
wxTextCtrl* depositField;
wxTextCtrl* pincodeField;
wxSpinCtrl* monthCtrl;
wxSpinCtrl* dayCtrl;
wxSpinCtrl* yearCtrl;

wxButton* submit;

wxCalendarCtrl* calendar;

ATMFrame::ATMFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) { // determines the size and position of the window
	log_in = new wxPanel(this); //panel as a parent 
	log_in->SetBackgroundColour(wxColour(*wxLIGHT_GREY));

	button1 = new wxButton(log_in, wxID_ANY, "ENTER", wxPoint(800, 450), wxSize(150, 80));// (parent, ID , position, size, style)
	title1 = new wxStaticText(log_in, wxID_ANY, "ATM NG MGA POGI", wxPoint(150, 100));
	textbox = new wxTextCtrl(log_in, wxID_ANY, "", wxPoint(300, 450), wxSize(500, 80), wxTE_PASSWORD);// (parent, ID , position, size)

	log_in->Bind(wxEVT_BUTTON, &ATMFrame::OnButtonAnyClicked, this);
	button1->Bind(wxEVT_BUTTON, &ATMFrame::OnEnterClicked, this);

	textbox->SetValidator(wxTextValidator(wxFILTER_DIGITS));
	title1->SetFont(titleFont);
	textbox->SetFont(passFont);

	this->Bind(wxEVT_CLOSE_WINDOW, &ATMFrame::OnClose, this);
	CreateStatusBar();
}

// LOG-IN EVENT HANDLERS AND FUNCTIONS
void ATMFrame::OnEnterClicked(wxCommandEvent& evt) {	
	LogIn();
	evt.Skip();
}

void ATMFrame::OnButtonAnyClicked(wxCommandEvent& evt) {
	wxLogMessage("Lopit");
}

void ATMFrame::OnClose(wxCloseEvent& evt) {
	wxLogMessage("Thank you for using our service.");
	evt.Skip();
}

void ATMFrame::LogIn() {
	wxString pinField = textbox->GetValue();
	Transaction.retrieve();
	Transaction.userLogin(pinField);
	wxLogStatus("Log In Successfully");
	wxLogMessage("Lopit");
	log_in->Hide();
	Creation();
}

// CREATION FUNCTIONS

void ATMFrame::Creation() {
	create = new wxPanel(this);
	this->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	this->Show();

	branding = new wxStaticText(this, wxID_ANY, "WELCOME TO ATMP", wxPoint(425, 20));
	name = new wxStaticText(this, wxID_ANY, "Full Name: ", wxPoint(400, 100));
	birthday = new wxStaticText(this, wxID_ANY, "Birthday: ", wxPoint(400, 170));

	//month = new wxStaticText(this, wxID_ANY, "Month: ", wxPoint(200, 70));
	//day = new wxStaticText(this, wxID_ANY, "Day: ", wxPoint(300, 70));
	//year = new wxStaticText(this, wxID_ANY, "Year: ", wxPoint(400, 70));

	contact = new wxStaticText(this, wxID_ANY, "Contact Number: ", wxPoint(400, 420));
	deposit = new wxStaticText(this, wxID_ANY, "Deposit Amount", wxPoint(400, 480));
	minimum = new wxStaticText(this, wxID_ANY, "(Minimum 5000)", wxPoint(510, 480));
	colon = new wxStaticText(this, wxID_ANY, ":", wxPoint(600, 480));
	pin = new wxStaticText(this, wxID_ANY, "PIN Code: ", wxPoint(400, 540));
	brand = new wxStaticText(this, wxID_ANY, "ATM NG MGA POGI", wxPoint(5, 700));

	nameField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(400, 120), wxSize(500, 30));
	contactField = new wxTextCtrl(this, wxID_ANY, "+63-", wxPoint(400, 440), wxSize(500, 30));
	depositField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(400, 500), wxSize(500, 30));
	pincodeField = new wxTextCtrl(this, wxID_ANY, "", wxPoint(400, 560), wxSize(500, 30), wxTE_PASSWORD);
	calendar = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime, wxPoint(400, 190), wxSize(500, 200));
	submit = new wxButton(this, wxID_ANY, "SUBMIT", wxPoint(400, 620), wxSize(500, 30));

	branding->SetFont(textFont);
	name->SetFont(createFont);
	birthday->SetFont(createFont);
	contact->SetFont(createFont);
	deposit->SetFont(createFont);
	pin->SetFont(createFont);
	colon->SetFont(createFont);
	
	nameField->SetFont(fieldFont);
	contactField->SetFont(fieldFont);
	depositField->SetFont(fieldFont);
	pincodeField->SetFont(fieldFont);

	brand->SetFont(brandFont);

	contactField->SetValidator(wxTextValidator(wxFILTER_DIGITS));

	submit->Bind(wxEVT_BUTTON, &ATMFrame::OnSubmitClicked, this);

	//monthCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(200, 100), wxSize(70,-1), wxSP_WRAP, 1, 12, 1);
	//dayCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(300, 100), wxSize(70, -1), wxSP_WRAP, 1, 12, 1);
	//yearCtrl = new wxSpinCtrl(this, wxID_ANY, "", wxPoint(400, 100), wxSize(70, -1), wxSP_WRAP, 1900, 2100, 1900);
	
}

void ATMFrame::OnSubmitClicked(wxCommandEvent& evt) {
	wxMessageBox("SUBMITTED");
}

// BANK FUNCTIONS EVENT HANDLERS AND FUNCTIONS
void ATMFrame::BankFunctions() {
	bank_functions = new wxPanel(this); //panel as a parent 
	this->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	bank_functions->Show();

	std::vector<wxButton*> buttons;
	wxGridSizer* gridSizer = new wxGridSizer(3, 2, wxSize());
	wxSizerFlags flags = wxSizerFlags().Expand(). Border(wxALL, 10);
	
	wxButton* checkbal = new wxButton(this, wxID_ANY, "CHECK BALANCE", wxDefaultPosition, wxSize(619,220));
	checkbal->SetFont(textFont);
	buttons.push_back(checkbal);

	wxButton* withdraw = new wxButton(this, wxID_ANY, "WITHDRAW CASH", wxDefaultPosition, wxSize(619, 220));
	withdraw->SetFont(textFont);
	buttons.push_back(withdraw);

	wxButton* deposit = new wxButton(this, wxID_ANY, "DEPOSIT", wxDefaultPosition, wxSize(619, 220));
	deposit->SetFont(textFont);
	buttons.push_back(deposit);

	wxButton* banktransfer = new wxButton(this, wxID_ANY, "BANK TRANSFER", wxDefaultPosition, wxSize(619, 220));
	banktransfer->SetFont(textFont);
	buttons.push_back(banktransfer);

	wxButton* accountsettings = new wxButton(this, wxID_ANY, "ACCOUNT SETTINGS", wxDefaultPosition, wxSize(619, 220));
	accountsettings->SetFont(textFont);
	buttons.push_back(accountsettings);

	wxButton* exit = new wxButton(this, wxID_ANY, "LOG OUT", wxDefaultPosition, wxSize(619, 220));
	exit->SetFont(textFont);
	buttons.push_back(exit);

	gridSizer->Add(checkbal, flags);
	gridSizer->Add(withdraw, flags);
	gridSizer->Add(deposit, flags);
	gridSizer->Add(banktransfer, flags);
	gridSizer->Add(accountsettings, flags);
	gridSizer->Add(exit, flags);

	this->SetSizer(gridSizer);
	gridSizer->SetSizeHints(this);

	exit->Bind(wxEVT_BUTTON, &ATMFrame::OnButtonAnyClicked, this);

}
