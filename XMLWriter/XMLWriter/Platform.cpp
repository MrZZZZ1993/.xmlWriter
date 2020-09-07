#include "stdafx.h"
#include "Platform.h"


CPlatform::CPlatform()
{
}

CPlatform::~CPlatform()
{
	m_plat.clear();
}

void CPlatform::AddPlatData(CString name, void*res)
{
	m_plat[name] = res;
}

void*CPlatform::GetPlatData(CString name)
{
	map<CString, void*>::iterator it = m_plat.find(name);
	if (it != m_plat.end())
		return it->second;
	else
		return nullptr;
}
