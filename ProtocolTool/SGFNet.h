#ifndef SGF_NET_H
#define SGF_NET_H

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/thread.h>
#include <event2/event_compat.h>
#include "SGFMsgHeader.h"
#include "NetObject.h"
#include "SGFINet.h"

#pragma pack(push, 1)


class SGFNet : public SGFINet
{
public:
    SGFNet( ui16 nCodecType=0 )
    {
        m_pBase = NULL;
        m_pListener = NULL;

        m_strIP = "";
        m_nPort = 0;
        m_nCpuCount = 0;
        m_bServer = false;
		m_nCodecType = nCodecType;
    }

    template<typename BaseType>
    SGFNet(BaseType* pBaseType, 
		void (BaseType::*handleRecieve)(const int, const ui32, const char*, const uint32_t), 
		void (BaseType::*handleEvent)(const int, const SGF_NET_EVENT, SGFINet*),ui16 nCodecType=0)
    {
        m_pBase = NULL;
        m_pListener = NULL;

        m_RecvCB = std::bind(handleRecieve, pBaseType, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        m_EventCB = std::bind(handleEvent, pBaseType, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        m_strIP = "";
        m_nPort = 0;
        m_nCpuCount = 0;
        m_bServer = false;
		m_nCodecType = nCodecType;
    }
    virtual ~SGFNet() {};

public:
    virtual bool Execute();

    virtual void Initialization(const char* strIP, const unsigned short nPort);
    virtual int Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount = 4);

    virtual bool Final();

    //无包头，内部组装
    virtual bool SendMsgWithOutHead(const ui32 nMsgID, const char* msg, const uint32_t nLen, const int nSockIndex);
    virtual bool SendMsgWithOutHead(const ui32 nMsgID, const char* msg, const uint32_t nLen, const std::list<int>& fdList);
    virtual bool SendMsgToAllClientWithOutHead(const ui32 nMsgID, const char* msg, const uint32_t nLen);
	
    virtual bool CloseNetObject(const int nSockIndex);
    virtual bool AddNetObject(const int nSockIndex, NetObject* pObject);
    virtual NetObject* GetNetObject(const int nSockIndex);

	virtual bool IsServer();
    virtual bool Log(int severity, const char* msg);
private:
    //已带上包头
    bool SendMsgToAllClient(const char* msg, const uint32_t nLen);
    bool SendMsg(const char* msg, const uint32_t nLen, const std::list<int>& fdList);
    bool SendMsg(const char* msg, const uint32_t nLen, const int nSockIndex);
	bool SendMsgWithPBMsgName(const char* msg, const uint32_t nLen, const int nSockIndex = 0);

private:
    void ExecuteClose();
    bool CloseSocketAll();

    bool Dismantle(NetObject* pObject);

	//解析方式
	//bool DismantleWithPBName(NetObject* pObject);


    int InitClientNet();
    int InitServerNet();
    void CloseObject(const int nSockIndex);

    static void listener_cb(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data);
    static void conn_readcb(struct bufferevent* bev, void* user_data);
    static void conn_writecb(struct bufferevent* bev, void* user_data);
    static void conn_eventcb(struct bufferevent* bev, short events, void* user_data);
    static void time_cb(evutil_socket_t fd, short _event, void* argc);
    static void log_cb(int severity, const char* msg);

protected:
    int DeCode(const char* strData, const uint32_t unLen, SGFMsgHead& xHead);
    int EnCode(const ui32 unMsgID, const char* strData, const uint32_t unDataLen, std::string& strOutData);

private:
    //<fd,object>
    std::map<int, NetObject*> m_mObject;
    std::vector<int> m_vRemoveObject;

    int m_nMaxConnect;
    std::string m_strIP;
    int m_nPort;
    int m_nCpuCount;
    bool m_bServer;

	ui16 m_nCodecType;

    struct event_base* m_pBase;
    struct evconnlistener* m_pListener;
    //////////////////////////////////////////////////////////////////////////
    NET_RECEIVE_FUNCTOR m_RecvCB;
    NET_EVENT_FUNCTOR m_EventCB;
	std::map<std::string,NET_PBMSG_RECIEVE_FUNCTOR_PTR> m_xReciveCB;

    //////////////////////////////////////////////////////////////////////////
};

#pragma pack(pop)

#endif
