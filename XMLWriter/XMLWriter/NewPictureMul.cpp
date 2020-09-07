// NewPictureMul.cpp : 实现文件
//

#include "stdafx.h"
#include "XMLWriter.h"
#include "NewPictureMul.h"
#include "afxdialogex.h"


// CNewPictureMul 对话框

IMPLEMENT_DYNAMIC(CNewPictureMul, CDialogEx)

CNewPictureMul::CNewPictureMul(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewPictureMul::IDD, pParent)
{

}

CNewPictureMul::~CNewPictureMul()
{
}

void CNewPictureMul::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_pictureName);
	DDX_Control(pDX, IDC_LIST1, m_pathList);
	DDX_Control(pDX, IDC_EDIT2, m_folder);
}


BEGIN_MESSAGE_MAP(CNewPictureMul, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CNewPictureMul::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewPictureMul::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CNewPictureMul::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewPictureMul 消息处理程序


void CNewPictureMul::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT | OFN_ENABLESIZING | OFN_HIDEREADONLY);
	if (fileDlg.DoModal() == IDOK)
	{                                       //批量获取图片
		POSITION pos_file;
		pos_file = fileDlg.GetStartPosition();
		while (pos_file != NULL)
		{
			CString pathName = fileDlg.GetNextPathName(pos_file);
			m_wholePath[m_pathList.GetCount()] = pathName;              //去掉路径“\\”之前的部分，只保留图片名字
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
			m_pathList.InsertString(m_pathList.GetCount(), _T("../bin/")+pathName);  //获取图片路径并且按顺序插入到列表中
		}
	}
}


void CNewPictureMul::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_pathList.DeleteString(m_pathList.GetCurSel());//删除选中的列表信息
}


void CNewPictureMul::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	CString name, path, folderPath;
	m_pictureName.GetWindowText(name);
	if (m_pathList.GetCount() == 0 || name == "")
		MessageBox(_T("Missing required input"), _T("Wrong"));
	else
	{
		if (!CRes::GetInstance()->FindRes(name))    //判断图片名称是否已经存在
		{
			RES*pRes = new RES;
			strcpy_s(pRes->m_name, CU_U2A(name.GetBuffer()).c_str());
			HTREEITEM TreeItemMul = (HTREEITEM)CPlatform::GetInstance()->GetPlatData(_T("TreeItemMul"));//获取树
			(*(CTreeCtrl*)CPlatform::GetInstance()->GetPlatData(_T("pictureTree"))).InsertItem(name, TreeItemMul);//添加到树
			pRes->m_type = 2;
			pRes->m_frameCount = m_pathList.GetCount();
			for (int i = 0; i < m_pathList.GetCount(); i++)
			{
				m_pathList.GetText(i, path);
				m_folder.GetWindowText(folderPath);        //却掉路径“/”之前的部分，只保留图片名称

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

				if (folderPath != _T(""))
					folderPath += _T("/");
				path = _T("../bin/") + folderPath + path;
				strcpy_s(pRes->m_mulPath[i], CU_U2A(path.GetBuffer()).c_str());
				pRes->m_wholePath1[i] = m_wholePath[i];
			}
			CRes::GetInstance()->AddRes(name, pRes);
			CDialogEx::OnOK();
		}
		else
			MessageBox(_T("The picture already exists"), _T("Wrong"));
	}
}
