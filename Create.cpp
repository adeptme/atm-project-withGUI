/*#include "Create.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <wxString>
#include <limits>
#include <algorithm>
#include <windows.h>
#include <conio.h>




wxString Create::decrypt(wxString pin) {   // decryption
    std::wxString temp = std::wxString(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] - 200;           // Decrypt by adjusting ASCII value
    }

    return wxString(temp);                 // Convert back to wxString and return
}

wxString Create::encrypt(wxString pin) {   // encryption
    std::wxString temp = std::wxString(pin.mb_str()); // Convert wxString to std::wxString

    for (size_t i = 0; i < temp.size(); i++) {
        temp[i] = temp[i] + 200;           // Encrypt by adjusting ASCII value
    }

    return wxString(temp);                 // Convert back to wxString and return
}

wxString Create :: generateRandAccNum() {
    int accNum = rand() % 90000 + 10000;
    //validator
    wxString converted = Format(wxT("%d"), (int)accNum);
    return converted;
}

bool Create::isEmpty() {
    return (first == NULL && last == NULL);
}

bool Create::detectFlashDrive() {
    DWORD fd = GetLogicalDrives();
    //cout << "Flash drive detected: ";
    for (char drive = 'D'; drive <= 'Z'; drive++) {
        if (fd & (1 << (drive - 'A'))) { // drive checker
            wxString fdpath = wxString(1, drive) + ":/"; // makes a wxString storing the path to drive

            //cout << fdpath << " "; // debug

            if (GetDriveTypeA(fdpath.c_str()) == DRIVE_REMOVABLE) {
                //cout << "\nFlash drive detected at: " << fdpath << endl;
                drivepath = fdpath + "ATMaccount.txt"; // directory of ATMAccount.txt in the drive
                ifstream file(drivepath);
                if (file.good()) { // exits program as file exists
                    //cout << "Account already created." << endl << "Terminating Program";
                    exit(0);
                }
                else { // file does not exist 
                    return true;
                }
            }
        }
    } // no flash drive found
    //cout << "\nNo removable flash drive detected." << endl;
    return false;
}

void Create::saveAccounts(wxString tCardNum, wxString tPin) {
    if (drivepath.empty()) {
        //cout << "The Flash Drive is not yet inserted." << endl;
        system("pause");
        return;
    }

    //cout << "Saving accounts to: " << drivepath << endl; // debug

    ofstream createFile(drivepath);
    if (!createFile) {
        //cout << "Error in opening the file" << endl;
        system("pause");
        return;
    }

    if (isEmpty()) {
        //cout << "No accounts to save. The accounts map is empty." << endl;
        system("pause");
        return;
    }
    createFile << tCardNum << " " << encrypt(tPin);
    createFile.close();
    //cout << "Accounts saved successfully to: " << drivepath << endl; // debug
}

void Create::retrieveFromDatabase() {
    ifstream file("accounts.txt", ios::in);  // Open the file in read mode
    if (!file.is_open()) {
        // Handle error opening file
        return;
    }

    string fileName, filePin, fileCardNumber, fileBalanceStr, fileBirthday, fileContactNum;

    // Read until the end of the file
    while (getline(file, fileName)) {
        getline(file, filePin);
        getline(file, fileCardNumber);
        getline(file, fileBalanceStr);   // Read balance as string first
        getline(file, fileBirthday);     // Read birthday
        getline(file, fileContactNum);   // Read contact number

        // Convert std::string to wxString for other fields
        wxString wxFileName(fileName);
        wxString wxFilePin(filePin);
        wxString wxFileCardNumber(fileCardNumber);
        wxString wxFileBirthday(fileBirthday);
        wxString wxFileContactNum(fileContactNum);

        // Convert balance from string to int
        int fileBalance = std::stoi(fileBalanceStr);

        // Pass wxStrings and int balance to DatatoLink
        DatatoLink(wxFileName, wxFilePin, wxFileCardNumber, wxFileBalance, wxFileBirthday, wxFileContactNum);
    }

    file.close();
}

void Create::DatatoLink(wxString fileName, wxString filePin, wxString fileCardNum, int fileBalance, wxString fileBirthday, wxString fileContactNum) {
    Account* newAccount = new Account();
    newAccount->name = fileName;
    newAccount->balance = fileBalance;
    newAccount->cardNum = fileCardNum;
    newAccount->pin = filePin;
    newAccount->birthday = fileBirthday;       // Set birthday
    newAccount->contact = fileContactNum;   // Set contact number
    newAccount->next = NULL;

    /* // Debugging the content of the new account
     cout << "User: " << newAccount->name << endl;
     cout << "Card Number: " << newAccount->cardNum << endl;
     cout << "Pin: " << newAccount->pin << endl;
     cout << "Balance: " << newAccount->balance << endl;
     cout << "Birthday: " << newAccount->birthday << endl;  // Display birthday
     cout << "Contact Number: " << newAccount->contact << endl;  // Display contact number
     system("pause");*/


/*


    if (isEmpty()) {
        first = last = newAccount;
    }
    else {
        last->next = newAccount;
        last = newAccount;
    }
}

void Create::createAccount() {
    wxString tName, tPin, tCardNum, tBalance, tBirthday, tContactNum;

    // Generate a unique account number
    Account* search = first;
    do {
        tCardNum = generateRandAccNum();
        search = search->next;
    } while (search != NULL);  // Check if the account number already exists

    //cout << "\nEnter account holder's name: ";
    //cin.ignore();
    //getline(cin, tName);
    
    bool valid_balance = false;
    do {
        //cout << "Enter initial balance: ";
        //cin >> tBalance;
        int balanceamount = std::stoi(tBalance);

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ////cout << "Invalid balance! Please enter a valid number." << endl;
        }
        else if (balanceamount < 0) {
            ////cout << "Balance cannot be negative!" << endl;
        }
        else {
            valid_balance = true;
        }
        tBalance = std::to_string(balanceamount);
    } while (!valid_balance);

    tPin = createPin();

    //cout << "\nEnter Birthday (MMDDYYYY): "; cin >> tBirthday;
    //cout << "\nEnter Contact Number (+63): "; cin >> tContactNum;

    //cout << "\nAccount created successfully! \nYour account number is: " << tCardNum << endl;


    // Add the new account to the linked list
    LinktoDatabase(tName, tPin, tCardNum, tBalance, tBirthday, tContactNum); // reuse function

    // Save the updated accounts to file
    saveAccounts(tCardNum, tPin);  // This saves the current accounts to the flash drive
}

void Create::LinktoDatabase(wxString fileName, wxString filePin, wxString fileCardNum, wxString fileBalance, wxString fileBirthday, wxString fileContactNum) {
    ofstream file("accounts.txt", ios::app); // Open in append mode
    if (file.is_open()) {
        Account* current = last;
        wxString tName, tPin, tCardNum, tBalance, tBirthday, tContactNum;
        while (current != NULL) {
            file << fileName << endl
                << filePin << endl
                << fileCardNum << endl
                << fileBalance << endl
                << fileBirthday << endl  // Save birthday
                << fileContactNum << endl;       // Save contact number

            current = current->next;

            /*if (current != NULL) {
                file << endl; // Add a new line between accounts
            }*/


/*////////////
        }
        saveAccounts(tCardNum, tPin);
        file.close();  // Close the file after writing
    }
    else {
        //cout << "Unable to open file." << endl;
    }
}

void Create::idleUSB(Create create) {
    if (detectFlashDrive() == false) {
        system("cls");
        //cout << "PLEASE INSERT A FLASH DRIVE." << endl;
        Sleep(1);
        idleUSB(create);
    }
    else {
        //cout << "FLASH DRIVE DETECTED";
        return;
    }
}

int main() {
    Create create;
    srand(time(0));
    create.idleUSB(create);
    create.retrieveFromDatabase();
    create.createAccount();

    return 0;
}
