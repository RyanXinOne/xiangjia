
// xiangjiaDlg.cpp : implementation file
//

#include "framework.h"
#include "xiangjia.h"
#include "xiangjiaDlg.h"
#include "afxdialogex.h"
#include "CModeDlg.h"
#include "CEditorDlg.h"

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

ULONGLONG t1 = 0, t2 = 0;  //用于计时

int count = 0;  //搜索节点计数
mark Alpha;  //多线程共享alpha输出

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
	t1 = 0;
	t2 = 0;
	count = 0;
	depth = 0;
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

	srand((unsigned)time(NULL));  //设置随机数种子
	//设置窗口大小
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

	//弹出模式选择
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

	//按照棋盘绘制棋子
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
		//标记上次移动的棋子
		MemDC.SelectObject(&lastBmp);
		if (!isReverseDisplay)
			dc.TransparentBlt(14 + (8 - last_move.x) * 80, 14 + (9 - last_move.y) * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
		else
			dc.TransparentBlt(14 + last_move.x * 80, 14 + last_move.y * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
	}
	if (last_move_from.chess != none)
	{
		//标记上次移动的棋子的起点
		MemDC.SelectObject(&lastfromBmp);
		if (!isReverseDisplay)
			dc.TransparentBlt(14 + (8 - last_move_from.x) * 80, 14 + (9 - last_move_from.y) * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
		else
			dc.TransparentBlt(14 + last_move_from.x * 80, 14 + last_move_from.y * 80, 82, 82, &MemDC, 0, 0, 82, 82, RGB(255, 0, 0));
	}
	if (activated_chess.chess != none)
	{
		//选中棋子
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

	//更新状态栏
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
	//刷新窗口
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
	//按下选择棋子
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
							MessageBox(_T("红方胜!"), _T("象甲"));
						}
						else
						{
							MessageBox(_T("黑方胜!"), _T("象甲"));
						}
						INT_PTR nRes;
						nRes = MessageBox(_T("要开始新游戏吗?"), _T("新游戏"), MB_YESNOCANCEL);
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
	aiM.cx = -1;  //忽略屏蔽判断
	int chessNumber;

	depth = level;
	chessNumber = getChessNumber(checkerboard);
	if (chessNumber < 20)  //棋子少时自动增加搜索深度
		depth++;
	if (chessNumber < 10)
		depth++;
	count = 0;
	t1 = GetTickCount64();
	aiM = threadShieldAlphaBeta(ai, checkerboard, depth, aiM);
	move(checkerboard[aiM.cx][aiM.cy], aiM.cx, aiM.cy, aiM.tx, aiM.ty, checkerboard);
	if (isSameBoard(checkerboard, aiLastLastBoard))  //走了死循环棋
	{
		move(checkerboard[aiM.tx][aiM.ty], aiM.tx, aiM.ty, aiM.cx, aiM.cy, checkerboard);
		aiM = threadShieldAlphaBeta(ai, checkerboard, depth, aiM);
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
			MessageBox(_T("红方胜!"), _T("象甲"));
		}
		else
		{
			MessageBox(_T("黑方胜!"), _T("象甲"));
		}
		INT_PTR nRes;
		nRes = MessageBox(_T("要开始新游戏吗?"), _T("新游戏"), MB_YESNOCANCEL);
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
	//抬起确认移动
	if (ai)
		aiMode(point);
	else
		freeMode(point);

	CDialogEx::OnLButtonUp(nFlags, point);
}

void CxiangjiaDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default 
	CMenu menu;       // 菜单（包含主菜单栏和子菜单）   
	CMenu* pSubMenu;  // 右键菜单   

	onRButtonPoint = point;  //保存鼠标右键按下时的坐标

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
	nRes = MessageBox(_T("确定要开始新游戏吗?"), _T("新游戏"), MB_YESNOCANCEL);
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
	//翻转棋盘显示
	isReverseDisplay = ~isReverseDisplay;
	refreshWindow();
}

void CxiangjiaDlg::OnRmenuSwitchMode()
{
	// TODO: Add your command handler code here
	//模式切换

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
	//棋盘编辑器

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

void taskFunc(taskFuncPara* tfParamNext, CCriticalSection* ccs)
//节点任务处理函数，并行使用ab算法
{
	mark result;  //外层需要保存得分和走法

	int c = 0;  //线程内节点计数

	result.score = AlphaBeta(tfParamNext->ctrl_col, tfParamNext->board, tfParamNext->searchDepth, tfParamNext->currentDepth, Alpha.score, INT_MAX, &c);

	result.cx = tfParamNext->i;
	result.cy = tfParamNext->j;
	result.tx = tfParamNext->n0;
	result.ty = tfParamNext->n1;

	ccs->Lock();
	//更新Alpha
	if (result.score > Alpha.score)
	{
		Alpha = result;
	}
	count += c;
	ccs->Unlock();

	delete tfParamNext;
}

UINT ThreadFunc(LPVOID lpParam)
//线程函数，不断获取任务参数直到任务列表为空
{
	threadFuncPara* threadParam = (threadFuncPara*)lpParam;

	taskFuncPara* taskParam;

	while (1)
	{
		threadParam->ccs1->Lock();
		if (*(threadParam->leftTaskNum) == 0)
			break;
		taskParam = *(threadParam->taskList + --(*(threadParam->leftTaskNum)));
		threadParam->ccs1->Unlock();

		taskFunc(taskParam, threadParam->ccs2);
	}

	threadParam->ccs1->Unlock();

	return 0;
}

mark CxiangjiaDlg::threadShieldAlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, mark shield)
//使用多线程且带有屏蔽走法的外层统一入口，输入参数：控制颜色，棋盘，搜索深度，屏蔽走法
{
	int i, j, n;
	int moverableList[20][2];
	int num = 0;
	int fancyBoard[9][10];
	mark result;
	taskFuncPara* tfParamNext;  //任务函数参数
	taskFuncPara* taskParmList[128];  //任务参数队列，交给线程执行
	int taskParmNum = 0; //任务数量
	threadFuncPara threadParam;  //线程函数参数
	HANDLE* threadList = new HANDLE[threadLimit];  //线程列表，线程池
	CWinThread* pThread;
	Alpha.score = INT_MIN;  //初始化全局Alpha，设为最小值
	count += 1;  //初始化计数
	CCriticalSection critical_section1;  //临界区线程锁1,用于管理任务接收
	CCriticalSection critical_section2;  //临界区线程锁2,用于更新Alpha

	//CSemaphore semaphoreWrite(threadLimit, threadLimit);  //信号量
	//使用信号量的好处：1.控制线程数量，防止进程崩溃；2.减小信号量，可使Alpha快速更新，从而减少所需检索的节点数量，因此调整信号量以获得最优效率

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!isSameColor(ctrl_col, board[i][j]))  //只能操控本方棋子
				continue;
			moverablePosition(board[i][j], i, j, board, moverableList, &num);  //更新棋子可走位置列表
			for (n = 0; n < num; n++)  //遍历可走位置
			{
				//屏蔽判断
				if (i == shield.cx && j == shield.cy && moverableList[n][0] == shield.tx && moverableList[n][1] == shield.ty)
					continue;

				//快速胜利判断
				if (board[moverableList[n][0]][moverableList[n][1]] == rjiang || board[moverableList[n][0]][moverableList[n][1]] == bjiang)
				{
					result.score = 10000 - 100;
					result.cx = i;
					result.cy = j;
					result.tx = moverableList[n][0];
					result.ty = moverableList[n][1];
					//更新Alpha
					if (result.score > Alpha.score)
					{
						Alpha = result;
					}
				}
				else
				{
					copyBoard(board, fancyBoard);
					//接下来全部使用fancyBoard
					move(fancyBoard[i][j], i, j, moverableList[n][0], moverableList[n][1], fancyBoard);
					//注意内层不需要shield

					tfParamNext = new taskFuncPara;
					tfParamNext->ctrl_col = ctrl_col;
					copyBoard(fancyBoard, tfParamNext->board);
					tfParamNext->searchDepth = searchDepth;
					tfParamNext->currentDepth = 2;
					tfParamNext->i = i;
					tfParamNext->j = j;
					tfParamNext->n0 = moverableList[n][0];
					tfParamNext->n1 = moverableList[n][1];

					//将任务参数加入列表
					taskParmList[taskParmNum++] = tfParamNext;
				}
			}
		}
	}

	threadParam.leftTaskNum = &taskParmNum;
	threadParam.taskList = taskParmList;
	threadParam.ccs1 = &critical_section1;
	threadParam.ccs2 = &critical_section2;

	//启动线程池,线程数量由用户设定
	for (i = 0; i < threadLimit; i++)
	{
		pThread = AfxBeginThread(ThreadFunc, &threadParam);
		threadList[i] = pThread->m_hThread;
	}

	//等待所有工作线程执行完成
	WaitForMultipleObjects(threadLimit, threadList, TRUE, 60 * 1000);  //等待最长一分钟，防止有线程异常导致程序无响应，无限为WSA_INFINITE
	
	result = Alpha;

	//清除残留的线程，危险方法，不推荐
	for (i = 0; i < threadLimit; i++)
	{
		if (TerminateThread(threadList[i], -1) && !disableWarning)
		{
			AfxMessageBox(_T("Certain thread was terminated unexpectedly."));
		}
	}

	delete []threadList;

	return result;
}
