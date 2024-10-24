#include "bankfunctions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <sstream>

using namespace std;

wxString transaction::decrypt(wxString pin) {   // decryption
    string temp = string(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] - 200;           // Decrypt by adjusting ASCII value
    }

    return temp;                 // Convert back to wxString and return
}

wxString transaction::encrypt(wxString pin) {   // encryption
    string temp = string(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] + 200;           // Encrypt by adjusting ASCII value
    }

    return temp;                 // Convert back to wxString and return
}

bool transaction::isEmpty() {
    return (first == NULL && accounts == NULL);
}

int transaction::detectFlashDrive() {
    DWORD fd = GetLogicalDrives();
    
    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) {
            string fdpath = string(1, drive) + ":/"; // makes a wxString storing the path to drive

            //cout << fdpath << " "; // debug

            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) {

                string drivepath = fdpath + "ATMaccount.txt"; // directory of ATMAccount.txt in the drive
                ifstream file(drivepath);
                if (file.good()) { // program proceeds to logging in
                    file.close();
                    return 1;
                }
                else { // exits program as file does not exist
                    file.close();
                    return 0;
                }
            }
        }
    }
    // card is not detected
    return -1;
}

bool transaction::accountFound(wxString target) {
    account* validator = first;

    while (validator != NULL) {
        if (validator->cardNum == target) {
            return true;
        }
        validator = validator->next;
    }
    return false;
}

bool transaction::searchInUSB(wxString acc_num, wxString pin) {
    
    string drivepath, fdpath;
    DWORD fd = GetLogicalDrives();
    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) {
            fdpath = string(1, drive) + ":/"; // makes a wxString storing the path to drive


            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) {
                drivepath = fdpath + "ATMaccount.txt";
                
            }
        }
    }
    ifstream file(drivepath);
    if (!file.is_open()) {
        wxLogMessage("CARD was ejected.");
        return false;
    }

    string fileCardNumber, encryptedPin;
    while (file >> fileCardNumber >> encryptedPin) {
        
        wxMessageBox(acc_num);
        if (fileCardNumber == acc_num) {
            // Decrypt the PIN
            wxString decryptedPin = decrypt(encryptedPin);
           
            wxMessageBox(decryptedPin);
            // Compare decrypted PIN with the user's input PIN
            if (decryptedPin == pin) {
                file.close();
                return true;
            }
        }
    }

    file.close();
    return false;
}

void transaction::saveToFile() {
    account* save = first;
    ofstream file("accounts.txt");
    if (file.is_open()) {
        while (save != NULL) {
            file << save->name << endl
                << save->pincode << endl
                << save->cardNum << endl
                << save->balance << endl
                << save->birthday << endl
                << save->contact << endl;

            save = save->next;

        }
    }
    file.close();
}

void transaction::filetoLink(wxString fileName, wxString filePin, wxString fileCardNumber, int fileBalance, wxString fileBirthday, wxString fileContact) { // pushes data of file to a linked list
    account* newaccount = new account();
    newaccount->name = fileName;
    newaccount->cardNum = fileCardNumber;
    newaccount->pincode = filePin;
    newaccount->balance = fileBalance;
    newaccount->birthday = fileBirthday;
    newaccount->contact = fileContact;
    newaccount->next = NULL;

    if (isEmpty()) {
        first = accounts = newaccount;
    }
    else {
        accounts->next = newaccount;
        accounts = newaccount;
    }
}

void transaction::retrieve() {
    ifstream file("accounts.txt");
    if (!file.is_open()) { // File Error
        return;
    }
    string fileName, filePin, fileCardNumber,fileBalance, fileBirthday, fileContact;

    while (!file.eof()) {
        getline(file, fileName);
            if (fileName.empty()) { // to prevent the iteration if stream reads a blank line
                return;
            }
        getline(file, filePin);
        getline(file, fileCardNumber);
        getline(file, fileBalance);
        getline(file, fileBirthday);
        getline(file, fileContact);

        int fileBal = stoi(fileBalance);
        filetoLink(fileName, filePin, fileCardNumber, fileBal, fileBirthday, fileContact);
    }
    file.close();
}

bool transaction::validateLoginOnBoth(wxString pin) {
    string drivepath, fdpath;
    DWORD fd = GetLogicalDrives();

    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) {
            fdpath = string(1, drive) + ":/"; // makes a wxString storing the path to drive

            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) { // Flash drive detected
                drivepath = fdpath + "ATMaccount.txt";
                
            }
        }
    }
    ifstream file(drivepath);
    string acc_num;
    file >> acc_num;

    wxString acc_numconverted(acc_num.c_str());

    if (!file.is_open()) { // Error opening USB file
        wxLogMessage("Error reading file.");
        return false;
    }
    file.close();
    
    return (search(acc_numconverted, pin) && searchInUSB(acc_numconverted, pin));
}

bool transaction::userLogin(wxString pin) {

    if (validateLoginOnBoth(pin) == true) { // Log In Successfully
        return true;
    }
    else { // Account Number or PIN incorrect
        return false;
    }
}

bool transaction::search(wxString acc_num, wxString pin) {

    account* search = first;

    while (search != NULL) {
        if (search->cardNum == acc_num) {
            if (search->pincode == pin) {
                login = search;
                return true;
            }
            else {
                return false;
            }
        }
        search = search->next;
    }
    return false;
}

int transaction::deposit(int Damount) {

    if (login->balance >= Damount) {
        
        login->balance += Damount;
        saveToFile();
        return login->balance;
    }
}

int transaction::withdraw(int inputbalance) {
    if (login->balance >= inputbalance) {
        login->balance -= inputbalance;
        saveToFile();
        return login->balance;
    }
    return -1;
}

int transaction::checkBal() {
    int temp = login->balance;

    return temp;
}

int transaction::bankTrans(int amounttransfer, wxString targetcardnum) {

    while (1) {

        if (accountFound(targetcardnum)) {

            if (login->balance >= amounttransfer) {
                account* targetAccount = first;

                // Find the target account
                while (targetAccount != NULL) {
                    if (targetAccount->cardNum == targetcardnum) {
                        login->balance -= amounttransfer;

                        targetAccount->balance += amounttransfer;

                        saveToFile();
                        return login->balance;
                    }
                    targetAccount = targetAccount->next;
                }
            }
            else {
            }
        }
    }
}

bool transaction::changePIN(wxString currentPin, wxString newPin) {

    if (comparepin(currentPin) == true) {
        login->pincode = newPin;
        saveToFile();
        updatePinInFile(newPin);
        return true;
    }
}

bool transaction::comparepin(wxString newPIN) {
    if (newPIN == login->pincode) {
        return true;
    }
    return false;
}

void transaction::updatePinInFile(wxString newPin) {

    string drivepath, fdpath;
    DWORD fd = GetLogicalDrives();
    //cout << "Flash drive detected: ";
    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) {
            fdpath = string(1, drive) + ":/"; // makes a wxString storing the path to drive

            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) {
                drivepath = fdpath + "ATMaccount.txt";
            }
        }
    }
   
    ofstream changefile(drivepath);

    if (!changefile) {
        return;
    }
    wxString encrypted = encrypt(newPin);
    
    changefile << login->cardNum << " " << encrypted;
    changefile.close();
}
