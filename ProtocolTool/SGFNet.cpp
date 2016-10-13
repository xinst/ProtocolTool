#include <WS2tcpip.h>
#include "SGFNet.h"


void SGFNet::conn_writecb(struct bufferevent* bev, void* user_data)
{
	//nothing.
	//you can log here 
}

void SGFNet::conn_eventcb(struct bufferevent* bev, short events, void* user_data)
{
    NetObject* pObject = (NetObject*)user_data;
    SGFNet* pNet = (SGFNet*)pObject->GetNet();
    if (pNet->m_EventCB)
    {
        pNet->m_EventCB(pObject->GetRealFD(), SGF_NET_EVENT(events), pNet);
    }
	
    if (events & BEV_EVENT_CONNECTED)
    {
#ifdef _DEBUG		
		std::cout << "Client connected. IP=" << pObject->GetDebugRemoteInfo() << std::endl;
#endif
    }
    else
    {
        pNet->CloseNetObject(pObject->GetRealFD());
#ifdef _DEBUG
		std::cout << "Client disconnected. IP=" << pObject->GetDebugRemoteInfo() << std::endl;
#endif
    }
}

void SGFNet::listener_cb(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data)
{
	SGFNet* pNet = (SGFNet*)user_data;
	//if the socket fd is same.
	bool bClose = pNet->CloseNetObject(fd);
    if (bClose)
    {
        return;
    }

	//connections is full for this net
    if (pNet->m_mObject.size() >= pNet->m_nMaxConnect)
    {
        return;
    }

    struct event_base* base = pNet->m_pBase;
    struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev)
    {
        fprintf(stderr, "Error constructing bufferevent!");
        //event_base_loopbreak(base);
        return;
    }

    struct sockaddr_in* pSin = (sockaddr_in*)sa;
    NetObject* pObject = new NetObject(pNet, fd, *pSin, bev);
    pObject->GetNet()->AddNetObject(fd, pObject);

    //setting the call back.
    bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, (void*)pObject);

    //config the libevent
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    //trigger a connected event
    conn_eventcb(bev, BEV_EVENT_CONNECTED, (void*)pObject);
}


void SGFNet::conn_readcb(struct bufferevent* bev, void* user_data)
{
    //recv data
    NetObject* pObject = (NetObject*)user_data;
    if (!pObject)
    {
        return;
    }

    SGFNet* pNet = (SGFNet*)pObject->GetNet();
    if (!pNet)
    {
        return;
    }

    if (pObject->NeedRemove())
    {
        return;
    }

#ifdef _DEBUG
	std::cout << "recv msg from " << pObject->GetDebugRemoteInfo() << std::endl;
#endif
    struct evbuffer* input = bufferevent_get_input(bev);
    if (!input)
    {
        return;
    }

    size_t len = evbuffer_get_length(input);
	
    //must new here
    char* strMsg = new char[len];

    if (evbuffer_remove(input, strMsg, len) > 0)
    {
        pObject->AddBuff(strMsg, len);
    }

    delete[] strMsg;

    while (1)
    {
		//dispatch msg by the codec type
		if (!pNet->Dismantle(pObject))
		{
			break;
		}
    }
}

//////////////////////////////////////////////////////////////////////////

bool SGFNet::Execute()
{
    ExecuteClose();
    if (m_pBase)
    {
        event_base_loop(m_pBase, EVLOOP_ONCE | EVLOOP_NONBLOCK);
    }

    return true;
}


void SGFNet::Initialization(const char* strIP, const unsigned short nPort)
{
    m_strIP = strIP;
    m_nPort = nPort;

    InitClientNet();
}

int SGFNet::Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount)
{
    m_nMaxConnect = nMaxClient;
    m_nPort = nPort;
    m_nCpuCount = nCpuCount;

    return InitServerNet();
}

bool SGFNet::Final()
{
    CloseSocketAll();
    if (m_pListener)
    {
        evconnlistener_free(m_pListener);
        m_pListener = NULL;
    }

    if (!m_bServer)
    {
        if (m_pBase)
        {
            event_base_free(m_pBase);
            m_pBase = NULL;
        }
    }

    return true;
}

bool SGFNet::SendMsgToAllClient(const char* msg, const uint32_t nLen)
{
    if (nLen <= 0)
    {
        return false;
    }

    std::map<int, NetObject*>::iterator it = m_mObject.begin();
    for (; it != m_mObject.end(); ++it)
    {
        NetObject* pNetObject = (NetObject*)it->second;
        if (pNetObject && !pNetObject->NeedRemove())
        {
            bufferevent* bev = pNetObject->GetBuffEvent();
            if (NULL != bev)
            {
                bufferevent_write(bev, msg, nLen);
            }
        }
    }

    return true;
}


bool SGFNet::SendMsg(const char* msg, const uint32_t nLen, const int nSockIndex)
{
    if (nLen <= 0)
    {
        return false;
    }

    std::map<int, NetObject*>::iterator it = m_mObject.find(nSockIndex);
    if (it != m_mObject.end())
    {
        NetObject* pNetObject = (NetObject*)it->second;
        if (pNetObject)
        {
            bufferevent* bev = pNetObject->GetBuffEvent();
            if (NULL != bev)
            {
                bufferevent_write(bev, msg, nLen);

                return true;
            }
        }
    }

    return false;
}

bool SGFNet::SendMsg(const char* msg, const uint32_t nLen, const std::list<int>& fdList)
{
    std::list<int>::const_iterator it = fdList.begin();
    for (; it != fdList.end(); ++it)
    {
        SendMsg(msg, nLen, *it);
    }

    return true;
}

bool SGFNet::CloseNetObject(const int nSockIndex)
{
    std::map<int, NetObject*>::iterator it = m_mObject.find(nSockIndex);
    if (it != m_mObject.end())
    {
        NetObject* pObject = it->second;

        pObject->SetNeedRemove(true);
        m_vRemoveObject.push_back(nSockIndex);

        return true;
    }

    return false;
}

bool SGFNet::Dismantle(NetObject* pObject)
{
    bool bNeedDismantle = false;

    int len = pObject->GetBuffLen();
    if (len > MSG_HEAD_LENGTH)
    {
        SGFMsgHead xHead;
        int nMsgBodyLength = DeCode(pObject->GetBuff(), len-MSG_HEAD_LENGTH, xHead);
        if (nMsgBodyLength > 0 && xHead.GetMsgID() > 0)
        {
            if (m_RecvCB)
            {
                m_RecvCB(pObject->GetRealFD(), xHead.GetMsgID(), pObject->GetBuff() + MSG_HEAD_LENGTH, nMsgBodyLength);
            }           

            pObject->RemoveBuff(0, nMsgBodyLength + MSG_HEAD_LENGTH);

            Dismantle(pObject);
        }
        else if (0 == nMsgBodyLength)
        {
            //not enough for a msg min length
            bNeedDismantle = false;
        }
        else
        {
			//has an error
            bNeedDismantle = false;
        }
    }

    return bNeedDismantle;
}

bool SGFNet::AddNetObject(const int nSockIndex, NetObject* pObject)
{
    //lock
    return m_mObject.insert(std::map<int, NetObject*>::value_type(nSockIndex, pObject)).second;
}

int SGFNet::InitClientNet()
{
    std::string strIP = m_strIP;
    int nPort = m_nPort;

    struct sockaddr_in addr;
    struct bufferevent* bev = NULL;

#ifdef _MSC_VER
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(nPort);

    if (inet_pton(AF_INET, strIP.c_str(), &addr.sin_addr) <= 0)
    {
        printf("inet_pton");
        return -1;
    }

    m_pBase = event_base_new();
    if (m_pBase == NULL)
    {
        printf("event_base_new ");
        return -1;
    }

    bev = bufferevent_socket_new(m_pBase, -1, BEV_OPT_CLOSE_ON_FREE);
    if (bev == NULL)
    {
        printf("bufferevent_socket_new ");
        return -1;
    }

    int bRet = bufferevent_socket_connect(bev, (struct sockaddr*)&addr, sizeof(addr));
    if (0 != bRet)
    {
        //int nError = GetLastError();
        printf("bufferevent_socket_connect error");
        return -1;
    }

    int sockfd = bufferevent_getfd(bev);
    NetObject* pObject = new NetObject(this, sockfd, addr, bev);
    if (!AddNetObject(0, pObject))
    {
        assert(0);
        return -1;
    }

    m_bServer = false;

    bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_eventcb, (void*)pObject);
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    event_set_log_callback(&SGFNet::log_cb);
    //event_base_loop(m_pBase, EVLOOP_ONCE|EVLOOP_NONBLOCK);

    return sockfd;
}

int SGFNet::InitServerNet()
{
    int nMaxClient = m_nMaxConnect;
    int nCpuCount = m_nCpuCount;
    int nPort = m_nPort;

    struct sockaddr_in sin;

#ifdef _MSC_VER
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);

#endif
    //////////////////////////////////////////////////////////////////////////

    struct event_config* cfg = event_config_new();

#ifdef _MSC_VER
    m_pBase = event_base_new_with_config(cfg);
#else
    //event_config_avoid_method(cfg, "epoll");
    if (event_config_set_flag(cfg, EVENT_BASE_FLAG_EPOLL_USE_CHANGELIST) < 0)
    {
        //Ê¹ÓÃEPOLL
        return -1;
    }

    if (event_config_set_num_cpus_hint(cfg, nCpuCount) < 0)
    {
        return -1;
    }

    m_pBase = event_base_new_with_config(cfg);//event_base_new()

#endif
    event_config_free(cfg);

    //////////////////////////////////////////////////////////////////////////

    if (!m_pBase)
    {
        fprintf(stderr, "Could not initialize libevent!\n");
        Final();

        return -1;
    }

    //init time
    //gettime(m_pBase, &m_pBase->event_tv);

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(nPort);

    m_pListener = evconnlistener_new_bind(m_pBase, listener_cb, (void*)this,
                                       LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
                                       (struct sockaddr*)&sin,
                                       sizeof(sin));

    if (!m_pListener)
    {
        fprintf(stderr, "Could not create a Listener with port %d \n",nPort);
        
		Final();

        return -1;
    }
	    
	//     signal_event = evsignal_new(m_pBase, SIGINT, signal_cb, (void *)this);
    //
    //     if (!signal_event || event_add(signal_event, NULL)<0)
    //     {
    //         fprintf(stderr, "Could not create/add a signal event!\n");
    //         Final();
    //         return -1;
    //     }

    m_bServer = true;

    event_set_log_callback(&SGFNet::log_cb);

    return m_nMaxConnect;
}

bool SGFNet::CloseSocketAll()
{
    std::map<int, NetObject*>::iterator it = m_mObject.begin();
    for (it; it != m_mObject.end(); ++it)
    {
        int nFD = it->first;
        m_vRemoveObject.push_back(nFD);
    }

    ExecuteClose();

    m_mObject.clear();

    return true;
}

NetObject* SGFNet::GetNetObject(const int nSockIndex)
{
    std::map<int, NetObject*>::iterator it = m_mObject.find(nSockIndex);
    if (it != m_mObject.end())
    {
        return it->second;
    }

    return NULL;
}

void SGFNet::CloseObject(const int nSockIndex)
{
    std::map<int, NetObject*>::iterator it = m_mObject.find(nSockIndex);
    if (it != m_mObject.end())
    {
        NetObject* pObject = it->second;

        struct bufferevent* bev = pObject->GetBuffEvent();

        bufferevent_free(bev);

        m_mObject.erase(it);

        delete pObject;
        pObject = NULL;
    }
}

void SGFNet::ExecuteClose()
{
    for (int i = 0; i < m_vRemoveObject.size(); ++i)
    {
        int nSocketIndex = m_vRemoveObject[i];
        CloseObject(nSocketIndex);
    }

    m_vRemoveObject.clear();
}

void SGFNet::log_cb(int severity, const char* msg)
{

}

bool SGFNet::IsServer()
{
	return m_bServer;
}

bool SGFNet::Log(int severity, const char* msg)
{
    log_cb(severity, msg);
    return true;
}

bool SGFNet::SendMsgWithOutHead(const uint32_t nMsgID, const char* msg, const uint32_t nLen, const int nSockIndex /*= 0*/)
{
    std::string strOutData;
    int nAllLen = EnCode(nMsgID, msg, nLen, strOutData);
    if (nAllLen == nLen + MSG_HEAD_LENGTH)
    {
        return SendMsg(strOutData.c_str(), strOutData.length(), nSockIndex);
    }

    return false;
}

bool SGFNet::SendMsgWithOutHead(const uint32_t nMsgID, const char* msg, const uint32_t nLen, const std::list<int>& fdList)
{
    std::string strOutData;
    int nAllLen = EnCode(nMsgID, msg, nLen, strOutData);
    if (nAllLen == nLen + MSG_HEAD_LENGTH)
    {
        return SendMsg(strOutData.c_str(), strOutData.length(), fdList);
    }

    return false;
}

bool SGFNet::SendMsgToAllClientWithOutHead(const ui32 nMsgID, const char* msg, const uint32_t nLen)
{
    std::string strOutData;
    int nAllLen = EnCode(nMsgID, msg, nLen, strOutData);
    if (nAllLen == nLen + MSG_HEAD_LENGTH)
    {
        return SendMsgToAllClient(strOutData.c_str(), strOutData.length());
    }

    return false;
}

int SGFNet::EnCode(const ui32 unMsgID, const char* strData, const uint32_t unDataLen, std::string& strOutData)
{
    SGFMsgHead xHead;
    xHead.SetMsgID(unMsgID);
    xHead.SetBodyLength(unDataLen);

    char szHead[MSG_HEAD_LENGTH] = { 0 };
    xHead.EnCode(szHead);

    strOutData.clear();
    strOutData.append(szHead, MSG_HEAD_LENGTH);
    strOutData.append(strData, unDataLen);

    return xHead.GetBodyLength() +MSG_HEAD_LENGTH;
}

int SGFNet::DeCode(const char* strData, const uint32_t unAllLen, SGFMsgHead& xHead)
{
    if (unAllLen < MSG_HEAD_LENGTH)
    {
        return -1;
    }
	
    if (MSG_HEAD_LENGTH != xHead.DeCode(strData))
    {
        return -2;
    }

    if (xHead.GetBodyLength() > unAllLen)
    {
        return -3;
    }
    return xHead.GetBodyLength();
}

bool SGFNet::SendMsgWithPBMsgName(const char* msg, const uint32_t nLen, const int nSockIndex /*= 0*/)
{
	return SendMsg(msg, nLen, nSockIndex);
}
//
//bool SGFNet::DismantleWithPBName(NetObject* pObject)
//{
//	bool bNeedDismantle = false;
//
//	int len = pObject->GetBuffLen();
//	if (len >= kMinMessageLen)
//	{
//		unsigned short nMsgLen = 0;
//		::memcpy(&nMsgLen, pObject->GetBuff(), sizeof(nMsgLen));
//		if (len < nMsgLen)
//		{
//			return false;
//		}
//		MessagePtr pMsg = SGFCodec::decode(pObject->GetBuff()+kTagHeaderLen, nMsgLen-kTagHeaderLen);
//		if (pMsg)
//		{
//			std::map<std::string,NET_PBMSG_RECIEVE_FUNCTOR_PTR>::iterator it = m_xReciveCB.find(pMsg->GetDescriptor()->full_name());
//			if (m_xReciveCB.end() != it)
//			{
//				NET_PBMSG_RECIEVE_FUNCTOR_PTR& pFunPtr = it->second;
//				NET_PBMSG_RECIEVE_FUNCTOR* pFunc = pFunPtr.get();
//				pFunc->operator()(pObject->GetRealFD(),pMsg);
//			}
//
//			pObject->RemoveBuff(0, nMsgLen);
//
//			DismantleWithPBName(pObject);
//		}
//		else
//		{
//			bNeedDismantle = false;
//		}
//	}
//
//	return bNeedDismantle;
//}
