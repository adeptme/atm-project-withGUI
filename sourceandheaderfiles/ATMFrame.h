#pragma once
#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/timer.h>
#include "bankfunctions.h"
#include "Create.h"

class ATMFrame : public wxFrame
{
public:
	
	ATMFrame(const wxString& title);
	transaction Transac;
	create Create;

private:
	// PANEL FUNCTIONS
	void Welcome();
	void Wait();
	void Register();
	void Transaction();
	void CheckBalance();
	void Deposit();
	void Withdraw();
	void BankTransfer();
	void Change();
	void ATransac();

	// START PANEL
	void LoginExistingAcc(wxCommandEvent& evt);
	void CreateNewAcc(wxCommandEvent& evt);
	void RegSubmitButton(wxCommandEvent& evt);

	// ANOTHER TRANSACTION PANELS
	void AnotherTransacNo(wxCommandEvent& evt);// back button for another transaction
	void AnotherTransacW(wxCommandEvent& evt); // another transac for withdraw
	void AnotherTransacD(wxCommandEvent& evt); // another transac for deposit
	void AnotherTransacBT(wxCommandEvent& evt); // another transac for bank transfer
	
	// BANK FUNCTIONS BUTTONS
	void ATBack(wxCommandEvent& evt);// Going back to the menu from the another transaction panel
	void SChanged(wxCommandEvent& evt); // Successful Changed text
	void OnButtonClicked(wxCommandEvent& evt);// button for each transaction
	void BalanceButton(wxCommandEvent& evt);
	void DepositsButton(wxCommandEvent& evt);
	void WithdrawsButton(wxCommandEvent& evt);
	void TransferButton(wxCommandEvent& evt);
	void ChangeButton(wxCommandEvent& evt);
	void ExitButton(wxCommandEvent& evt);// hanggang dito yung button for each transaction

	// BACK BUTTONS
	void BalanceBack(wxCommandEvent& evt);// back button for each transaction
	void DepositBack(wxCommandEvent& evt);
	void WithdrawBack(wxCommandEvent& evt);
	void FundTransBack(wxCommandEvent& evt);
	void ChangePinBack(wxCommandEvent& evt);//hanggang dito yung button for each transaction

	//Calendar
	void bDayDateChanged(wxCalendarEvent& evt);
};
