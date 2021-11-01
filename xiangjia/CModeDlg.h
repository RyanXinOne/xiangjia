#pragma once
extern int player;
extern int ai;
extern int level;
extern int depth;
extern int ai_first;
// CModeDlg dialog

class CModeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModeDlg)

public:
	CModeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CModeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XIANGJIA_MODE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
};
