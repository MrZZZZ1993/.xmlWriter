// NewPicture.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "XMLWriter.h"
#include "NewPicture.h"
#include "afxdialogex.h"
#include "Res.h"
#include "XMLWriterDlg.h"
// CNewPicture 对话框

IMPLEMENT_DYNAMIC(CNewPicture, CDialogEx)

CNewPicture::CNewPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewPicture::IDD, pParent)
{
	
}

CNewPicture::~CNewPicture()
{
}

void CNewPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT3, m_dir);
	DDX_Control(pDX, IDC_EDIT4, m_frame);
	DDX_Control(pDX, IDC_EDIT2, m_picturePath);
	DDX_Control(pDX, IDC_EDIT5, m_folder);
}


BEGIN_MESSAGE_MAP(CNewPicture, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewPicture::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewPicture::OnBnClickedButton1)
END_MESSAGE_MAP()


// CNewPicture 消息处理程序

BOOL CNewPicture::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CNewPicture::OnBnClickedOk()     //确定按钮事件响应
{
	// TODO:  在此添加控件通知处理程序代码

	CString name, path, dir, frame, folderPath;   //从窗口获取图片名字，路径，文件夹名称
	m_name.GetWindowText(name);         
	m_picturePath.GetWindowText(path);
	m_folder.GetWindowText(folderPath);
	
	int nPos = path.Find('/');                  //把绝对路径带有‘/’
	while (nPos)
	{
		path = path.Mid(nPos + 1, path.GetLength() - nPos);
		nPos = path.Find('/');

		if (nPos == -1)
		{
			nPos = 0;
		}
	}

	if (folderPath != _T(""))                 
		folderPath += _T("/");

	if (name == "" || path == "")          //判断图片名称和路径是否为空
		MessageBox(_T("Missing required input"), _T("Wrong"));
	else
	{
		path = _T("../bin/") + folderPath + path;    //生成相对路径
		HTREEITEM TreeItemSin = (HTREEITEM)CPlatform::GetInstance()->GetPlatData(_T("TreeItemSin"));  //获取树
		if (CRes::GetInstance()->FindRes(name))
		{
			MessageBox(_T("The picture already exists"), _T("Wrong"));  //判断图片名称是否重复
			return;
		}
		else
		{                                                //把图片添加到资源
			RES*pRes = new RES;
			strcpy_s(pRes->m_name, CU_U2A(name.GetBuffer()).c_str());
			strcpy_s(pRes->m_path, CU_U2A(path.GetBuffer()).c_str());
			strcpy_s(pRes->m_wholePath, CU_U2A(m_wholePath.GetBuffer()).c_str());
			(*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(name, TreeItemSin); //添加到树形结构
			pRes->m_type = 1;
			m_dir.GetWindowText(dir);
			m_frame.GetWindowText(frame);
			pRes->m_dir = _ttoi(dir);
			pRes->m_frame = _ttoi(frame);
			CRes::GetInstance()->AddRes(name, pRes);
			CDialogEx::OnOK();
		}
	}
}

void CNewPicture::OnBnClickedButton1()             //获取图片路径
{
	// TODO:  在此添加控件通知处理程序代码

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY);
	if (fileDlg.DoModal() == IDOK)
	{
		CString picturePath = fileDlg.GetPathName();        //把图片带有“\\”之前的部分去掉，只保留图片名称
		m_wholePath = picturePath;
		int nPos = picturePath.Find('\\');
		while (nPos)
		{
			picturePath = picturePath.Mid(nPos + 1, picturePath.GetLength() - nPos);
			nPos = picturePath.Find('\\');

			if (nPos == -1)
			{
				nPos = 0;
			}
		}
		m_picturePath.SetWindowText(_T("../bin/") + picturePath);
	}
}
