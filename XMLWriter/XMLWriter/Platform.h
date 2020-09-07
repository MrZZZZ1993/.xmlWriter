#pragma once
#include<iostream>
using namespace std;
#include <map>
#include "Singleton.h"

class CPlatform:public CSingleton<CPlatform>
{
public:
	CPlatform();
	~CPlatform();
	void AddPlatData(CString, void*);
	void*GetPlatData(CString);
private:
	map<CString, void*>m_plat;
};

