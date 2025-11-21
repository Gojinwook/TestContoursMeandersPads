
// Master_One.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMasterOneApp:
// See Master_One.cpp for the implementation of this class
//

class CMasterOneApp : public CWinApp
{
public:
	CMasterOneApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMasterOneApp theApp;
