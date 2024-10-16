#pragma once
#include <fstream>
#include <string>
#include <wx/wx.h>

struct info{
	wxString accname;
	wxString accnum;
	long double balance;
	wxString accountpin;
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

	void deposit(long double amount);
	
};

