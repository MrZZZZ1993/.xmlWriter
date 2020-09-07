
// XMLWriterDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "NewPicture.h"
#include "afxwin.h"
#include "Singleton.h"
#include "Platform.h"
#include "Res.h"
#include "NewPictureStatic.h"
#include "NewPictureMul.h"

// CXMLWriterDlg �Ի���
class CXMLWriterDlg : public CDialogEx
{
// ����
public:
	CXMLWriterDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XMLWRITER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_pictureTree;    //ͼƬ���νṹ
	afx_msg void OnBnClickedOk();
	CNewPicture m_newPicture;
	CNewPictureStatic m_newPictureStatic;
	CNewPictureMul m_newPictureMul;
	CEdit m_name;
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_dir;
	CEdit m_frame;
	CEdit m_frameCount;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_pictureName;
	HTREEITEM m_currentItem;
	RES*m_pRes;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton4();
	int m_curSel;
	CListBox m_pathList;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CButton m_addPath;
	CButton m_deletePath;
	CEdit m_folder;
	CStatic m_showPicture;
	afx_msg void OnLbnSelchangeList1();
	CString m_wholePath;
	CListBox m_wholePathList;
};
