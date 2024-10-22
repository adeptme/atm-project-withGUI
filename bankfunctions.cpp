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
    wxString temp = wxString(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] - 200;           // Decrypt by adjusting ASCII value
    }

    return wxString(temp);                 // Convert back to wxString and return
}

wxString transaction::encrypt(wxString pin) {   // encryption
    wxString temp = wxString(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] + 200;           // Encrypt by adjusting ASCII value
    }

    return wxString(temp);                 // Convert back to wxString and return
}

bool transaction::isEmpty() {
    return (first == NULL && accounts == NULL);
}

bool transaction::detectFlashDrive() {
    DWORD fd = GetLogicalDrives();
    //cout << "Flash drive detected: ";
    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) {
            fdpath = wxString(1, drive) + ":/"; // makes a wxString storing the path to drive

            //cout << fdpath << " "; // debug

            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) {
                //cout << "\nFlash drive detected at: " << fdpath << endl;
                drivepath = fdpath + "ATMaccount.txt"; // directory of ATMAccount.txt in the drive
                ifstream file(drivepath);
                if (file.good()) { // program proceeds to logging in
                    //cout << "Account in USB exists.";
                    file.close();
                    return true;
                }
                else { // exits program as file does not exist
                    file.close();
                    //cout << "Card is not registered.";
                    exit(0);
                }
            }
        }
    }
    //cout << "\nNo removable flash drive detected." << endl;
    return false;
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
    ifstream file(drivepath);
    if (!file.is_open()) {
        //cout << "Error opening USB file." << endl;
        return false;
    }

    wxString fileCardNumber, encryptedPin;
    while (file >> fileCardNumber >> encryptedPin) {
        if (fileCardNumber == acc_num) {
            // Decrypt the PIN
            wxString decryptedPin = decrypt(encryptedPin);
            //cout << endl << "Decryted Pin: " << decryptedPin << endl;

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
    else {
        //cout << "Unable to open file.";
    }
    file.close();
}

void transaction::filetoLink(wxString fileName, wxString filePin, wxString fileCardNumber, wxString fileBalance, wxString fileBirthday, wxString fileContact) { // pushes data of file to a linked list
    account* newaccount = new account();
    newaccount->name = fileName;
    newaccount->cardNum = fileCardNumber;
    newaccount->pincode = filePin;
    newaccount->balance = fileBalance;
    newaccount->birthday = fileBirthday;
    newaccount->contact = fileContact;
    newaccount->next = NULL;

    //cout << "User: " << newaccount->name << endl;
    //cout << "Card Number: " << newaccount->cardNum << endl;
    //cout << "Pin: " << newaccount->pincode << endl;
    //cout << "Balance: " << newaccount->balance << endl;
    //cout << "Birthday: " << newaccount->birthday << endl;
    //cout << "Contact Number: " << newaccount->contact << endl << endl;
    system("pause");

    if (isEmpty()) {
        first = accounts = newaccount;
        //cout << "first account" << endl;

    }
    else {
        accounts->next = newaccount;
        accounts = newaccount;
    }
}

void transaction::retrieve() {
    ifstream file("accounts.txt");
    if (!file.is_open()) {
        //cout << "File Error" << endl;
        return;
    }
    wxString skip;
    wxString fileName, filePin, fileCardNumber, fileBalance, fileBirthday, fileContact;

    while (!file.eof()) {
        //getline(file, skip); // to skip 1st line
        getline(file, fileName);
        if (fileName.empty()) {
            return;
        }
        getline(file, filePin);
        getline(file, fileCardNumber);
        getline(file, fileBalance);
        getline(file, fileBirthday);
        getline(file, fileContact);


        filetoLink(fileName, filePin, fileCardNumber, fileBalance, fileBirthday, fileContact);
    }
    file.close();
}

bool transaction::validateLoginOnBoth(wxString acc_num, wxString pin) {
    return (search(acc_num, pin) && searchInUSB(acc_num, pin));
}

bool transaction::userLogin() {

    //cout << "User: " << first->name << endl;
    //cout << "Pin: " << first->pincode << endl;
    //cout << "Card Number: " << first->cardNum << endl;
    //cout << "Balance: " << first->balance << endl << endl;
    //cout << "Birthday: " << first->birthday << endl;
    //cout << "Contact Number: " << first->contact << endl << endl;

    wxString acc_num, pin;
    //cout << "Enter your account number: ";
    //cin >> acc_num;
    //cout << "Enter your pin: ";
    //cin >> pin;


    if (validateLoginOnBoth(acc_num, pin) == true) {
        //cout << "\n\nLog In Successfully!!!\n";
        system("pause");
        return true;
    }
    else {
        //cout << "\n\nAccount Number or PIN incorrect!!!\n";
        system("pause");
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

void transaction::mainMenu() {
    //cout << "\n***************************";
    //cout << "\n\tATM MACHINE\n";
    //cout << "***************************";
    //cout << "\n1.) Login";
    //cout << "\n0.) Exit";
    //cout << "\nEnter your choice: ";
}

void transaction::withdraw() {
    int amount;
    //cout << "Enter amount to withdraw: ";
    //cin >> amount;

    int bal = std::stoi(login->balance);

    if (bal >= amount) {
        bal -= amount;

        login->balance = std::to_string(bal);

        //cout << "Withdrawal successful! Remaining balance: " << fixed << setprecision(2) << bal << endl;
        saveToFile();
    }
    else {
        //cout << "Insufficient balance!\n";
    }
}

void transaction::checkBal() {
    wxString balance;
    int bal = std::stoi(login->balance);
    if (bal > 0) {
        //cout << " Your current balance is: " << login->balance << endl;
    }
    else {
        //cout << "Invalid balance." << endl;
    }
}

void transaction::bankTrans() {
    int amountrans;
    wxString targetcardnum;

    while (1) {
        //cout << "Enter the target account number: ";
        //cin >> targetcardnum;

        if (accountFound(targetcardnum)) {
            //cout << "Enter amount to transfer: ";
            //cin >> amountrans;

            if (login->balance >= amountrans) {
                account* targetAccount = first;

                // Find the target account
                while (targetAccount != NULL) {
                    if (targetAccount->cardNum == targetcardnum) {
                        login->balance -= amountrans;

                        int targetbal += targetAccount->balance;

                        //cout << "Transfer Successful! Your remaining balance is " << bal << endl;

                        saveToFile();
                        return;
                    }
                    targetAccount = targetAccount->next;
                }
            }
            else {
                //cout << "Insufficient Balance!" << endl;
            }
        }
        else {
            char retry;
            //cout << "Target account not found! Would you like to try again? (Y/N): ";
            //cin >> retry;

            if (retry == 'Y' || retry == 'y') {
                continue;
            }
            else {
                //cout << "Transfer cancelled!" << endl;
                return;
            }
        }
    }
}

void transaction::loginWithFlashDrive() {

    wxString acc_num, pin;
    //cout << "Enter your account number: ";
    //cin >> acc_num;
    //cout << "Enter your PIN: ";
    //cin >> pin;

    if (validateLoginOnBoth(acc_num, pin)) {
        //cout << "\n\nLog In Successfully!!!\n";
    }
    else {
        //cout << "\n\nAccount Number or PIN incorrect!!!\n";
    }
}

/*
void transaction::accSett() {
    wxString newPin;
    //cout << "Enter new PIN (4 digits): ";

    while (true) {
        newPin.clear();
        char ch;
        while (newPin.length() < 4) {
            ch = _getch();
            if (isdigit(ch)) {
                newPin += ch;
                //cout << '*';
            } else if (ch == 13) {
                break;
            } else if (ch == 8 && !newPin.empty()) {
                newPin.pop_back();
                //cout << "\b \b";
            }
        }

        if (newPin.length() == 4) {
            break;
        } else {
            //cout << "\nInvalid input. PIN must be exactly 4 digits." << endl;
            //cout << "Enter new PIN (4 digits): ";
        }
    }


    login->pincode = newPin;

    //cout << "\nPIN updated successfully." << endl;

    //updateAccount(*login);
    //updatePinInFile(*login, newPin);
} */

void transaction::changePIN() {
    wxString newPin;

    //cout << "Enter your PIN: ";
    //cin >> newPin;

    login->pincode = newPin;
    saveToFile();
    updatePinInFile(newPin);
}

void transaction::updatePinInFile(wxString newPin) {

    ofstream changefile(drivepath);

    if (!changefile) {
        //cout << "Error opening file!" << endl;
        return;
    }
    wxString encrypted = encrypt(newPin);
    changefile << login->cardNum << " " << encrypted;

    ////cout << temp << endl;

    //cout << "Account PIN in USB changed!" << endl;
    changefile.close();
}

void transaction::idleUSB(transaction transac) {
    if (detectFlashDrive() == false) {
        system("cls");
        //cout << "PLEASE INSERT A FLASH DRIVE." << endl;
        Sleep(1);
        idleUSB(transac);
    }
    else {
        //cout << "FLASH DRIVE DETECTED";
        return;
    }
}


int main() {
    transaction transac;
    int choice;
    transac.retrieve();
    transac.idleUSB(transac);

    while (1) {
        transac.mainMenu();
        //cin >> choice;
        switch (choice) {
        case 1:
            while (1) {
                system("cls");
                transac.detectFlashDrive();

                // Detect flash drive before login
                if (transac.userLogin() == true) {

                    transac.checkBal();
                    //transac.withdraw();
                    //transac.bankTrans();
                    transac.changePIN();
                    break;
                }
            }
            break;

        case 0:
            system("cls");
            //cout << "Thank you for using this ATM";
            return 0;

        default:
            //cout << "Invalid choice, Please try again.";
        }
    }
}
