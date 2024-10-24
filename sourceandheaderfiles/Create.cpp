#include "Create.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <String>
#include <limits>
#include <algorithm>
#include <windows.h>
#include <conio.h>

wxString create::decrypt(wxString pin) {   // decryption
    string temp = string(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] - 200;           // Decrypt by adjusting ASCII value
    }

    return temp;                 // Convert back to wxString and return
}

wxString create::encrypt(wxString pin) {   // encryption
    string temp = string(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] + 200;           // Encrypt by adjusting ASCII value
    }

    return temp;                 // Convert back to wxString and return
}

wxString create:: generateRandAccNum() {
    int accNum = rand() % 90000 + 10000;
    //validator
    wxString converted;
    converted << accNum;
    return converted;
}

bool create::isEmpty() {
    return (first == NULL && last == NULL);
}


int create::detectFlashDrive() {
    DWORD fd = GetLogicalDrives();

    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) { // drive checker
            wxString fdpath = wxString(1, drive) + ":/"; // makes a wxString storing the path to drive

            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) {
                
                drivepath = fdpath + "ATMaccount.txt"; // directory of ATMAccount.txt in the drive
                ifstream file(drivepath);
                if (file.good()) { // exits program as file exists
    
                    return 0;
                }
                else { // file does not exist 
                    return 1;
                }
            }
        }
    } // card is not detected
    return -1;
}

void create::saveAccounts(wxString tCardNum, wxString tPin) {

    string drivepath, fdpath;
    DWORD fd = GetLogicalDrives();
    //cout << "Flash drive detected: ";
    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) {
            fdpath = string(1, drive) + ":/"; // makes a wxString storing the path to drive

            //cout << fdpath << " "; // debug

            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) {
                drivepath = fdpath + "ATMaccount.txt";
                //cout << "\nFlash drive detected at: " << fdpath << endl;
            }
        }
    }

    if (drivepath.empty()) {
        wxLogMessage("Insert USB.");
        return;
    }

    ofstream createFile(drivepath);
    if (!createFile) { // Error in opening the file
        wxLogMessage("USB file cannot be opened.");
        return;
    }

    if (isEmpty()) { // No accounts to save. The accounts map is empty.
        wxLogMessage("No accounts in linked list.");
        return;
    }
    createFile << tCardNum << " " << encrypt(tPin);
    createFile.close();
    // Accounts saved successfully
}

void create::retrieveFromDatabase() {
    ifstream file("accounts.txt", ios::in);  // Open the file in read mode
    if (!file.is_open()) { // Handle error opening file
        return;
    }

    string fileName, filePin, fileCardNumber, fileBalance, fileBirthday, fileContact;

    // Read until the end of the file
    while (getline(file, fileName)) {
        getline(file, filePin);
        getline(file, fileCardNumber);
        getline(file, fileBalance);   
        getline(file, fileBirthday);   
        getline(file, fileContact); 

        int fileBal = stoi(fileBalance);
        datatoLink(fileName, filePin, fileCardNumber, fileBal, fileBirthday, fileContact);
    }

    file.close();
}

void create::datatoLink(wxString fileName, wxString filePin, wxString fileCardNum, int fileBalance, wxString fileBirthday, wxString fileContact) {
    Account* newAccount = new Account();
    newAccount->name = fileName;
    newAccount->balance = fileBalance;
    newAccount->cardNum = fileCardNum;
    newAccount->pin = filePin;
    newAccount->birthday = fileBirthday;      
    newAccount->contact = fileContact;  
    newAccount->next = NULL;
    if (isEmpty()) {
        first = last = newAccount;
    }
    else {
        last->next = newAccount;
        last = newAccount;
    }
}

void create::createAccount(wxString tName, wxString tPin, int tBalance, wxString tBirthday, wxString tContact) {
    wxString tCardNum;
    retrieveFromDatabase();
    Account* search = first;
    do {
        tCardNum = generateRandAccNum();
        search = search->next;
    } while (search != NULL); 

    wxMessageBox("ACCOUNT REGISTERED!!!");
    wxMessageBox("CARD NUMBER: " + tCardNum + "\nName: " + tName + "\nBirthday: " + tBirthday + "\nContact Number: " + tContact);
    
    LinktoDatabase(tName, tPin, tCardNum, tBalance, tBirthday, tContact); 
    
    saveAccounts(tCardNum, tPin); 
    }


void create::LinktoDatabase(wxString fileName, wxString filePin, wxString fileCardNum, int fileBalance, wxString fileBirthday, wxString fileContact) {
    ofstream file("accounts.txt", ios::app); // Open in append mode
    if (file.is_open()) {
        Account* current = last;
        while (current != NULL) { 
            file << fileName << endl
                << filePin << endl
                << fileCardNum << endl
                << fileBalance << endl
                << fileBirthday << endl  
                << fileContact << endl;     

            current = current->next;
        }
        saveAccounts(fileCardNum, filePin);
        file.close();  
    } // in append mode to put the new account to bottom of the txt file
}
