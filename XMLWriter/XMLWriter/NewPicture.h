#pragma once
#include "afxcmn.h"
#include "NewPicture.h"
#include "afxwin.h"
#include "Singleton.h"
#include "Platform.h"


// CNewPicture �Ի���

class CNewPicture : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPicture)

public:
	CNewPicture(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewPicture();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();   //ȷ����ť�¼���Ӧ
	CEdit m_name;                    //ͼƬ���Ʊ༭��
	CTreeCtrl pictureTree;             //ͼƬ�����б�
	CEdit m_dir;                      //�������༭��
	CEdit m_frame;                     //ÿ��֡���༭��
	//afx_msg void OnBnClickedButton4();        //
	//afx_msg void OnBnClickedButton3();
	CEdit m_picturePath;                      //ͼƬ·���༭��
	afx_msg void OnBnClickedButton1();        //���ͼƬ��ť�¼���Ӧ
	CEdit m_folder;                          //�ļ������Ʊ༭��
	CString m_wholePath;                         //����·��
};
