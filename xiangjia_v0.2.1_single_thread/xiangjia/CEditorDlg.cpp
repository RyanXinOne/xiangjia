// CEditorDlg.cpp : implementation file
//

#include <afxcontrolbars.h>
#include "xiangjia.h"
#include "CEditorDlg.h"
#include "afxdialogex.h"
#include "chess_engine.h"

int RX;
int RY;

// CEditorDlg dialog

IMPLEMENT_DYNAMIC(CEditorDlg, CDialogEx)

CEditorDlg::CEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XIANGJIA_EDITOR, pParent)
{

}

CEditorDlg::~CEditorDlg()
{
}

void CEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TYPE, mTypeBox);
	DDX_Control(pDX, IDC_COLOR, mColorBox);
}


BEGIN_MESSAGE_MAP(CEditorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &CEditorDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELETE, &CEditorDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDOK, &CEditorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditorDlg message handlers


BOOL CEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	mTypeBox.InsertString(0, _T("车"));
	mTypeBox.InsertString(1, _T("马"));
	mTypeBox.InsertString(2, _T("炮"));
	mTypeBox.InsertString(3, _T("兵"));
	mTypeBox.InsertString(4, _T("象"));
	mTypeBox.InsertString(5, _T("士"));
	mTypeBox.InsertString(6, _T("将"));

	mColorBox.InsertString(0, _T("红"));
	mColorBox.InsertString(1, _T("黑"));

	((CButton*)GetDlgItem(IDC_ADD))->SetCheck(TRUE);

	if (RX >= 0 && RX <= 8 && RY >= 0 && RY <= 9)
	{
		((CComboBox*)GetDlgItem(IDC_XPOS))->SetCurSel(RX);
		((CComboBox*)GetDlgItem(IDC_YPOS))->SetCurSel(RY);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}



void CEditorDlg::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TYPE)->EnableWindow(true);
	GetDlgItem(IDC_COLOR)->EnableWindow(true);
}


void CEditorDlg::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TYPE)->EnableWindow(false);
	GetDlgItem(IDC_COLOR)->EnableWindow(false);
}


void CEditorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int chess;
	int type, color;

	RX = ((CComboBox*)GetDlgItem(IDC_XPOS))->GetCurSel();
	RY = ((CComboBox*)GetDlgItem(IDC_YPOS))->GetCurSel();

	if (::SendMessage(::GetDlgItem(m_hWnd, IDC_ADD), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了增添棋子
	{
		type = mTypeBox.GetCurSel();
		color = mColorBox.GetCurSel();

		if (color)
		{
			switch (type)
			{
			case 0:
				chess = bche;
				break;
			case 1:
				chess = bma;
				break;
			case 2:
				chess = bpao;
				break;
			case 3:
				chess = bbing;
				break;
			case 4:
				chess = bxiang;
				break;
			case 5:
				chess = bshi;
				break;
			case 6:
				chess = bjiang;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (type)
			{
			case 0:
				chess = rche;
				break;
			case 1:
				chess = rma;
				break;
			case 2:
				chess = rpao;
				break;
			case 3:
				chess = rbing;
				break;
			case 4:
				chess = rxiang;
				break;
			case 5:
				chess = rshi;
				break;
			case 6:
				chess = rjiang;
				break;
			default:
				break;
			}
		}

		checkerboard[RX][RY] = chess;
	}
	else if (::SendMessage(::GetDlgItem(m_hWnd, IDC_DELETE), BM_GETCHECK, NULL, NULL) == BST_CHECKED)//如果选择了删除棋子
	{
		checkerboard[RX][RY] = none;
	}

	CDialogEx::OnOK();
}
