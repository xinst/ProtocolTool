#include "stdwx.h"
#include "NetWorkThread.h"
#include "SGFNet.h"

NetWorkThread::NetWorkThread(wxDialog* parent,const std::string& strIP,int nPort,bool bLoginThread )
{
	m_parent = parent;
	m_bStop = false;
	m_pNet = nullptr;

	m_strIP = strIP;
	m_nPort = nPort;
	m_bLoginThread = bLoginThread;
}

void NetWorkThread::OnRecvMsgHandler(const int nSockIndex, const ui32 nMsgID, const char* msg, const uint32_t nLen)
{
	if (nMsgID==MAKE_MSG_ID(0x0FFF,0x01))
	{
		//��½Э��
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, ID_RECV_LOGIN_MSG);
		event.SetInt(nMsgID);
		char* pData = new char[nLen];
		memset(pData, 0, nLen);
		memcpy(pData, msg, nLen);
		event.SetClientData(pData);
		event.SetExtraLong(nLen);
		m_parent->GetEventHandler()->AddPendingEvent(event);
	}
	else
	{
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, ID_RECV_PROTO_MSG);
		event.SetInt(nMsgID);
		m_parent->GetEventHandler()->AddPendingEvent(event);
	}
}

void NetWorkThread::OnSockEventHandler(const int nSockIndex, const SGF_NET_EVENT e, SGFINet* p)
{
	if (e == SGF_NET_EVENT_CONNECTED)
	{		
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, ID_RECV_CONNECT_MSG);
		if (m_bLoginThread)
		{
			event.SetString("Connect LoginServer OK");
			event.SetInt(100);
		}
		else
		{
			event.SetString("Connect GatewayServer OK");
			event.SetInt(200);
		}
		m_parent->GetEventHandler()->AddPendingEvent(event);
	}
	else 
	{
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, ID_RECV_CONNECT_MSG);
		
		if (m_bLoginThread)
		{
			event.SetString("Connect LoginServer Err");
			event.SetInt(10);
		}
		else
		{
			event.SetString("Connect GatewayServer Err");
			event.SetInt(20);
		}

		m_parent->GetEventHandler()->AddPendingEvent(event);
	}
}

void NetWorkThread::SendMsg(ui32 nMsgID, const std::string& msgData)
{
	{
		wxMutexLocker locker(m_Mutex);
		NetMsg msg;
		msg.nMsgID = nMsgID;
		msg.strMsgData = msgData;
		m_MsgList.push(msg);
	}
}

wxThread::ExitCode NetWorkThread::Entry()
{
	while (!m_bStop)
	{
		if (TestDestroy())
		{
			break;
		}
		this->Sleep(500);

		if (m_strIP.length()>0&&m_nPort!=0)
		{
			if (m_pNet == nullptr)
			{
				m_pNet = new SGFNet(this, &NetWorkThread::OnRecvMsgHandler, &NetWorkThread::OnSockEventHandler);
				m_pNet->Initialization(m_strIP.c_str(), m_nPort);
			}
		}

		if (m_pNet)
		{
			{
				wxMutexLocker locker(m_Mutex);
				while (m_MsgList.size())
				{
					NetMsg msg = m_MsgList.front();
					m_pNet->SendMsgWithOutHead(msg.nMsgID, msg.strMsgData.c_str(), msg.strMsgData.length(), 0);
					m_MsgList.pop();
				}
			}
			m_pNet->Execute();
		}
	}

	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = nullptr;
	}

	return 0;
}
