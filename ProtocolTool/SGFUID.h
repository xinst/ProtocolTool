//*************************************************************************
// SGFUID.h 2016-3-23 16:15
// Author: Xin Songtao
// Purpose: 
//
//*************************************************************************

#ifndef SGF_UID_H__
#define SGF_UID_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SGFPlatform.h"
#include "lexical_cast.hpp"

struct SGFUID
{
	ui64 nData64;
	ui64 nHead64;

	SGFUID()
	{
		nData64 = 0;
		nHead64 = 0;
	}

	SGFUID(ui64 nHeadData, ui64 nData)
	{
		nHead64 = nHeadData;
		nData64 = nData;
	}

	SGFUID(const SGFUID& xData)
	{
		nHead64 = xData.nHead64;
		nData64 = xData.nData64;
	}

	SGFUID& operator=(const SGFUID& xData)
	{
		nHead64 = xData.nHead64;
		nData64 = xData.nData64;

		return *this;
	}

	ui64 GetData() const
	{
		return nData64;
	}

	ui64 GetHead() const
	{
		return nHead64;
	}

	void SetData(const ui64 nData)
	{
		nData64 = nData;
	}

	void SetHead(const ui64 nData)
	{
		nHead64 = nData;
	}

	bool IsNull() const
	{
		return 0 == nData64 && 0 == nHead64;
	}

	bool operator == (const SGFUID& id) const
	{
		return this->nData64 == id.nData64 && this->nHead64 == id.nHead64;
	}

	bool operator != (const SGFUID& id) const
	{
		return this->nData64 != id.nData64 || this->nHead64 != id.nHead64;
	}

	bool operator < (const SGFUID& id) const
	{
		if (this->nHead64 == id.nHead64)
		{
			return this->nData64 < id.nData64;
		}

		return this->nHead64 < id.nHead64;
	}

	std::string ToString() const
	{
		return lexical_cast<std::string>(nHead64)+ "-" + lexical_cast<std::string>(nData64);
	}

	bool FromString(const std::string& strID)
	{
		size_t nStrLength = strID.length();
		size_t nPos = strID.find('-');
		if (nPos == std::string::npos)
		{
			return false;
		}

		std::string strHead = strID.substr(0, nPos);
		std::string strData = "";
		if (nPos + 1 < nStrLength)
		{
			strData = strID.substr(nPos + 1, nStrLength - nPos);
		}

		try
		{
			nHead64 = lexical_cast<ui64>(strHead);
			nData64 = lexical_cast<ui64>(strData);

			return true;
		}
		catch (...)
		{
			return false;
		}
	}
};

#define NULL_GUID SGFUID()

#endif // SGF_UID_H__