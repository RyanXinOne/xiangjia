
// xiangjiaDlg.h : header file
//

#pragma once


// CxiangjiaDlg dialog
class CxiangjiaDlg : public CDialogEx
{
// Construction
public:
	CxiangjiaDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XIANGJIA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	void newGame();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRmenuRollback();
	afx_msg void OnRmenuNew();
};
