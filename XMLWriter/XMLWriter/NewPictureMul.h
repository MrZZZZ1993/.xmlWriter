#pragma once
#include "afxwin.h"
#include "Res.h"
#include "Platform.h"

// CNewPictureMul �Ի���

class CNewPictureMul : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPictureMul)

public:
	CNewPictureMul(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewPictureMul();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_pictureName;              //ͼƬ���Ʊ༭��
	CListBox m_pathList;             //ͼƬ·���б�
	afx_msg void OnBnClickedButton1();   //���ͼƬ·����ť�¼���Ӧ
	afx_msg void OnBnClickedButton2();      //ɾ��ͼƬ·����ť�¼���Ӧ
	afx_msg void OnBnClickedOk();         //ȷ����ť�¼���Ӧ
	CEdit m_folder;                    //�ļ������Ʊ༭��
	CString m_wholePath[100];       //����·��
};
