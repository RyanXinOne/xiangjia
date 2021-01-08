#include "ai_engine.h"
#include <ctime>
#include <cstdlib>

int getChessValue(const int chess, const int x, const int y)
//��ȡ������ֵ�����룺�������ͣ�x���꣬y����
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
//������������
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
//��������
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

mark MaxMin(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth)
//����Сֵ�㷨(�޼�֦)�����������������ɫ�����̣�������ȣ���ǰ���(�ⲿ��������1)������ֵΪ��������ṹ��
{
	int oppo_col = (ctrl_col == red) ? black : red;
	int i, j, n;
	int moverableList[20][2];
	int num = 0;
	int fancyBoard[9][10];
	mark result[100];  //���������������
	int resultNum = 0;  //�������������������

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!isSameColor(ctrl_col, board[i][j]))  //ֻ�ܲٿر�������
				continue;
			moverablePosition(board[i][j], i, j, board, moverableList, &num);  //�������ӿ���λ���б�
			for (n = 0; n < num; n++)  //��������λ��
			{
				copyBoard(board, fancyBoard);
				//������ȫ��ʹ��fancyBoard
				move(fancyBoard[i][j], i, j, moverableList[n][0], moverableList[n][1], fancyBoard);

				if (isGameOver(fancyBoard))  //ʤ����
				{
					result[resultNum].score = 10000 - currentDepth * 100;
				}
				else
				{
					if (currentDepth < searchDepth)  //δ�ﵽ������
					{
						result[resultNum].score = -MaxMin(oppo_col, fancyBoard, searchDepth, currentDepth + 1).score;
					}
					else  //�ﵽ������
					{
						result[resultNum].score = evaluate(ctrl_col, fancyBoard);
					}
				}

				//������ߵĵ÷�
				if (result[resultNum].score > result[0].score)
				{
					result[resultNum].cx = i;
					result[resultNum].cy = j;
					result[resultNum].tx = moverableList[n][0];
					result[resultNum].ty = moverableList[n][1];
					result[0] = result[resultNum];
					resultNum = 1;
				}
				else if (result[resultNum].score == result[0].score)
				{
					result[resultNum].cx = i;
					result[resultNum].cy = j;
					result[resultNum].tx = moverableList[n][0];
					result[resultNum].ty = moverableList[n][1];
					resultNum++;
				}
			}
		}
	}

	//�������һ�����
	srand((int)time(0));
	i = rand() % (resultNum);
	return result[i];
}

mark AlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, mark alpha, mark beta, int* count)
//a-b�㷨(��֦)�����������������ɫ�����̣�������ȣ���ǰ���(�ⲿ����1)��alphaֵ(�ⲿ������Сֵ)��betaֵ(�ⲿ�������ֵ)
{
	int oppo_col = (ctrl_col == red) ? black : red;
	int i, j, n;
	int moverableList[20][2];
	int num = 0;
	int fancyBoard[9][10];
	mark result;

	/*
	if (isGameOver(board))  //һ��ʤ��ֱ�ӷ��ؼ������֣����ṹ����
	{
		result.score = currentDepth % 2 ? (-10000 + (currentDepth - 1) * 100) : (10000 - (currentDepth - 1) * 100);
		return result;
	}
	*/

	if (currentDepth == searchDepth + 1)  //����Ҷ�ӽڵ���������(��ʵ����������һ��ľ���)
	{
		result.score = currentDepth % 2 ? -evaluate(oppo_col, board) : evaluate(oppo_col, board);
		//��ײ��ǵз���������С������ײ����ҷ����ҷ��������
		return result;
	}

	(*count)++;  //����

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!isSameColor(ctrl_col, board[i][j]))  //ֻ�ܲٿر�������
				continue;
			moverablePosition(board[i][j], i, j, board, moverableList, &num);  //�������ӿ���λ���б�
			for (n = 0; n < num; n++)  //��������λ��
			{
				//����ʤ���ж�
				if (board[moverableList[n][0]][moverableList[n][1]] == rjiang || board[moverableList[n][0]][moverableList[n][1]] == bjiang)
				{
					result.score = currentDepth % 2 ? (10000 - currentDepth * 100) : (-10000 + currentDepth * 100);
				}
				else
				{
					copyBoard(board, fancyBoard);
					//������ȫ��ʹ��fancyBoard
					move(fancyBoard[i][j], i, j, moverableList[n][0], moverableList[n][1], fancyBoard);

					result.score = AlphaBeta(oppo_col, fancyBoard, searchDepth, currentDepth + 1, alpha, beta, count).score;
				}

				result.cx = i;
				result.cy = j;
				result.tx = moverableList[n][0];
				result.ty = moverableList[n][1];

				if (currentDepth % 2)  //�ҷ�������÷����
				{
					if (result.score > alpha.score)  //��������ֵalpha
					{
						alpha = result;
						if (alpha.score >= beta.score)  //��֦
							return alpha;
					}
				}
				else  //�з�������÷���С��
				{
					if (result.score < beta.score)  //��������ֵbeta
					{
						beta = result;
						if (alpha.score >= beta.score)  //��֦
							return beta;
					}
				}
				
			}
		}
	}
	return currentDepth % 2 ? alpha : beta;
}

mark ShieldAlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, mark alpha, mark beta, int* count, mark shield)
//a-b�㷨(��֦)(�����ض�����)�����������������ɫ�����̣�������ȣ���ǰ���(�ⲿ����1)��alphaֵ(�ⲿ������Сֵ)��betaֵ(�ⲿ�������ֵ)�������߷�
{
	int oppo_col = (ctrl_col == red) ? black : red;
	int i, j, n;
	int moverableList[20][2];
	int num = 0;
	int fancyBoard[9][10];
	mark result;

	/*
	if (isGameOver(board))  //һ��ʤ��ֱ�ӷ��ؼ������֣����ṹ����
	{
		result.score = currentDepth % 2 ? (-10000 + (currentDepth - 1) * 100) : (10000 - (currentDepth - 1) * 100);
		return result;
	}
	*/

	if (currentDepth == searchDepth + 1)  //����Ҷ�ӽڵ���������(��ʵ����������һ��ľ���)
	{
		result.score = currentDepth % 2 ? -evaluate(oppo_col, board) : evaluate(oppo_col, board);
		//��ײ��ǵз���������С������ײ����ҷ����ҷ��������
		return result;
	}

	(*count)++;  //����

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!isSameColor(ctrl_col, board[i][j]))  //ֻ�ܲٿر�������
				continue;
			moverablePosition(board[i][j], i, j, board, moverableList, &num);  //�������ӿ���λ���б�
			for (n = 0; n < num; n++)  //��������λ��
			{
				//�����ж�
				if (i == shield.cx && j == shield.cy && moverableList[n][0] == shield.tx && moverableList[n][1] == shield.ty)
					continue;

				//����ʤ���ж�
				if (board[moverableList[n][0]][moverableList[n][1]] == rjiang || board[moverableList[n][0]][moverableList[n][1]] == bjiang)
				{
					result.score = currentDepth % 2 ? (10000 - currentDepth * 100) : (-10000 + currentDepth * 100);
				}
				else
				{
					copyBoard(board, fancyBoard);
					//������ȫ��ʹ��fancyBoard
					move(fancyBoard[i][j], i, j, moverableList[n][0], moverableList[n][1], fancyBoard);
					//ע���ڲ㲻��Ҫshield
					result.score = AlphaBeta(oppo_col, fancyBoard, searchDepth, currentDepth + 1, alpha, beta, count).score;
				}

				result.cx = i;
				result.cy = j;
				result.tx = moverableList[n][0];
				result.ty = moverableList[n][1];

				if (currentDepth % 2)  //�ҷ�������÷����
				{
					if (result.score > alpha.score)  //��������ֵalpha
					{
						alpha = result;
						if (alpha.score >= beta.score)  //��֦
							return alpha;
					}
				}
				else  //�з�������÷���С��
				{
					if (result.score < beta.score)  //��������ֵbeta
					{
						beta = result;
						if (alpha.score >= beta.score)  //��֦
							return beta;
					}
				}

			}
		}
	}
	return currentDepth % 2 ? alpha : beta;
}

void moveGenerator(const int ctrl_col, const int board[9][10], int orderlyMoveList[100][4], int* allnum)
//�����ƶ������������ճ������ڡ�������ʿ������˳����������˳���б������Ż�a-b������������֦�ʲ������߼�ֵ�ߵ�����
//��Ҫ��������ƶ��б������߷�����
{
	int finder_che[2][2];
	int finder_che_num = 0;
	int finder_ma[2][2];
	int finder_ma_num = 0;
	int finder_pao[2][2];
	int finder_pao_num = 0;
	int finder_xiang[2][2];
	int finder_xiang_num = 0;
	int finder_shi[2][2];
	int finder_shi_num = 0;
	int finder_jiang[2];
	int finder_jiang_num = 0;
	int finder_bing[5][2];
	int finder_bing_num = 0;
	int i, j;
	int moverableList[20][2];
	int num;
	

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (!isSameColor(ctrl_col, board[i][j]))  //ֻ�ܲٿر�������
				continue;
			switch (board[i][j])
			{
			case rche:
			case bche:
				finder_che[finder_che_num][0] = i;
				finder_che[finder_che_num][1] = j;
				finder_che_num++;
				break;
			case rma:
			case bma:
				finder_ma[finder_ma_num][0] = i;
				finder_ma[finder_ma_num][1] = j;
				finder_ma_num++;
				break;
			case rpao:
			case bpao:
				finder_pao[finder_pao_num][0] = i;
				finder_pao[finder_pao_num][1] = j;
				finder_pao_num++;
				break;
			case rbing:
			case bbing:
				finder_bing[finder_bing_num][0] = i;
				finder_bing[finder_bing_num][1] = j;
				finder_bing_num++;
				break;
			case rxiang:
			case bxiang:
				finder_xiang[finder_xiang_num][0] = i;
				finder_xiang[finder_xiang_num][1] = j;
				finder_xiang_num++;
				break;
			case rshi:
			case bshi:
				finder_shi[finder_shi_num][0] = i;
				finder_shi[finder_shi_num][1] = j;
				finder_shi_num++;
				break;
			case rjiang:
			case bjiang:
				finder_jiang[0] = i;
				finder_jiang[1] = j;
				finder_jiang_num++;
				break;
			default:
				break;
			}

		}
	}

	for (i = 0; i < finder_che_num; i++)
	{
		moverablePosition(board[finder_che[i][0]][finder_che[i][1]], finder_che[i][0], finder_che[i][1], board, moverableList, &num);
		for (j = 0; j < num; j++)
		{
			orderlyMoveList[(*allnum)][0] = finder_che[i][0];
			orderlyMoveList[(*allnum)][1] = finder_che[i][1];
			orderlyMoveList[(*allnum)][2] = moverableList[j][0];
			orderlyMoveList[(*allnum)][3] = moverableList[j][1];
			(*allnum)++;
		}
	}

	for (i = 0; i < finder_ma_num; i++)
	{
		moverablePosition(board[finder_ma[i][0]][finder_ma[i][1]], finder_ma[i][0], finder_ma[i][1], board, moverableList, &num);
		for (j = 0; j < num; j++)
		{
			orderlyMoveList[(*allnum)][0] = finder_ma[i][0];
			orderlyMoveList[(*allnum)][1] = finder_ma[i][1];
			orderlyMoveList[(*allnum)][2] = moverableList[j][0];
			orderlyMoveList[(*allnum)][3] = moverableList[j][1];
			(*allnum)++;
		}
	}

	for (i = 0; i < finder_pao_num; i++)
	{
		moverablePosition(board[finder_pao[i][0]][finder_pao[i][1]], finder_pao[i][0], finder_pao[i][1], board, moverableList, &num);
		for (j = 0; j < num; j++)
		{
			orderlyMoveList[(*allnum)][0] = finder_pao[i][0];
			orderlyMoveList[(*allnum)][1] = finder_pao[i][1];
			orderlyMoveList[(*allnum)][2] = moverableList[j][0];
			orderlyMoveList[(*allnum)][3] = moverableList[j][1];
			(*allnum)++;
		}
	}

	for (i = 0; i < finder_bing_num; i++)
	{
		moverablePosition(board[finder_bing[i][0]][finder_bing[i][1]], finder_bing[i][0], finder_bing[i][1], board, moverableList, &num);
		for (j = 0; j < num; j++)
		{
			orderlyMoveList[(*allnum)][0] = finder_bing[i][0];
			orderlyMoveList[(*allnum)][1] = finder_bing[i][1];
			orderlyMoveList[(*allnum)][2] = moverableList[j][0];
			orderlyMoveList[(*allnum)][3] = moverableList[j][1];
			(*allnum)++;
		}
	}

	for (i = 0; i < finder_xiang_num; i++)
	{
		moverablePosition(board[finder_xiang[i][0]][finder_xiang[i][1]], finder_xiang[i][0], finder_xiang[i][1], board, moverableList, &num);
		for (j = 0; j < num; j++)
		{
			orderlyMoveList[(*allnum)][0] = finder_xiang[i][0];
			orderlyMoveList[(*allnum)][1] = finder_xiang[i][1];
			orderlyMoveList[(*allnum)][2] = moverableList[j][0];
			orderlyMoveList[(*allnum)][3] = moverableList[j][1];
			(*allnum)++;
		}
	}

	for (i = 0; i < finder_shi_num; i++)
	{
		moverablePosition(board[finder_shi[i][0]][finder_shi[i][1]], finder_shi[i][0], finder_shi[i][1], board, moverableList, &num);
		for (j = 0; j < num; j++)
		{
			orderlyMoveList[(*allnum)][0] = finder_shi[i][0];
			orderlyMoveList[(*allnum)][1] = finder_shi[i][1];
			orderlyMoveList[(*allnum)][2] = moverableList[j][0];
			orderlyMoveList[(*allnum)][3] = moverableList[j][1];
			(*allnum)++;
		}
	}

	for (i = 0; i < finder_jiang_num; i++)
	{
		moverablePosition(board[finder_jiang[0]][finder_jiang[1]], finder_jiang[0], finder_jiang[1], board, moverableList, &num);
		for (j = 0; j < num; j++)
		{
			orderlyMoveList[(*allnum)][0] = finder_jiang[0];
			orderlyMoveList[(*allnum)][1] = finder_jiang[1];
			orderlyMoveList[(*allnum)][2] = moverableList[j][0];
			orderlyMoveList[(*allnum)][3] = moverableList[j][1];
			(*allnum)++;
		}
	}
}

mark OrderlyAlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, mark alpha, mark beta, int* count)
//a-b�㷨(����˳�����)�����������������ɫ�����̣�������ȣ���ǰ���(�ⲿ����1)��alphaֵ(�ⲿ������Сֵ)��betaֵ(�ⲿ�������ֵ)
{
	int oppo_col = (ctrl_col == red) ? black : red;
	int n;
	int fancyBoard[9][10];
	mark result;
	int orderlyMoveList[100][4];
	int allnum = 0;

	if (isGameOver(board))  //һ��ʤ��ֱ�ӷ��ؼ������֣����ṹ����
	{
		if (currentDepth % 2)
			result.score = -10000 + (currentDepth - 1) * 100;
		else
			result.score = 10000 - (currentDepth - 1) * 100;
		return result;
	}

	if (currentDepth == searchDepth + 1)  //����Ҷ�ӽڵ���������(��ʵ����������һ��ľ���)
	{
		if (currentDepth % 2)
			result.score = -evaluate(oppo_col, board);  //��ײ��ǵз����ҷ�������С�����ȼ��ڷ������ֵ��෴��
		else
			result.score = evaluate(oppo_col, board);  //��ײ����ҷ����ҷ��������
		return result;
	}

	(*count)++;  //����

	if (currentDepth % 2)  //�ҷ�������÷����
	{
		moveGenerator(ctrl_col, board, orderlyMoveList, &allnum);
		for (n = 0; n < allnum; n++)  //��������λ��
		{
			copyBoard(board, fancyBoard);
			//������ȫ��ʹ��fancyBoard
			move(fancyBoard[orderlyMoveList[n][0]][orderlyMoveList[n][1]], orderlyMoveList[n][0], orderlyMoveList[n][1], orderlyMoveList[n][2], orderlyMoveList[n][3], fancyBoard);

			result.cx = orderlyMoveList[n][0];
			result.cy = orderlyMoveList[n][1];
			result.tx = orderlyMoveList[n][2];
			result.ty = orderlyMoveList[n][3];
			result.score = OrderlyAlphaBeta(oppo_col, fancyBoard, searchDepth, currentDepth + 1, alpha, beta, count).score;

			if (result.score > alpha.score)  //��������ֵalpha
			{
				alpha = result;
				if (alpha.score >= beta.score)  //��֦
					return alpha;
			}
		}
		return alpha;
	}
	else  //�з�������÷���С��
	{
		moveGenerator(ctrl_col, board, orderlyMoveList, &allnum);
		for (n = 0; n < allnum; n++)  //��������λ��
		{
			copyBoard(board, fancyBoard);
			//������ȫ��ʹ��fancyBoard
			move(fancyBoard[orderlyMoveList[n][0]][orderlyMoveList[n][1]], orderlyMoveList[n][0], orderlyMoveList[n][1], orderlyMoveList[n][2], orderlyMoveList[n][3], fancyBoard);

			result.cx = orderlyMoveList[n][0];
			result.cy = orderlyMoveList[n][1];
			result.tx = orderlyMoveList[n][2];
			result.ty = orderlyMoveList[n][3];
			result.score = OrderlyAlphaBeta(oppo_col, fancyBoard, searchDepth, currentDepth + 1, alpha, beta, count).score;

			if (result.score < beta.score)  //��������ֵbeta
			{
				beta = result;
				if (alpha.score >= beta.score)  //��֦
					return beta;
			}
		}
		return beta;
	}
}
