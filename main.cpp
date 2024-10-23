#include "ATMFrame.h"
#include <wx/wx.h>
#include <wx/calctrl.h>
#include <wx/datetime.h>
#include <vector>


wxFont titleFont(80, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD);
wxFont brandFont(15, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont fieldFont(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_LIGHT);
wxFont userinputfieldFont2(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont textFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont createFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
wxFont pastFont(40, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

//WELCOME PANEL
wxPanel* welcome;
wxStaticText* welcomeatmp;
wxButton* loginexistingacc;
wxButton* createanaccount;

// login PANEL
wxPanel* Menu;
wxStaticText* MenuText;
wxStaticText* pintext;

// transaction PANEL
wxPanel* transaction;
wxButton* AllButton; //button kada transaction
wxButton* DButton;
wxButton* WButton;
wxButton* BTButton;
wxButton* CButton;
wxButton* exits;//hanggang dito yung button of each transaction

wxStaticText* transtxt;
wxStaticText* baltxt;
wxStaticText* textD;
wxStaticText* textWD;
wxStaticText* BTtxt;
wxStaticText* changepintext;

wxButton* EnterPin; //enter pin button sa simula

//Register PANEL
wxPanel* regpanel;

wxStaticText* regpaneltxt;
wxStaticText* regnametxt;
wxStaticText* regpintxt;
wxStaticText* regbalancetxt;
wxStaticText* regcontacttxt;
wxStaticText* regcontact63;
wxStaticText* regcalendartxt;

wxTextCtrl* regnameField;
wxTextCtrl* regpinField;
wxTextCtrl* egbalanceField;
wxTextCtrl* regcontactField;
wxTextCtrl* regbalanceField;

wxCalendarCtrl* regcalendar;

wxButton* regsubmitbutton;

//Check Balance Panel
wxPanel* balance;
wxButton* BackButton;

//Deposit PANEL
wxPanel* depositpanel;
wxButton* DepositButton;
wxStaticText* amounttextD;
wxTextCtrl* amountD;
wxButton* proceedD;

//Withdraw PANEL
wxPanel* withdraw;
wxButton* WithdrawButton;
wxStaticText* amountW;
wxTextCtrl* enteramountW;
wxButton* proceedW;

//Fund Transfer PANEL
wxPanel* BankTransferPanel;
wxButton* BankTransferButton;
wxStaticText* recpnt_accntxt;
wxTextCtrl* recpnt_accn;
wxStaticText* trans_entr_amnttxt;
wxTextCtrl* trans_entr_amnt;
wxButton* proceed_trans_amnt;

//Change PIN PANEL
wxPanel* changepinpanel;
wxButton* ChangePinButton;
wxStaticText* CurrentPinText;
wxTextCtrl* CurrentPin;
wxStaticText* NewPinText;
wxTextCtrl* NewPin;
wxStaticText* VerifyNewPinText;
wxTextCtrl* VerifyNewPin;
wxButton* proceedCP;

//Another Transaction PANEL
wxPanel* atransaction;
wxStaticText* aTransac;
wxButton* yesbutton;
wxButton* nobutton;

wxTextCtrl* pin;//for pin input at the start


ATMFrame::ATMFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    Transac.retrieve();
    welcome = new wxPanel(this);
    loginexistingacc = new wxButton(welcome, wxID_ANY, "Login existing account", wxPoint(450, 400), wxSize(400, 25));
    loginexistingacc->Bind(wxEVT_BUTTON, &ATMFrame::LoginExistingAcc, this);
    createanaccount = new wxButton(welcome, wxID_ANY, "Create a new account", wxPoint(450, 300), wxSize(400, 25));
    createanaccount->Bind(wxEVT_BUTTON, &ATMFrame::CreateNewAcc, this);
    welcomeatmp = new wxStaticText(welcome, wxID_ANY, "WELCOME TO ATM NG MGA POGI", wxPoint(200, 50));
    welcomeatmp->SetFont(pastFont);

    Welcome();
    Transaction();
    CheckBalance();
    Deposit();
    Withdraw();
    BankTransfer();
    Change();
    Register();
    ATransac();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(welcome, 1, wxEXPAND);
    mainSizer->Add(Menu, 1, wxEXPAND);
    mainSizer->Add(regpanel, 1, wxEXPAND);
    mainSizer->Add(transaction, 1, wxEXPAND);
    mainSizer->Add(balance, 1, wxEXPAND);
    mainSizer->Add(depositpanel, 1, wxEXPAND);
    mainSizer->Add(withdraw, 1, wxEXPAND);
    mainSizer->Add(BankTransferPanel, 1, wxEXPAND);
    mainSizer->Add(changepinpanel, 1, wxEXPAND);
    mainSizer->Add(atransaction, 1, wxEXPAND);

    Menu->Hide();
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

void ATMFrame::Welcome() {
    Menu = new wxPanel(this);
    MenuText = new wxStaticText(Menu, wxID_ANY, "WELCOME TO ATMP", wxPoint(150, 100));
    MenuText->SetFont(titleFont);

    EnterPin = new wxButton(Menu, wxID_ANY, "ENTER", wxPoint(520, 350), wxSize(100, 30));
    EnterPin = Transac.validateLoginOnBoth;

    pintext = new wxStaticText(Menu, wxID_ANY, "ENTER PIN", wxPoint(300, 330));
    pin = new wxTextCtrl(Menu, wxID_ANY, "", wxPoint(300, 350), wxSize(200, 30), wxTE_PASSWORD);
    pin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    EnterPin->Bind(wxEVT_BUTTON, &ATMFrame::OnButtonClicked, this);
}

// WAG MUNA GALAWIN
void ATMFrame::Register() {
    
    regpanel = new wxPanel(this);
    regpaneltxt = new wxStaticText(regpanel, wxID_ANY, "REGISTER ACCOUNT", wxPoint(170, 50));
    regpaneltxt->SetFont(pastFont);
    regnametxt = new wxStaticText(regpanel, wxID_ANY, "NAME :", wxPoint(150, 140));
    regnametxt->SetFont(brandFont);
    regnameField = new wxTextCtrl(regpanel, wxID_ANY, "", wxPoint(500, 140), wxSize(400, 25));

    regpintxt = new wxStaticText(regpanel, wxID_ANY, "PIN :", wxPoint(150, 190));
    regpintxt->SetFont(brandFont);
    regpinField = new wxTextCtrl(regpanel, wxID_ANY, "", wxPoint(500, 190), wxSize(400, 25));

    regbalancetxt = new wxStaticText(regpanel, wxID_ANY, "INITIAL DEPOSIT :", wxPoint(150, 240));
    regbalancetxt->SetFont(brandFont);
    regbalanceField = new wxTextCtrl(regpanel, wxID_ANY, "", wxPoint(500, 240), wxSize(400, 25));

    regcontacttxt = new wxStaticText(regpanel, wxID_ANY, "CONTACT NUMBER:", wxPoint(150, 290));
    regcontact63 = new wxStaticText(regpanel, wxID_ANY, "+63-", wxPoint(450, 290));
    regcontacttxt->SetFont(brandFont);
    regcontact63->SetFont(brandFont);
    regcontactField = new wxTextCtrl(regpanel, wxID_ANY, "*********", wxPoint(500, 290), wxSize(400, 25));
    regcontactField->SetFont(fieldFont);
    regcontactField->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (regcontactField->GetValue() == "*********") {
            regcontactField->SetFont(userinputfieldFont2);
            regcontactField->Clear();
        }
        event.Skip();
        });

    regcalendartxt = new wxStaticText(regpanel, wxID_ANY, "BIRTHDAY", wxPoint(150, 350));
    regcalendartxt->SetFont(brandFont);
    regcalendar = new wxCalendarCtrl(regpanel, wxID_ANY, wxDefaultDateTime, wxPoint (500, 350));
    //calendar->Bind(wxEVT_CALENDAR_SEL_CHANGED, &MainFrame::OnDateChanged, this);

    regsubmitbutton = new wxButton(regpanel, wxID_ANY, "SUBMIT", wxPoint(500, 550), wxSize(400, 25));
    regsubmitbutton->Bind(wxEVT_BUTTON, &ATMFrame::RegSubmitButton, this);
    regsubmitbutton->SetFont(userinputfieldFont2);
    
}



void ATMFrame::Transaction() {
    transaction = new wxPanel(this);
    transtxt = new wxStaticText(transaction, wxID_ANY, "TRANSACTION", wxPoint(260, 50));
    transtxt->SetFont(pastFont);

    AllButton = new wxButton(transaction, wxID_ANY, "BALANCE INQUIRY", wxPoint(100, 200), wxSize(300, 100));
    AllButton->SetFont(textFont);
    AllButton->Bind(wxEVT_BUTTON, &ATMFrame::BalanceButton, this);

    DButton = new wxButton(transaction, wxID_ANY, "DEPOSIT", wxPoint(100, 330), wxSize(300, 100));
    DButton->SetFont(textFont);
    DButton->Bind(wxEVT_BUTTON, &ATMFrame::DepositsButton, this);


    WButton = new wxButton(transaction, wxID_ANY, "WITHDRAW", wxPoint(100, 460), wxSize(300, 100));
    WButton->SetFont(textFont);
    WButton->Bind(wxEVT_BUTTON, &ATMFrame::WithdrawsButton, this);


    BTButton = new wxButton(transaction, wxID_ANY, "FUND TRANSFER", wxPoint(500, 200), wxSize(300, 100));
    BTButton->SetFont(textFont);
    BTButton->Bind(wxEVT_BUTTON, &ATMFrame::TransferButton, this);


    CButton = new wxButton(transaction, wxID_ANY, "CHANGE PIN", wxPoint(500, 330), wxSize(300, 100));
    CButton->SetFont(textFont);
    CButton->Bind(wxEVT_BUTTON, &ATMFrame::ChangeButton, this);


    exits = new wxButton(transaction, wxID_ANY, "EXIT", wxPoint(500, 460), wxSize(300, 100));
    exits->SetFont(textFont);
    exits->Bind(wxEVT_BUTTON, &ATMFrame::ExitButton, this);
}

void ATMFrame::CheckBalance() {
    balance = new wxPanel(this);
    baltxt = new wxStaticText(balance, wxID_ANY, "BALANCE INQUIRY", wxPoint(215, 50));
    baltxt->SetFont(pastFont);
    BackButton = new wxButton(balance, wxID_ANY, "BACK", wxPoint(550, 550), wxSize(300, 100));
    BackButton->SetFont(textFont);
    BackButton->Bind(wxEVT_BUTTON, &ATMFrame::BalanceBack, this);
}

void ATMFrame::Deposit() {
    depositpanel = new wxPanel(this);
    textD = new wxStaticText(depositpanel, wxID_ANY, "DEPOSIT", wxPoint(320, 50));
    textD->SetFont(pastFont);

    DepositButton = new wxButton(depositpanel, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    DepositButton->SetFont(textFont);
    DepositButton->Bind(wxEVT_BUTTON, &ATMFrame::DepositBack, this);

    amounttextD = new wxStaticText(depositpanel, wxID_ANY, "ENTER AMOUNT:", wxPoint(200, 150));
    amounttextD->SetFont(textFont);

    amountD = new wxTextCtrl(depositpanel, wxID_ANY, "minimum amount 500php", wxPoint(450, 150), wxSize(250, 30));
    amountD->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    amountD->SetFont(fieldFont);
    amountD->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (amountD->GetValue() == "minimum amount 500php") {
            amountD->SetFont(userinputfieldFont2);
            amountD->Clear();
        }
        event.Skip();
        });
   

    proceedD = new wxButton(depositpanel, wxID_ANY, "PROCEED", wxPoint(200, 200), wxSize(500, 100));
    proceedD->SetFont(textFont);
    proceedD->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransac, this);
}

void ATMFrame::Withdraw() {
    withdraw = new wxPanel(this);
    textWD = new wxStaticText(withdraw, wxID_ANY, "WITHDRAW", wxPoint(320, 50));
    textWD->SetFont(pastFont);

    WithdrawButton = new wxButton(withdraw, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    WithdrawButton->SetFont(textFont);
    WithdrawButton->Bind(wxEVT_BUTTON, &ATMFrame::WithdrawBack, this);

    amountW = new wxStaticText(withdraw, wxID_ANY, "ENTER AMOUNT:", wxPoint(200, 150));
    amountW->SetFont(textFont);

    enteramountW = new wxTextCtrl(withdraw, wxID_ANY, "", wxPoint(450, 150), wxSize(250, 30));
    enteramountW->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    enteramountW->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (enteramountW->GetValue() == "minimum amount 500php") {
            enteramountW->SetFont(userinputfieldFont2);
            enteramountW->Clear();
        }
        event.Skip();
        });

    proceedW = new wxButton(withdraw, wxID_ANY, "PROCEED", wxPoint(200, 200), wxSize(500, 100));
    proceedW->SetFont(textFont);
    proceedW->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransac, this);

}



void ATMFrame::BankTransfer() {
    BankTransferPanel = new wxPanel(this);
    BTtxt = new wxStaticText(BankTransferPanel, wxID_ANY, "FUND TRANSFER", wxPoint(230, 50));
    BTtxt->SetFont(pastFont);

    BankTransferButton = new wxButton(BankTransferPanel, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    BankTransferButton->SetFont(textFont);
    BankTransferButton->Bind(wxEVT_BUTTON, &ATMFrame::FundTransBack, this);

    recpnt_accntxt = new wxStaticText(BankTransferPanel, wxID_ANY, "ACCOUNT NUMBER", wxPoint(140, 150));
    recpnt_accntxt->SetFont(textFont);

    recpnt_accn = new wxTextCtrl(BankTransferPanel, wxID_ANY, "*****", wxPoint(500, 150), wxSize(250, 30));
    recpnt_accn->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    enteramountW->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (enteramountW->GetValue() == "*****") {
            enteramountW->SetFont(userinputfieldFont2);
            enteramountW->Clear();
        }
        event.Skip();
        });


    trans_entr_amnttxt = new wxStaticText(BankTransferPanel, wxID_ANY, "ENTER AMOUNT", wxPoint(140, 200));
    trans_entr_amnttxt->SetFont(textFont);
    trans_entr_amnt = new wxTextCtrl(BankTransferPanel, wxID_ANY, "minimum amount 500php", wxPoint(500, 200), wxSize(250, 30));
    trans_entr_amnt->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    trans_entr_amnt->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (trans_entr_amnt->GetValue() == "minimum amount 500php") {
            trans_entr_amnt->SetFont(userinputfieldFont2);
            trans_entr_amnt->Clear();
        }
        event.Skip();
        });

    proceed_trans_amnt = new wxButton(BankTransferPanel, wxID_ANY, "PROCEED", wxPoint(140, 250), wxSize(610, 60));
    proceed_trans_amnt->SetFont(textFont);
    proceed_trans_amnt->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransac, this);
}

void ATMFrame::Change() {
    changepinpanel = new wxPanel(this);
    changepintext = new wxStaticText(changepinpanel, wxID_ANY, "CHANGE PIN", wxPoint(275, 50));
    changepintext->SetFont(pastFont);

    ChangePinButton = new wxButton(changepinpanel, wxID_ANY, "CANCEL", wxPoint(550, 550), wxSize(300, 100));
    ChangePinButton->SetFont(textFont);
    ChangePinButton->Bind(wxEVT_BUTTON, &ATMFrame::ChangePinBack, this);

    CurrentPinText = new wxStaticText(changepinpanel, wxID_ANY, "CURRENT PIN:", wxPoint(220, 150));
    CurrentPinText->SetFont(textFont);

    CurrentPin = new wxTextCtrl(changepinpanel, wxID_ANY, "", wxPoint(420, 150), wxSize(250, 30));
    CurrentPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    NewPinText = new wxStaticText(changepinpanel, wxID_ANY, "NEW PIN:", wxPoint(220, 220));
    NewPinText->SetFont(textFont);

    NewPin = new wxTextCtrl(changepinpanel, wxID_ANY, "", wxPoint(420, 220), wxSize(250, 30));
    NewPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    VerifyNewPinText = new wxStaticText(changepinpanel, wxID_ANY, "CONFIRM PIN:", wxPoint(220, 270));
    VerifyNewPinText->SetFont(textFont);

    VerifyNewPin = new wxTextCtrl(changepinpanel, wxID_ANY, "", wxPoint(420, 270), wxSize(250, 30));
    VerifyNewPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    proceedCP = new wxButton(changepinpanel, wxID_ANY, "PROCEED", wxPoint(220, 320), wxSize(450, 60));
    proceedCP->SetFont(textFont);
    proceedCP->Bind(wxEVT_BUTTON, &ATMFrame::SChanged, this);
    
}

void ATMFrame::ATransac() {
    atransaction = new wxPanel(this);
    aTransac = new wxStaticText(atransaction, wxID_ANY, "WOULD YOU LIKE TO MAKE ANOTHER TRANSACTION?", wxPoint(275, 50));
    aTransac->SetFont(textFont);

    yesbutton = new wxButton(atransaction, wxID_ANY, "YES", wxPoint(220, 320), wxSize(450, 60));
    yesbutton->SetFont(textFont);
    nobutton = new wxButton(atransaction, wxID_ANY, "NO", wxPoint(620, 320), wxSize(450, 60));
    nobutton->SetFont(textFont);

    yesbutton->Bind(wxEVT_BUTTON, &ATMFrame::ATBack, this);
    nobutton->Bind(wxEVT_BUTTON, &ATMFrame::AnotherTransacNo, this);
}

void ATMFrame::LoginExistingAcc(wxCommandEvent& evt) {
    welcome->Hide();
    Menu->Show();
    Layout();
}

void ATMFrame::CreateNewAcc(wxCommandEvent& evt) {
    welcome->Hide();
    regpanel->Show();
    wxMessageBox("Account Successfully Created");
    Layout();
}

void ATMFrame::RegSubmitButton(wxCommandEvent& evt) {
    regpanel->Hide();
    Menu->Show();
    Layout();
}

void ATMFrame::OnButtonClicked(wxCommandEvent& evt) {
    Menu->Hide();
    transaction->Show();
    //regpanel->Show(); checker lang ng REGISTER PANEL
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

void ATMFrame::AnotherTransacNo(wxCommandEvent& evt) {
    wxLogMessage("Thank you for using our service!");
    Close(true);
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
