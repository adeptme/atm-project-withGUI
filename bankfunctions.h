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
    account() : next(NULL) {}
};

class transaction {  //user info and storing it to file handling keme
private:
    account* first;
    account* accounts;
    account* login;
    wxString drivepath;
    wxString fdpath;

    

public:
    transaction() : first(NULL), accounts(NULL), login(NULL) {}
    wxString decrypt(wxString pin);
    wxString encrypt(wxString pin);
    bool isEmpty();
    bool detectFlashDrive();
    bool accountFound(wxString target);

    void mainMenu();

    void retrieve();
    void saveToFile();
    void filetoLink(wxString fileName, wxString filePin, wxString fileCardNumber, wxString fileBalance, wxString fileBirthday, wxString fileContact);

    bool search(wxString acc_num, wxString pin);
    bool validateLoginOnBoth(wxString acc_num, wxString pin);
    bool searchInUSB(wxString acc_num, wxString pin);
    bool userLogin();
    //bool validateOnBoth(wxwxString acc_num, wxwxString pin, wxwxString (*decryptFunc)(const wxwxString&));
    void idleUSB(transaction transac);

    void changePIN();
    void withdraw();
    void checkBal();
    void bankTrans();
    void accSett();
    void updateAccount(const account& updatedAccount);
    void updatePinInFile(wxString newPin);
    void loginWithFlashDrive();
};
