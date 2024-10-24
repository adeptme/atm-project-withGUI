#pragma once
#include <fstream>
#include <String>
#include <wx/wx.h>

struct account {
    wxString name;
    wxString cardNum;
    wxString pincode;
    wxString birthday;
    int balance;
    wxString contact;
    account* next;
    account() : balance(0), next(nullptr) {}
};

class transaction {  //user info and storing it to file handling keme
private:
    account* first;
    account* accounts;
    account* login;
public:
    transaction() : first(nullptr), accounts(nullptr), login(nullptr) {}
    
    // encryption & decryption
    wxString decrypt(wxString pin);
    wxString encrypt(wxString pin);

    // search function
    bool isEmpty();
    int detectFlashDrive();
    bool accountFound(wxString target);
    bool search(wxString acc_num, wxString pin);
    bool validateLoginOnBoth(wxString pin);
    bool searchInUSB(wxString acc_num, wxString pin);
    bool userLogin(wxString pin);
    bool comparepin(wxString newPIN);
    bool changePIN(wxString currentPin, wxString newPin);

    // file handling
    void retrieve();
    void saveToFile();
    void filetoLink(wxString fileName, wxString filePin, wxString fileCardNumber, int fileBalance, wxString fileBirthday, wxString fileContact);

    // bank functions
    int deposit(int Damount);
    int withdraw(int inputbalance);
    int checkBal();
    int bankTrans(int amounttransfer, wxString targetcardnum);
    void updatePinInFile(wxString newPin);
};
