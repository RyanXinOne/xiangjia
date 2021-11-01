#include "chess_engine.h"

int iniboard[9][10] = {
	{rche, none, none, rbing, none, none, bbing, none, none, bche},
	{rma, none, rpao, none, none, none, none, bpao, none, bma},
	{rxiang, none, none, rbing, none, none, bbing, none, none, bxiang},
	{rshi, none, none, none, none, none, none, none, none, bshi},
	{rjiang, none, none, rbing, none, none, bbing, none, none, bjiang},
	{rshi, none, none, none, none, none, none, none, none, bshi},
	{rxiang, none, none, rbing, none, none, bbing, none, none, bxiang},
	{rma, none, rpao, none, none, none, none, bpao, none, bma},
	{rche, none, none, rbing, none, none, bbing, none, none, bche}};

int checkerboard[9][10];

void initialize()
{
    int i, j;
    for (i = 0; i <= 8; i++)
    {
        for (j = 0; j <= 9; j++)
        {
            checkerboard[i][j] = iniboard[i][j];
        }
    }
}

int isSameColor(const int a, const int b)
//a是一个非空棋子，b是任意棋子，判断颜色是否相同
{
    if (a >= 1 && a <= 7)
    {
        return (b >= 1 && b <= 7);
    }
    else
    {
        return (b >= 8 && b <= 14);
    }
}

void moverablePosition(const int chess, const int x, const int y, const int board[9][10], int moverableList[20][2], int* num)
// 输入变量：棋子类型，棋子x坐标，棋子y坐标，棋盘，输出坐标列表，输出可走位置数量
{
    int i;
    (*num) = 0;
    switch (chess)
    {
    case rche:
    case bche:
        for (i = x + 1; i <= 8; i++)  //搜索棋子左侧可走位置
        {
            if (board[i][y] == none)
            {
                moverableList[(*num)][0] = i;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
            else if (!isSameColor(chess, board[i][y]))  //判断能不能吃
            {
                moverableList[(*num)][0] = i;
                moverableList[(*num)][1] = y;
                (*num)++;
                break;
            }
            else
            {

                break;
            }
        }
        for (i = x - 1; i >= 0; i--)  //搜索棋子右侧可走位置
        {
            if (board[i][y] == none)
            {
                moverableList[(*num)][0] = i;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
            else if (!isSameColor(chess, board[i][y]))  //判断能不能吃
            {
                moverableList[(*num)][0] = i;
                moverableList[(*num)][1] = y;
                (*num)++;
                break;
            }
            else
            {
                break;
            }
        }
        for (i = y + 1; i <= 9; i++)  //搜索棋子上方可走位置
        {
            if (board[x][i] == none)
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
            }
            else if (!isSameColor(chess, board[x][i]))  //判断能不能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
                break;
            }
            else
            {
                break;
            }
        }
        for (i = y - 1; i >= 0; i--)  //搜索棋子下方可走位置
        {
            if (board[x][i] == none)
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
            }
            else if (!isSameColor(chess, board[x][i]))  //判断能不能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
                break;
            }
            else
            {
                break;
            }
        }
        break;
    case rma:
    case bma:
        if (y + 1 <= 9)  //判断马脚有没有超出边界
        {
            if (board[x][y + 1] == none)  //判断上方有没有被拦住马脚
            {
                if (x + 1 <= 8 && y + 2 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 1][y + 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 1;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
                if (x - 1 >= 0 && y + 2 <= 9)
                {
                    if (!isSameColor(chess, board[x - 1][y + 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 1;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (y - 1 >= 0)  //判断马脚有没有超出边界
        {
            if (board[x][y - 1] == none)  //判断下方有没有被拦住马脚
            {
                if (x + 1 <= 8 && y - 2 >= 0)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 1][y - 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 1;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
                if (x - 1 >= 0 && y - 2 >= 0)
                {
                    if (!isSameColor(chess, board[x - 1][y - 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 1;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x + 1 <= 8)  //判断马脚有没有超出边界
        {
            if (board[x + 1][y] == none)  //判断左侧有没有被拦住马脚
            {
                if (x + 2 <= 8 && y + 1 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y + 1]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y + 1;
                        (*num)++;
                    }
                }
                if (x + 2 <= 8 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x + 2][y - 1]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y - 1;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0)  //判断马脚有没有超出边界
        {
            if (board[x - 1][y] == none)  //判断右侧有没有被拦住马脚
            {
                if (x - 2 >= 0 && y + 1 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y + 1]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y + 1;
                        (*num)++;
                    }
                }
                if (x - 2 >= 0 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x - 2][y - 1]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y - 1;
                        (*num)++;
                    }
                }
            }
        }
        break;
    case rpao:
    case bpao:
        bool isAttack;
        isAttack = false;
        for (i = x + 1; i <= 8; i++)  //搜索棋子左侧可走位置
        {
            if (!isAttack)
            {
                if (board[i][y] == none)
                {
                    moverableList[(*num)][0] = i;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[i][y] != none)
                {
                    if (!isSameColor(chess, board[i][y]))
                    {
                        moverableList[(*num)][0] = i;
                        moverableList[(*num)][1] = y;
                        (*num)++;
                    }
                    break;
                }
            }
        }
        isAttack = false;
        for (i = x - 1; i >= 0; i--)  //搜索棋子右侧可走位置
        {
            if (!isAttack)
            {
                if (board[i][y] == none)
                {
                    moverableList[(*num)][0] = i;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[i][y] != none)
                {
                    if (!isSameColor(chess, board[i][y]))
                    {
                        moverableList[(*num)][0] = i;
                        moverableList[(*num)][1] = y;
                        (*num)++;
                    }
                    break;
                }
            }
        }
        isAttack = false;
        for (i = y + 1; i <= 9; i++)  //搜索棋子上方可走位置
        {
            if (!isAttack)
            {
                if (board[x][i] == none)
                {
                    moverableList[(*num)][0] = x;
                    moverableList[(*num)][1] = i;
                    (*num)++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[x][i] != none)
                {
                    if (!isSameColor(chess, board[x][i]))
                    {
                        moverableList[(*num)][0] = x;
                        moverableList[(*num)][1] = i;
                        (*num)++;
                    }
                    break;
                }
            }
        }
        isAttack = false;
        for (i = y - 1; i >= 0; i--)  //搜索棋子下方可走位置
        {
            if (!isAttack)
            {
                if (board[x][i] == none)
                {
                    moverableList[(*num)][0] = x;
                    moverableList[(*num)][1] = i;
                    (*num)++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[x][i] != none)
                {
                    if (!isSameColor(chess, board[x][i]))
                    {
                        moverableList[(*num)][0] = x;
                        moverableList[(*num)][1] = i;
                        (*num)++;
                    }
                    break;
                }
            }
        }
        break;
    case rbing:
        if (y <= 4)  //未过河时
        {
            if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        else  //过河时
        {
            if (y + 1 <= 9)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
                {
                    moverableList[(*num)][0] = x;
                    moverableList[(*num)][1] = y + 1;
                    (*num)++;
                }
            }
            if (x + 1 <= 8)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
                {
                    moverableList[(*num)][0] = x + 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
            if (x - 1 >= 0)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
                {
                    moverableList[(*num)][0] = x - 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
        }
        break;
    case bbing:
        if (y >= 5)  //未过河时
        {
            if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        else  //过河时
        {
            if (y - 1 >= 0)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
                {
                    moverableList[(*num)][0] = x;
                    moverableList[(*num)][1] = y - 1;
                    (*num)++;
                }
            }
            if (x + 1 <= 8)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
                {
                    moverableList[(*num)][0] = x + 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
            if (x - 1 >= 0)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
                {
                    moverableList[(*num)][0] = x - 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
        }
        break;
    case rxiang:
        if (x + 1 <= 8 && y + 1 <= 4)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y + 1] == none)  //判断左上有没有被拦住象脚
            {
                if (x + 2 <= 8 && y + 2 <= 4)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 4)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y + 1] == none)  //判断右上有没有被拦住象脚
            {
                if (x - 2 >= 0 && y + 2 <= 4)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 0)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y - 1] == none)  //判断左下有没有被拦住象脚
            {
                if (x + 2 <= 8 && y - 2 >= 0)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 0)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y - 1] == none)  //判断右下有没有被拦住象脚
            {
                if (x - 2 >= 0 && y - 2 >= 0)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        break;
    case bxiang:
        if (x + 1 <= 8 && y + 1 <= 9)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y + 1] == none)  //判断左上有没有被拦住象脚
            {
                if (x + 2 <= 8 && y + 2 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 9)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y + 1] == none)  //判断右上有没有被拦住象脚
            {
                if (x - 2 >= 0 && y + 2 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 5)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y - 1] == none)  //判断左下有没有被拦住象脚
            {
                if (x + 2 <= 8 && y - 2 >= 5)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 5)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y - 1] == none)  //判断右下有没有被拦住象脚
            {
                if (x - 2 >= 0 && y - 2 >= 5)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //判断是否能吃
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        break;
    case rshi:
        if (x + 1 <= 5 && y + 1 <= 2)  //判断左上是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y + 1 <= 2)  //判断右上是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5 && y - 1 >= 0)  //判断左下是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y - 1 >= 0)  //判断右下是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        break;
    case bshi:
        if (x + 1 <= 5 && y + 1 <= 9)  //判断左上是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y + 1 <= 9)  //判断右上是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5 && y - 1 >= 7)  //判断左下是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y - 1 >= 7)  //判断右下是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        break;
    case rjiang:
        for (i = y + 1; i <= 9; i++)
        {
            if (board[x][i] == none)
            {
                continue;
            }
            else if (board[x][i] == bjiang)  //判断是否可以飞杀将
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
                break;
            }
            else
            {
                break;
            }
        }
        if (y + 1 <= 2)  //判断上方是否超出边界
        {
            if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (y - 1 >= 0)  //判断下方是否超出边界
        {
            if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5)  //判断左侧是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
        }
        if (x - 1 >= 3)  //判断右侧是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
        }
        break;
    case bjiang:
        for (i = y - 1; i >= 0; i--)  //搜索棋子下方可走位置
        {
            if (board[x][i] == none)
            {
                continue;
            }
            else if (board[x][i] == rjiang)  //判断是否可以飞杀将
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
                break;
            }
            else
            {
                break;
            }
        }
        if (y + 1 <= 9)  //判断上方是否超出边界
        {
            if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (y - 1 >= 7)  //判断下方是否超出边界
        {
            if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5)  //判断左侧是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
        }
        if (x - 1 >= 3)  //判断右侧是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
        }
        break;
    default:
        break;
    }
}

void moverablePositionCount(const int chess, const int x, const int y, const int board[9][10], int* num)
// 纯计数模式，输入变量：棋子类型，棋子x坐标，棋子y坐标，棋盘，输出可走位置数量
{
    int i;
    switch (chess)
    {
    case rche:
    case bche:
        for (i = x + 1; i <= 8; i++)  //搜索棋子左侧可走位置
        {
            if (board[i][y] == none)
                (*num)++;
            else if (!isSameColor(chess, board[i][y]))  //判断能不能吃
                (*num)++;
            else
            {

                break;
            }
        }
        for (i = x - 1; i >= 0; i--)  //搜索棋子右侧可走位置
        {
            if (board[i][y] == none)
                (*num)++;
            else if (!isSameColor(chess, board[i][y]))  //判断能不能吃
                (*num)++;
            else
            {
                break;
            }
        }
        for (i = y + 1; i <= 9; i++)  //搜索棋子上方可走位置
        {
            if (board[x][i] == none)
                (*num)++;
            else if (!isSameColor(chess, board[x][i]))  //判断能不能吃
                (*num)++;
            else
            {
                break;
            }
        }
        for (i = y - 1; i >= 0; i--)  //搜索棋子下方可走位置
        {
            if (board[x][i] == none)
                (*num)++;
            else if (!isSameColor(chess, board[x][i]))  //判断能不能吃
                (*num)++;
            else
            {
                break;
            }
        }
        break;
    case rma:
    case bma:
        if (y + 1 <= 9)  //判断马脚有没有超出边界
        {
            if (board[x][y + 1] == none)  //判断上方有没有被拦住马脚
            {
                if (x + 1 <= 8 && y + 2 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 1][y + 2]))  //判断是否能吃
                        (*num)++;
                }
                if (x - 1 >= 0 && y + 2 <= 9)
                {
                    if (!isSameColor(chess, board[x - 1][y + 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (y - 1 >= 0)  //判断马脚有没有超出边界
        {
            if (board[x][y - 1] == none)  //判断下方有没有被拦住马脚
            {
                if (x + 1 <= 8 && y - 2 >= 0)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 1][y - 2]))  //判断是否能吃
                        (*num)++;
                }
                if (x - 1 >= 0 && y - 2 >= 0)
                {
                    if (!isSameColor(chess, board[x - 1][y - 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x + 1 <= 8)  //判断马脚有没有超出边界
        {
            if (board[x + 1][y] == none)  //判断左侧有没有被拦住马脚
            {
                if (x + 2 <= 8 && y + 1 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y + 1]))  //判断是否能吃
                        (*num)++;
                }
                if (x + 2 <= 8 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x + 2][y - 1]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0)  //判断马脚有没有超出边界
        {
            if (board[x - 1][y] == none)  //判断右侧有没有被拦住马脚
            {
                if (x - 2 >= 0 && y + 1 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y + 1]))  //判断是否能吃
                        (*num)++;
                }
                if (x - 2 >= 0 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x - 2][y - 1]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        break;
    case rpao:
    case bpao:
        bool isAttack;
        isAttack = false;
        for (i = x + 1; i <= 8; i++)  //搜索棋子左侧可走位置
        {
            if (!isAttack)
            {
                if (board[i][y] == none)
                    (*num)++;
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[i][y] != none)
                {
                    if (!isSameColor(chess, board[i][y]))
                        (*num)++;
                    break;
                }
            }
        }
        isAttack = false;
        for (i = x - 1; i >= 0; i--)  //搜索棋子右侧可走位置
        {
            if (!isAttack)
            {
                if (board[i][y] == none)
                    (*num)++;
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[i][y] != none)
                {
                    if (!isSameColor(chess, board[i][y]))
                        (*num)++;
                    break;
                }
            }
        }
        isAttack = false;
        for (i = y + 1; i <= 9; i++)  //搜索棋子上方可走位置
        {
            if (!isAttack)
            {
                if (board[x][i] == none)
                    (*num)++;
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[x][i] != none)
                {
                    if (!isSameColor(chess, board[x][i]))
                        (*num)++;
                    break;
                }
            }
        }
        isAttack = false;
        for (i = y - 1; i >= 0; i--)  //搜索棋子下方可走位置
        {
            if (!isAttack)
            {
                if (board[x][i] == none)
                    (*num)++;
                else
                {
                    isAttack = true;
                }
            }
            else  //判断是否能吃
            {
                if (board[x][i] != none)
                {
                    if (!isSameColor(chess, board[x][i]))
                        (*num)++;
                    break;
                }
            }
        }
        break;
    case rbing:
        if (y <= 4)  //未过河时
        {
            if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
                (*num)++;
        }
        else  //过河时
        {
            if (y + 1 <= 9)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
                    (*num)++;
            }
            if (x + 1 <= 8)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
                    (*num)++;
            }
            if (x - 1 >= 0)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
                    (*num)++;
            }
        }
        break;
    case bbing:
        if (y >= 5)  //未过河时
        {
            if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
                (*num)++;
        }
        else  //过河时
        {
            if (y - 1 >= 0)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
                    (*num)++;
            }
            if (x + 1 <= 8)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
                    (*num)++;
            }
            if (x - 1 >= 0)  //判断是否超出边界
            {
                if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
                    (*num)++;
            }
        }
        break;
    case rxiang:
        if (x + 1 <= 8 && y + 1 <= 4)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y + 1] == none)  //判断左上有没有被拦住象脚
            {
                if (x + 2 <= 8 && y + 2 <= 4)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 4)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y + 1] == none)  //判断右上有没有被拦住象脚
            {
                if (x - 2 >= 0 && y + 2 <= 4)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 0)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y - 1] == none)  //判断左下有没有被拦住象脚
            {
                if (x + 2 <= 8 && y - 2 >= 0)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 0)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y - 1] == none)  //判断右下有没有被拦住象脚
            {
                if (x - 2 >= 0 && y - 2 >= 0)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        break;
    case bxiang:
        if (x + 1 <= 8 && y + 1 <= 9)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y + 1] == none)  //判断左上有没有被拦住象脚
            {
                if (x + 2 <= 8 && y + 2 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 9)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y + 1] == none)  //判断右上有没有被拦住象脚
            {
                if (x - 2 >= 0 && y + 2 <= 9)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 5)  //判断象脚有没有超出边界
        {
            if (board[x + 1][y - 1] == none)  //判断左下有没有被拦住象脚
            {
                if (x + 2 <= 8 && y - 2 >= 5)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 5)  //判断象脚有没有超出边界
        {
            if (board[x - 1][y - 1] == none)  //判断右下有没有被拦住象脚
            {
                if (x - 2 >= 0 && y - 2 >= 5)  //判断是否超出边界
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //判断是否能吃
                        (*num)++;
                }
            }
        }
        break;
    case rshi:
        if (x + 1 <= 5 && y + 1 <= 2)  //判断左上是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //判断是否能吃
                (*num)++;
        }
        if (x - 1 >= 3 && y + 1 <= 2)  //判断右上是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //判断是否能吃
                (*num)++;
        }
        if (x + 1 <= 5 && y - 1 >= 0)  //判断左下是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //判断是否能吃
                (*num)++;
        }
        if (x - 1 >= 3 && y - 1 >= 0)  //判断右下是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //判断是否能吃
                (*num)++;
        }
        break;
    case bshi:
        if (x + 1 <= 5 && y + 1 <= 9)  //判断左上是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //判断是否能吃
                (*num)++;
        }
        if (x - 1 >= 3 && y + 1 <= 9)  //判断右上是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //判断是否能吃
                (*num)++;
        }
        if (x + 1 <= 5 && y - 1 >= 7)  //判断左下是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //判断是否能吃
                (*num)++;
        }
        if (x - 1 >= 3 && y - 1 >= 7)  //判断右下是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //判断是否能吃
                (*num)++;
        }
        break;
    case rjiang:
        for (i = y + 1; i <= 9; i++)
        {
            if (board[x][i] == none)
            {
                continue;
            }
            else if (board[x][i] == bjiang)  //判断是否可以飞杀将
                (*num)++;
            else
            {
                break;
            }
        }
        if (y + 1 <= 2)  //判断上方是否超出边界
        {
            if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
                (*num)++;
        }
        if (y - 1 >= 0)  //判断下方是否超出边界
        {
            if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
                (*num)++;
        }
        if (x + 1 <= 5)  //判断左侧是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
                (*num)++;
        }
        if (x - 1 >= 3)  //判断右侧是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
                (*num)++;
        }
        break;
    case bjiang:
        for (i = y - 1; i >= 0; i--)  //搜索棋子下方可走位置
        {
            if (board[x][i] == none)
            {
                continue;
            }
            else if (board[x][i] == rjiang)  //判断是否可以飞杀将
                (*num)++;
            else
            {
                break;
            }
        }
        if (y + 1 <= 9)  //判断上方是否超出边界
        {
            if (!isSameColor(chess, board[x][y + 1]))  //判断是否能吃
                (*num)++;
        }
        if (y - 1 >= 7)  //判断下方是否超出边界
        {
            if (!isSameColor(chess, board[x][y - 1]))  //判断是否能吃
                (*num)++;
        }
        if (x + 1 <= 5)  //判断左侧是否超出边界
        {
            if (!isSameColor(chess, board[x + 1][y]))  //判断是否能吃
                (*num)++;
        }
        if (x - 1 >= 3)  //判断右侧是否超出边界
        {
            if (!isSameColor(chess, board[x - 1][y]))  //判断是否能吃
                (*num)++;
        }
        break;
    default:
        break;
    }
}

int move(const int chess, const int ox, const int oy, const int tx, int const ty, int board[9][10], int valid)
//移动一颗棋子，输入参数：棋子种类，棋子原x坐标，棋子原y坐标，棋子目标x坐标，棋子目标y坐标，棋盘，是否验证合法性(默认为0)
{
    if (valid)
    {
        int i;
        int moverableList[20][2] = { 0 };
        int num = 0;
        moverablePosition(chess, ox, oy, board, moverableList, &num);  //移动需合法
        for (i = 0; i < num; i++)
        {
            if (tx == moverableList[i][0] && ty == moverableList[i][1])
            {
                board[tx][ty] = chess;
                board[ox][oy] = none;
                return 1;
            }
        }
        return 0;
    }
    else
    {
        board[tx][ty] = chess;
        board[ox][oy] = none;
        return 1;
    }
}

int isGameOver(const int board[9][10])
//遍历将军营方式判断游戏是否结束
{
    int i, j;
    int vic_r = red, vic_b = black;
    for (i = 3; i <= 5; i++)
    {
        for (j = 0; j <= 9; j++)
        {
            if (j == 3)
            {
                j = 6;
                continue;
            }
            if (board[i][j] == rjiang)
            {
                vic_b = none;
            }
            if (board[i][j] == bjiang)
            {
                vic_r = none;
            }
        }
    }
    return vic_r ? red : (vic_b ? black : none);
}

int getChessNumber(const int board[9][10])
{
    int i, j;
    int num = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (board[i][j])
                num += (board[i][j] == rche || board[i][j] == bche || board[i][j] == rpao || board[i][j] == bpao) ? 2 : 1;
        }
    }
    return num;
}

int getMoverableNumber(const int board[9][10])
//获取当前局面双方总走法数量
{
    int i, j;
    int num = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 10; j++)
        {
            moverablePositionCount(board[i][j], i, j, board, &num);
        }
    }
    return num;
}

int isSameBoard(const int boardA[9][10], const int boardB[9][10])
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (boardA[i][j] != boardB[i][j])
                return 0;
        }
    }
    return 1;
}
