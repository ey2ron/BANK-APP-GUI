#pragma once
#include <fstream>
#include <string>
#include <wx/wx.h>

struct info{
	wxString accname;
	wxString accnum;
	long double balance;
	wxString accountpin;
	wxString bday;
};
//hello
struct user {
	info data;
	user* next;
	user(info x) :data(x), next(nullptr) {}
};

class BankFunctions
{
private:
	user* head = nullptr;
	user* usbhead = nullptr;
public:
	bool isempty();
	bool isFlashDriveInserted();
	void savelocal();
	void retrievelocal();
	void newacc(info x);
	void Adduser(info x);
	bool usbempty();
	bool uniqueAccountNumber(wxString accountNumber);
	wxString randAccNum();
	user* gethead();
	bool doesaccexists(wxString num);
	user* locateaddress(wxString num);
	void saveUSB();
	void retrieveUSB();
	bool pincheck(wxString pin);
	void deposit(long double amount);
	bool withdraw(long double amount);
	double returnbalance();
	wxString returnaccnum();
	bool Transfer(wxString userid, double long amount);
	bool changepin(wxString currentpin, wxString newpin, wxString confirmpin);
	bool recoverpin(wxString accnum,wxString bdayinpt, wxString newpin);
	
	wxString encryption(wxString input);
	wxString decrypt(wxString input);
	
};

