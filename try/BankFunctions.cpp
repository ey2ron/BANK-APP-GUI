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

using namespace std;



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

void BankFunctions::savelocal(){
	ofstream myFile("BankAccountsIBM.txt");
	if (!myFile) {
		wxLogError("File Not Found");
		return;
	}


	myFile << "AccountName AccountNumber Balance Pin" << endl;
	user* p = head;
	while (p != nullptr) {
		myFile << p->data.accname << " "
			<< p->data.accnum << " "
			<< p->data.balance << " "
			<< p->data.accountpin << endl;
		p = p->next;
	}

	myFile.close();
	wxLogMessage("Data saved successfully.");
}

void BankFunctions::retrievelocal(){
	info p;
	ifstream myFile("BankAccountsIBM.txt");
	if (!myFile) {
		wxLogError("File Errorg.");
		return;
	}

	string header;
	getline(myFile, header);
	string name, num, pin;
	while (myFile >> name >> num >> p.balance >> pin) {
		p.accname = wxString(name);
		p.accnum = wxString(num);
		p.accountpin = pin;
		Adduser(p);
	}

	myFile.close();
	wxLogMessage("Data retrieved successfully.");
}

bool BankFunctions::checkUSB() {
	info p;
	string absolutepath = "D:/BankAccountsIBM-USB.txt";
	ifstream myFile(absolutepath);

	string header;
	string name, num, pin;

	getline(myFile, header);
	while (myFile >> name >> num >> p.balance >> pin){
		p.accname = wxString(name);
		p.accnum = wxString(num);
		p.accountpin = pin;
		if (accverify(p.accnum)) {
			usbhead->data = p;
			myFile.close();
			return true;
		}
	}
	myFile.close();
	return false;
}

void BankFunctions::saveUSB() {
	user* acc2save2usb = usbhead;
	ofstream myFile("D:/BankAccountsIBM-USB.txt");
	myFile << "AccountName AccountNumber Balance Pin" << endl;
	myFile << acc2save2usb->data.accname << " " 
		<< acc2save2usb->data.accnum << " " 
		<< acc2save2usb->data.balance << " " 
		<< acc2save2usb->data.accountpin << endl;
	myFile.close();
}

bool BankFunctions::accverify(wxString accountnum) {
	
	user* x = head;
	wxString numpin;
	while (x != NULL) {
		if (x->data.accnum == accountnum) {
			if (x->data.accountpin == numpin) {
				return true;
			}
		}
		x = x->next;
	}
	return false;
}

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


