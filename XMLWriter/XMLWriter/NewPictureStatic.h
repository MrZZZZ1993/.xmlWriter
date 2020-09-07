#pragma once
#include "afxwin.h"
#include "Platform.h"
#include "Res.h"

// CNewPictureStatic �Ի���

class CNewPictureStatic : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPictureStatic)

public:
	CNewPictureStatic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewPictureStatic();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_radioSin;     //��ѡ��
	afx_msg void OnBnClickedRadio2();     //������ӵ�ѡ�¼���Ӧ
	afx_msg void OnBnClickedRadio3();    //������ӵ�ѡ�¼���Ӧ
	int m_radio;      //��ѡ���±�
	CEdit m_pictureName; //ͼƬ���Ʊ༭��
	CEdit m_picturePath;  //ͼƬ·���༭��
	CButton m_addPictureSin;  //������Ӱ�ť
	CButton m_addPicture;     //������Ӱ�ť
	CButton m_deletePicture;  //ɾ����ť
	CListBox m_pathList;    //�������ͼƬ·���б�
	afx_msg void OnBnClickedOk();   //ȷ����ť�¼���Ӧ
	afx_msg void OnBnClickedButton4();   //������Ӱ�ť�¼���Ӧ
	afx_msg void OnBnClickedButton2();   //������Ӱ�ť�¼���Ӧ
	afx_msg void OnBnClickedButton3();   //ɾ����ť�¼���Ӧ
	CEdit m_folder;                  //�ļ��б༭��
	CString m_wholePath;              //����·��
	CString m_wholePath1[100];            //����·������
};
