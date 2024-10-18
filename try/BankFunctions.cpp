#include "BankFunctions.h"
#include <string>
#include <fstream>
#include <wx/wx.h>
#include <random>
#include <chrono>
#include <sstream>
#include <set>
#include <iomanip>
#include <windows.h>
#include <istream>
#include <iostream>
#include <wx/calctrl.h>

using namespace std;

// NEW ACC
void BankFunctions::newacc(info x) {
	user* newnode = new user(x);
	if (isempty()) {
		head = newnode;
	}
	else {
		user* temp = head;
		while (temp->next!= nullptr) {
			temp = temp->next;
		}
		temp->next = newnode;
	}
	usbhead = newnode;
	saveUSB();
}

// ADD ADD
void BankFunctions::Adduser(info x) {
	user* newnode = new user(x);
	if (isempty()) {
		head = newnode;
	}

	else {
		user* p = head;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = newnode;
		
	}
	
}
//=======================================================CHECKERS=========================================//
bool BankFunctions::isempty() {
	return (head == nullptr);
}

bool BankFunctions::usbempty() {
	return(usbhead == nullptr);
}

user* BankFunctions::gethead() {
	user* x = head;
	return x;
}

wxString BankFunctions::randAccNum() {
	static mt19937 gen(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<> distr(0, 999999999);

	int number = distr(gen);
	ostringstream intToNum;
	intToNum << setw(9) << setfill('0') << number;

	return intToNum.str();
}

bool BankFunctions::uniqueAccountNumber(wxString accountNumber) {
	user* currentNode = gethead();
	while (currentNode != nullptr) {
		if (currentNode->data.accnum == accountNumber) {
			return false;
		}
		currentNode = currentNode->next;
	}
	return true;
}


//===================================================TRANSACTIONS==============================================================//

bool BankFunctions::pincheck(wxString pin) {
	user* check = usbhead;
	if(check->data.accountpin==pin){
		return true;
	}
	else {
		return false;
	}
}

void BankFunctions::deposit(long double amount) {
	user* current = usbhead;
		current->data.balance += amount;
}

double BankFunctions::returnbalance() {
	user* current = usbhead;
	return current->data.balance;
}

wxString BankFunctions::returnaccnum() {
	user* current = usbhead;
	return current->data.accnum;
}

bool BankFunctions::withdraw(long double amount) {
	user* current = usbhead;
	if (current->data.balance < amount) {
		return false;
	}
	else {

		current->data.balance -= amount;
		return true;
	}
}

bool BankFunctions::Transfer(wxString userid, double long amount) {
	user* sender = usbhead;
	user* recipient = locateaddress(userid);

	if (sender == recipient) {
		wxMessageBox(" NOW YOU LOOK STUPID FOR DOING THAT ( YOU TRIED SENDING MONEY TO YOURSELF)");
		return false;
	}
	if (recipient == nullptr) {
		wxMessageBox("RECIPIENT NOT FOUND");
		return false;
	}
	
	if (sender->data.balance < amount) {
		wxMessageBox("INSUFFICIENT BALANCE IN YOUR ACCOUNT");
		return false;
	}

	else {
		sender->data.balance -= amount;
		recipient->data.balance += amount;
		wxMessageBox("FUNDS SUCCESSFULLY TRANSFERED");
		return true;
	}
}

bool BankFunctions::changepin(wxString currentpin, wxString newpin, wxString confirmpin) {
	user* current = usbhead;

	if (current->data.accountpin != currentpin) {
		wxMessageBox("Incorrect current PIN.");
		return false;
	}
	if (current->data.accountpin == newpin) {
		wxMessageBox("CANNOT USE THE CURRENT PIN");
		return false;
	}

	if (newpin != confirmpin) {
		wxLogMessage("New PIN and confirm PIN do not match.");
		return false;
	}

	if ((currentpin.length() != 4 && currentpin.length()!=6) || (newpin.length() != 4 && newpin.length()!=6) ) {
		wxLogMessage("PIN must be 4 or 6 digits.");
		return false;
	
	}
		usbhead->data.accountpin = confirmpin;
		return true;
		
}
//frfr


//==============================================FILE HANDLING=============================================//
bool BankFunctions::isFlashDriveInserted() {
	DWORD driveMask = GetLogicalDrives();
	for (char driveLetter = 'A'; driveLetter <= 'Z'; ++driveLetter) {
		if (driveMask & (1 << (driveLetter - 'A'))) {
			string drivePath = string(1, driveLetter) + ":\\";
			UINT driveType = GetDriveTypeA(drivePath.c_str());

			if (driveType == DRIVE_REMOVABLE) {
				return true;
			}
		}
	}
	return false;
}

void BankFunctions::savelocal() {
	ofstream myFile("BankAccountsIBM.txt");
	if (!myFile) {
		wxLogError("File Not Found");
		return;
	}


	myFile << "AccountName AccountNumber Balance Pin Bday" << endl;
	user* p = head;
	while (p != nullptr) {
		myFile << p->data.accname << " "
			<< p->data.accnum << " "
			<< p->data.balance << " "
			<< p->data.accountpin << " "
			<< p->data.bday <<endl;
		p = p->next;
	}

	myFile.close();
	wxLogMessage("Data saved successfully.");
}

void BankFunctions::retrievelocal() {
	info p;
	ifstream myFile("BankAccountsIBM.txt");
	if (!myFile) {
		wxLogError("File Errorg.");
		return;
	}

	string header;
	getline(myFile, header);
	string name, num, pin, bday;
	while (myFile >> name >> num >> p.balance >> pin >> bday) {
		p.accname = wxString(name);
		p.accnum = wxString(num);
		p.accountpin = pin;
		p.bday = wxString(bday);
		Adduser(p);
	}

	myFile.close();
	wxLogMessage("Data retrieved successfully.");
}

void BankFunctions::retrieveUSB() {
	string filePath = "D:/BankAccountsIBM-USB.txt";

	ifstream myFile(filePath);
	if (!myFile) {
		usbhead = nullptr;
		wxLogError("FILE DOES NOT EXIST, USB File Error: Could not open %s", filePath);
		return;
	}

	string header;
	string heder;
	header = wxString(heder);
	string num;
	wxString temp;
	getline(myFile, header);
	(myFile >> num);
	temp = wxString(num);
	myFile.close();
	if (doesaccexists(num)) {
		usbhead = locateaddress(num);
		wxLogMessage("Data retrieved from USB successfully and synced with usbhead.");
	}

}

bool BankFunctions::doesaccexists(wxString accnum) {
	user* traverse = head;
	while (traverse != nullptr) {
		if (traverse->data.accnum == accnum) {
			wxLogMessage("Account Exists!");
			return true;
		}
		traverse = traverse->next;
	}
	return false;
}

user* BankFunctions::locateaddress(wxString num) {
	user* temp = head;
	while (temp != nullptr) {
		if (temp->data.accnum == num) {
			return temp;
		}
		temp = temp->next;
	}
	return nullptr;
}




void BankFunctions::saveUSB() {
	string filePath = "D:/BankAccountsIBM-USB.txt";


	ofstream myFile(filePath);
	if (!myFile) {
		wxLogError("USB File Error: Could not find");
		return;
	}
	if (usbhead != nullptr) {
		myFile << "AccountNumber" << endl;
		myFile << usbhead->data.accnum << endl;
	}
	else {
		wxLogWarning("No account in usbhead to save.");
	}

	myFile.close();
	wxLogMessage("Account number saved to USB successfully ");
}

bool BankFunctions::recoverpin(wxString accnum, wxString bdayinput,wxString newpin) {
	user* temp = usbhead;
	if (temp->data.accnum != accnum) {
		wxMessageBox("Incorrect Account Number");
		return false;
	}

	if (temp == nullptr) {
		wxMessageBox("account not found");
		return false;
	}
	if (temp->data.bday == bdayinput) {
		temp->data.accountpin = newpin;
		wxMessageBox("CHANGED PIN");
			return true;
	}
	else {
		wxMessageBox("BDAY OR ACCOUNT NUM NOT MATCHED, PLEASE INPUT CORRECT BDAY");
		return false;
	}
}
