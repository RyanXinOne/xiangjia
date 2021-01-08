
// xiangjiaDlg.cpp : implementation file
//

#include "framework.h"
#include "xiangjia.h"
#include "xiangjiaDlg.h"
#include "afxdialogex.h"
#include "CModeDlg.h"
#include "CEditorDlg.h"
#include "ai_engine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] = {
IDS_STATUSBAR1,
IDS_STATUSBAR2,
IDS_STATUSBAR3,
};

int isAllowRollback;
int lastBoard[9][10];
int aiLastLastBoard[9][10];
int aiLastBoard[9][10];
int isReverseDisplay = 0;
CPoint onRButtonPoint;

ULONGLONG t1 = 0, t2 = 0;  //���ڼ�ʱ
int count = 0;  //���ڼ���

struct {
	int chess;
	int x;
	int y;
}activated_chess, last_move, last_move_from;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CxiangjiaDlg dialog

CxiangjiaDlg::CxiangjiaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XIANGJIA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CxiangjiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CxiangjiaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_RMENU_ROLLBACK, &CxiangjiaDlg::OnRmenuRollback)
	ON_COMMAND(ID_RMENU_NEW, &CxiangjiaDlg::OnRmenuNew)
	ON_COMMAND(ID_RMENU_32778, &CxiangjiaDlg::OnRmenuReverseBoard)
	ON_COMMAND(ID_RMENU_32779, &CxiangjiaDlg::OnRmenuSwitchMode)
	ON_COMMAND(ID_RMENU_32780, &CxiangjiaDlg::OnRmenuBoardEditor)
END_MESSAGE_MAP()

// CxiangjiaDlg message handlers

void CxiangjiaDlg::gameDlgIni()
{
	initialize();
	activated_chess.chess = none;
	last_move.chess = none;
	last_move_from.chess = none;
	isAllowRollback = 0;
	copyBoard(checkerboard, lastBoard);
	copyBoard(checkerboard, aiLastBoard);
	copyBoard(checkerboard, aiLastLastBoard);
}

BOOL CxiangjiaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//���ô��ڴ�С
	CRect clientrect;
	GetClientRect(&clientrect);
	CRect windowrect;
	GetWindowRect(&windowrect);
	int width = 750 + windowrect.Width() - clientrect.Width();
	int height = 854 + windowrect.Height() - clientrect.Height();
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);

	mstatusBar.Create(this);
	mstatusBar.SetIndicators(indicators, 3);
	mstatusBar.SetPaneInfo(0, IDS_STATUSBAR1, SBPS_NORMAL, 100);
	mstatusBar.SetPaneInfo(1, IDS_STATUSBAR2, SBPS_NORMAL, 200);
	mstatusBar.SetPaneInfo(2, IDS_STATUSBAR2, SBPS_NORMAL, 200);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	//����ģʽѡ��
	INT_PTR nRes;
	CModeDlg modeDlg;
	nRes = modeDlg.DoModal();
	if (nRes == IDOK)
	{
		gameDlgIni();
	}
	else
	{
		exit(0);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CxiangjiaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CxiangjiaDlg::OnPaint()
{
	int i, j;
	CPaintDC dc(this);
	CDC MemDC;
	CBitmap* pOldBmp;
	POINT pt;

	CBitmap bgBmp;
	bgBmp.LoadBitmapW(IDB_BG);

	CImageList chessmen_bmp;
	chessmen_bmp.Create(IDB_CHESSMEN, 72, 14, RGB(0, 255, 0));

	CBitmap tarBmp;
	tarBmp.LoadBitmapW(IDB_TARGET);

	CBitmap lastBmp;
	lastBmp.LoadBitmapW(IDB_LAST);

	CBitmap lastfromBmp;
	lastfromBmp.LoadBitmapW(IDB_LASTFROM);

	MemDC.CreateCompatibleDC(&dc);
	pOldBmp = MemDC.SelectObject(&bgBmp);

	//�������̻�������
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!checkerboard[i][j])
			{
				continue;
			}
			if (!isReverseDisplay)
			{
				pt.x = 19 + (8 - i) * 80;
				pt.y = 19 + (9 - j) * 80;
			}
			else
			{
				pt.x = 19 + i * 80;
				pt.y = 19 + j * 80;
			}
			chessmen_bmp.Draw(&MemDC, checkerboard[i][j] - 1, pt, ILD_TRANSPARENT);
		}
	}

	CRect rect;
	GetClientRect(&rect);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	
	if (last_move.chess != none)
	{
		//����ϴ��ƶ�������
		MemDC.SelectObject(&lastBmp);
		if (!isReverseDisplay)
			dc.TransparentBlt(14 + (8 - last_move.x) * 80, 14 + (9 - last_move.y) * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
		else
			dc.TransparentBlt(14 + last_move.x * 80, 14 + last_move.y * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
	}
	if (last_move_from.chess != none)
	{
		//����ϴ��ƶ������ӵ����
		MemDC.SelectObject(&lastfromBmp);
		if (!isReverseDisplay)
			dc.TransparentBlt(14 + (8 - last_move_from.x) * 80, 14 + (9 - last_move_from.y) * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
		else
			dc.TransparentBlt(14 + last_move_from.x * 80, 14 + last_move_from.y * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
	}
	if (activated_chess.chess != none)
	{
		//ѡ������
		MemDC.SelectObject(&tarBmp);
		if (!isReverseDisplay)
			dc.TransparentBlt(14 + (8 - activated_chess.x) * 80, 14 + (9 - activated_chess.y) * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255,0,0));
		else
			dc.TransparentBlt(14 + activated_chess.x * 80, 14 + activated_chess.y * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
	}
	
	MemDC.SelectObject(&pOldBmp);
	MemDC.DeleteDC();
	bgBmp.DeleteObject();
	tarBmp.DeleteObject();

	//����״̬��
	CString str;
	str.Format(_T("depth: %d"), depth);
	mstatusBar.SetPaneText(0, str);
	str.Format(_T("evaluated: %d nodes"), count);
	mstatusBar.SetPaneText(1, str);
	str.Format(_T("time: %lld ms"), t2 - t1);
	mstatusBar.SetPaneText(2, str);
}

void CxiangjiaDlg::refreshWindow()
{
	//ˢ�´���
	InvalidateRect(NULL, FALSE);
	UpdateWindow();
}

HCURSOR CxiangjiaDlg::OnQueryDragIcon()
{
	// The system calls this function to obtain the cursor to display while the user drags
	//  the minimized window.
	return static_cast<HCURSOR>(m_hIcon);
}

void CxiangjiaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//����ѡ������
	if ((point.x - 19) % 80 >= 0 && (point.x - 19) % 80 <= 72 && (point.y - 19) % 80 >= 0 && (point.y - 19) % 80 <= 72)
	{
		int px, py;
		if (!isReverseDisplay)
		{
			px = 8 - (point.x - 19) / 80;
			py = 9 - (point.y - 19) / 80;
		}
		else
		{
			px = (point.x - 19) / 80;
			py = (point.y - 19) / 80;
		}
		if (px >= 0 && px <= 8 && py >= 0 && py <= 9)
		{
			if (player && isSameColor(player, checkerboard[px][py]))
			{
				activated_chess.chess = checkerboard[px][py];
				activated_chess.x = px;
				activated_chess.y = py;
				refreshWindow();
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CxiangjiaDlg::freeMode(CPoint point)
{
	int tx, ty;
	int isMoveSuccessfully;
	int isEnd;
	int tmpBoard[9][10];
	if (activated_chess.chess != none)
	{
		if ((point.x - 19) % 80 >= 0 && (point.x - 19) % 80 <= 72 && (point.y - 19) % 80 >= 0 && (point.y - 19) % 80 <= 72)
		{
			if (!isReverseDisplay)
			{
				tx = 8 - (point.x - 19) / 80;
				ty = 9 - (point.y - 19) / 80;
			}
			else
			{
				tx = (point.x - 19) / 80;
				ty = (point.y - 19) / 80;
			}
			if (tx >= 0 && tx <= 8 && ty >= 0 && ty <= 9)
			{
				copyBoard(lastBoard, tmpBoard);
				copyBoard(checkerboard, lastBoard);
				isMoveSuccessfully = move(activated_chess.chess, activated_chess.x, activated_chess.y, tx, ty, checkerboard, 1);
				if (isMoveSuccessfully)
				{
					t1 = 0;
					t2 = 0;
					count = 0;
					depth = 0;
					player = (player == red) ? black : red;
					last_move_from = activated_chess;
					last_move = activated_chess;
					last_move.x = tx;
					last_move.y = ty;
					activated_chess.chess = none;
					refreshWindow();
					isAllowRollback = 1;
					isEnd = isGameOver(checkerboard);
					if (isEnd)
					{
						if (isEnd == red)
						{
							MessageBox(_T("�췽ʤ!"), _T("���"));
						}
						else
						{
							MessageBox(_T("�ڷ�ʤ!"), _T("���"));
						}
						INT_PTR nRes;
						nRes = MessageBox(_T("Ҫ��ʼ����Ϸ��?"), _T("����Ϸ"), MB_YESNOCANCEL);
						if (nRes == IDYES)
						{
							INT_PTR nRes;
							CModeDlg modeDlg;
							nRes = modeDlg.DoModal();
							if (nRes == IDOK)
							{
								gameDlgIni();
							}
							refreshWindow();
						}
					}
				}
				else
				{
					copyBoard(tmpBoard, lastBoard);
				}
			}
		}
	}
}

void CxiangjiaDlg::aiLoop()
{
	mark aiM;
	int chessNumber;

	depth = level;
	chessNumber = getChessNumber(checkerboard);
	if (chessNumber < 20)  //������ʱ�Զ������������
		depth++;
	if (chessNumber < 10)
		depth++;
	mark alpha;
	alpha.score = INT_MIN;
	mark beta;
	beta.score = INT_MAX;
	count = 0;
	t1 = GetTickCount64();
	aiM = AlphaBeta(ai, checkerboard, depth, 1, alpha, beta, &count);
	move(checkerboard[aiM.cx][aiM.cy], aiM.cx, aiM.cy, aiM.tx, aiM.ty, checkerboard);
	if (isSameBoard(checkerboard, aiLastLastBoard))  //������ѭ����
	{
		move(checkerboard[aiM.tx][aiM.ty], aiM.tx, aiM.ty, aiM.cx, aiM.cy, checkerboard);
		alpha.score = INT_MIN;
		beta.score = INT_MAX;
		aiM = ShieldAlphaBeta(ai, checkerboard, depth, 1, alpha, beta, &count, aiM);
		move(checkerboard[aiM.cx][aiM.cy], aiM.cx, aiM.cy, aiM.tx, aiM.ty, checkerboard);
	}
	t2 = GetTickCount64();
	copyBoard(aiLastBoard, aiLastLastBoard);
	copyBoard(checkerboard, aiLastBoard);
	last_move_from.chess = checkerboard[aiM.tx][aiM.ty];
	last_move_from.x = aiM.cx;
	last_move_from.y = aiM.cy;
	last_move.chess = checkerboard[aiM.tx][aiM.ty];
	last_move.x = aiM.tx;
	last_move.y = aiM.ty;
	refreshWindow();
}

void CxiangjiaDlg::aiMode(CPoint point)
{
	int tx, ty;
	int isMoveSuccessfully;
	int isEnd = 0;
	int tmpBoard[9][10];
	if (ai_first)
	{
		isEnd = isGameOver(checkerboard);
		if (!isEnd)
		{
			aiLoop();
		}
		player = black;
		ai_first = 0;
	}

	if (activated_chess.chess != none)
	{
		if ((point.x - 19) % 80 >= 0 && (point.x - 19) % 80 <= 72 && (point.y - 19) % 80 >= 0 && (point.y - 19) % 80 <= 72)
		{
			if (!isReverseDisplay)
			{
				tx = 8 - (point.x - 19) / 80;
				ty = 9 - (point.y - 19) / 80;
			}
			else
			{
				tx = (point.x - 19) / 80;
				ty = (point.y - 19) / 80;
			}
			if (tx >= 0 && tx <= 8 && ty >= 0 && ty <= 9)
			{
				copyBoard(lastBoard, tmpBoard);
				copyBoard(checkerboard, lastBoard);
				isMoveSuccessfully = move(activated_chess.chess, activated_chess.x, activated_chess.y, tx, ty, checkerboard, 1);
				if (isMoveSuccessfully)
				{
					t1 = 0;
					t2 = 0;
					count = 0;
					depth = 0;
					last_move_from = activated_chess;
					last_move = activated_chess;
					last_move.x = tx;
					last_move.y = ty;
					activated_chess.chess = none;
					refreshWindow();
					isEnd = isGameOver(checkerboard);
					if (!isEnd)
					{
						aiLoop();
						isAllowRollback = 1;
						isEnd = isGameOver(checkerboard);
					}
				}
				else
				{
					copyBoard(tmpBoard, lastBoard);
				}
			}
		}
	}
	if (isEnd)
	{
		if (isEnd == red)
		{
			MessageBox(_T("�췽ʤ!"), _T("���"));
		}
		else
		{
			MessageBox(_T("�ڷ�ʤ!"), _T("���"));
		}
		INT_PTR nRes;
		nRes = MessageBox(_T("Ҫ��ʼ����Ϸ��?"), _T("����Ϸ"), MB_YESNOCANCEL);
		if (nRes == IDYES)
		{
			INT_PTR nRes;
			CModeDlg modeDlg;
			nRes = modeDlg.DoModal();
			if (nRes == IDOK)
			{
				gameDlgIni();
			}
			refreshWindow();
		}
	}
}

void CxiangjiaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//̧��ȷ���ƶ�
	if (ai)
		aiMode(point);
	else
		freeMode(point);

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CxiangjiaDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default 
	CMenu menu;       // �˵����������˵������Ӳ˵���   
	CMenu* pSubMenu;  // �Ҽ��˵�   

	onRButtonPoint = point;  //��������Ҽ�����ʱ������

	// ���ز˵���Դ��menu����   
	menu.LoadMenu(IDR_RMENU);
	// ��Ϊ�Ҽ��˵��ǵ���ʽ�˵������������˵���������ȡ�Ӳ˵�   
	pSubMenu = menu.GetSubMenu(0);
	// ������ֵ�ɿͻ�����ת��Ϊ��Ļ����   
	ClientToScreen(&point);
	// �����Ҽ��˵����˵������point.x����ֵ����   
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CDialogEx::OnRButtonDown(nFlags, point);
}

void CxiangjiaDlg::OnRmenuRollback()
{
	// TODO: Add your command handler code here
	//�������ָ̻�
	if (isAllowRollback)
	{
		int i, j;
		for (i = 0; i <= 8; i++)
		{
			for (j = 0; j <= 9; j++)
			{
				copyBoard(lastBoard, checkerboard);
				activated_chess.chess = none;
				last_move_from.chess = none;
				last_move.chess = none;
				copyBoard(checkerboard, aiLastBoard);
				copyBoard(checkerboard, aiLastLastBoard);
			}
		}
		refreshWindow();
		if (!ai)
		{
			player = (player == red) ? black : red;
		}
		isAllowRollback = 0;
	}
}

void CxiangjiaDlg::OnRmenuNew()
{
	// TODO: Add your command handler code here
	INT_PTR nRes;
	nRes = MessageBox(_T("ȷ��Ҫ��ʼ����Ϸ��?"), _T("����Ϸ"), MB_YESNOCANCEL);
	if (nRes == IDYES)
	{
		INT_PTR nRes;
		CModeDlg modeDlg;
		nRes = modeDlg.DoModal();
		if (nRes == IDOK)
		{
			gameDlgIni();
		}
		refreshWindow();
	}
}

void CxiangjiaDlg::OnRmenuReverseBoard()
{
	// TODO: Add your command handler code here
	//��ת������ʾ
	isReverseDisplay = !isReverseDisplay;
	refreshWindow();
}

void CxiangjiaDlg::OnRmenuSwitchMode()
{
	// TODO: Add your command handler code here
	//ģʽ�л�

	INT_PTR nRes;
	CModeDlg modeDlg;
	nRes = modeDlg.DoModal();
	if (nRes == IDOK)
	{
		activated_chess.chess = none;
		isAllowRollback = 0;
		copyBoard(checkerboard, aiLastBoard);
		copyBoard(checkerboard, aiLastLastBoard);
		refreshWindow();
	}
}

void CxiangjiaDlg::OnRmenuBoardEditor()
{
	// TODO: Add your command handler code here
	//���̱༭��

	INT_PTR nRes;
	CEditorDlg editorDlg;
	if ((onRButtonPoint.x - 19) % 80 >= 0 && (onRButtonPoint.x - 19) % 80 <= 72 && (onRButtonPoint.y - 19) % 80 >= 0 && (onRButtonPoint.y - 19) % 80 <= 72)
	{
		if (!isReverseDisplay)
		{
			RX = 8 - (onRButtonPoint.x - 19) / 80;
			RY = 9 - (onRButtonPoint.y - 19) / 80;
		}
		else
		{
			RX = (onRButtonPoint.x - 19) / 80;
			RY = (onRButtonPoint.y - 19) / 80;
		}
	}
	else
	{
		RX = -1;
		RY = -1;
	}

	nRes = editorDlg.DoModal();
	if (nRes == IDOK)
	{
		activated_chess.chess = none;
		last_move.chess = none;
		last_move_from.chess = none;
		isAllowRollback = 0;
		copyBoard(checkerboard, aiLastBoard);
		copyBoard(checkerboard, aiLastLastBoard);
		refreshWindow();
	}
}
