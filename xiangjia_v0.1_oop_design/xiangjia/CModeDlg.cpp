// CModeDlg.cpp : implementation file
//

#include <afxcontrolbars.h>
#include "xiangjia.h"
#include "CModeDlg.h"
#include "afxdialogex.h"

int gameMode;
int level;
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


void CModeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO1), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮1
	{
		if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO3), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮1
		{
			//ai，我方执红
			gameMode = 1;
		}
		else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO4), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮2
		{
			//ai，我方执黑
			gameMode = 2;
		}
	}
	else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_RADIO2), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了单选按钮2
	{
		//自由模式
		gameMode = 0;
	}

	level = ((CComboBox*)GetDlgItem(IDC_LEVEL))->GetCurSel() + 1;

	CDialogEx::OnOK();
}
