
// TakeOwnerShip.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTakeOwnerShipApp:
// �йش����ʵ�֣������ TakeOwnerShip.cpp
//

class CTakeOwnerShipApp : public CWinApp
{
public:
	CTakeOwnerShipApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTakeOwnerShipApp theApp;