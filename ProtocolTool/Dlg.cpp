#include "stdwx.h"
#include "Dlg.h"
#include <wx/dir.h>
#include <thread>
#include <chrono>
#include <functional>
#include <wx/utils.h> 

#include "NetWorkThread.h"
#include "SGFMsgBase.pb.h"
#include "CommGameMsg.pb.h"

///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE(Dlg, wxDialog)
	EVT_CLOSE(Dlg::OnClose)
	EVT_DIRPICKER_CHANGED(WX_ID_DIR_PICKER,Dlg::OnProtoDirSelected)
	EVT_CHOICE(WX_ID_MSG_CHOICE, Dlg::OnMsgSelected)
	EVT_BUTTON(WX_ID_BTN_LOGIN, Dlg::OnBtnLogin)
	EVT_BUTTON(WX_ID_BTN_SEND, Dlg::OnBtnSend)
	EVT_COMMAND(ID_RECV_CONNECT_MSG, wxEVT_COMMAND_TEXT_UPDATED, Dlg::OnNetWorkMsg)
	EVT_COMMAND(ID_RECV_PROTO_MSG, wxEVT_COMMAND_TEXT_UPDATED, Dlg::OnProtoMsg)
	EVT_COMMAND(ID_RECV_LOGIN_MSG, wxEVT_COMMAND_TEXT_UPDATED, Dlg::OnLoginMsg)
END_EVENT_TABLE()


Dlg::Dlg(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) 
: wxDialog(parent, id, title, pos, size, style)
{
	SetMinSize(wxSize(1024, 768));
	//this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Server IP:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer4->Add(m_staticText1, 0, wxALIGN_CENTER | wxALL, 5);

	m_pServerIPCtrl = new wxTextCtrl(this, wxID_ANY, wxString("127.0.0.1"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_pServerIPCtrl, 0, wxALIGN_CENTER | wxALL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Port:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer4->Add(m_staticText2, 0, wxALIGN_CENTER | wxALL, 5);

	m_pServerPortCtrl = new wxTextCtrl(this, wxID_ANY, wxString("8100"), wxDefaultPosition, wxDefaultSize, 0);
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
	
	m_pBtnLogin = new wxButton(this, WX_ID_BTN_LOGIN, wxT("Login"), wxDefaultPosition, wxDefaultSize, 0);
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
	m_pProtoMsgChoice = new wxChoice(this, WX_ID_MSG_CHOICE, wxDefaultPosition, wxDefaultSize, m_pProtoMsgChoiceChoices, wxCB_SORT);
	bSizer5->Add(m_pProtoMsgChoice, 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

	m_pBtnSend = new wxButton(this, WX_ID_BTN_SEND, wxT("Send"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(m_pBtnSend, 0, wxALIGN_CENTER | wxALL, 5);	
	m_pBtnSend->Enable(false);

	bSizer1->Add(bSizer5, 0, wxEXPAND, 5);
	
	wxStaticLine* m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer1->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);

	m_pFGSizer = new wxFlexGridSizer(40,2,2,2);
	bSizer7->Add(m_pFGSizer, 0, wxALL, 5);

	wxStaticText* pStatic = new wxStaticText(this, wxID_ANY, wxString("Msg ID:"), wxDefaultPosition, wxDefaultSize, 0);
	pStatic->Wrap(-1);
	m_pFGSizer->Add(pStatic);

	m_pMsgIDCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
	m_pFGSizer->Add(m_pMsgIDCtrl);
	
	wxStaticLine* m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);
	bSizer7->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);
	
	m_pListBoxCtrl = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0);
	bSizer7->Add(m_pListBoxCtrl, 1, wxEXPAND| wxTOP|wxLEFT|wxRIGHT, 5);
	m_pListBoxCtrl->SetBackgroundColour( *wxBLACK );
	m_pListBoxCtrl->SetForegroundColour( *wxGREEN);

	
	bSizer1->Add(bSizer7, 1, wxEXPAND, 5);
	
	this->SetSizer(bSizer1);
	this->Layout();	

	m_pNetWorkThrd = nullptr;
	m_pLoginThrd = nullptr;
}

Dlg::~Dlg()
{
	DestoryThread(m_pLoginThrd);
	DestoryThread(m_pNetWorkThrd);

	ProtocolManager::Instance()->ReleaseInstance();
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
	wxString strPath = event.GetPath();
	InitCtrls(strPath);

}

void Dlg::OnMsgSelected(wxCommandEvent& event)
{
	InitProtocolField(event.GetString());
}

void Dlg::InitProtocolField(const wxString& strMsgName)
{
	for (size_t i=0;i<m_FieldList.size();i++)
	{
		m_FieldList.at(i).Clear();
		m_FieldList.at(i).Enable(false);
		m_FieldList.at(i).Show(false);
	}

	auto msgInfo = ProtocolManager::Instance()->GetProtoMessageInfo(strMsgName.ToStdString());
	
	for(size_t i=0;i<msgInfo.fields.size();i++)
	{
		wxString strLabel = wxString::Format("[%s] [%s] %s : ", msgInfo.fields.at(i).strLabelType, msgInfo.fields.at(i).strFieldType, msgInfo.fields.at(i).name);
		if (m_FieldList.size()<=i)
		{
			FieldCtrl ctrl;

			wxStaticText* pStatic = new wxStaticText(this, wxID_ANY, strLabel, wxDefaultPosition, wxDefaultSize, 0);
			pStatic->Wrap(-1);
			m_pFGSizer->Add(pStatic);

			wxTextCtrl* pTextCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
			m_pFGSizer->Add(pTextCtrl);

			ctrl.nIndex = i;
			ctrl.pStaticTxt = pStatic;
			ctrl.pTextCtrl = pTextCtrl;

			m_FieldList.push_back(ctrl);
		}
		else
		{
			FieldCtrl ctrl = m_FieldList.at(i);
			ctrl.pStaticTxt->SetLabelText(strLabel);
			ctrl.pTextCtrl->SetValue("");
			ctrl.Enable(true);
			ctrl.Show(true);
		}
	}
	Layout();
}

void Dlg::OnBtnLogin(wxCommandEvent& event)
{
	DestoryThread(m_pLoginThrd);
	// create the thread
	unsigned long nPort = 0;
	m_pServerPortCtrl->GetValue().ToULong(&nPort);
	m_pLoginThrd = new NetWorkThread(this,m_pServerIPCtrl->GetValue().ToStdString(),nPort);
	wxThreadError err = m_pLoginThrd->Create();

	if (err != wxTHREAD_NO_ERROR)
	{
		wxMessageBox(_("Couldn't create thread!"));
		return;
	}

	err = m_pLoginThrd->Run();

	if (err != wxTHREAD_NO_ERROR)
	{
		wxMessageBox(_("Couldn't run thread!"));
		return;
	}
}

void Dlg::OnBtnSend(wxCommandEvent& event)
{
	std::vector<std::string> fieldValueList;

	for (size_t i=0;i<m_FieldList.size();i++)
	{
		if(m_FieldList.at(i).pTextCtrl&&
			m_FieldList.at(i).pTextCtrl->IsShown()&&
			m_FieldList.at(i).pTextCtrl->IsEnabled())
		{
			fieldValueList.push_back( m_FieldList.at(i).pTextCtrl->GetValue().ToStdString() );
		}
	}

	unsigned long nMsgID;
	m_pMsgIDCtrl->GetValue().ToULong(&nMsgID,16);

	wxString strProtoMsgName = m_pProtoMsgChoice->GetString( m_pProtoMsgChoice->GetCurrentSelection() );

	MessagePtr pMsg = ProtocolManager::Instance()->FillProtoMsg(strProtoMsgName.ToStdString(), fieldValueList);
	if (pMsg)
	{
		std::string strMsgData = pMsg->SerializeAsString();

		SGFMsg::MsgBase msg;
		msg.set_msg_data(strMsgData);
		msg.mutable_player_id()->set_index(0);
		msg.mutable_player_id()->set_svrid(0);
		
		m_pNetWorkThrd->SendMsg(nMsgID,msg.SerializeAsString());
	}
}

void Dlg::OnNetWorkMsg(wxCommandEvent& event)
{
	if (m_pListBoxCtrl)
	{
		wxString strMsgID = wxString::Format("recv:%#x",event.GetInt());
		m_pListBoxCtrl->Append(strMsgID);
	}
}

void Dlg::OnProtoMsg(wxCommandEvent& event)
{
	if (m_pListBoxCtrl)
	{
		wxString strMsgID = wxString::Format("recv:%#x", event.GetInt());
		m_pListBoxCtrl->Append(strMsgID);
	}
}

void Dlg::OnLoginMsg(wxCommandEvent& event)
{
	SGFMsg::MsgBase xMsg;
	if (xMsg.ParseFromArray(event.GetString().c_str(),event.GetString().length()))
	{
		SGFMsg::AccountLoginRes res;
		if(res.ParseFromString(xMsg.msg_data()))
		{
			DestoryThread(m_pNetWorkThrd);
			// create the thread
			unsigned long nPort = res.port();

			m_pNetWorkThrd = new NetWorkThread(this, res.ip(),res.port());
			wxThreadError err = m_pNetWorkThrd->Create();

			if (err != wxTHREAD_NO_ERROR)
			{
				wxMessageBox(_("Couldn't create thread!"));
				return;
			}

			err = m_pNetWorkThrd->Run();

			if (err != wxTHREAD_NO_ERROR)
			{
				wxMessageBox(_("Couldn't run thread!"));
				return;
			}

			DestoryThread(m_pLoginThrd);

			m_pBtnSend->Enable(true);
		}
	}
}

void Dlg::DestoryThread(NetWorkThread*& p)
{
	if (p)
	{
		p->Stop();
		while (p->IsRunning())
		{
			wxMicroSleep(100);
		}
		//delete m_pNetWorkThrd;
		p = nullptr;
	}
}
