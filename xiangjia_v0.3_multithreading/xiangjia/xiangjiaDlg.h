
// xiangjiaDlg.h : header file
//

#pragma once

#include "aiEngine.h"

//AlphaBeta节点任务函数所需参数
struct taskFuncPara {
	int ctrl_col;
	int board[9][10];
	int searchDepth;
	int currentDepth;
	int i;
	int j;
	int n0;
	int n1;
};

//线程函数所需参数
struct threadFuncPara {
	int* leftTaskNum;  //剩余任务数量
	taskFuncPara** taskList;
	CCriticalSection* ccs1;
	CCriticalSection* ccs2;
};

// CxiangjiaDlg dialog
class CxiangjiaDlg : public CDialogEx
{
// Construction
public:
	CxiangjiaDlg(CWnd* pParent = nullptr);	// standard constructor
	CStatusBar mstatusBar;

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
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()



public:
	void gameDlgIni();
	void refreshWindow();
	void freeMode(CPoint point);
	void aiLoop();
	void aiMode(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRmenuRollback();
	afx_msg void OnRmenuNew();
	afx_msg void OnRmenuReverseBoard();
	afx_msg void OnRmenuSwitchMode();
	afx_msg void OnRmenuBoardEditor();

	mark threadShieldAlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, mark shield);

};

void updateAlphaList(mark result);
void taskFunc(LPVOID lpParam, CCriticalSection* ccs);
UINT ThreadFunc(LPVOID lpParam);
