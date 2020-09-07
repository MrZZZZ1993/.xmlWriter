#pragma once
#include "afxwin.h"
#include "Platform.h"
#include "Res.h"

// CNewPictureStatic 对话框

class CNewPictureStatic : public CDialogEx
{
	DECLARE_DYNAMIC(CNewPictureStatic)

public:
	CNewPictureStatic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewPictureStatic();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_radioSin;     //单选框
	afx_msg void OnBnClickedRadio2();     //单张添加单选事件响应
	afx_msg void OnBnClickedRadio3();    //批量添加单选事件响应
	int m_radio;      //单选框下标
	CEdit m_pictureName; //图片名称编辑框
	CEdit m_picturePath;  //图片路径编辑框
	CButton m_addPictureSin;  //单张添加按钮
	CButton m_addPicture;     //批量添加按钮
	CButton m_deletePicture;  //删除按钮
	CListBox m_pathList;    //批量添加图片路径列表
	afx_msg void OnBnClickedOk();   //确定按钮事件响应
	afx_msg void OnBnClickedButton4();   //单张添加按钮事件响应
	afx_msg void OnBnClickedButton2();   //多张添加按钮事件响应
	afx_msg void OnBnClickedButton3();   //删除按钮事件响应
	CEdit m_folder;                  //文件夹编辑框
	CString m_wholePath;              //绝对路径
	CString m_wholePath1[100];            //绝对路径集合
};
