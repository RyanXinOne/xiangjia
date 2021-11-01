#include "aiEngine.h"

int getChessValue(const int chess, const int x, const int y)
//获取子力价值，输入：棋子类型，x坐标，y坐标
{
	switch (chess)
	{
	case rche:
	case bche:
		return 600;
	case rma:
	case bma:
		return 350;
	case rpao:
	case bpao:
		return 400;
	case rbing:
	case bbing:
		return 150;
	case rxiang:
	case bxiang:
		return 300;
	case rshi:
	case bshi:
		return 250;
	case rjiang:
	case bjiang:
		return 1000;
	default:
		return 0;
	}
}

int bingPositionValue[10][9] = {
	{ 0, 0, 5, 5,10, 5, 5, 0, 0},
	{ 5,10,21,30,42,30,21,10, 5},
	{ 4, 8,18,26,37,26,18, 8, 4},
	{ 3, 6,10,17,22,17,10, 6, 3},
	{ 2, 4, 7, 8,12, 8, 7, 4, 2},
	{ 1, 2, 4, 4, 7, 4, 4, 2, 1},
	{ 0, 0, 1, 0, 2, 0, 1, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int maPositionValue[10][9] = {
	{ 5,10,15,12,15,12,15,10, 5},
	{ 5,22,20,22, 7,22,20,22, 5},
	{ 5,15,20,17,20,17,20,15, 5},
	{ 5,17,20,22,20,22,20,17, 5},
	{ 5,10,15,15,20,15,15,10, 5},
	{-5, 0,-3, 1, 1, 1,-3, 0,-5},
	{-5,-2, 0,-1, 1,-1, 0,-2,-5},
	{-8, 0, 0,-4,-7,-4, 0, 0,-8},
	{-5,-2, 0,-6,-4,-6, 0,-2,-5},
	{-5,-5,-8,-10,-10,-10,-8,-5,-5}
};
int paoPositionValue[10][9] = {
	{ 0, 0,-3,-3, 0,-3,-3, 0, 0},
	{ 0, 2, 0, 2,-3, 2, 0, 2, 0},
	{-3, 0, 0,-3,-3,-3, 0, 0,-3},
	{ 0, 2, 0, 2, 0, 2, 0, 2, 0},
	{ 0, 0,-3, 0, 0, 0,-3, 0, 0},
	{ 0, 0, 0, 1, 1, 1, 0, 0, 0},
	{ 0,-2, 0,-1, 1,-1, 0,-2, 0},
	{ 0, 0, 0,-4,-4,-4, 0, 0, 0},
	{ 0,-2, 0,-6,-4,-6, 0,-2, 0},
	{ 0, 0, 0,-5,-5,-5, 0, 0, 0}
};
int chePositionValue[10][9] = {
	{15,15,12,17,20,17,12,15,15},
	{15,17,15,22,17,22,15,17,15},
	{12,15,15,17,17,17,15,15,12},
	{ 0, 2, 0,17,15,17, 0, 2, 0},
	{10,10, 7,25,25,25, 7,10,10},
	{10,10,10,26,26,26,10,10,10},
	{ 0,-2, 0,14,14,14, 0,-2, 0},
	{ 0, 0, 0,11,11,11, 0, 0, 0},
	{ 0,-2, 0, 9,11, 9, 0,-2, 0},
	{-10, 0, 0,10,10,10, 0, 0,-10}
};
int xiangPositionValue[10][9] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-10, 0, 0, 0,20, 0, 0, 0,-10},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int shiPositionValue[10][9] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0,10, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int jiangPositionValue[10][9] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0,-15,-10,-15, 0, 0, 0},
	{ 0, 0, 0,-10,-20,-10, 0, 0, 0},
	{ 0, 0, 0,10,30,10, 0, 0, 0}
};

int getPositionValue(const int chess, const int x, const int y)
{
	switch (chess)
	{
	case rche:
		return chePositionValue[y][x];
	case bche:
		return chePositionValue[9 - y][8 - x];
	case rma:
		return maPositionValue[y][x];
	case bma:
		return maPositionValue[9 - y][8 - x];
	case rpao:
		return paoPositionValue[y][x];
	case bpao:
		return paoPositionValue[9 - y][8 - x];
	case rbing:
		return bingPositionValue[y][x];
	case bbing:
		return bingPositionValue[9 - y][8 - x];
	case rxiang:
		return xiangPositionValue[y][x];
	case bxiang:
		return xiangPositionValue[9 - y][8 - x];
	case rshi:
		return shiPositionValue[y][x];
	case bshi:
		return shiPositionValue[9 - y][8 - x];
	case rjiang:
		return jiangPositionValue[y][x];
	case bjiang:
		return jiangPositionValue[9 - y][8 - x];
	default:
		return 0;
	}
}

int getFlexibilityValue(const int chess, int num)
{
	switch (chess)
	{
	case rche:
	case bche:
		return 3 * num;
	case rma:
	case bma:
		return 5 * num;
	case rpao:
	case bpao:
		return 3 * num;
	case rbing:
	case bbing:
		return 5 * num;
	case rxiang:
	case bxiang:
		return 2 * num;
	case rshi:
	case bshi:
		return 2 * num;
	case rjiang:
	case bjiang:
		return 5 * num;
	default:
		return 0;
	}
}

int evaluate(const int ctrl_col, const int board[9][10])
//局面评估函数
{
	int sum = 0;
	int i, j;
	int num;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!board[i][j])
				continue;
			num = 0;
			moverablePositionCount(board[i][j], i, j, board, &num);
			if (isSameColor(ctrl_col, board[i][j]))
			{
				sum += (getChessValue(board[i][j], i, j) + getPositionValue(board[i][j], i, j) + getFlexibilityValue(board[i][j], num));
			}
			else
			{
				sum -= (getChessValue(board[i][j], i, j) + getPositionValue(board[i][j], i, j) + getFlexibilityValue(board[i][j], num));
			}
		}
	}
	return sum;
}

void copyBoard(const int from[9][10], int to[9][10])
//复制棋盘
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			to[i][j] = from[i][j];
		}
	}
}

int AlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, int alpha, int beta, int* count)
//a-b算法(剪枝)，输入参数：控制颜色，棋盘，搜索深度，当前深度(外部请设1)，alpha值(外部请设最小值)，beta值(外部请设最大值)，节点计数
{
	int oppo_col = (ctrl_col == red) ? black : red;
	int i, j, n;
	int moverableList[20][2];
	int num = 0;
	int fancyBoard[9][10];
	int result;

	if (currentDepth == searchDepth + 1)  //到达叶子节点评估局面(其实评估的是上一层的局面)
	{
		//最底层是敌方，力求最小化；最底层是我方，我方力求最大化
		return currentDepth % 2 ? -evaluate(oppo_col, board) : evaluate(oppo_col, board);;
	}

	(*count)++;  //计数

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!isSameColor(ctrl_col, board[i][j]))  //只能操控本方棋子
				continue;
			moverablePosition(board[i][j], i, j, board, moverableList, &num);  //更新棋子可走位置列表
			for (n = 0; n < num; n++)  //遍历可走位置
			{
				//快速胜利判断
				if (board[moverableList[n][0]][moverableList[n][1]] == rjiang || board[moverableList[n][0]][moverableList[n][1]] == bjiang)
				{
					result = currentDepth % 2 ? (10000 - currentDepth * 100) : (-10000 + currentDepth * 100);
				}
				else
				{
					copyBoard(board, fancyBoard);
					//接下来全部使用fancyBoard
					move(fancyBoard[i][j], i, j, moverableList[n][0], moverableList[n][1], fancyBoard);

					result = AlphaBeta(oppo_col, fancyBoard, searchDepth, currentDepth + 1, alpha, beta, count);
				}

				if (currentDepth % 2)  //我方，力求得分最大化
				{
					if (result > alpha)  //更新下限值alpha
					{
						alpha = result;
						if (alpha >= beta)  //剪枝
							return INT_MAX;  //剪枝结果必定被舍弃
					}
				}
				else  //敌方，力求得分最小化
				{
					if (result < beta)  //更新上限值beta
					{
						beta = result;
						if (alpha >= beta)  //剪枝
							return INT_MIN;  //剪枝结果必定被舍弃
					}
				}

			}
		}
	}
	return currentDepth % 2 ? alpha : beta;
}
