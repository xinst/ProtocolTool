#ifndef NetObject_h__
#define NetObject_h__

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/thread.h>
#include <event2/event_compat.h>
#include "SGFUID.h"

class SGFINet;

class NetObject
{
public:
	NetObject(SGFINet* pNet, int32_t fd, sockaddr_in& addr, bufferevent* pBev)
	{
		m_nLogicState = 0;
		m_nServerID = 0;
		m_nFD = fd;
		m_bNeedRemove = false;

		m_pNet = pNet;

		m_pBev = pBev;
		memset(&m_sin, 0, sizeof(m_sin));
		m_sin = addr;
		
		char pIP[512] = {0};
				
		evutil_inet_ntop(addr.sin_family, &addr.sin_addr, pIP,sizeof(pIP));

		m_strRemoteIP = pIP;

#ifdef _WIN32
		m_nRemotePort = htons(addr.sin_port);
#else
		m_nRemotePort = htobe16(addr.sin_port);
#endif

#ifdef _DEBUG
		std::cout<<"ClientInfo:["<<m_strRemoteIP<<":"<<m_nRemotePort<<"]"<<std::endl;
		m_strDebugRemoteInfo = m_strRemoteIP + ":" + std::to_string(m_nRemotePort);
#endif // _DEBUG		
	}

	virtual ~NetObject()
	{
	}

	int AddBuff(const char* str, uint32_t nLen)
	{
		m_strBuff.append(str, nLen);

		return (int)m_strBuff.length();
	}

	int CopyBuffTo(char* str, uint32_t nStart, uint32_t nLen)
	{
		if (nStart + nLen > m_strBuff.length())
		{
			return 0;
		}

		memcpy(str, m_strBuff.data() + nStart, nLen);

		return nLen;
	}

	int RemoveBuff(uint32_t nStart, uint32_t nLen)
	{
		if (nStart < 0)
		{
			return 0;
		}

		//移除前面，则后面跟上
		if (nStart + nLen > m_strBuff.length())
		{
			return 0;
		}

		//把后面的挪到前面来
		m_strBuff.erase(nStart, nLen);

		return (int)m_strBuff.length();
	}

	const char* GetBuff()
	{
		return m_strBuff.data();
	}

	int GetBuffLen() const
	{
		return (int)m_strBuff.length();
	}

	bufferevent* GetBuffEvent()
	{
		return m_pBev;
	}

	SGFINet* GetNet()
	{
		return m_pNet;
	}
	//////////////////////////////////////////////////////////////////////////
	int GetConnectKeyState() const
	{
		return m_nLogicState;
	}

	void SetConnectKeyState(const int nState)
	{
		m_nLogicState = nState;
	}
	bool NeedRemove()
	{
		return m_bNeedRemove;
	}
	void SetNeedRemove(bool b)
	{
		m_bNeedRemove = b;
	}
	const std::string& GetAccount() const
	{
		return m_strUserData;
	}

	void SetAccount(const std::string& strData)
	{
		m_strUserData = strData;
	}
	int GetServerID() const
	{
		return m_nServerID;
	}

	void SetServerID(const int nData)
	{
		m_nServerID = nData;
	}
	const SGFUID& GetUserID()
	{
		return m_nUserID;
	}

	void SetUserID(const SGFUID& nUserID)
	{
		m_nUserID = nUserID;
	}

	const SGFUID& GetClientID()
	{
		return m_nClientID;
	}

	void SetClientID(const SGFUID& xClientID)
	{
		m_nClientID = xClientID;
	}

	int GetRealFD()
	{
		return m_nFD;
	}

	bool GetRemoteInfo( std::string& strIP,ui32& nPort )
	{
		strIP = m_strRemoteIP;
		nPort = m_nRemotePort;
		return true;
	}

#ifdef _DEBUG
	const std::string& GetDebugRemoteInfo() const
	{
		return m_strDebugRemoteInfo;
	}
#endif // _DEBUG


private:
	sockaddr_in m_sin;
	bufferevent* m_pBev;
	std::string m_strBuff;
	std::string m_strUserData;

	std::string m_strRemoteIP;
	ui32 m_nRemotePort;

	int32_t m_nLogicState;
	int32_t m_nServerID;
	SGFUID m_nUserID;
	SGFUID m_nClientID;
	SGFINet* m_pNet;
	//
	int m_nFD;
	bool m_bNeedRemove;

#ifdef _DEBUG
	std::string m_strDebugRemoteInfo;
#endif // _DEBUG
};


#endif // NetObject_h__