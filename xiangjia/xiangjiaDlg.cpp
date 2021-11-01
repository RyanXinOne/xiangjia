
// xiangjiaDlg.cpp : implementation file
//

#include "framework.h"
#include "xiangjia.h"
#include "xiangjiaDlg.h"
#include "afxdialogex.h"
#include "CModeDlg.h"
#include "ai_engine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


chessman* activated_chess;
chessman* last_move;
chessman* last_board[9][10];
chessman medium_board[9][10];
chessman medium_board2[9][10];
chessman medium_board3[9][10];
colors player;
colors ai;
int ai_first_move;
bool allowRollback;

void CxiangjiaDlg::newGame()
{
	initialize();
	activated_chess = &reset;
	last_move = &reset;

	INT_PTR nRes;
	CModeDlg modeDlg;
	nRes = modeDlg.DoModal();
	if (nRes == IDOK)
	{
		if (gameMode == 0)
		{
			player = colors::red;
			ai = colors::none;
		}
		else if (gameMode == 1)
		{
			player = colors::red;
			ai = colors::black;
		}
		else
		{
			player = colors::none;
			ai = colors::red;
			ai_first_move = 1;
		}
		allowRollback = false;
		copyBoard(checkerboard, last_board, medium_board);  //lastBoard初始化
	}
	else
	{
		exit(0);
	}
}


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
END_MESSAGE_MAP()

// CxiangjiaDlg message handlers

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
	newGame();

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

	MemDC.CreateCompatibleDC(&dc);
	pOldBmp = MemDC.SelectObject(&bgBmp);

	//按照棋盘绘制棋子
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (checkerboard[i][j]->species == types::none)
			{
				continue;
			}
			pt.x = 19 + (8 - i) * 80;
			pt.y = 19 + (9 - j) * 80;
			chessmen_bmp.Draw(&MemDC, checkerboard[i][j]->imageNo, pt, ILD_TRANSPARENT);
		}
	}

	CRect rect;
	GetClientRect(&rect);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	if (activated_chess->species != types::none)
	{
		//选中棋子
		MemDC.SelectObject(&tarBmp);
		dc.TransparentBlt(14 + (8 - activated_chess->pos.x) * 80, 14 + (9 - activated_chess->pos.y) * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255,0,0));
	}

	if (last_move->species != types::none)
	{
		//标记上次移动的棋子
		MemDC.SelectObject(&lastBmp);
		dc.TransparentBlt(14 + (8 - last_move->pos.x) * 80, 14 + (9 - last_move->pos.y) * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
	}

	MemDC.SelectObject(&pOldBmp);
	MemDC.DeleteDC();
	bgBmp.DeleteObject();
	tarBmp.DeleteObject();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CxiangjiaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CxiangjiaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//按下选择棋子
	if ((point.x - 19) % 80 >= 0 && (point.x - 19) % 80 <= 72 && (point.y - 19) % 80 >= 0 && (point.y - 19) % 80 <= 72)
	{
		int px, py;
		px = 8 - (point.x - 19) / 80;
		py = 9 - (point.y - 19) / 80;
		if (px >= 0 && px <= 8 && py >= 0 && py <= 9)
		{
			if (checkerboard[px][py]->colour == player)
			{
				activated_chess = checkerboard[px][py];
				InvalidateRect(NULL, FALSE);
				UpdateWindow();
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);

}


void CxiangjiaDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//抬起确认移动
	position dest;
	int isMoveSuccessfully;
	colors isEnd;
	mark aiM;
	chessman* tmp_board[9][10];
	if (ai_first_move)  //ai先走时行棋
	{
		aiM = search(ai, checkerboard, level);
		dest.x = aiM.move_to.x;
		dest.y = aiM.move_to.y;
		checkerboard[aiM.chess_pos.x][aiM.chess_pos.y]->move(dest, checkerboard);
		last_move = checkerboard[dest.x][dest.y];
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
		player = colors::black;
		ai_first_move = 0;
	}
	if (activated_chess->species != types::none)
	{
		if ((point.x - 19) % 80 >= 0 && (point.x - 19) % 80 <= 72 && (point.y - 19) % 80 >= 0 && (point.y - 19) % 80 <= 72)
		{
			dest.x = 8 - (point.x - 19) / 80;
			dest.y = 9 - (point.y - 19) / 80;
			if (dest.x >= 0 && dest.x <= 8 && dest.y >= 0 && dest.y <= 9)
			{
				copyBoard(last_board, tmp_board, medium_board2);  //移动失败时备份
				copyBoard(checkerboard, last_board, medium_board);  //保存移动前棋盘用于悔棋
				isMoveSuccessfully = activated_chess->move(dest, checkerboard);
				if (isMoveSuccessfully)
				{
					//自由模式玩家切换
					if (ai == colors::none)
					{
						if (player == colors::red)
						{
							player = colors::black;
						}
						else
						{
							player = colors::red;
						}
					}
					allowRollback = true;
					last_move = activated_chess;
					activated_chess = &reset;
					InvalidateRect(NULL, FALSE);
					UpdateWindow();
					isEnd = isGameOver(checkerboard);
					if (isEnd == colors::none)
					{
						if (ai != colors::none)  //ai后走时行棋
						{
							aiM = search(ai, checkerboard, level);
							dest.x = aiM.move_to.x;
							dest.y = aiM.move_to.y;
							checkerboard[aiM.chess_pos.x][aiM.chess_pos.y]->move(dest, checkerboard);
							last_move = checkerboard[dest.x][dest.y];
							InvalidateRect(NULL, FALSE);
							UpdateWindow();
							isEnd = isGameOver(checkerboard);
						}
					}
					if (isEnd != colors::none)
					{
						//player = colors::none;
						if (isEnd == colors::red)
						{
							MessageBox(_T("红方胜!"),_T("象甲"));
						}
						else
						{
							MessageBox(_T("黑方胜!"), _T("象甲"));
						}
						INT_PTR nRes;
						nRes = MessageBox(_T("要开始新游戏吗?"), _T("新游戏"), MB_YESNOCANCEL);
						if (nRes == IDYES)
						{
							newGame();
							InvalidateRect(NULL, FALSE);
							UpdateWindow();
						}
					}
				}
				else
				{
					copyBoard(tmp_board, last_board, medium_board);  //移动失败时恢复
				}
			}
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CxiangjiaDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default 
	CMenu menu;       // 菜单（包含主菜单栏和子菜单）   
	CMenu* pSubMenu;  // 右键菜单   

	// 加载菜单资源到menu对象   
	menu.LoadMenu(IDR_RMENU);
	// 因为右键菜单是弹出式菜单，不包含主菜单栏，所以取子菜单   
	pSubMenu = menu.GetSubMenu(0);
	// 将坐标值由客户坐标转换为屏幕坐标   
	ClientToScreen(&point);
	// 弹出右键菜单，菜单左侧与point.x坐标值对齐   
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CxiangjiaDlg::OnRmenuRollback()
{
	// TODO: Add your command handler code here
	//悔棋棋盘恢复
	if (allowRollback)
	{
		int a, b;
		for (a = 0; a <= 8; a++)
		{
			for (b = 0; b <= 9; b++)
			{
				copyBoard(last_board, checkerboard, medium_board3);
				activated_chess = &reset;
				last_move = &reset;
			}
		}
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
		if (ai == colors::none)
		{
			if (player == colors::red)
			{
				player = colors::black;
			}
			else
			{
				player = colors::red;
			}
		}
		allowRollback = false;
	}
}

void CxiangjiaDlg::OnRmenuNew()
{
	// TODO: Add your command handler code here
	INT_PTR nRes;
	nRes = MessageBox(_T("确定要开始新游戏吗?"), _T("新游戏"), MB_YESNOCANCEL);
	if (nRes == IDYES)
	{
		newGame();
		InvalidateRect(NULL, FALSE);
		UpdateWindow();
	}
}
