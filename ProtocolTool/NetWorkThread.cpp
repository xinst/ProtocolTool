#include "stdwx.h"
#include "NetWorkThread.h"
#include "NFCNet.h"

NetWorkThread::NetWorkThread(wxDialog* parent,const std::string& strIP,int nPort )
{
	m_parent = parent;
	m_bStop = false;
	m_nState = 0;
	m_pNet = nullptr;

	m_strIP = strIP;
	m_nPort = nPort;
}

void NetWorkThread::OnRecvMsgHandler(const int nSockIndex, const int nMsgID, const char* msg, const uint32_t nLen)
{

}

void NetWorkThread::OnSockEventHandler(const int nSockIndex, const NF_NET_EVENT e, NFINet* p)
{
	if (e == NF_NET_EVENT_CONNECTED)
	{
		m_nState = 1;

		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, ID_RECV_PROTOCOL_MSG);
		event.SetString("Connect Server OK");
		m_parent->GetEventHandler()->AddPendingEvent(event);
	}
}

void NetWorkThread::SendMsg(int16_t nMsgID, const std::string& msgData)
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
		//if (TestDestroy())
		//{
		//	break;
		//}
		this->Sleep(500);
		
		//if (m_nState==0)
		{
			if (m_pNet==nullptr)
			{
				m_pNet = new NFCNet(this, &NetWorkThread::OnRecvMsgHandler, &NetWorkThread::OnSockEventHandler);
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
