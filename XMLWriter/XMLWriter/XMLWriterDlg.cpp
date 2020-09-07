
// XMLWriterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XMLWriter.h"
#include "XMLWriterDlg.h"
#include "afxdialogex.h"
#include "Res.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CXMLWriterDlg �Ի���



CXMLWriterDlg::CXMLWriterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXMLWriterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXMLWriterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_pictureTree);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT3, m_dir);
	DDX_Control(pDX, IDC_EDIT6, m_frame);
	DDX_Control(pDX, IDC_EDIT7, m_frameCount);
	DDX_Control(pDX, IDC_LIST1, m_pathList);
	DDX_Control(pDX, IDC_BUTTON5, m_addPath);
	DDX_Control(pDX, IDC_BUTTON6, m_deletePath);
	DDX_Control(pDX, IDC_EDIT8, m_folder);
	DDX_Control(pDX, IDC_PICTURE, m_showPicture);
	DDX_Control(pDX, IDC_LIST2, m_wholePathList);
}

BEGIN_MESSAGE_MAP(CXMLWriterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CXMLWriterDlg::OnBnClickedOk)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CXMLWriterDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON1, &CXMLWriterDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CXMLWriterDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CXMLWriterDlg::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CXMLWriterDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &CXMLWriterDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CXMLWriterDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CXMLWriterDlg::OnBnClickedButton6)
	ON_LBN_SELCHANGE(IDC_LIST1, &CXMLWriterDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CXMLWriterDlg ��Ϣ�������

BOOL CXMLWriterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	HTREEITEM m_hTreeItemStatic = m_pictureTree.InsertItem(_T("SinglePicWithSingleFrame"));
	HTREEITEM m_hTreeItemSin = m_pictureTree.InsertItem(_T("SinglePicWithMultipleFrame"));
	HTREEITEM m_hTreeItemMul = m_pictureTree.InsertItem(_T("MultiplePic"));

	CPlatform::GetInstance()->AddPlatData(_T("TreeItemStatic"), m_hTreeItemStatic);
	CPlatform::GetInstance()->AddPlatData(_T("TreeItemSin"), m_hTreeItemSin);
	CPlatform::GetInstance()->AddPlatData(_T("TreeItemMul"), m_hTreeItemMul);
	CPlatform::GetInstance()->AddPlatData(_T("pictureTree"), &m_pictureTree);
	m_pictureTree.ModifyStyle(0xF, TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS);
	m_name.EnableWindow(false);
	m_pathList.EnableWindow(false);
	m_dir.EnableWindow(false);
	m_frame.EnableWindow(false);
	m_frameCount.EnableWindow(false);
	m_addPath.EnableWindow(false);
	m_deletePath.EnableWindow(false);
	m_folder.EnableWindow(false);

	HICON icon[2];
	icon[0]=AfxGetApp()->LoadIcon(IDI_ICON3);
	CImageList*m_imageList=new CImageList;
	m_imageList->Create(16,16,ILC_COLOR32|ILC_MASK,7,7);
	m_imageList->Add(icon[0]);
	m_pictureTree.SetImageList(m_imageList,TVSIL_NORMAL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CXMLWriterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CXMLWriterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CXMLWriterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXMLWriterDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (m_pictureName == "SinglePicWithMultipleFrame")              //ѡ��ͼƬ���ͣ�����Ӧ�ĶԻ���
		m_newPicture.DoModal();
	else if (m_pictureName == "MultiplePic")
		m_newPictureMul.DoModal();
	else
		m_newPictureStatic.DoModal();
		
	
}


void CXMLWriterDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	                                                               //���νṹ����¼�
	m_currentItem = pNMTreeView->itemNew.hItem;
	m_pictureName = m_pictureTree.GetItemText(m_currentItem);
	m_pRes = CRes::GetInstance()->FindRes(m_pictureName);
	CBitmap bitmap;  // CBitmap�������ڼ���λͼ   
	CImage img, imDest;
	HRESULT ret;
	HBITMAP hbitmap;
	CDC *pDc;
	RECT rect;
	int pictureWidth;
	int tempWidth;
	int tempHeight;
	double ratio;
	m_pathList.ResetContent();
	if (m_pRes)
	{
		m_addPath.EnableWindow(true);
		m_deletePath.EnableWindow(true);
	
		m_folder.EnableWindow(true);
		m_name.SetWindowText(m_pictureName);
		switch (m_pRes->m_type)
		{
		case 0:
			m_pathList.EnableWindow(false);
			m_dir.EnableWindow(false);
			m_frame.EnableWindow(false);
			m_dir.SetWindowText(_T(""));
			m_frame.SetWindowText(_T(""));
			m_frameCount.SetWindowText(_T(""));
			m_pathList.AddString(CU_A2U(m_pRes->m_path).c_str());
			ret = img.Load(CU_A2U(m_pRes->m_wholePath).c_str());
			if(strcmp(m_pRes->m_wholePath,"")!=0)
			{
				pictureWidth = img.GetWidth();
				tempWidth = pictureWidth;
				tempHeight = img.GetHeight();
				while (pictureWidth > 200 || tempHeight>400)   //����������ͼƬ
				{
					pictureWidth /= 2;
					tempHeight /= 2;
				}
				ratio = (double)pictureWidth / (double)tempWidth;
				imDest.Create(ratio*tempWidth, ratio*img.GetHeight(), 32);
				img.StretchBlt(imDest.GetDC(), 0, 0, ratio*tempWidth, ratio*img.GetHeight());//����ͼƬ
				imDest.ReleaseDC();
				hbitmap = (HBITMAP)imDest.Detach();
				m_showPicture.SetBitmap(hbitmap);    // ����ͼƬ�ؼ�λͼ
			}
			else
				m_showPicture.SetBitmap(NULL);
			break;
		case 1:
			m_pathList.EnableWindow(false);
			m_dir.EnableWindow(true);
			m_frame.EnableWindow(true);
			char c2[10], c1[10];
			_itoa_s(m_pRes->m_frame, c2, 10);
			_itoa_s(m_pRes->m_dir, c1, 10);
			m_frame.SetWindowText(CU_A2U(c2).c_str());
			m_dir.SetWindowText(CU_A2U(c1).c_str());
			m_frameCount.SetWindowText(_T(""));
			m_pathList.AddString(CU_A2U(m_pRes->m_path).c_str());
			ret = img.Load(CU_A2U(m_pRes->m_wholePath).c_str());
			if(strcmp(m_pRes->m_wholePath,"")!=0)
			{
				pictureWidth = img.GetWidth();
				tempWidth = pictureWidth;
				tempHeight = img.GetHeight();
				while (pictureWidth > 200 || tempHeight>400)
				{
					pictureWidth /= 2;
					tempHeight /= 2;
				}
				ratio = (double)pictureWidth / (double)tempWidth;
				imDest.Create(ratio*tempWidth, ratio*img.GetHeight(), 32);
				img.StretchBlt(imDest.GetDC(), 0, 0, ratio*tempWidth, ratio*img.GetHeight());
				imDest.ReleaseDC();

				hbitmap = (HBITMAP)imDest.Detach();
				m_showPicture.SetBitmap(hbitmap);    // ����ͼƬ�ؼ�λͼ
			}
			else
				m_showPicture.SetBitmap(NULL);
			break;
		case 2:
			m_pathList.EnableWindow(true);
			m_dir.EnableWindow(false);
			m_frame.EnableWindow(false);
			char c[10];
			_itoa_s(m_pRes->m_frameCount, c, 10);
			m_frameCount.SetWindowText(CU_A2U(c).c_str());
			m_dir.SetWindowText(_T(""));
			m_frame.SetWindowText(_T(""));
			for (int i = 0; i < m_pRes->m_frameCount; i++)
			{
				m_pathList.InsertString(i,CU_A2U(m_pRes->m_mulPath[i]).c_str());
	     		m_wholePathList.InsertString(i,m_pRes->m_wholePath1[i]);
			}
			break;
		}
	}
	else
	{
		m_name.EnableWindow(false);
		m_dir.EnableWindow(false);
		m_frame.EnableWindow(false);
		m_pathList.EnableWindow(false);
		m_name.SetWindowText(_T(""));
		m_dir.SetWindowText(_T(""));
		m_frame.SetWindowText(_T(""));
		m_frameCount.SetWindowText(_T(""));
		m_folder.SetWindowTextW(_T(""));
		m_addPath.EnableWindow(false);
		m_deletePath.EnableWindow(false);
		m_folder.EnableWindow(false);
		m_showPicture.SetBitmap(NULL);
	}
	*pResult = 0;
}


void CXMLWriterDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (!m_pRes)                       //��������޸���Ϣ
	{
		MessageBox(_T("There is no information to save"), _T("Wrong"), 0);
		return;
	}

	if (m_pathList.GetCount()==0)
	{
		MessageBox(_T("Please fill the path"), _T("Wrong"), 0);
		return;
	}

	RES*pRes = CRes::GetInstance()->FindRes(m_pictureName);
	CString path, dir, frame, frameCount;
	switch (pRes->m_type)
	{
	case 0:
		m_pathList.GetText(0, path);
		strcpy_s(pRes->m_path, CU_U2A(path.GetBuffer()).c_str());
		strcpy_s(pRes->m_wholePath, CU_U2A(m_wholePath.GetBuffer()).c_str());
		break;
	case 1:
		m_dir.GetWindowText(dir);
		m_frame.GetWindowText(frame);
		pRes->m_dir = _ttoi(dir);
		pRes->m_frame = _ttoi(frame);
		m_pathList.GetText(0, path);
		strcpy_s(pRes->m_path, CU_U2A(path.GetBuffer()).c_str());
		strcpy_s(pRes->m_wholePath, CU_U2A(m_wholePath.GetBuffer()).c_str());
		break;
	case 2:
		pRes->m_frameCount = m_pathList.GetCount();
		char c[10];
		_itoa_s(m_pRes->m_frameCount, c, 10);
		m_frameCount.SetWindowText(CU_A2U(c).c_str());
		for (int i = 0; i < pRes->m_frameCount; i++)
		{
			m_pathList.GetText(i, path);
			strcpy_s(pRes->m_mulPath[i], CU_U2A(path.GetBuffer()).c_str());
			m_wholePathList.GetText(i,pRes->m_wholePath1[i]);
		}
		break;
	}
	MessageBox(_T("Modification succeeded"), _T("Success"), 0);
	return;
}


void CXMLWriterDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	if (!m_pRes)
	{
		MessageBox(_T("You should select an item"), _T("Wrong"), 0);
		return;
	}

	CRes::GetInstance()->DeleteRes(m_pictureName);
	m_pictureTree.DeleteItem(m_currentItem);
}


void CXMLWriterDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CFileDialog fileDlg(FALSE, _T("*.xml"), NULL, OFN_READONLY, _T("*.xml|*.xml||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();                     //���浽XML�ļ�
		CRes::GetInstance()->SaveFile(filePath);
	}
}


void CXMLWriterDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	

}


void CXMLWriterDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CFileDialog fileDlg(TRUE, _T("*.xml"), NULL, OFN_READONLY, _T("*.xml|*.xml||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();                     //��ȡXML�ļ�
		CRes::GetInstance()->LoadFile(filePath);
	}
}


void CXMLWriterDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CString folderPath;
	m_folder.GetWindowText(folderPath);            //�޸�ҳ�����·��
	if (folderPath != _T(""))
		folderPath += _T("/");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY);
	if (fileDlg.DoModal() == IDOK)
	{
		CString picturePath = fileDlg.GetPathName();
		m_wholePath=picturePath;
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
		switch (m_pRes->m_type)
		{
		case 0:
		case 1:
			{
				m_pathList.ResetContent();
				m_pathList.AddString(_T("../bin/")+folderPath+picturePath);
			}
			break;
		case 2:
			if (m_pathList.GetCount() == 0)
				m_pathList.AddString(picturePath);
			else
			{
				m_pathList.InsertString(m_pathList.GetCurSel()+1,_T("../bin/")+folderPath+picturePath);
				m_wholePathList.InsertString(m_pathList.GetCurSel()+1,m_wholePath);
			}
			break;
		}
	}
}


void CXMLWriterDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_pathList.DeleteString(m_pathList.GetCurSel());
}


void CXMLWriterDlg::OnLbnSelchangeList1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CImage img, imDest;
	HRESULT ret;
	HBITMAP hbitmap;
	CDC *pDc;
	RECT rect;
	int pictureWidth;
	int tempWidth;
	int tempHeight;
	double ratio=1;
	ret = img.Load(m_pRes->m_wholePath1[m_pathList.GetCurSel()]);

	if(m_pRes->m_wholePath1[m_pathList.GetCurSel()]!="")
	{
		pictureWidth = img.GetWidth();
		tempWidth = pictureWidth;
		tempHeight = img.GetHeight();
		while (pictureWidth > 200 || tempHeight>400)
		{
			pictureWidth /= 2;
			tempHeight /= 2;
		}
		ratio = (double)pictureWidth / (double)tempWidth;
		imDest.Create(ratio*tempWidth, ratio*img.GetHeight(), 32);
		img.StretchBlt(imDest.GetDC(), 0, 0, ratio*tempWidth, ratio*img.GetHeight());
		imDest.ReleaseDC();

		hbitmap = (HBITMAP)imDest.Detach();
		m_showPicture.SetBitmap(hbitmap);    // ����ͼƬ�ؼ�λͼ
	}
	else
		m_showPicture.SetBitmap(NULL);
}
