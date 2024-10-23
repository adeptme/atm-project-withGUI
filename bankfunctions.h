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
    account() : balance(0), next(NULL) {}
};

class transaction {  //user info and storing it to file handling keme
private:
    account* first;
    account* accounts;
    account* login;
public:

    transaction() : first(NULL), accounts(NULL), login(NULL) {}
    wxString decrypt(wxString pin);
    wxString encrypt(wxString pin);
    bool isEmpty();
    bool detectFlashDrive();
    bool accountFound(wxString target);

    void retrieve();
    void saveToFile();
    void filetoLink(wxString fileName, wxString filePin, wxString fileCardNumber, int fileBalance, wxString fileBirthday, wxString fileContact);

    bool search(wxString acc_num, wxString pin);
    bool validateLoginOnBoth(wxString pin);
    bool searchInUSB(wxString acc_num, wxString pin);
    bool userLogin(wxString pin);
    //bool validateOnBoth(wxwxString acc_num, wxwxString pin, wxwxString (*decryptFunc)(const wxwxString&));
    void idleUSB(transaction transac);

    void changePIN();
    int withdraw(int inputbalance);
    int checkBal();
    int bankTrans(int amounttransfer, wxString targetcardnum);
    //void accSett();
    //void updateAccount(const account& updatedAccount);
    void updatePinInFile(wxString newPin);
    bool loginWithFlashDrive();
};
