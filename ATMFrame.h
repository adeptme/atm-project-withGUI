#pragma once
#include <wx/wx.h>
#include <wx/calctrl.h>
#include "bankfunctions.h"

class ATMFrame : public wxFrame
{
public:
	ATMFrame(const wxString& title);
	void Register();
	void Transaction();
	void CheckBalance();
	void Deposit();
	void Withdraw();
	void BankTransfer();
	void Change();
	void ATransac();
private:
	void AnotherTransac(wxCommandEvent& evt);//button for another transaction
	void AnotherTransacBack(wxCommandEvent& evt);//back button for another transaction
	void ATBack(wxCommandEvent& evt);//Going back to the menu from the another transaction panel
	void SChanged(wxCommandEvent& evt); //Successful Changed text
	void OnButtonClicked(wxCommandEvent& evt);//button for each transaction
	void BalanceButton(wxCommandEvent& evt);
	void DepositsButton(wxCommandEvent& evt);
	void WithdrawsButton(wxCommandEvent& evt);
	void TransferButton(wxCommandEvent& evt);
	void ChangeButton(wxCommandEvent& evt);
	void ExitButton(wxCommandEvent& evt);//hanggang dito yung button for each transaction

	void BalanceBack(wxCommandEvent& evt);//back button for each transaction
	void DepositBack(wxCommandEvent& evt);
	void WithdrawBack(wxCommandEvent& evt);
	void FundTransBack(wxCommandEvent& evt);
	void ChangePinBack(wxCommandEvent& evt);//hanggang dito yung button for each transaction
};
