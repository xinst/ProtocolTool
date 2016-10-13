//*************************************************************************
// SGFMsgHeader.h 2016-3-23 16:36
// Author: Xin Songtao
// Purpose: 
//
//*************************************************************************

#ifndef SGF_MSGHEADER_H__
#define SGF_MSGHEADER_H__

#include <cstring>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <list>
#include "SGFPlatform.h"

#ifdef _MSC_VER
#include <Winsock2.h>
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MSG_HEAD_LENGTH 8

struct  SGFMsgHead
{
	SGFMsgHead()
		:m_unSize(0)
		,m_unMsgID(0)
	{

	}

	//主机次序到网络次序
	i64 SGF_HTONLL(i64 nData)
	{
#ifdef _MSC_VER
		return htonll(nData);
#else
		return htobe64(nData);
#endif	
	 }

	//网络次序到主机次序
	i64 SGF_NTOHLL(i64 nData)
	{
#ifdef _MSC_VER
		return ntohll(nData);
#else
		return be64toh(nData);
#endif
	}	


	//主机次序到网络次序
	i32 SGF_HTONL(i32 nData)
	{
#ifdef _MSC_VER
		return htonl(nData);
#else
		return htobe32(nData);
#endif
	}
	//网络次序到主机次序
	i32 SGF_NTOHL(i32 nData)
	{
#ifdef _MSC_VER
		return ntohl(nData);
#else
		return be32toh(nData);
#endif
	}
	//主机次序到网络次序
	i16 SGF_HTONS(i16 nData)
	{
#ifdef _MSC_VER
		return htons(nData);
#else
		return htobe16(nData);
#endif
	}
	//网络次序到主机次序
	i16 SGF_NTOHS(i16 nData)
	{
#ifdef _MSC_VER
		return ntohs(nData);
#else
		return be16toh(nData);
#endif
	}

	// 内存结构[ MsgID(2) | MsgSize(4) ]
	virtual int EnCode(char* strData)
	{
		ui32 nOffset = 0;

		ui32 nMsgID = SGF_HTONL(m_unMsgID);
		memcpy(strData + nOffset, (void*)(&nMsgID), sizeof(m_unMsgID));
		nOffset += sizeof(m_unMsgID);

		ui32 nPackSize = m_unSize + MSG_HEAD_LENGTH;
		ui32 nSize = SGF_HTONL(nPackSize);
		memcpy(strData + nOffset, (void*)(&nSize), sizeof(m_unSize));
		nOffset += sizeof(m_unSize);

		if (nOffset != MSG_HEAD_LENGTH)
		{
			assert(0);
		}

		return nOffset;
	}

	virtual int DeCode(const char* strData)
	{
		ui32 nOffset = 0;

		ui32 nMsgID = 0;
		memcpy(&nMsgID, strData + nOffset, sizeof(m_unMsgID));
		m_unMsgID = SGF_NTOHL(nMsgID);
		nOffset += sizeof(m_unMsgID);

		ui32 nPackSize = 0;
		memcpy(&nPackSize, strData + nOffset, sizeof(m_unSize));
		m_unSize = SGF_NTOHL(nPackSize) - MSG_HEAD_LENGTH;
		nOffset += sizeof(m_unSize);

		if (nOffset != MSG_HEAD_LENGTH)
		{
			assert(0);
		}

		return nOffset;
	}

	virtual ui32 GetMsgID() const
	{
		return m_unMsgID;
	}
	virtual void SetMsgID(ui32 nMsgID)
	{
		m_unMsgID = nMsgID;
	}

	virtual ui32 GetBodyLength() const
	{
		return m_unSize;
	}
	virtual void SetBodyLength(ui32 nLength)
	{
		m_unSize = nLength;
	}

protected:
	ui32 m_unSize;
	ui32 m_unMsgID;
};


#endif // SGFMSGHEADER_H__