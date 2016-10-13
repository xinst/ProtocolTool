#ifndef SGFI_NET_H
#define SGFI_NET_H

#include <cstring>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>

#ifndef _MSC_VER
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <vector>
#include <functional>
#include <memory>
#include <list>
#include <vector>

#include <assert.h>

#include "SGFUID.h"


typedef std::shared_ptr<google::protobuf::Message> MessagePtr;

#pragma pack(push, 1)

enum SGF_NET_EVENT
{
    SGF_NET_EVENT_EOF =			0x10,  //掉线
    SGF_NET_EVENT_ERROR =		0x20,  //未知错误
    SGF_NET_EVENT_TIMEOUT =		0x40,  //连接超时
    SGF_NET_EVENT_CONNECTED =	0x80,  //连接成功(作为客户端)
};

class SGFINet;
class NetObject;

typedef std::function<void(const int nSockIndex, const ui32 nMsgID, const char* msg, const uint32_t nLen)> NET_RECEIVE_FUNCTOR;
typedef std::shared_ptr<NET_RECEIVE_FUNCTOR> NET_RECEIVE_FUNCTOR_PTR;

typedef std::function<void(const int nSockIndex, const SGF_NET_EVENT nEvent, SGFINet* pNet)> NET_EVENT_FUNCTOR;
typedef std::shared_ptr<NET_EVENT_FUNCTOR> NET_EVENT_FUNCTOR_PTR;

typedef std::function<void(int severity, const char* msg)> NET_EVENT_LOG_FUNCTOR;
typedef std::shared_ptr<NET_EVENT_LOG_FUNCTOR> NET_EVENT_LOG_FUNCTOR_PTR;

typedef std::function<void(const int nSockIndex,MessagePtr pMsg)> NET_PBMSG_RECIEVE_FUNCTOR;
typedef std::shared_ptr<NET_PBMSG_RECIEVE_FUNCTOR> NET_PBMSG_RECIEVE_FUNCTOR_PTR;


class SGFINet
{
public:

	virtual ~SGFINet(){}

    virtual bool Execute() = 0;

    virtual void Initialization(const char* strIP, const unsigned short nPort) = 0;
    virtual int Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount = 4) = 0;

    virtual bool Final() = 0;

    //无包头，内部组装
    virtual bool SendMsgWithOutHead(const uint32_t nMsgID, const char* msg, const uint32_t nLen, const int nSockIndex = 0) = 0;

    //已带上包头
    virtual bool SendMsgToAllClient(const char* msg, const uint32_t nLen) = 0;

    //无包头，内部组装
    virtual bool SendMsgToAllClientWithOutHead(const uint32_t nMsgID, const char* msg, const uint32_t nLen) = 0;

    virtual bool CloseNetObject(const int nSockIndex) = 0;
    virtual NetObject* GetNetObject(const int nSockIndex) = 0;
    virtual bool AddNetObject(const int nSockIndex, NetObject* pObject) = 0;

	//直接发送pb结构的消息
	virtual bool SendMsgWithPBMsgName(const char* msg, const uint32_t nLen, const int nSockIndex = 0) = 0;

    virtual bool IsServer() = 0;

    virtual bool Log(int severity, const char* msg) = 0;
};

#pragma pack(pop)

#endif//SGFI_NET_H
