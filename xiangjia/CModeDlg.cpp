// CModeDlg.cpp : implementation file
//

#include <afxcontrolbars.h>
#include "xiangjia.h"
#include "CModeDlg.h"
#include "afxdialogex.h"
#include "chess_engine.h"

int player;
int ai;
int ai_first;
int level;
int depth;
// CModeDlg dialog

IMPLEMENT_DYNAMIC(CModeDlg, CDialogEx)

CModeDlg::CModeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XIANGJIA_MODE, pParent)
{

}

CModeDlg::~CModeDlg()
{
}

void CModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO2, &CModeDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CModeDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CModeDlg message handlers


BOOL CModeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	//设置初始选中值
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(TRUE);
	((CComboBox*)GetDlgItem(IDC_LEVEL))->SetCurSel(3);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CModeDlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	//选择自由模式时禁用其他选项
	GetDlgItem(IDC_RADIO3)->SetWindowText(_T("红先"));
	GetDlgItem(IDC_RADIO4)->SetWindowText(_T("黑先"));
	GetDlgItem(IDC_LEVEL)->EnableWindow(false);
}


void CModeDlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_RADIO3)->SetWindowText(_T("执红"));
	GetDlgItem(IDC_RADIO4)->SetWindowText(_T("执黑"));
	GetDlgItem(IDC_LEVEL)->EnableWindow(true);
}

void CModeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO1), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮1
	{
		if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO3), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮3
		{
			//ai，我方执红
			player = red;
			ai = black;
			ai_first = 0;
		}
		else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO4), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮4
		{
			//ai，我方执黑
			player = none;
			ai = red;
			ai_first = 1;
		}
	}
	else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO2), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮2
	{
		if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO3), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮3
		{
			//自由，红先走
			player = red;
			ai = none;
			ai_first = 0;
		}
		else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO4), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮4
		{
			//自由，黑先走
			player = black;
			ai = none;
			ai_first = 0;
		}
	}

	level = ((CComboBox*)GetDlgItem(IDC_LEVEL))->GetCurSel() + 2;
	depth = 0;

	CDialogEx::OnOK();
}
