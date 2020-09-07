#pragma once
#include "afxwin.h"
#include "Res.h"
#include "Platform.h"

// CNewPictureMul 对话框

class CNewPictureMul : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPictureMul)

public:
	CNewPictureMul(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewPictureMul();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_pictureName;              //图片名称编辑框
	CListBox m_pathList;             //图片路径列表
	afx_msg void OnBnClickedButton1();   //添加图片路径按钮事件响应
	afx_msg void OnBnClickedButton2();      //删除图片路径按钮事件响应
	afx_msg void OnBnClickedOk();         //确定按钮事件响应
	CEdit m_folder;                    //文件夹名称编辑框
	CString m_wholePath[100];       //绝对路径
};
