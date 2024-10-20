#include "ATMFrame.h"
#include "bankfunctions.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <wx/calctrl.h>
#include <wx/datetime.h>
#include <vector>

wxPanel* Menu;
wxPanel* transaction;
wxPanel* balance;


wxFont titleFont(80, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD);
wxFont brandFont(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont textFont(32, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont createFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont fieldFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont pastFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

wxStaticText* MenuText; //title page kada panel
wxStaticText* transtxt;
wxStaticText* baltxt;
wxStaticText* textD;
wxStaticText* textWD;
wxStaticText* BTtxt;
wxStaticText* changepintext;//hanggang dito yung title page panel

//Register Panel
wxPanel* regpanel;
wxStaticText* regpaneltxt;
wxStaticText* nametxt;
wxTextCtrl* name;
wxStaticText* bdaytxt;
wxStaticText* contacttxt;
wxTextCtrl* contact;
wxStaticText* regpanelpintxt;
wxTextCtrl* regpanelpin;
wxButton* proceedregpanel;

//Deposit Panel
wxPanel* depositpanel;
wxStaticText* amounttextD;//Static txt enter amount for deposit
wxTextCtrl* amountD;//enter amount for deposit
wxButton* proceedD;

//Withdraw Panel
wxPanel* withdraw;
wxStaticText* amountW;
wxTextCtrl* enteramountW;
wxButton* proceedW;

//Fund Transfer Panel
wxPanel* BankTransferPanel;
wxStaticText* recpnt_accntxt;
wxTextCtrl* recpnt_accn;
wxStaticText* trans_entr_amnttxt;
wxTextCtrl* trans_entr_amnt;
wxButton* proceed_trans_amnt;

//Change PIN Panel
wxPanel* changepinpanel;
wxStaticText* CurrentPinText;
wxTextCtrl* CurrentPin;
wxStaticText* NewPinText;
wxTextCtrl* NewPin;
wxStaticText* VerifyNewPinText;
wxTextCtrl* VerifyNewPin;
wxButton* proceedCP;

//Another Transaction
wxPanel* atransaction;
wxStaticText* aTransac;
wxButton* yesbutton;
wxButton* nobutton;


wxButton* EnterPin; //enter pin button sa simula
wxButton* AllButton; //button kada transaction
wxButton* DButton;
wxButton* WButton;
wxButton* BTButton;
wxButton* CButton;
wxButton* exits;//hanggang dito yung button of each transaction

wxButton* BackButton; //back button kada transaction
wxButton* DepositButton;
wxButton* WithdrawButton;
wxButton* BankTransferButton;
wxButton* ChangePinButton;//hanggang dito yung button kada transaction


wxTextCtrl* pin;//for pin input at the start


ATMFrame::ATMFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    Menu = new wxPanel(this);
    MenuText = new wxStaticText(Menu, wxID_ANY, "WELCOME TO ATMP", wxPoint(150, 100));
    MenuText->SetFont(titleFont);
    EnterPin = new wxButton(Menu, wxID_ANY, "ENTER", wxPoint(520, 350), wxSize(100, 30));
    pin = new wxTextCtrl(Menu, wxID_ANY, "", wxPoint(300, 350), wxSize(200, 30), wxTE_PASSWORD);
    pin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    EnterPin->Bind(wxEVT_BUTTON, &ATMFrame::OnButtonClicked, this);

    Transaction();
    CheckBalance();
    Deposit();
    Withdraw();
    BankTransfer();
    Change();
    Register();
    ATransac();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(Menu, 1, wxEXPAND);
    mainSizer->Add(regpanel, 1, wxEXPAND);
    mainSizer->Add(transaction, 1, wxEXPAND);
    mainSizer->Add(balance, 1, wxEXPAND);
    mainSizer->Add(depositpanel, 1, wxEXPAND);
    mainSizer->Add(withdraw, 1, wxEXPAND);
    mainSizer->Add(BankTransferPanel, 1, wxEXPAND);
    mainSizer->Add(changepinpanel, 1, wxEXPAND);
    mainSizer->Add(atransaction, 1, wxEXPAND);

    regpanel->Hide();
    transaction->Hide();
    balance->Hide();
    depositpanel->Hide();
    withdraw->Hide();
    BankTransferPanel->Hide();
    changepinpanel->Hide();
    atransaction->Hide();
    SetSizer(mainSizer);
    Layout();
}

void ATMFrame::Register() {
    regpanel = new wxPanel(this);
    regpaneltxt = new wxStaticText(regpanel, wxID_ANY, "REGISTER ACCOUNT", wxPoint(170, 50));
    regpaneltxt->SetFont(pastFont);
    nametxt = new wxStaticText(regpanel, wxID_ANY, "NAME:", wxPoint(150, 140));
    nametxt->SetFont(brandFont);
    name = new wxTextCtrl(regpanel, wxID_ANY, "", wxPoint(250, 140), wxSize(400, 25));


}

void ATMFrame::Transaction() {
    transaction = new wxPanel(this);
    transtxt = new wxStaticText(transaction, wxID_ANY, "TRANSACTION", wxPoint(260, 50));
    transtxt->SetFont(pastFont);

    AllButton = new wxButton(transaction, wxID_ANY, "BALANCE INQUIRY", wxPoint(100, 200), wxSize(300, 100));
    AllButton->SetFont(fieldFont);
    AllButton->Bind(wxEVT_BUTTON, &ATMFrame::BalanceButton, this);

    DButton = new wxButton(transaction, wxID_ANY, "DEPOSIT", wxPoint(100, 330), wxSize(300, 100));
    DButton->SetFont(fieldFont);
    DButton->Bind(wxEVT_BUTTON, &ATMFrame::DepositsButton, this);


    WButton = new wxButton(transaction, wxID_ANY, "WITHDRAW", wxPoint(100, 460), wxSize(300, 100));
    WButton->SetFont(fieldFont);
    WButton->Bind(wxEVT_BUTTON, &ATMFrame::WithdrawsButton, this);


    BTButton = new wxButton(transaction, wxID_ANY, "FUND TRANSFER", wxPoint(500, 200), wxSize(300, 100));
    BTButton->SetFont(fieldFont);
    BTButton->Bind(wxEVT_BUTTON, &ATMFrame::TransferButton, this);


    CButton = new wxButton(transaction, wxID_ANY, "CHANGE PIN", wxPoint(500, 330), wxSize(300, 100));
    CButton->SetFont(fieldFont);
    CButton->Bind(wxEVT_BUTTON, &ATMFrame::ChangeButton, this);


    exits = new wxButton(transaction, wxID_ANY, "EXIT", wxPoint(500, 460), wxSize(300, 100));
    exits->SetFont(fieldFont);
    exits->Bind(wxEVT_BUTTON, &ATMFrame::ExitButton, this);
}

void ATMFrame::CheckBalance() {
    balance = new wxPanel(this);
    baltxt = new wxStaticText(balance, wxID_ANY, "BALANCE INQUIRY", wxPoint(215, 50));
    baltxt->SetFont(pastFont);
    BackButton = new wxButton(balance, wxID_ANY, "BACK", wxPoint(550, 550), wxSize(300, 100));
    BackButton->SetFont(fieldFont);
    BackButton->Bind(wxEVT_BUTTON, &ATMFrame::BalanceBack, this);
}

void ATMFrame::Deposit() {
    depositpanel = new wxPanel(this);
    textD = new wxStaticText(depositpanel, wxID_ANY, "DEPOSIT", wxPoint(320, 50));
    textD->SetFont(pastFont);

    DepositButton = new wxButton(depositpanel, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    DepositButton->SetFont(fieldFont);
    DepositButton->Bind(wxEVT_BUTTON, &ATMFrame::DepositBack, this);

    amounttextD = new wxStaticText(depositpanel, wxID_ANY, "ENTER AMOUNT:", wxPoint(200, 150));
    amounttextD->SetFont(fieldFont);

    amountD = new wxTextCtrl(depositpanel, wxID_ANY, "", wxPoint(450, 150), wxSize(250, 30));
    amountD->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceedD = new wxButton(depositpanel, wxID_ANY, "PROCEED", wxPoint(200, 200), wxSize(500, 100));
    proceedD->SetFont(fieldFont);
    proceedD->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransac, this);
}

void ATMFrame::Withdraw() {
    withdraw = new wxPanel(this);
    textWD = new wxStaticText(withdraw, wxID_ANY, "WITHDRAW", wxPoint(320, 50));
    textWD->SetFont(pastFont);

    WithdrawButton = new wxButton(withdraw, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    WithdrawButton->SetFont(fieldFont);
    WithdrawButton->Bind(wxEVT_BUTTON, &ATMFrame::WithdrawBack, this);

    amountW = new wxStaticText(withdraw, wxID_ANY, "ENTER AMOUNT:", wxPoint(200, 150));
    amountW->SetFont(fieldFont);

    enteramountW = new wxTextCtrl(withdraw, wxID_ANY, "", wxPoint(450, 150), wxSize(250, 30));
    enteramountW->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceedW = new wxButton(withdraw, wxID_ANY, "PROCEED", wxPoint(200, 200), wxSize(500, 100));
    proceedW->SetFont(fieldFont);
    proceedW->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransac, this);

}

void ATMFrame::BankTransfer() {
    BankTransferPanel = new wxPanel(this);
    BTtxt = new wxStaticText(BankTransferPanel, wxID_ANY, "FUND TRANSFER", wxPoint(230, 50));
    BTtxt->SetFont(pastFont);

    BankTransferButton = new wxButton(BankTransferPanel, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    BankTransferButton->SetFont(fieldFont);
    BankTransferButton->Bind(wxEVT_BUTTON, &ATMFrame::FundTransBack, this);

    recpnt_accntxt = new wxStaticText(BankTransferPanel, wxID_ANY, "ACCOUNT NUMBER", wxPoint(140, 150));
    recpnt_accntxt->SetFont(fieldFont);

    recpnt_accn = new wxTextCtrl(BankTransferPanel, wxID_ANY, "", wxPoint(500, 150), wxSize(250, 30));
    recpnt_accn->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    trans_entr_amnttxt = new wxStaticText(BankTransferPanel, wxID_ANY, "ENTER AMOUNT", wxPoint(140, 200));
    trans_entr_amnttxt->SetFont(fieldFont);

    trans_entr_amnt = new wxTextCtrl(BankTransferPanel, wxID_ANY, "", wxPoint(500, 200), wxSize(250, 30));
    trans_entr_amnt->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceed_trans_amnt = new wxButton(BankTransferPanel, wxID_ANY, "PROCEED", wxPoint(140, 250), wxSize(610, 60));
    proceed_trans_amnt->SetFont(fieldFont);
    proceed_trans_amnt->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransac, this);
}

void ATMFrame::Change() {
    changepinpanel = new wxPanel(this);
    changepintext = new wxStaticText(changepinpanel, wxID_ANY, "CHANGE PIN", wxPoint(275, 50));
    changepintext->SetFont(pastFont);

    ChangePinButton = new wxButton(changepinpanel, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    ChangePinButton->SetFont(fieldFont);
    ChangePinButton->Bind(wxEVT_BUTTON, &ATMFrame::ChangePinBack, this);

    CurrentPinText = new wxStaticText(changepinpanel, wxID_ANY, "CURRENT PIN:", wxPoint(220, 150));
    CurrentPinText->SetFont(fieldFont);

    CurrentPin = new wxTextCtrl(changepinpanel, wxID_ANY, "", wxPoint(420, 150), wxSize(250, 30));
    CurrentPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    NewPinText = new wxStaticText(changepinpanel, wxID_ANY, "NEW PIN:", wxPoint(220, 220));
    NewPinText->SetFont(fieldFont);

    NewPin = new wxTextCtrl(changepinpanel, wxID_ANY, "", wxPoint(420, 220), wxSize(250, 30));
    NewPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    VerifyNewPinText = new wxStaticText(changepinpanel, wxID_ANY, "CONFIRM PIN:", wxPoint(220, 270));
    VerifyNewPinText->SetFont(fieldFont);

    VerifyNewPin = new wxTextCtrl(changepinpanel, wxID_ANY, "", wxPoint(420, 270), wxSize(250, 30));
    VerifyNewPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceedCP = new wxButton(changepinpanel, wxID_ANY, "PROCEED", wxPoint(220, 320), wxSize(450, 60));
    proceedCP->SetFont(fieldFont);
    proceedCP->Bind(wxEVT_BUTTON, &ATMFrame::SChanged, this);
    
}

void ATMFrame::ATransac() {
    atransaction = new wxPanel(this);
    aTransac = new wxStaticText(atransaction, wxID_ANY, "WOULD YOU LIKE TO MAKE ANOTHER TRANSACTION?", wxPoint(275, 50));
    aTransac->SetFont(fieldFont);

    yesbutton = new wxButton(atransaction, wxID_ANY, "YES", wxPoint(220, 320), wxSize(450, 60));
    yesbutton->SetFont(fieldFont);
    nobutton = new wxButton(atransaction, wxID_ANY, "NO", wxPoint(620, 320), wxSize(450, 60));
    nobutton->SetFont(fieldFont);

    yesbutton->Bind(wxEVT_BUTTON, &ATMFrame::ATBack, this);
    nobutton->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransacBack, this);
}


void ATMFrame::OnButtonClicked(wxCommandEvent& evt) {
    Menu->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::BalanceButton(wxCommandEvent& evt) {
    transaction->Hide();
    balance->Show();
    Layout();
}

void ATMFrame::DepositsButton(wxCommandEvent& evt) {
    transaction->Hide();
    depositpanel->Show();
    Layout();
}

void ATMFrame::WithdrawsButton(wxCommandEvent& evt) {
    transaction->Hide();
    withdraw->Show();
    Layout();
}

void ATMFrame::TransferButton(wxCommandEvent& evt) {
    transaction->Hide();
    BankTransferPanel->Show();
    Layout();
}

void ATMFrame::ChangeButton(wxCommandEvent& evt) {
    transaction->Hide();
    changepinpanel->Show();
    Layout();
}

void ATMFrame::ExitButton(wxCommandEvent& evt) {
    Close(true);
}

void ATMFrame::BalanceBack(wxCommandEvent& evt) {
    balance->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::DepositBack(wxCommandEvent& evt) {
    depositpanel->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::WithdrawBack(wxCommandEvent& evt) {
    withdraw->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::FundTransBack(wxCommandEvent& evt) {
    BankTransferPanel->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::ChangePinBack(wxCommandEvent& evt) {
    changepinpanel->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::AnotherTransac(wxCommandEvent& evt) {
    depositpanel->Hide();
    withdraw->Hide();
    BankTransferPanel->Hide();
    atransaction->Show();
    Layout();
}

void ATMFrame::AnotherTransacBack(wxCommandEvent& evt) {
    depositpanel->Hide();
    atransaction->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::ATBack(wxCommandEvent& evt) {
    atransaction->Hide();
    transaction->Show();
    Layout();
}

void ATMFrame::SChanged(wxCommandEvent& evt) {
    wxMessageBox("SUCCESSFULLY CHANGED PIN");
    changepinpanel->Hide();
    transaction->Show();
    Layout();
}
