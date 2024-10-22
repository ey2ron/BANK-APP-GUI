#include "MainFrame.h"
#include <wx/wx.h>
#include <Windows.h>
#include <regex>
#include <wx/calctrl.h>
#include <wx/textfile.h>

using namespace std;

wxColour customColor(177, 195, 154); 
wxString bdaydate;

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
 wxButton* Forgotpin;
 wxButton* ExitEnrollButton; 
 wxButton* IMbutton;
 wxTextCtrl* pinenter;
 wxButton* pinverify;
 wxCalendarCtrl* calendar;
 wxPanel* IBbuttonPanel;
 wxTextCtrl* reenterPin;
 wxTextCtrl* reenternewpin;

 //================================================= TRANSACTION PANELS =============================================//
 wxPanel* depositPanel;
 /**/wxTextCtrl* depositamount;
 /**/wxButton* depositbutton;
 /**/wxButton* Exitdepobutton;

 wxPanel* balancePanel;
 /**/wxStaticText* DisplayBalance;
 /**/wxStaticText* DisplayAccnum;
 /**/wxButton* Exitbalancebutton;

 wxPanel* withdrawPanel;
 /**/wxTextCtrl* withdrawamount;
 /**/wxButton* withdrawbutton;
 /**/wxButton* exitwithdraw;


 wxPanel* transferPanel;
 /**/wxTextCtrl* Targetrecipient;
 /**/wxTextCtrl* TransferAmount;
 /**/wxButton* ConfirmTransfer;
 /**/wxButton* exittransfer;

 wxPanel* pinPanel;
 /**/wxTextCtrl* CurrentPin;
 /**/wxTextCtrl* NewPin;
 /**/wxTextCtrl* ConfirmNewPin;
 /**/wxButton* ConfirmPinbutton;
 /**/wxButton* ExitChangePin;

 wxPanel* Recoverpanel;
 /**/wxTextCtrl* recoveraccnum;
 /**/wxTextCtrl* recoverbdayyear;
 /**/wxTextCtrl* recoverbdaymonth;
 /**/wxTextCtrl* recoverbdayday;
 /**/wxTextCtrl* createnewpin;
 /**/wxButton* recoverpin;
 /**/wxButton* exitrecover;

 wxPanel* exitPanel;

 //mascot signuppanel
 wxStaticText* mascotpanel1;
 wxStaticText* mascotpanel2;
 wxStaticText* mascotpanel3;
 wxStaticText* mascotpanel4;
 wxStaticText* mascotpanel5;

 wxFont inputfont(12, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
 wxFont inputfont2(20, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
 wxFont inputfont3(38, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
 wxFont buttonFont(14, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 wxFont buttonFont1(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 wxFont ThankyouFont(28, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 wxFont ASCIIFont(14, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD);
 wxFont ASCIIFont1(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 wxFont ASCIIFont2(20, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 wxFont DisplayFont(34, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

 //====================================================================================================================//

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
    panel->SetBackgroundColour(customColor); 

    IBMlogo();
    
    // Interact with the Bank button
    IBbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 318), wxSize(504, 94));
    IBbuttonPanel->SetBackgroundColour(*wxBLACK);
    wxButton* IBbutton = new wxButton(IBbuttonPanel, wxID_ANY, "Interact with the Bank", wxPoint(2, 2), wxSize(500, 90));
    IBbutton->SetFont(buttonFont);
    IBbutton->Bind(wxEVT_BUTTON, &MainFrame::OnButton1Clicked, this);

    
    
    // Interact with ATM Machine button 
    wxPanel* IMbuttonPanel = new wxPanel(panel, wxID_ANY, wxPoint(378, 418), wxSize(504, 94));
    IMbuttonPanel->SetBackgroundColour(*wxBLACK);
    IMbutton = new wxButton(IMbuttonPanel, wxID_ANY, "Interact with ATM Machine", wxPoint(2, 2), wxSize(500, 90));
    IMbutton->SetFont(buttonFont);
    
    if (bank.usbempty()) {
        IMbutton->Disable();
    }
   
  
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

void MainFrame::IBMlogo() {
    wxPanel* logopanel1 = new wxPanel(panel, wxID_ANY, wxPoint(385, 80), wxSize(300, 200));
    wxStaticText* staticText1 = new wxStaticText(logopanel1, wxID_ANY,
        "    / $$$$$$ \n"
        "   | _   $$ _/ \n"
        "       |  $$    \n"
        "       |  $$    \n"
        "       |  $$    \n"
        "       |  $$    \n"
        "    / $$$$$$  \n"
        "   | ______/  \n",
        wxPoint(10, 10));
    staticText1->SetFont(ASCIIFont);

    wxPanel* logopanel2 = new wxPanel(panel, wxID_ANY, wxPoint(525, 80), wxSize(300, 200));
    wxStaticText* staticText2 = new wxStaticText(logopanel2, wxID_ANY,
        "   /$$$$$$$   \n"
        "  | $$   __  $$  \n"
        "  | $$        \\ $$ \n"
        "  | $$$$$$$   \n"
        "  | $$   __  $$  \n"
        "  | $$         \\ $$ \n"
        "  | $$$$$$$/  \n"
        "  |_______/  ",
        wxPoint(10, 10));
    staticText2->SetFont(ASCIIFont);

    wxPanel* logopanel3 = new wxPanel(panel, wxID_ANY, wxPoint(665, 80), wxSize(300, 200));
    wxStaticText* staticText3 = new wxStaticText(logopanel3, wxID_ANY,
        "      / $$          / $$ \n"
        "     | $$$       / $$$ \n"
        "     | $$$$   / $$$$ \n"
        "     | $$ $$/$$   $$ \n"
        "     | $$  $$$   | $$ \n"
        "     | $$  \\ $     | $$ \n"
        "     | $$   \\/      | $$ \n"
        "     |__/           |__/",
        wxPoint(10, 10));
    staticText3->SetFont(ASCIIFont);
}

    // BANK MENU
void MainFrame::OnButton1Clicked(wxCommandEvent& evt) {
   

    panel->Hide();
        bankpanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
        bankpanel->SetBackgroundColour(customColor);   
        

        wxPanel* thebank = new wxPanel(bankpanel, wxID_ANY, wxPoint(285, 80), wxSize(900, 200));
        wxStaticText* thebankk = new wxStaticText(thebank, wxID_ANY,
            " _________  ____  ____  ________        ______        _       ____  _____  ___  ____   \n"
            "|  _   _  ||_   ||   _||_   __  |      |_   _ \\      / \\     |_   \\|_   _||_  ||_  _|  \n"
            "|_/ | | \\_|  | |__| |    | |_ \\_|        | |_) |    / _ \\      |   \\ | |    | |_/ /    \n"
            "    | |      |  __  |    |  _| _         |  __'.   / ___ \\     | |\\ \\| |    |  __'.    \n"
            "   _| |_    _| |  | |_  _| |__/ |       _| |__) |_/ /   \\ \\_  _| |_\\   |_  _| |  \\ \\_  \n"
            "  |_____|  |____||____||________|      |_______/|____| |____||_____ \\____||____||____| \n",
            wxPoint(10, 10));
        thebankk->SetFont(ASCIIFont1);

        // Enroll for a Bank Account button
        wxButton* enrollButton = new wxButton(bankpanel, wxID_ANY, "Enroll for a Bank Account", wxPoint(378, 290), wxSize(500, 90));
        enrollButton->SetFont(buttonFont);
        enrollButton->Bind(wxEVT_BUTTON, &MainFrame::OnEnrollButtonClicked, this);
       
        // FORGOT PIN
        Forgotpin = new wxButton(bankpanel, wxID_ANY,"Forgot Pin", wxPoint(378, 390), wxSize(504, 94));
        Forgotpin->SetFont(buttonFont);
        Forgotpin->Bind(wxEVT_BUTTON, &MainFrame::OnRecoverPin, this);

        // Return to Main Menu button
        wxPanel* returnPanel = new wxPanel(bankpanel, wxID_ANY, wxPoint(1100, 660), wxSize(170, 50));
        returnPanel->SetBackgroundColour(*wxBLACK);
        wxButton* returnButton = new wxButton(returnPanel, wxID_ANY, " return ", wxPoint(2, 2), wxSize(165, 45));
        returnButton->SetFont(buttonFont1);
        returnButton->Bind(wxEVT_BUTTON, &MainFrame::OnReturnButtonClicked, this);
    
}


//ENROLL PANEL

void MainFrame::OnEnrollButtonClicked(wxCommandEvent& evt) {
    if (bank.usbempty()) {
        bankpanel->Hide();

        EnrollPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
        EnrollPanel->SetBackgroundColour(customColor);
        EnrollPanel->Show();

        wxPanel* thebank2 = new wxPanel(EnrollPanel, wxID_ANY, wxPoint(320, 10), wxSize(600, 110));
        wxStaticText* thebankk2 = new wxStaticText(thebank2, wxID_ANY,
            "  ______   _____   ______  ____  _____   _____  _____  _______   \n"
            ".' ____ \\ |_   _|.' ___  ||_   \\|_   _| |_   _||_   _||_   __ \\  \n"
            "| (___ \\_|  | | / .'   \\_|  |   \\ | |     | |    | |    | |__) | \n"
            " _.____`.   | | | |   ____  | |\\ \\| |     | '    ' |    |  ___/  \n"
            "| \\____) | _| |_\\ `.___]  |_| |_\\   |_     \\ \\__/ /    _| |_     \n"
            " \\______.'|_____|`._____.'|_____| \\____|     `.__.'    |_____|    \n",
            wxPoint(10, 10));
        thebankk2->SetFont(ASCIIFont1);

        wxPanel* ascii = new wxPanel(EnrollPanel, wxID_ANY, wxPoint(810,100), wxSize(900,700));
        wxStaticText* ascii2 = new wxStaticText(ascii, wxID_ANY,
            "                  :%*-                              \n"
            "                .*+++*:                             \n"
            "               .#+=@++%.                            \n"
            "              =*+==@++++                            \n"
            "             +++=+%@+++#:                           \n"
            "            =*==*%*@+++++                           \n"
            "           =*+#***#%++++#.                          \n"
            "          .#+%%*+++++++++++#%:.                     \n"
            "         :#++++++++++++++++++++#+.                  \n"
            "       .%+++++++++++++++++++++++++%=#%**+++++++++   \n"
            "      .*++++++++++++%+++++++++++++++++++++#%+++%.   \n"
            "     .%++++*###*+++++++++++++++++++++*#%#%%#+#=.    \n"
            "     +++**.    .=+++++++++++#@@++++++%*%#+=++-      \n"
            "    .@+%.  +@@%: ++++++++++++++++++++#*===++%.      \n"
            "    .#+=  #@@@@@::+++++++++++++++++++*+*#+*=        \n"
            "   .+++%. #@@@@@.+++++++++*#*+#++++++#+=+#.         \n"
            "  .*++++#. :**:.#+++++++#-....  %++++++#--@%%:.     \n"
            "  -*#::-*+*###*++++++++*:@@@@@* .#+++++ :+   .=     \n"
            "  =++#%#+++++++++**++++-#@@@@@@. %+++#. :=    =:    \n"
            "  .+%++++++++++*++#+++++#-@@@@@% .#++*-  .-:    +   \n"
            "**+*.#++++++++%##%+++++#=:=-..-*++#:     :--+*%.+   \n"
            "%@+++.%++++++*      ++++++++++++++%.      .*+++%.   \n"
            " -#+++.+%#++++#    +++++++**##+++*.        =+++*    \n"
            "   -#+++.@%%*+%%++++++++++#=:-#%.         .%+++-    \n"
            "    .-#++.#%#%%#*++++++++++++*%           .*++*:    \n"
            "      *++-  =%#%##%@@@%@@@%@@#.          .%+++#.    \n"
            "       *+%..#*##:***%%#*++++@#%          ++++%.     \n"
            "      -+#: #*=  .*+=%%#*###*=.        .*+++*:      \n"
            "       #+#:        ..*#-             -#+++*:       \n"
            "       *+++*:      .*+++###+%      -#++++#.        \n"
            "       .%+++++#%%#*+++++++++#   -%+++++**.         \n"
            "         +#*****##%%%%#####%%#*++*+##**.           \n"
            "          .%###%.   -%######*+++#%%@:              \n"
            "            =%##%.     .=*####*+-.                 \n"
            "             :%%%.                                  ",                                                                                 
            wxPoint(10, 10));
        ascii2->SetFont(ASCIIFont1);
        ascii2->SetForegroundColour(wxColour(37, 72, 210));



        wxStaticText* SInputname = new wxStaticText(EnrollPanel, wxID_ANY, "Input Name:", wxPoint(40, 130), wxSize(450, 30));
        SInputname->SetFont(buttonFont); 
        Inputname = new wxTextCtrl(EnrollPanel, wxID_ANY, "", wxPoint(40, 150), wxSize(500, 30));
        Inputname->SetFont(inputfont);
        Inputname->Bind(wxEVT_TEXT, &MainFrame::OnInputChanged, this);
        mascotpanel1 = new wxStaticText(EnrollPanel, wxID_ANY, "Hi New User!", wxPoint(650, 180), wxSize(200, 30));
        mascotpanel1->SetFont(ASCIIFont2);
        mascotpanel1->SetForegroundColour(wxColour(37, 72, 210));
        mascotpanel1->Hide();
        Inputname->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent&) {
            mascotpanel2->Hide();
            mascotpanel3->Hide();
            mascotpanel1->Show();
            mascotpanel5->Hide();
            mascotpanel4->Hide();
            });
      
        wxStaticText* SCalendar = new wxStaticText(EnrollPanel, wxID_ANY, "Select your birth date:", wxPoint(40, 400), wxSize(450, 30));
        SCalendar->SetFont(buttonFont);
        calendar = new wxCalendarCtrl(EnrollPanel, wxID_ANY, wxDefaultDateTime, wxPoint(40, 415), wxSize(220, 170));
        calendar->SetFont(buttonFont);
        calendar->Bind(wxEVT_CALENDAR_SEL_CHANGED, &MainFrame::OnDateChanged, this);
        mascotpanel3 = new wxStaticText(EnrollPanel, wxID_ANY, "Your birth date will\nbe needed for\nrecovering account.", wxPoint(575, 180), wxSize(190, 30));
        mascotpanel3->SetFont(ASCIIFont2);
        mascotpanel3->SetForegroundColour(wxColour(37, 72, 210));
        mascotpanel3->Hide();
        calendar->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent&) {
            mascotpanel1->Hide();
            mascotpanel4->Hide();
            mascotpanel2->Hide();
            mascotpanel5->Hide();
            mascotpanel3->Show();
            });

        wxStaticText* SInputpin = new wxStaticText(EnrollPanel, wxID_ANY, "Input Password (4 or 6 Digits)", wxPoint(40, 220), wxSize(450, 30));
        SInputpin->SetFont(buttonFont);
        InputPin = new wxTextCtrl(EnrollPanel, wxID_ANY, "", wxPoint(40, 250), wxSize(500, 30), wxTE_PASSWORD);
        InputPin->SetFont(inputfont);
        InputPin->Bind(wxEVT_TEXT, &MainFrame::OnInputChanged, this);
        InputPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));
        mascotpanel2 = new wxStaticText(EnrollPanel, wxID_ANY, "Please do not forget\nyour password ^^", wxPoint(575, 180), wxSize(190, 30));
        mascotpanel2->SetFont(ASCIIFont2);
        mascotpanel2->SetForegroundColour(wxColour(37, 72, 210));
        mascotpanel2->Hide();
        InputPin->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent&) {
            mascotpanel1->Hide();
            mascotpanel5->Hide();
            mascotpanel3->Hide();
            mascotpanel4->Hide();
            mascotpanel2->Show();
            });

        wxStaticText* SreenterPin = new wxStaticText(EnrollPanel, wxID_ANY, "Reenter Pin:", wxPoint(40, 310), wxSize(450, 30));
        SreenterPin->SetFont(buttonFont);
        reenterPin = new wxTextCtrl(EnrollPanel, wxID_ANY, "", wxPoint(40, 340), wxSize(500, 30), wxTE_PASSWORD);
        reenterPin->SetFont(inputfont);
        reenterPin->Bind(wxEVT_TEXT, &MainFrame::OnInputChanged, this);
        reenterPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

        ConfirmButton = new wxButton(EnrollPanel, wxID_ANY, "Continue", wxPoint(220, 610), wxSize(130, 50));
        ConfirmButton->SetFont(buttonFont);
        ConfirmButton->SetForegroundColour(*wxGREEN);
        ConfirmButton->Bind(wxEVT_BUTTON, &MainFrame::onConfirmButtonClicked, this); ConfirmButton->Disable();
        mascotpanel4 = new wxStaticText(EnrollPanel, wxID_ANY, "Thank you. Enjoy!", wxPoint(600, 180), wxSize(200, 30));
        mascotpanel4->SetFont(ASCIIFont2);
        mascotpanel4->SetForegroundColour(wxColour(37, 72, 210));
        mascotpanel4->Hide();
        ConfirmButton->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent&) {
            mascotpanel2->Hide();
            mascotpanel1->Hide();
            mascotpanel3->Hide();
            mascotpanel4->Show();
            mascotpanel5->Hide();
            });

        ExitEnrollButton = new wxButton(EnrollPanel, wxID_ANY, "return to menu", wxPoint(1100, 40), wxSize(165, 45));
        ExitEnrollButton->SetFont(buttonFont1);
        ExitEnrollButton->Bind(wxEVT_BUTTON, &MainFrame::ExitEnroll, this);
        mascotpanel5 = new wxStaticText(EnrollPanel, wxID_ANY, "Are you sure you\nwant to exit?", wxPoint(600, 180), wxSize(200, 30));
        mascotpanel5->SetFont(ASCIIFont2);
        mascotpanel5->SetForegroundColour(wxColour(37, 72, 210));
        mascotpanel5->Hide();
        ExitEnrollButton->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent&) {
            mascotpanel2->Hide();
            mascotpanel1->Hide();
            mascotpanel3->Hide();
            mascotpanel4->Hide();
            mascotpanel5->Show();
            });
    }else{
        wxLogMessage("EXISTING ACCOUNT IN FLASHDRIVE FOUND, CANNOT ENROLL FOR NEW");
        return;
    }

}
//RECOVER PIN
void MainFrame::OnRecoverPin(wxCommandEvent& evt) {
    bankpanel->Hide();

    Recoverpanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    Recoverpanel->SetBackgroundColour(customColor);

    wxPanel* thebank1 = new wxPanel(Recoverpanel, wxID_ANY, wxPoint(320, 30), wxSize(900, 200));
    wxStaticText* thebankk1 = new wxStaticText(thebank1, wxID_ANY,
        " _______     ________    ______    ___   ____   ____  ________  _______     \n"
        "|_   __ \\   |_   __  | .' ___  | .'   `. |_  _| |_  _||_   __  ||_   __ \\    \n"
        "  | |__) |    | |_ \\_|/ .'   \\_|/  .-.  \\ \\ \\   / /    | |_ \\_|  | |__) |   \n"
        "  |  __ /     |  _| _ | |       | |   | |  \\ \\ / /     |  _| _   |  __ /    \n"
        " _| |  \\ \\_  _| |__/ |\\ `.___.'\\\\  `-'  /   \\ ' /     _| |__/ | _| |  \\ \\_  \n"
        "|____| |___||________| `.____ .' `.___.'     \\_/     |________||____| |___| \n",
        wxPoint(10, 10));
    thebankk1->SetFont(ASCIIFont1);

    new wxStaticText(Recoverpanel, wxID_ANY, "Account Number:", wxPoint(350, 180)); 
    recoveraccnum = new wxTextCtrl(Recoverpanel, wxID_ANY, "Enter Account Number ", wxPoint(350, 210), wxSize(550, 50), wxTE_CENTER);
    recoveraccnum->SetFont(inputfont2);
    recoveraccnum->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    recoveraccnum->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (recoveraccnum->GetValue() == "Enter Account Number ") {
            recoveraccnum->Clear();
        }
        event.Skip();
        });

    new wxStaticText(Recoverpanel, wxID_ANY, "Birthdate (Year):", wxPoint(350, 280));
    recoverbdayyear = new wxTextCtrl(Recoverpanel, wxID_ANY, " Birthdate(YEAR) ", wxPoint(350, 310), wxSize(165, 30), wxTE_CENTER);
    recoverbdayyear->SetFont(inputfont);
    recoverbdayyear->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    recoverbdayyear->SetMaxLength(4);
    recoverbdayyear->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (recoverbdayyear->GetValue() == " Birthdate(YEAR) ") {
            recoverbdayyear->Clear();
        }
        event.Skip();
        });

    new wxStaticText(Recoverpanel, wxID_ANY, "Birthdate (Month):", wxPoint(545, 280));
    recoverbdaymonth = new wxTextCtrl(Recoverpanel, wxID_ANY, " Birthdate(MONTH) ", wxPoint(545, 310), wxSize(165, 30), wxTE_CENTER);
    recoverbdaymonth->SetFont(inputfont);
    recoverbdaymonth->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    recoverbdaymonth->SetMaxLength(2);
    
    recoverbdaymonth->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (recoverbdaymonth->GetValue() == " Birthdate(MONTH) ") {
            recoverbdaymonth->Clear();
        }
        event.Skip();
        });

    new wxStaticText(Recoverpanel, wxID_ANY, "Birthdate (Day):", wxPoint(740, 280));
    recoverbdayday = new wxTextCtrl(Recoverpanel, wxID_ANY, " Birthdate(DAY) ", wxPoint(740, 310), wxSize(163, 30), wxTE_CENTER);
    recoverbdayday->SetFont(inputfont);
    recoverbdayday->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    recoverbdayday->SetMaxLength(2);
    recoverbdayday->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (recoverbdayday->GetValue() == " Birthdate(DAY) ") {
            recoverbdayday->Clear();
        }
        event.Skip();
        });

    new wxStaticText(Recoverpanel, wxID_ANY, "New PIN (4 or 6 digits):", wxPoint(350, 380));
    createnewpin = new wxTextCtrl(Recoverpanel, wxID_ANY, " Input New Pin ( 4 or 6 digits)", wxPoint(350, 410), wxSize(550, 50), wxTE_CENTER);
    createnewpin->SetFont(inputfont2);
    createnewpin->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    createnewpin->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (createnewpin->GetValue() == " Input New Pin ( 4 or 6 digits)") {
            createnewpin->Clear();
        }
        event.Skip();
        });

    new wxStaticText(Recoverpanel, wxID_ANY, "Re-enter New Pin:", wxPoint(350, 480));
    reenternewpin = new wxTextCtrl(Recoverpanel, wxID_ANY, " Reenter Pin", wxPoint(350, 510), wxSize(550, 50), wxTE_CENTER);
    reenternewpin->SetFont(inputfont2);
    reenternewpin->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    reenternewpin->Bind(wxEVT_SET_FOCUS, [=](wxFocusEvent& event) {
        if (reenternewpin->GetValue() == " Reenter Pin") {
            reenternewpin->Clear();
        }
        event.Skip();
        });

    recoverpin = new wxButton(Recoverpanel, wxID_ANY, "Recover Pin", wxPoint(378,610), wxSize(500, 70));
    recoverpin->SetFont(buttonFont);
    recoverpin->Bind(wxEVT_BUTTON, &MainFrame::OnRecoverButtonClicked,this);
   
    exitrecover = new wxButton(Recoverpanel, wxID_ANY, "return to menu", wxPoint(1100, 660), wxSize(165, 45));
    exitrecover->SetFont(buttonFont1);
    exitrecover->Bind(wxEVT_BUTTON, &MainFrame::ExitRecover, this);
}


void MainFrame::OnRecoverButtonClicked(wxCommandEvent& evt) {
    if (recoveraccnum->IsEmpty() || createnewpin->IsEmpty() || recoverbdayyear->IsEmpty() || recoverbdaymonth->IsEmpty() || recoverbdayday->IsEmpty()) {
        wxMessageBox("PLEASE FILL OUT ALL FORMS");
        return;
    }
    wxString newpen = createnewpin->GetValue();
    wxString newpen2 = reenternewpin->GetValue();
    if (!newpen.IsEmpty() && (newpen.Length() == 4 || newpen.Length() == 6)) {
        if (newpen == newpen2) { 
            wxString accnum = recoveraccnum->GetValue();
            wxString year = recoverbdayyear->GetValue();
            wxString month = recoverbdaymonth->GetValue();
            wxString day = recoverbdayday->GetValue();
            wxString pin = createnewpin->GetValue();

            wxString bdayinput = year + "-" + month + "-" + day;
            if (bank.recoverpin(accnum, bdayinput, pin)) {
                bank.savelocal();
                Recoverpanel->Hide();
                bankpanel->Show();
            }
            else {
                return;
            }

        }
        else 
            wxMessageBox("PIN DOES NOT MATCH");
        return;

    }
    else {
        wxMessageBox("Invalid Pin Length");
        return;
    }
}


void MainFrame::ExitRecover(wxCommandEvent& evt) {
    Recoverpanel->Hide();
    bankpanel->Show();
}

//EXIT ENROLL
void MainFrame::ExitEnroll(wxCommandEvent& evt){
    EnrollPanel->Hide();
    panel->Show();
}


//INPUT PARAMETERS
void MainFrame::OnInputChanged(wxCommandEvent& evt){
	if (Inputname && InputPin && calendar) {
		wxString sname = Inputname->GetValue();
		wxString pin = InputPin->GetValue();
        wxString reenter = reenterPin->GetValue(); 
        if (!sname.IsEmpty() && (pin.Length() == 4 || pin.Length() == 6)) {
            if (pin  == reenter){
                ConfirmButton->Enable();
            }
            else { 
                
            }
		}
		else {
			ConfirmButton->Disable();
		}
	}
}

void MainFrame::OnDateChanged(wxCalendarEvent& evt) {
    wxDateTime selectedday = evt.GetDate();
    wxString dateStr = selectedday.FormatISODate();
    bdaydate = dateStr;
}

//CONFIRMATION BUTTON
void MainFrame::onConfirmButtonClicked(wxCommandEvent& evt) {
	info temp;
        IMbutton->Enable();
	    wxString sname = temp.accname = Inputname->GetValue();
		wxString spin = temp.accountpin = InputPin->GetValue();
        wxString sbday = temp.bday = bdaydate;
       
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
   enterpinPanel->SetBackgroundColour(customColor);

   wxStaticText* banner2 = new wxStaticText(enterpinPanel, wxID_ANY,
       "      _     _________  ____    ____   ____    ____       _        ______  ____  ____  _____  ____  _____  ________  \n"
       "     / \\   |  _   _  ||_   \\  /   _| |_   \\  /   _|     / \\     .' ___  ||_   ||   _||_   _||_   \\|_   _||_   __  | \n"
       "    / _ \\  |_/ | | \\_|  |   \\/   |     |   \\/   |      / _ \\   / .'   \\_|  | |__| |    | |    |   \\ | |    | |_ \\_| \n"
       "   / ___ \\     | |      | |\\  /| |     | |\\  /| |     / ___ \\  | |         |  __  |    | |    | |\\ \\| |    |  _| _  \n"
       " _/ /   \\ \\_  _| |_    _| |_\\/_| |_   _| |_\\/_| |_  _/ /   \\ \\_\\ `.___.'\\ _| |  | |_  _| |_  _| |_\\   |_  _| |__/ | \n"
       "|____| |____||_____|  |_____||_____| |_____||_____||____| |____|`.____ .'|____||____||_____||_____ \\____||________| \n"
       , wxPoint(180, 2), wxSize(900, 150));

   banner2->SetFont(ASCIIFont1);
   
   wxStaticText* pinenterhere = new wxStaticText(enterpinPanel, wxID_ANY, " Enter Pin Here", wxPoint(360, 220), wxSize(500, 30));
   pinenterhere->SetFont(buttonFont);

   pinenter = new wxTextCtrl(enterpinPanel, wxID_ANY, "", wxPoint(360, 250), wxSize(500, 94), wxTE_PASSWORD | wxTE_CENTER);
   pinenter->SetFont(inputfont3);
   pinenter->SetValidator(wxTextValidator(wxFILTER_DIGITS));


   pinverify = new wxButton(enterpinPanel, wxID_ANY, "Confirm Pin", wxPoint(410, 350), wxSize(400, 94));
   pinverify->SetFont(buttonFont);
   pinverify->Bind(wxEVT_BUTTON, &MainFrame::pinverifybutton, this);
   
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
    atmPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    atmPanel->SetBackgroundColour(customColor);


    wxStaticText* banner1 = new wxStaticText(atmPanel, wxID_ANY,
        "      _     _________  ____    ____   ____    ____       _        ______  ____  ____  _____  ____  _____  ________  \n"
        "     / \\   |  _   _  ||_   \\  /   _| |_   \\  /   _|     / \\     .' ___  ||_   ||   _||_   _||_   \\|_   _||_   __  | \n"
        "    / _ \\  |_/ | | \\_|  |   \\/   |     |   \\/   |      / _ \\   / .'   \\_|  | |__| |    | |    |   \\ | |    | |_ \\_| \n"
        "   / ___ \\     | |      | |\\  /| |     | |\\  /| |     / ___ \\  | |         |  __  |    | |    | |\\ \\| |    |  _| _  \n"
        " _/ /   \\ \\_  _| |_    _| |_\\/_| |_   _| |_\\/_| |_  _/ /   \\ \\_\\ `.___.'\\ _| |  | |_  _| |_  _| |_\\   |_  _| |__/ | \n"
        "|____| |____||_____|  |_____||_____| |_____||_____||____| |____|`.____ .'|____||____||_____||_____ \\____||________| \n"
        , wxPoint(180, 2), wxSize(900, 150));

    banner1->SetFont(ASCIIFont1);
   
    // Display Balance Button
    
    wxButton* balanceButton = new wxButton(atmPanel, wxID_ANY, "Display Balance", wxPoint(85, 180), wxSize(500, 90));
    balanceButton->SetFont(buttonFont);
    balanceButton->Bind(wxEVT_BUTTON, &MainFrame::OnDisplayBalanceClicked, this);


    // Withdraw Button
    wxButton* withdrawButton = new wxButton(atmPanel, wxID_ANY, "Withdraw", wxPoint(85, 320), wxSize(500, 90));
    withdrawButton->SetFont(buttonFont);
    withdrawButton->Bind(wxEVT_BUTTON, &MainFrame::OnWithdrawClicked, this);

    // Deposit Button

    wxButton* depositButton = new wxButton(atmPanel, wxID_ANY, "Deposit", wxPoint(85, 460), wxSize(500, 90));
    depositButton->SetFont(buttonFont);
    depositButton->Bind(wxEVT_BUTTON, &MainFrame::OnDepositClicked, this);

    // Fund Transfer Button

    wxButton* transferButton = new wxButton(atmPanel, wxID_ANY, "Fund Transfer", wxPoint(680, 180), wxSize(500, 90));
    transferButton->SetFont(buttonFont);
    transferButton->Bind(wxEVT_BUTTON, &MainFrame::OnTransferClicked, this);

    // Change PIN Button
    
    wxButton* pinButton = new wxButton(atmPanel, wxID_ANY, "Change PIN", wxPoint(680, 320), wxSize(500, 90));
    pinButton->SetFont(buttonFont);
    pinButton->Bind(wxEVT_BUTTON, &MainFrame::OnChangePinClicked, this);

    // Exit and Save Button

    exitPanel = new wxPanel(atmPanel, wxID_ANY, wxPoint(680, 460), wxSize(504, 94));
    wxButton* exitButton = new wxButton(exitPanel, wxID_ANY, "Exit and Save", wxPoint(2, 2), wxSize(500, 90));
    exitButton->SetFont(buttonFont);
    exitButton->Bind(wxEVT_BUTTON, &MainFrame::OnExitATMClicked, this);

}


 
void MainFrame::OnDisplayBalanceClicked(wxCommandEvent& evt) {
    balancePanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    balancePanel->SetBackgroundColour(customColor);
    atmPanel->Hide();
    balancePanel->Show();

    wxStaticText* asciiArtt1 = new wxStaticText(balancePanel, wxID_ANY,
        "   ___  ___   __   ___   _  ___________\n"
        "  / _ )/ _ | / /  / _ | / |/ / ___/ __/\n"
        " / _  / __ |/ /__/ __ |/    / /__/ _/  \n"
        "/____/_/ |_/____/_/ |_/_/|_/\\___/___/  \n",
        wxPoint(465, 40), wxSize(600, 150));

    
    wxStaticText* Accnum = new wxStaticText(balancePanel, wxID_ANY, " User Account Number: ", wxPoint(373, 260), wxSize(500, 90), wxTE_CENTER);
    Accnum->SetFont(buttonFont);
    DisplayAccnum = new wxStaticText(balancePanel, wxID_ANY, bank.returnaccnum(), wxPoint(373, 300), wxSize(500, 40),wxTE_CENTER);
    DisplayAccnum->SetFont(DisplayFont);
    asciiArtt1->SetFont(ASCIIFont1); 

    double balance = bank.returnbalance();
    wxString convertbalance = wxString::Format("%.2lf", balance);
    
    wxStaticText* balans = new wxStaticText(balancePanel, wxID_ANY, " User Remaining Balance: ", wxPoint(373, 360), wxSize(500, 40), wxTE_CENTER);
    balans->SetFont(buttonFont);
    DisplayBalance = new wxStaticText(balancePanel, wxID_ANY,convertbalance, wxPoint(373, 400), wxSize(500, 40),wxTE_CENTER);
    DisplayBalance->SetFont(DisplayFont);

    Exitdepobutton = new wxButton(balancePanel, wxID_ANY, "return", wxPoint(1100, 660), wxSize(165, 45));
    Exitdepobutton->SetFont(buttonFont1);
    Exitdepobutton->Bind(wxEVT_BUTTON, &MainFrame::onexitdisplay, this);


}

void MainFrame::onexitdisplay(wxCommandEvent& evt) {
    balancePanel->Hide();
    atmPanel->Show();
}

void MainFrame::OnWithdrawClicked(wxCommandEvent& evt) {
    withdrawPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    withdrawPanel->SetBackgroundColour(customColor);
    atmPanel->Hide();
    withdrawPanel->Show();

    wxStaticText* withdrawAsciiArt = new wxStaticText(withdrawPanel, wxID_ANY,
        "  _      ______________ _____  ___  ___ _      __\n"
        " | | /| / /  _/_  __/ // / _ \\/ _ \\/ _ | | /| / /\n"
        " | |/ |/ // /  / / / _  / // / , _/ __ | |/ |/ / \n"
        " |__/|__/___/ /_/ /_//_/____/_/|_/_/ |_|__/|__/  \n",
        wxPoint(405, 40), wxSize(600, 150));
    withdrawAsciiArt->SetFont(ASCIIFont1); 

    wxStaticText* withdrawLabel = new wxStaticText(withdrawPanel, wxID_ANY, "Enter Withdrawal Amount:", wxPoint(378, 270), wxSize(500, 30));
    withdrawLabel->SetFont(buttonFont);

    withdrawamount = new wxTextCtrl(withdrawPanel, wxID_ANY, "", wxPoint(378, 318), wxSize(500, 90), wxTE_CENTER);
    withdrawamount->SetFont(ASCIIFont2);
    withdrawamount->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    withdrawbutton = new wxButton(withdrawPanel, wxID_ANY, "Proceed", wxPoint(378, 418), wxSize(500, 90));
    withdrawbutton->SetFont(buttonFont);
    withdrawbutton->Bind(wxEVT_BUTTON, &MainFrame::onwithdrawbuttonclicked, this);

    exitwithdraw = new wxButton(withdrawPanel, wxID_ANY, "return", wxPoint(1100, 660), wxSize(165, 45));
    exitwithdraw->SetFont(buttonFont1);
    exitwithdraw->Bind(wxEVT_BUTTON, &MainFrame::onexitwithdraw, this);
}

void MainFrame::onwithdrawbuttonclicked(wxCommandEvent& evt) {
    wxString amount = withdrawamount->GetValue();
    double amountstr = stod(amount.ToStdString());
    if (bank.withdraw(amountstr)) {
        wxMessageBox("WITHDRAW SUCCRESS");
        bank.savelocal();
        withdrawPanel->Hide();
        atmPanel->Show();
    }
    else wxMessageBox("INSUFFICIENT AMOUNT TO WITHDRAW"); return;
}

void MainFrame::onexitwithdraw(wxCommandEvent& evt) {
    withdrawPanel->Hide();
    atmPanel->Show();
}

void MainFrame::OnDepositClicked(wxCommandEvent& evt) {
    depositPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    depositPanel->SetBackgroundColour(customColor);
    atmPanel->Hide();
    depositPanel->Show();

    wxStaticText* depositAsciiArt = new wxStaticText(depositPanel, wxID_ANY,
        "   ___  _______  ____  ______________\n"
        "  / _ \\/ __/ _ \\/ __ \\/ __/  _/_  __/\n"
        " / // / _// ___/ /_/ /\\ \\_/ /  / /   \n"
        "/____/___/_/   \\____/___/___/ /_/    \n",
        wxPoint(465, 40), wxSize(400, 150));
    depositAsciiArt->SetFont(ASCIIFont1);

    wxStaticText* depositLabel = new wxStaticText(depositPanel, wxID_ANY, "Enter Deposit Amount:", wxPoint(378, 270), wxSize(500, 30));
    depositLabel->SetFont(buttonFont);

    depositamount = new wxTextCtrl(depositPanel, wxID_ANY, "", wxPoint(378, 318), wxSize(500, 90), wxTE_CENTER);
    depositamount->SetFont(ASCIIFont2);
    depositamount->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    depositbutton = new wxButton(depositPanel, wxID_ANY, "DEPOSIT", wxPoint(378, 418), wxSize(500, 90));
    depositbutton->SetFont(buttonFont);
    depositbutton->Bind(wxEVT_BUTTON, &MainFrame::ondepositamount,this);

    wxButton* depositbuttonback1 = new wxButton(depositPanel, wxID_ANY, "return", wxPoint(1100, 660), wxSize(165, 45));
    depositbuttonback1->SetFont(buttonFont1);
    depositbuttonback1->Bind(wxEVT_BUTTON, &MainFrame::onexitdeposit,this);
}

void MainFrame::onexitdeposit(wxCommandEvent& evt) {
    depositPanel->Hide();
    atmPanel->Show();
}

void MainFrame::ondepositamount(wxCommandEvent& evt) {
    wxString depo = depositamount->GetValue();
    double depostr = stod(depo.ToStdString());
    bank.deposit(depostr);
    wxMessageBox("DEPOSIT SUCCESS");
    bank.savelocal();
    depositPanel->Hide();
    atmPanel->Show();
}

void MainFrame::OnTransferClicked(wxCommandEvent& evt) {
    transferPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    transferPanel->SetBackgroundColour(customColor);
    atmPanel->Hide();

    // Create a wxStaticText to display the updated deposit ASCII art
    wxStaticText* TRANSFERtAsciiArt = new wxStaticText(transferPanel, wxID_ANY,
        "   ___  ___   _  ____ __  _________  ___   _  _________________ \n"
        "  / _ )/ _ | / |/ / //_/ /_  __/ _ \\/ _ | / |/ / __/ __/ __/ _ \\ \n"
        " / _  / __ |/    / ,<     / / / , _/ __ |/    /\\ \\/ _// _// , _/ \n"
        "/____/_/ |_/_/|_/_/|_|   /_/ /_/|_/_/ |_/_/|_/___/_/ /___/_/|_|  \n",
        wxPoint(375, 40), wxSize(850, 90)); 
    TRANSFERtAsciiArt->SetFont(ASCIIFont1);


    wxStaticText* recipientLabel = new wxStaticText(transferPanel, wxID_ANY, "Enter Recipient Account Number:", wxPoint(378, 180), wxSize(500, 30));
    recipientLabel->SetFont(buttonFont);

    Targetrecipient = new wxTextCtrl(transferPanel, wxID_ANY, "", wxPoint(378, 220), wxSize(500, 90), wxTE_CENTER);
    Targetrecipient->SetFont(ASCIIFont2);
    Targetrecipient->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    wxStaticText* amountLabel = new wxStaticText(transferPanel, wxID_ANY, "Enter Transfer Amount:", wxPoint(378, 320), wxSize(500, 30));
    amountLabel->SetFont(buttonFont);

    TransferAmount = new wxTextCtrl(transferPanel, wxID_ANY, "", wxPoint(378, 360), wxSize(500, 90), wxTE_CENTER);
    TransferAmount->SetFont(ASCIIFont2);
    TransferAmount->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    ConfirmTransfer = new wxButton(transferPanel, wxID_ANY, "Confirm Transfer", wxPoint(378, 460), wxSize(500, 90));
    ConfirmTransfer->SetFont(buttonFont);
    ConfirmTransfer->Bind(wxEVT_BUTTON, &MainFrame::onconfirmtransfer, this);


    exittransfer = new wxButton(transferPanel, wxID_ANY, "return", wxPoint(1100, 660), wxSize(165, 45));
    exittransfer->SetFont(buttonFont1);
    exittransfer->Bind(wxEVT_BUTTON, &MainFrame::onexittransfer, this);

}

void MainFrame::onconfirmtransfer(wxCommandEvent& evt) {
    wxString id = Targetrecipient->GetValue();
    wxString transmount = TransferAmount->GetValue();
    double transferamount = stod(transmount.ToStdString());
    if (!bank.Transfer(id, transferamount)) {
        return;
    }
    else {
        bank.savelocal();
        transferPanel->Hide();
        atmPanel->Show();
    }
}
void MainFrame::onexittransfer(wxCommandEvent& evt) {
    transferPanel->Hide();
    atmPanel->Show();
}

void MainFrame::OnChangePinClicked(wxCommandEvent& evt) {
    pinPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    pinPanel->SetBackgroundColour(customColor);
    atmPanel->Hide();

    // Create a wxStaticText to display the new ASCII art
    wxStaticText* pinAsciiArt = new wxStaticText(pinPanel, wxID_ANY,
        "   ___  __________________  ___  _____  __  \n"
        "  / _ \\/ __/ __/ __/_  __/ / _ \\/  _/ |/ /  \n"
        " / , _/ _/_\\ \\/ _/  / /   / ___// //    /   \n"
        "/_/|_/___/___/___/ /_/   /_/  /___/_/|_/    \n",
        wxPoint(425, 40), wxSize(750, 90));
    pinAsciiArt->SetFont(ASCIIFont1); 


    wxStaticText* currentPinLabel = new wxStaticText(pinPanel, wxID_ANY, "Enter Current Pin:", wxPoint(378, 180), wxSize(500, 30));
    currentPinLabel->SetFont(buttonFont);

    CurrentPin = new wxTextCtrl(pinPanel, wxID_ANY, "", wxPoint(378, 210), wxSize(500, 90), wxTE_CENTER| wxTE_PASSWORD);
    CurrentPin->SetFont(ASCIIFont2);
    CurrentPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    wxStaticText* newPinLabel = new wxStaticText(pinPanel, wxID_ANY, "Enter New Pin:", wxPoint(378, 310), wxSize(500, 30));
    newPinLabel->SetFont(buttonFont);

    NewPin = new wxTextCtrl(pinPanel, wxID_ANY, "", wxPoint(378, 340), wxSize(500, 90), wxTE_CENTER| wxTE_PASSWORD);
    NewPin->SetFont(ASCIIFont2);
    NewPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    wxStaticText* confirmNewPinLabel = new wxStaticText(pinPanel, wxID_ANY, "Confirm New Pin:", wxPoint(378, 440), wxSize(500, 30));
    confirmNewPinLabel->SetFont(buttonFont);

    ConfirmNewPin = new wxTextCtrl(pinPanel, wxID_ANY,"", wxPoint(378, 470), wxSize(500, 90), wxTE_CENTER|wxTE_PASSWORD);
    ConfirmNewPin->SetFont(ASCIIFont2);
    ConfirmNewPin->SetValidator(wxTextValidator(wxFILTER_DIGITS));

    ConfirmPinbutton = new wxButton(pinPanel, wxID_ANY, "Change Pin", wxPoint(378, 570), wxSize(500, 90));
    ConfirmPinbutton->SetFont(buttonFont);
    ConfirmPinbutton->Bind(wxEVT_BUTTON, &MainFrame::ConfirmPin, this);

    ExitChangePin = new wxButton(pinPanel, wxID_ANY, "Return", wxPoint(1100, 660), wxSize(165, 45));
    ExitChangePin->SetFont(buttonFont1);
    ExitChangePin->Bind(wxEVT_BUTTON, &MainFrame::exitchangepin, this);
}
void MainFrame::ConfirmPin(wxCommandEvent& evt) {
    if (CurrentPin->IsEmpty()|| ConfirmNewPin->IsEmpty() || NewPin->IsEmpty()) {
        wxMessageBox("Please fill out all forms");
        return;
    }
    else {
        wxString current = CurrentPin->GetValue(), newpin = NewPin->GetValue(), confirm = ConfirmNewPin->GetValue();
        if (bank.changepin(current,newpin,confirm)) {
            bank.savelocal();
            pinPanel->Hide();
            atmPanel->Show();
        }
        else {
            return;
        }
    }
}



void MainFrame::exitchangepin(wxCommandEvent& evt) {
    pinPanel->Hide();
    atmPanel->Show();
}

void MainFrame::OnExitATMClicked(wxCommandEvent& evt) {
    atmPanel->Hide();
    ThankyouPanel = new wxPanel(this, wxID_ANY, wxPoint(2, 2), wxSize(1280, 720));
    ThankyouPanel->SetBackgroundColour(customColor); 
    wxStaticText* thanks = new wxStaticText(ThankyouPanel, wxID_ANY, "Thank you for using the program, Have a Nice day!", wxPoint(100, 318), wxSize(350, 70));
    thanks->SetFont(ThankyouFont);
    wxButton* OkayButton = new wxButton(ThankyouPanel, wxID_ANY, "Continue", wxPoint(525, 518), wxSize(220, 50));
    OkayButton->SetFont(buttonFont);
    OkayButton->Bind(wxEVT_BUTTON, &MainFrame::OnOkayButtonClicked, this);

}

void MainFrame::OnOkayButtonClicked(wxCommandEvent& evt) {
    wxLogMessage("Data Saved. System is Closing.");  
    Close(true);
}

void MainFrame::OnButton3Clicked(wxCommandEvent& evt) {
    wxLogMessage("System Closing");
    Close(true); 
}
