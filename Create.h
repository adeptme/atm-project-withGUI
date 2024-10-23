#pragma once
#include <fstream>
#include <String>
#include <wx/wx.h>

using namespace std;

struct Account {
    string name;
    int balance;
    string cardNum;
    string pin;
    string birthday;
    string contact;
    Account* next;
    Account() : balance(0), next(NULL) {}
};

class create {
private:

    Account* first; // points to first account
    Account* last; // points to last account

    //map<string, Account> accounts;
    string drivepath;

public:
    create() : first(NULL), last(NULL) {};

    wxString generateRandAccNum();
    wxString encrypt(wxString pin);
    wxString decrypt(wxString pin);

    bool isEmpty();
    bool detectFlashDrive();
    
    void retrieveFromDatabase();
    
    void datatoLink(wxString fileName, wxString filePin, wxString fileCardNum, int fileBalance, wxString fileBirthday, wxString fileContact);
    void createAccount(wxString tName, wxString tPin, int tBalance, wxString tBirthday, wxString tContactNum);

    void saveAccounts(wxString tCardNum, wxString tPin);
    void LinktoDatabase(wxString fileName, wxString filePin, wxString fileCardNum, int fileBalance, wxString fileBirthday, wxString fileContact);
    
    void idleUSB(create C);
};