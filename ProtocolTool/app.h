//*************************************************************************
// app.h 2016-8-4 10:53
// Author: Stonexin
// Purpose: 应用程序入口
//
//*************************************************************************

#ifndef APP_H__
#define APP_H__

#include "Dlg.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	virtual int  OnExit();
};

DECLARE_APP(MyApp)

#endif // APP_H__