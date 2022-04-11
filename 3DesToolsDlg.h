// 3DesToolsDlg.h : header file
//

#if !defined(AFX_3DESTOOLSDLG_H__DA6429F6_ACFC_4B46_8278_4794F882FF9E__INCLUDED_)
#define AFX_3DESTOOLSDLG_H__DA6429F6_ACFC_4B46_8278_4794F882FF9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy3DesToolsDlg dialog

class CMy3DesToolsDlg : public CDialog
{
// Construction
public:
	CMy3DesToolsDlg(CWnd* pParent = NULL);	// standard constructor
	void ShowInput();
	void EncDecFun(int mode); // 0 ENC   1- ENC
// Dialog Data
	//{{AFX_DATA(CMy3DesToolsDlg)
	enum { IDD = IDD_MY3DESTOOLS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DesToolsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy3DesToolsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCancel2();
	afx_msg void OnOk2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DESTOOLSDLG_H__DA6429F6_ACFC_4B46_8278_4794F882FF9E__INCLUDED_)
