//*************************************************************************
// NetWorkThread.h 2016-8-5 16:27
// Author: Stonexin
// Purpose: 
//
//*************************************************************************

#ifndef PROTOCOL_THREAD_H__
#define PROTOCOL_THREAD_H__

#include <atomic>
#include <wx/thread.h>
#include <queue>
#include "SGFINet.h"
class SGFNet;

#define MAKE_MSG_ID(msg_type,msg_id)      (((msg_type)<<8)|(msg_id))
#define GET_MSG_TYPE(raw_val)			  (((raw_val)>>8)&0x0000ffff)
#define GET_MSG_ID(raw_val)				  ((raw_val)&0x000000ff)

const int ID_RECV_CONNECT_MSG = 100000;
const int ID_RECV_LOGIN_MSG = 100001;
const int ID_RECV_PROTO_MSG = 100002;

struct NetMsg
{
	ui32 nMsgID;
	std::string strMsgData;
};


// a thread class that will periodically send events to the GUI thread
class NetWorkThread : public wxThread
{
	wxDialog* m_parent;
	std::atomic_bool m_bStop;

	SGFNet*	m_pNet;

	std::string m_strIP;
	unsigned short      m_nPort;

	wxMutex		m_Mutex;
	std::queue<NetMsg>	m_MsgList;
	bool	m_bLoginThread;

public:
	NetWorkThread(wxDialog* parent,const std::string& strIP,int nPort,bool bLoginThread=false );

	void OnRecvMsgHandler(const int nSockIndex, const ui32 nMsgID, const char* msg, const uint32_t nLen);


	void OnSockEventHandler(const int nSockIndex, const SGF_NET_EVENT e, SGFINet* p);

	void SendMsg( ui32 nMsgID,const std::string& msgData );


	void Stop(){
		m_bStop = true;
	}

	virtual ExitCode Entry();
};


#endif // PROTOCOL_THREAD_H__
