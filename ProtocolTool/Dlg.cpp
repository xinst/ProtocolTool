#include "stdwx.h"
#include "Dlg.h"
#include <wx/dir.h>
#include <thread>
#include <chrono>
#include <functional>
#include <wx/utils.h> 

///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(Dlg, wxDialog)
	EVT_CLOSE(Dlg::OnClose)
	EVT_DIRPICKER_CHANGED(WX_ID_DIR_PICKER,Dlg::OnProtoDirSelected)
END_EVENT_TABLE()


Dlg::Dlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
: wxDialog(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Server IP:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer4->Add(m_staticText1, 0, wxALIGN_CENTER | wxALL, 5);

	m_pServerIPCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_pServerIPCtrl, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Port:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer4->Add(m_staticText2, 0, wxALIGN_CENTER | wxALL, 5);

	m_pServerPortCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_pServerPortCtrl, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("UserName:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer4->Add(m_staticText3, 0, wxALIGN_CENTER | wxALL, 5);

	m_pUserNameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_pUserNameCtrl, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticText4 = new wxStaticText(this, wxID_ANY, wxT("Password:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText4->Wrap(-1);
	bSizer4->Add(m_staticText4, 0, wxALIGN_CENTER | wxALL, 5);

	m_pPwdCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_pPwdCtrl, 0, wxALIGN_CENTER | wxALL, 5);
	
	m_pBtnLogin = new wxButton(this, wxID_ANY, wxT("Login"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_pBtnLogin, 0, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT | wxALL, 5);


	bSizer1->Add(bSizer4, 0, wxALL,5);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText5 = new wxStaticText(this, wxID_ANY, wxT("ProtosDir:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText5->Wrap(-1);
	bSizer5->Add(m_staticText5, 0, wxALIGN_CENTER | wxALL, 5);

	m_pDirCtrl = new wxDirPickerCtrl(this, WX_ID_DIR_PICKER, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE);
	bSizer5->Add(m_pDirCtrl, 1, wxALL | wxLEFT | wxRIGHT, 5);

	m_staticText6 = new wxStaticText(this, wxID_ANY, wxT("ProtoMsg:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText6->Wrap(-1);
	bSizer5->Add(m_staticText6, 0, wxALIGN_CENTER | wxALL, 5);

	wxArrayString m_pProtoMsgChoiceChoices;
	m_pProtoMsgChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_pProtoMsgChoiceChoices, wxCB_SORT);
	m_pProtoMsgChoice->SetSelection(0);
	bSizer5->Add(m_pProtoMsgChoice, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

	m_button3 = new wxButton(this, wxID_ANY, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(m_button3, 0, wxALIGN_CENTER | wxALL, 5);
	

	bSizer1->Add(bSizer5, 0, wxEXPAND, 5);
	
	wxStaticLine* m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer1->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	m_pFGSizer = new wxFlexGridSizer(0, 2, 0, 0);
	m_pFGSizer->SetFlexibleDirection(wxBOTH);
	m_pFGSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	bSizer7->Add(m_pFGSizer, 2, wxEXPAND|wxALL, 5);


	wxStaticLine* m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	bSizer7->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxVERTICAL);

	m_pListBoxCtrl = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	bSizer10->Add(m_pListBoxCtrl, 1, wxEXPAND| wxTOP|wxLEFT|wxRIGHT, 5);


	bSizer7->Add(bSizer10, 3, wxEXPAND, 5);


	bSizer1->Add(bSizer7, 1, wxEXPAND, 5);

	this->SetSizer(bSizer1);
	this->Layout();

	SetMinSize(wxSize(950, 580));
	this->SetSizer(bSizer1);
	this->Layout();	
	this->Centre(wxBOTH);
}

void Dlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

void Dlg::InitCtrls( const wxString& dir  )
{
	//get the proto list
	ProtocolManager::Instance()->InitProtocol(dir.ToStdString());

	auto msgList = ProtocolManager::Instance()->GetProtocolMessageList("");
	m_pProtoMsgChoice->Clear();
	for (size_t i=0;i<msgList.size();i++)
	{
		m_pProtoMsgChoice->AppendString( wxString(msgList.at(i)) );
	}
}

void Dlg::OnProtoDirSelected(wxFileDirPickerEvent& event)
{
	InitCtrls(event.GetPath());
}

Dlg::~Dlg()
{
	ProtocolManager::Instance()->ReleaseInstance();
}
