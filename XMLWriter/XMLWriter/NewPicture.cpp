// NewPicture.cpp : ʵ���ļ�
//
#pragma once
#include "stdafx.h"
#include "XMLWriter.h"
#include "NewPicture.h"
#include "afxdialogex.h"
#include "Res.h"
#include "XMLWriterDlg.h"
// CNewPicture �Ի���

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


// CNewPicture ��Ϣ�������

BOOL CNewPicture::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CNewPicture::OnBnClickedOk()     //ȷ����ť�¼���Ӧ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString name, path, dir, frame, folderPath;   //�Ӵ��ڻ�ȡͼƬ���֣�·�����ļ�������
	m_name.GetWindowText(name);         
	m_picturePath.GetWindowText(path);
	m_folder.GetWindowText(folderPath);
	
	int nPos = path.Find('/');                  //�Ѿ���·�����С�/��
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

	if (name == "" || path == "")          //�ж�ͼƬ���ƺ�·���Ƿ�Ϊ��
		MessageBox(_T("Missing required input"), _T("Wrong"));
	else
	{
		path = _T("../bin/") + folderPath + path;    //�������·��
		HTREEITEM TreeItemSin = (HTREEITEM)CPlatform::GetInstance()->GetPlatData(_T("TreeItemSin"));  //��ȡ��
		if (CRes::GetInstance()->FindRes(name))
		{
			MessageBox(_T("The picture already exists"), _T("Wrong"));  //�ж�ͼƬ�����Ƿ��ظ�
			return;
		}
		else
		{                                                //��ͼƬ��ӵ���Դ
			RES*pRes = new RES;
			strcpy_s(pRes->m_name, CU_U2A(name.GetBuffer()).c_str());
			strcpy_s(pRes->m_path, CU_U2A(path.GetBuffer()).c_str());
			strcpy_s(pRes->m_wholePath, CU_U2A(m_wholePath.GetBuffer()).c_str());
			(*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(name, TreeItemSin); //��ӵ����νṹ
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

void CNewPicture::OnBnClickedButton1()             //��ȡͼƬ·��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY);
	if (fileDlg.DoModal() == IDOK)
	{
		CString picturePath = fileDlg.GetPathName();        //��ͼƬ���С�\\��֮ǰ�Ĳ���ȥ����ֻ����ͼƬ����
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
