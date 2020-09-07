// NewPictureStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "XMLWriter.h"
#include "NewPictureStatic.h"
#include "afxdialogex.h"


// CNewPictureStatic 对话框

IMPLEMENT_DYNAMIC(CNewPictureStatic, CDialogEx)

CNewPictureStatic::CNewPictureStatic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewPictureStatic::IDD, pParent)
{

}

CNewPictureStatic::~CNewPictureStatic()
{
}

void CNewPictureStatic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO2, m_radioSin);
	DDX_Control(pDX, IDC_EDIT1, m_pictureName);
	DDX_Control(pDX, IDC_EDIT2, m_picturePath);
	DDX_Control(pDX, IDC_BUTTON4, m_addPictureSin);
	DDX_Control(pDX, IDC_BUTTON2, m_addPicture);
	DDX_Control(pDX, IDC_BUTTON3, m_deletePicture);
	DDX_Control(pDX, IDC_LIST1, m_pathList);
	DDX_Control(pDX, IDC_EDIT3, m_folder);
}


BEGIN_MESSAGE_MAP(CNewPictureStatic, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO2, &CNewPictureStatic::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CNewPictureStatic::OnBnClickedRadio3)
	ON_BN_CLICKED(IDOK, &CNewPictureStatic::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &CNewPictureStatic::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewPictureStatic::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CNewPictureStatic::OnBnClickedButton3)
END_MESSAGE_MAP()


// CNewPictureStatic 消息处理程序

BOOL CNewPictureStatic::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_radio = 1;
	m_radioSin.SetCheck(BST_CHECKED);     //默认单张添加
	m_pictureName.EnableWindow(true);
	m_picturePath.EnableWindow(true);
	m_addPictureSin.EnableWindow(true);
	m_addPicture.EnableWindow(false);
	m_deletePicture.EnableWindow(false);
	m_pathList.EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CNewPictureStatic::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_radio = 1;
    m_pictureName.EnableWindow(true);    //选中单张添加，并且将批量添加功能禁用
	m_picturePath.EnableWindow(true);
	m_addPictureSin.EnableWindow(true);
	m_addPicture.EnableWindow(false);
	m_deletePicture.EnableWindow(false);
	m_pathList.EnableWindow(false);
}


void CNewPictureStatic::OnBnClickedRadio3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_radio = 2;                                          //选中批量添加，将单张添加功能禁用
	m_pictureName.EnableWindow(false);
	m_picturePath.EnableWindow(false);
	m_addPictureSin.EnableWindow(false);
	m_addPicture.EnableWindow(true);
	m_deletePicture.EnableWindow(true);
	m_pathList.EnableWindow(true);
}


void CNewPictureStatic::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	HTREEITEM TreeItemStatic = (HTREEITEM)CPlatform::GetInstance()->GetPlatData(_T("TreeItemStatic"));
	CString folderPath;
	m_folder.GetWindowText(folderPath);
	if (folderPath != _T(""))
		folderPath += _T("/");

	switch (m_radio)                      //1.单张添加      2,批量添加   保存至资源当中
	{
	case 1:
	{
			  CString name, path;
			  m_pictureName.GetWindowText(name);
			  m_picturePath.GetWindowText(path);
			  

			  int nPos = path.Find('/');
			  while (nPos)
			  {
				  path = path.Mid(nPos + 1, path.GetLength() - nPos);
				  nPos = path.Find('/');

				  if (nPos == -1)
				  {
					  nPos = 0;
				  }
			  }

			  if (name == "" || path == "")
				  MessageBox(_T("Missing required input"), _T("Wrong"));
			  else
			  {
				  path = _T("../bin/") + folderPath + path;
				  if (!CRes::GetInstance()->FindRes(name))
				  {
					  RES*pRes = new RES;
					  strcpy_s(pRes->m_name, CU_U2A(name.GetBuffer()).c_str());
					  strcpy_s(pRes->m_path, CU_U2A(path.GetBuffer()).c_str());
					  strcpy_s(pRes->m_wholePath, CU_U2A(m_wholePath.GetBuffer()).c_str());
					  (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(name, TreeItemStatic);
					  pRes->m_type = 0;
					  CRes::GetInstance()->AddRes(name, pRes);
					  CDialogEx::OnOK();
				  }
				  else
					  MessageBox(_T("The picture already exists"), _T("Wrong"));
			  }
	}
		break;
	case 2:
	{
			  CString path;
			  if (m_pathList.GetCount()==0)
				  MessageBox(_T("Missing required input"), _T("Wrong"));
			  else
			  {
				  for (int i = 0; i < m_pathList.GetCount(); i++)
				  {
					  RES*pRes = new RES;
					  m_pathList.GetText(i, path);
					  CString name = path;
					  int nPos = name.Find('/');
					  while (nPos)
					  {
						  name = name.Mid(nPos + 1, name.GetLength() - nPos);
						  nPos = name.Find('/');
						  if (nPos == -1)
						  {
							  nPos = 0;
						  }
					  }
					  path = _T("../bin/") + folderPath + name;
					  nPos = name.ReverseFind('.');
					  name = name.Left(nPos);
					

					 if (!CRes::GetInstance()->FindRes(name))
					 {
						 strcpy_s(pRes->m_name, CU_U2A(name.GetBuffer()).c_str());
						 strcpy_s(pRes->m_path, CU_U2A(path.GetBuffer()).c_str());
						 strcpy_s(pRes->m_wholePath, CU_U2A(m_wholePath1[i].GetBuffer()).c_str());
						 pRes->m_type = 0;
						 CRes::GetInstance()->AddRes(name, pRes);
						 (*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(name, TreeItemStatic);
					 }
				  }
				  CDialogEx::OnOK();
			  }
	}
		break;
	}
}


void CNewPictureStatic::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码

	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY);   //获取图片路径
	if (fileDlg.DoModal() == IDOK)
	{
		CString picturePath = fileDlg.GetPathName();
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
		m_picturePath.SetWindowText(_T("../bin/")+picturePath);
	}
}


void CNewPictureStatic::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY);
	if (fileDlg.DoModal() == IDOK)
	{
		POSITION pos_file;                                //批量获取图片并且添加到列表当中
		pos_file = fileDlg.GetStartPosition();
		while (pos_file != NULL)
		{
			CString pathName = fileDlg.GetNextPathName(pos_file);
			m_wholePath1[m_pathList.GetCount()] = pathName;
			int nPos = pathName.Find('\\');
			while (nPos)
			{
				pathName = pathName.Mid(nPos + 1, pathName.GetLength() - nPos);
				nPos = pathName.Find('\\');

				if (nPos == -1)
				{
					nPos = 0;
				}
			}
			m_pathList.InsertString(m_pathList.GetCount(), _T("../bin/") + pathName);
		}
	}
}


void CNewPictureStatic::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_pathList.DeleteString(m_pathList.GetCurSel());   //删除选中列表内容
}
