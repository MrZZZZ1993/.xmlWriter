#include "stdafx.h"
#include "Res.h"


CRes::CRes()
{
}

CRes::~CRes()
{
	DeleteAllRes();
}

void CRes::AddRes(CString name, RES*pRes)
{
	m_res[name] = pRes;
}

void CRes::DeleteRes(CString name)
{
	map<CString, RES*>::iterator it = m_res.find(name);
	if (it != m_res.end())
	{
		delete it->second;
		m_res.erase(it);
	}
}

//RES*CRes::GetRes(CString name)
//{
//	map<CString, RES*>::iterator it = m_res.find(name);
//	if (it != m_res.end())
//		return it->second;
//	else
//		return nullptr;
//}

void CRes::SaveFile(CString fileName)
{
	char name[200];
	strcpy_s(name, CU_U2A(fileName.GetBuffer()).c_str());

	TiXmlDocument *pDocument = new TiXmlDocument;
	if (!pDocument)
		return;

	map<CString, RES*>::iterator it = m_res.begin();
	for (; it != m_res.end(); it++)
	{
		RES*pRes = it->second;
		switch (pRes->m_type)
		{
		case 0:
		{
				  TiXmlElement *element = new TiXmlElement("STATICIMAGE");
				  element->SetAttribute("imgType", pRes->m_type);
				  element->SetAttribute("name", pRes->m_name);
				  element->SetAttribute("path", pRes->m_path);
				  pDocument->LinkEndChild(element);
		}
			break;
		case 1:
		{
				  TiXmlElement *element = new TiXmlElement("SINGLEIMAGE");
				  element->SetAttribute("imgType", pRes->m_type);
				  element->SetAttribute("name", pRes->m_name);
				  element->SetAttribute("path", pRes->m_path);
				  element->SetAttribute("countFrame", pRes->m_frame);
				  element->SetAttribute("countDir", pRes->m_dir);
				  pDocument->LinkEndChild(element);
		}
			break;
		case 2:
		{
				  TiXmlElement *element = new TiXmlElement("MULIMAGE");
				  element->SetAttribute("imgType", pRes->m_type);
				  element->SetAttribute("title", pRes->m_name);
				  element->SetAttribute("countFrame", pRes->m_frameCount);
				  for (int i = 0; i<pRes->m_frameCount; i++)
				  {
					  TiXmlElement *childElement = new TiXmlElement("child");
					  childElement->SetAttribute("path", pRes->m_mulPath[i]);
					  element->LinkEndChild(childElement);
				  }
				  pDocument->LinkEndChild(element);
		}
			break;
		}
	}
	pDocument->SaveFile(name);
}

RES* CRes::FindRes(CString name)
{
	map<CString, RES*>::iterator it = m_res.find(name);
	if (it != m_res.end())
		return it->second;
	else
		return nullptr;
}

void CRes::DeleteAllRes()
{
	map<CString, RES*>::iterator it = m_res.begin();
	for (; it != m_res.end(); it++)
		delete it->second;
	m_res.clear();
}

void CRes::LoadFile(CString fileName)
{
	DeleteAllRes();

	(*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).DeleteAllItems();
	HTREEITEM TreeItemStatic = (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(_T("SinglePicWithSingleFrame"));
	HTREEITEM TreeItemSin = (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(_T("SinglePicWithMultipleFrame"));
	HTREEITEM TreeItemMul = (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(_T("MultiplePic"));
	CPlatform::GetInstance()->AddPlatData(_T("TreeItemStatic"), TreeItemStatic);
	CPlatform::GetInstance()->AddPlatData(_T("TreeItemSin"), TreeItemSin);
	CPlatform::GetInstance()->AddPlatData(_T("TreeItemMul"), TreeItemMul);

	char filename[200];
	strcpy_s(filename, CU_U2A(fileName.GetBuffer()).c_str());

	TiXmlDocument *doc = new TiXmlDocument(filename);
	doc->LoadFile();
	TiXmlElement*element = doc->FirstChildElement();
	while (element)
	{
		RES*pRes = new RES;
		element->Attribute("imgType", &(pRes->m_type));
		switch (pRes->m_type)
		{
		case 0:
		{
				  strcpy_s(pRes->m_name, element->Attribute("name"));
				  strcpy_s(pRes->m_path, element->Attribute("path"));
				  CString pitureName = CU_A2U(pRes->m_name).c_str();
				  AddRes(pitureName, pRes);
				  (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(pitureName, TreeItemStatic);
		}
			break;
		case 1:
		{
				  strcpy_s(pRes->m_name, element->Attribute("name"));
				  strcpy_s(pRes->m_path, element->Attribute("path"));
				  CString pitureName = CU_A2U(pRes->m_name).c_str();
				  element->Attribute("countFrame", &(pRes->m_frame));
				  element->Attribute("countDir", &(pRes->m_dir));
				  AddRes(pitureName, pRes);
				  (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(pitureName, TreeItemSin);
		}
			break;
		case 2:
		{
				  strcpy_s(pRes->m_name, element->Attribute("title"));
				  CString pitureName = CU_A2U(pRes->m_name).c_str();
				  element->Attribute("countFrame", &(pRes->m_frameCount));
				  TiXmlElement*child = element->FirstChildElement();
				  int count = 0;
				  while (child)
				  {
					  strcpy_s(pRes->m_mulPath[count], child->Attribute("path"));
					  count++;
					  child = child->NextSiblingElement();
				  }
				  AddRes(pitureName, pRes);
				  (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(pitureName, TreeItemMul);
		}
			break;
		}
		element = element->NextSiblingElement();
	}
}