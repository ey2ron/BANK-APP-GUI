#include "MainFrame.h"
#include <wx/wx.h>
#include <Windows.h>
#include <regex>

using namespace std;

 wxPanel* panel;
 wxPanel* bankpanel;
 wxPanel* atmPanel;
 wxPanel* ThankyouPanel;
 wxPanel* PinPanel;
 wxPanel* EnrollPanel;
 wxPanel* enterpinPanel;
 wxButton* ConfirmButton;
 wxTextCtrl* InputPin;
 wxTextCtrl* Inputname;
 wxButton* ExitEnrollButton; 
 wxTextCtrl* pinenter;
 wxButton* pinverify;

 //================================================= TRANSACTION PANELS ======================================//
 wxPanel* depositPanel;
 /**/wxTextCtrl* depositamount;
 /**/wxButton* depositbutton;

 wxPanel* balancePanel;

 wxPanel* withdrawPanel;

 wxPanel* transferPanel;

 wxPanel* pinPanel;

 wxPanel* exitPanel;


 
 wxFont buttonFont(14, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 wxFont ThankyouFont(28, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 

 MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
     
     if (!bank.isFlashDriveInserted()) {
         wxLogError("No flash drive detected. Please insert a flash drive to continue.");
         Close(true);
         return;
     }
     else {
         bank.retrievelocal();
         bank.retrieveUSB();
         FirstPanel();
     }
 }
// STARTMENU
void MainFrame::FirstPanel() {
    panel = new wxPanel(this);
    panel->SetBackgroundColour(*wxLIGHT_GREY);

    // Interact with the Bank button
    wxPanel* IBbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 318), wxSize(504, 94));
    IBbuttonPanel->SetBackgroundColour(*wxBLACK);
    wxButton* IBbutton = new wxButton(IBbuttonPanel, wxID_ANY, "Interact with the Bank", wxPoint(2, 2), wxSize(500, 90));
    IBbutton->SetFont(buttonFont);
    IBbutton->Bind(wxEVT_BUTTON, &MainFrame::OnButton1Clicked, this);

    // Interact with ATM Machine button 
    wxPanel* IMbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 418), wxSize(504, 94));
    IMbuttonPanel->SetBackgroundColour(*wxBLACK);
    wxButton* IMbutton = new wxButton(IMbuttonPanel, wxID_ANY, "Interact with ATM Machine", wxPoint(2, 2), wxSize(500, 90));
    IMbutton->SetFont(buttonFont);
    IMbutton->Bind(wxEVT_BUTTON, &MainFrame::OnButton2Clicked, this);

    // Exit Program button
    wxPanel* EbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 518), wxSize(504, 94));
    EbuttonPanel->SetBackgroundColour(*wxBLACK);
    wxButton* Ebutton = new wxButton(EbuttonPanel, wxID_ANY, "Exit Program", wxPoint(2, 2), wxSize(500, 90));
    Ebutton->SetBackgroundColour(*wxWHITE);
    Ebutton->SetForegroundColour(*wxBLACK);
    Ebutton->SetFont(buttonFont);
    Ebutton->Bind(wxEVT_ENTER_WINDOW, [Ebutton](wxMouseEvent&) {
        Ebutton->SetForegroundColour(*wxRED);
        Ebutton->Refresh();
        });
    Ebutton->Bind(wxEVT_LEAVE_WINDOW, [Ebutton](wxMouseEvent&) {
        Ebutton->SetForegroundColour(*wxBLACK);
        Ebutton->Refresh();
        });
    Ebutton->Bind(wxEVT_BUTTON, &MainFrame::OnButton3Clicked, this);
   
}
    // BANK MENU
void MainFrame::OnButton1Clicked(wxCommandEvent& evt) {
  
    panel->Hide();
        bankpanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
        bankpanel->SetBackgroundColour(*wxWHITE);   
        

        // Enroll for a Bank Account button
        wxPanel* enrollPanel = new wxPanel(bankpanel, wxID_ANY, wxPoint(378, 318), wxSize(504, 94));
        enrollPanel->SetBackgroundColour(*wxBLACK);
        wxButton* enrollButton = new wxButton(enrollPanel, wxID_ANY, "Enroll for a Bank Account", wxPoint(2, 2), wxSize(500, 90));
        enrollButton->SetFont(buttonFont);
        enrollButton->Bind(wxEVT_BUTTON, &MainFrame::OnEnrollButtonClicked, this);
       

        // Return to Main Menu button
        wxPanel* returnPanel = new wxPanel(bankpanel, wxID_ANY, wxPoint(378, 518), wxSize(504, 94));
        returnPanel->SetBackgroundColour(*wxBLACK);
        wxButton* returnButton = new wxButton(returnPanel, wxID_ANY, "3. Return back to the main menu", wxPoint(2, 2), wxSize(500, 90));
        returnButton->SetFont(buttonFont);
        returnButton->Bind(wxEVT_BUTTON, &MainFrame::OnReturnButtonClicked, this);
    
}
//ENROLL PANEL

void MainFrame::OnEnrollButtonClicked(wxCommandEvent& evt) {
    if (bank.usbempty()) {
        bankpanel->Hide();
        EnrollPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
        EnrollPanel->SetBackgroundColour(*wxWHITE);
        EnrollPanel->Show();

        Inputname = new wxTextCtrl(EnrollPanel, wxID_ANY, "", wxPoint(378, 318), wxSize(504, 94));
        Inputname->SetFont(buttonFont);
        Inputname->Bind(wxEVT_TEXT, &MainFrame::OnInputChanged, this);


        InputPin = new wxTextCtrl(EnrollPanel, wxID_ANY, "", wxPoint(378, 418), wxSize(504, 94));
        InputPin->SetFont(buttonFont);
        InputPin->Bind(wxEVT_TEXT, &MainFrame::OnInputChanged, this);
        InputPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

        ConfirmButton = new wxButton(EnrollPanel, wxID_ANY, "Confirm Account", wxPoint(378, 518), wxSize(504, 94));
        ConfirmButton->SetFont(buttonFont);
        ConfirmButton->Bind(wxEVT_BUTTON, &MainFrame::onConfirmButtonClicked, this); ConfirmButton->Disable();

        ExitEnrollButton = new wxButton(EnrollPanel, wxID_ANY, "return to menu", wxPoint(378, 618), wxSize(504, 94));
        ExitEnrollButton->SetFont(buttonFont);
        ExitEnrollButton->Bind(wxEVT_BUTTON, &MainFrame::ExitEnroll, this);
    }else{
        wxLogMessage("EXISTING ACCOUNT IN FLASHDRIVE FOUND, CANNOT ENROLL FOR NEW");
        return;
    }

}

//EXIT ENROLL
void MainFrame::ExitEnroll(wxCommandEvent& evt){
    EnrollPanel->Hide();
    panel->Show();
}


//INPUT PARAMETERS
void MainFrame::OnInputChanged(wxCommandEvent& evt){
    if (Inputname && InputPin) {
        wxString sname = Inputname->GetValue();
        wxString pin = InputPin->GetValue();
        if (!sname.IsEmpty() && (pin.length() == 4 || pin.length() == 6)) {
            ConfirmButton->Enable();
        }
        else {
            ConfirmButton->Disable();
		}
	}
}

//CONFIRMATION BUTTON
void MainFrame::onConfirmButtonClicked(wxCommandEvent& evt) {
	info temp;
	
		wxString sname = temp.accname = Inputname->GetValue();
		wxString spin = temp.accountpin = InputPin->GetValue();
		temp.balance = 5000;
		temp.accnum = bank.randAccNum();
		bank.newacc(temp);
        bank.savelocal();
        wxLogMessage("Account Added");
        EnrollPanel->Hide();
        bankpanel->Show();
	
}


void MainFrame::OnReturnButtonClicked(wxCommandEvent& evt) {
    bankpanel->Hide();
    panel->Show();
}

//ATM MENU
void MainFrame::OnButton2Clicked(wxCommandEvent& evt) {
    panel->Hide();
    enterpinPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    pinenter = new wxTextCtrl(enterpinPanel, wxID_ANY,"ENTER PIN HERE", wxPoint(378, 18), wxSize(504, 94));
    pinenter->SetFont(buttonFont);
    pinenter->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    pinenter->Bind(wxEVT_TEXT, &MainFrame::PinEnterChanged, this);

    pinverify = new wxButton(enterpinPanel, wxID_ANY, "Confirm Pin", wxPoint(378, 100), wxSize(400, 94));
    pinverify->SetFont(buttonFont);
    pinverify->Bind(wxEVT_BUTTON, &MainFrame::pinverifybutton, this);
   
}

void MainFrame::PinEnterChanged(wxCommandEvent& evt) {

}

void MainFrame::pinverifybutton(wxCommandEvent& evt) {
    wxString pin = pinenter->GetValue();
    if (bank.pincheck(pin)) {
        enterpinPanel->Hide();
        ATMPANEL();
    }
    else {
        wxLogMessage("WRONG PIN");
        return;
    }
}

void MainFrame::ATMPANEL() {
    //enterpinPanel->Hide();
    atmPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    atmPanel->SetBackgroundColour(*wxWHITE);

    // Display Balance Button
    balancePanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 18), wxSize(504, 94));
    balancePanel->SetBackgroundColour(*wxBLACK);
    wxButton* balanceButton = new wxButton(balancePanel, wxID_ANY, "Display Balance", wxPoint(2, 2), wxSize(500, 90));
    balanceButton->SetFont(buttonFont);
    balanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnDisplayBalanceClicked, this);


    // Withdraw Button
    withdrawPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 118), wxSize(504, 94));
    withdrawPanel->SetBackgroundColour(*wxBLACK);
    wxButton* withdrawButton = new wxButton(withdrawPanel, wxID_ANY, "Withdraw", wxPoint(2, 2), wxSize(500, 90));
    withdrawButton->SetFont(buttonFont);
    withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnWithdrawClicked, this);

    // Deposit Button

    wxButton* depositButton = new wxButton(atmPanel, wxID_ANY, "Deposit", wxPoint(378, 218), wxSize(500, 90));
    depositButton->SetFont(buttonFont);
    depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositClicked, this);

    // Fund Transfer Button
    transferPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 318), wxSize(504, 94));
    transferPanel->SetBackgroundColour(*wxBLACK);
    wxButton* transferButton = new wxButton(transferPanel, wxID_ANY, "Fund Transfer", wxPoint(2, 2), wxSize(500, 90));
    transferButton->SetFont(buttonFont);
    transferButton->Bind(wxEVT_BUTTON, &MainFrame::OnTransferClicked, this);

    // Change PIN Button
    pinPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 418), wxSize(504, 94));
    pinPanel->SetBackgroundColour(*wxBLACK);
    wxButton* pinButton = new wxButton(pinPanel, wxID_ANY, "Change PIN", wxPoint(2, 2), wxSize(500, 90));
    pinButton->SetFont(buttonFont);
    pinButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangePinClicked, this);

    // Exit and Save Button
    exitPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(378, 518), wxSize(504, 94));
    exitPanel->SetBackgroundColour(*wxBLACK);
    wxButton* exitButton = new wxButton(exitPanel, wxID_ANY, "Exit and Save", wxPoint(2, 2), wxSize(500, 90));
    exitButton->SetFont(buttonFont);
    exitButton->Bind(wxEVT_BUTTON, &MainFrame::OnExitATMClicked, this);

}


 
void MainFrame::OnDisplayBalanceClicked(wxCommandEvent& evt) {
    
}
void MainFrame::OnWithdrawClicked(wxCommandEvent& evt) {
   
}



void MainFrame::OnDepositClicked(wxCommandEvent& evt) {
    depositPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    depositPanel->SetBackgroundColour(*wxLIGHT_GREY);
    atmPanel->Hide();
    depositPanel->Show();

  
    depositamount = new wxTextCtrl(depositPanel, wxID_ANY, "INPUT AMOUNT TO DEPOSIT", wxPoint(378, 518), wxSize(500, 90));
    depositamount->SetFont(buttonFont);
    depositamount->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    depositbutton = new wxButton(depositPanel, wxID_ANY, "DEPOSIT", wxPoint(378, 418), wxSize(500, 90));
    depositbutton->SetFont(buttonFont);
    depositbutton->Bind(wxEVT_BUTTON, &MainFrame::ondepositamount,this);
}

void MainFrame::ondepositamount(wxCommandEvent& evt) {
    wxString depo = depositamount->GetValue();
    double depostr;
    if (!depo.ToCDouble(&depostr)) {
        wxMessageBox("Please enter a valid numeric amount.", "Input Error", wxOK | wxICON_ERROR);
        return;
    }
    bank.deposit(depostr);
    wxMessageBox("DEPOSIT SUCCESS");
    bank.savelocal();
    depositPanel->Hide();
    atmPanel->Show();
}

void MainFrame::OnTransferClicked(wxCommandEvent& evt) {
    
}

void MainFrame::OnChangePinClicked(wxCommandEvent& evt) {
        
}

void MainFrame::OnExitATMClicked(wxCommandEvent& evt) {
    atmPanel->Hide();
    ThankyouPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    ThankyouPanel->SetBackgroundColour(*wxLIGHT_GREY); 
    wxStaticText* thanks = new wxStaticText(ThankyouPanel, wxID_ANY, "Thank you for using the program, Have a Nice day!", wxPoint(100, 318), wxSize(350, 70));
    thanks->SetFont(ThankyouFont);
    wxButton* OkayButton = new wxButton(ThankyouPanel, wxID_ANY, "Continue", wxPoint(578, 518), wxSize(220, 50));
    OkayButton->SetFont(buttonFont);
    OkayButton->Bind(wxEVT_BUTTON, &MainFrame::OnOkayButtonClicked, this);

}

void MainFrame::OnOkayButtonClicked(wxCommandEvent& evt) {
    wxLogMessage("Data Saved. System is Closing");
    Close(true);
}

void MainFrame::OnButton3Clicked(wxCommandEvent& evt) {
    wxLogMessage("System Closing");
    Close(true); 
}