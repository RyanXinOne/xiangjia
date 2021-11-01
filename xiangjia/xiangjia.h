
// xiangjia.h : main header file for the PROJECT_NAME application
//

#pragma once

#include "resource.h"		// main symbols


// CxiangjiaApp:
// See xiangjia.cpp for the implementation of this class
//

class CxiangjiaApp : public CWinApp
{
public:
	CxiangjiaApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CxiangjiaApp theApp;
