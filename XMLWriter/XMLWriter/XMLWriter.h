
// XMLWriter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXMLWriterApp: 
// �йش����ʵ�֣������ XMLWriter.cpp
//

class CXMLWriterApp : public CWinApp
{
public:
	CXMLWriterApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CXMLWriterApp theApp;