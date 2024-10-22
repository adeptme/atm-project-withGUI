/*#pragma once
#include <fstream>
#include <string>
#include <wx/wx.h>

using namespace std;

struct Account {
    wxString name;
    int balance;
    wxString cardNum;
    wxString pin;
    wxString birthday;
    wxString contact;
    Account* next;
    Account() : next(NULL) {}
};

class Create {
private:

    Account* first; // points to first account
    Account* last; // points to last account

    //map<wxString, Account> accounts;
    wxString drivepath;
    wxString generateRandAccNum();



    wxString createPin(wxString pin) {
        char ch;
        return pin;
    }

    wxString encrypt(wxString pin); 

    wxString decrypt(wxString pin);


public:
    Create() : first(NULL), last(NULL) {};

    bool isEmpty();
    bool detectFlashDrive();
    bool verifyPin(const Account& account);
    void retrieveFromDatabase();
    void saveAccounts(wxString tCardNum, wxString tPin);
    void DatatoLink(wxString fileName, wxString filePin, wxString fileCardNum, int fileBalance, wxString fileBirthday, wxString fileContactNum);
    void createAccount();
    void LinktoDatabase(wxString fileName, wxString filePin, wxString fileCardNum, int fileBalance, wxString fileBirthday, wxString fileContactNum);
    void idleUSB(Create create);

};*/

