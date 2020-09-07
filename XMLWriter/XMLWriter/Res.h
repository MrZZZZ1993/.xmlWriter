#pragma once
#include<iostream>
using namespace std;
#include <map>
#include "Singleton.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "stdafx.h"
#include "Platform.h"

struct RES
{
	char m_name[200];        //ͼƬ����
	char m_path[200];          //ͼƬ·�������ŵ�֡�����Ŷ�֡��
	char m_wholePath[100];
	CString m_wholePath1[100];
	int m_dir;                 //���Ŷ�֡������
	int m_frame;                 //���Ŷ�֡ÿ��֡��
	int m_frameCount;           //���Ŷ�֡��֡��
	int m_type;                  //ͼƬ����
	char m_mulPath[100][200];   //���Ŷ�֡ͼƬ·��
	RES()
	{
		for (int i = 0; i < 100; i++)
		{
			strcpy_s(m_mulPath[i], "");        //��ʼ�����Ŷ�֡·��
			strcpy_s(m_wholePath, "");   
		}
	}
};

class CRes :public CSingleton<CRes>
{
public:
	CRes();
	~CRes();
	void AddRes(CString name, RES*pRes);   //�����Դ
	void DeleteRes(CString name);             //ɾ����Դ
	//RES*GetRes(CString name);                 
	void SaveFile(CString fileName);     //���浽XML�ļ�
	void LoadFile(CString fileName);    //����XML�ļ�
	void DeleteAllRes();              //ɾ��������Դ
	RES* FindRes(CString name);           //������Դ
private:
	map<CString, RES*>m_res;
};

