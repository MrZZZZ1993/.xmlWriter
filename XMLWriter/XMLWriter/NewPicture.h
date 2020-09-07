#pragma once
#include "afxcmn.h"
#include "NewPicture.h"
#include "afxwin.h"
#include "Singleton.h"
#include "Platform.h"


// CNewPicture 对话框

class CNewPicture : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPicture)

public:
	CNewPicture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewPicture();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();   //确定按钮事件响应
	CEdit m_name;                    //图片名称编辑框
	CTreeCtrl pictureTree;             //图片树形列表
	CEdit m_dir;                      //总行数编辑框
	CEdit m_frame;                     //每行帧数编辑框
	//afx_msg void OnBnClickedButton4();        //
	//afx_msg void OnBnClickedButton3();
	CEdit m_picturePath;                      //图片路径编辑框
	afx_msg void OnBnClickedButton1();        //添加图片按钮事件相应
	CEdit m_folder;                          //文件夹名称编辑框
	CString m_wholePath;                         //绝对路径
};
