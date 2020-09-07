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
	char m_name[200];        //图片名称
	char m_path[200];          //图片路径（单张单帧，单张多帧）
	char m_wholePath[100];
	CString m_wholePath1[100];
	int m_dir;                 //单张多帧总行数
	int m_frame;                 //单张多帧每行帧数
	int m_frameCount;           //多张多帧总帧数
	int m_type;                  //图片类型
	char m_mulPath[100][200];   //多张多帧图片路径
	RES()
	{
		for (int i = 0; i < 100; i++)
		{
			strcpy_s(m_mulPath[i], "");        //初始化多张多帧路径
			strcpy_s(m_wholePath, "");   
		}
	}
};

class CRes :public CSingleton<CRes>
{
public:
	CRes();
	~CRes();
	void AddRes(CString name, RES*pRes);   //添加资源
	void DeleteRes(CString name);             //删除资源
	//RES*GetRes(CString name);                 
	void SaveFile(CString fileName);     //保存到XML文件
	void LoadFile(CString fileName);    //加载XML文件
	void DeleteAllRes();              //删除所有资源
	RES* FindRes(CString name);           //查找资源
private:
	map<CString, RES*>m_res;
};

