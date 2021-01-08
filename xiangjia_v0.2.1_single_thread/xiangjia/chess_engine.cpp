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
//a��һ���ǿ����ӣ�b���������ӣ��ж���ɫ�Ƿ���ͬ
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
// ����������������ͣ�����x���꣬����y���꣬���̣���������б��������λ������
{
    int i;
    (*num) = 0;
    switch (chess)
    {
    case rche:
    case bche:
        for (i = x + 1; i <= 8; i++)  //��������������λ��
        {
            if (board[i][y] == none)
            {
                moverableList[(*num)][0] = i;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
            else if (!isSameColor(chess, board[i][y]))  //�ж��ܲ��ܳ�
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
        for (i = x - 1; i >= 0; i--)  //���������Ҳ����λ��
        {
            if (board[i][y] == none)
            {
                moverableList[(*num)][0] = i;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
            else if (!isSameColor(chess, board[i][y]))  //�ж��ܲ��ܳ�
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
        for (i = y + 1; i <= 9; i++)  //���������Ϸ�����λ��
        {
            if (board[x][i] == none)
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
            }
            else if (!isSameColor(chess, board[x][i]))  //�ж��ܲ��ܳ�
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
        for (i = y - 1; i >= 0; i--)  //���������·�����λ��
        {
            if (board[x][i] == none)
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = i;
                (*num)++;
            }
            else if (!isSameColor(chess, board[x][i]))  //�ж��ܲ��ܳ�
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
        if (y + 1 <= 9)  //�ж������û�г����߽�
        {
            if (board[x][y + 1] == none)  //�ж��Ϸ���û�б���ס���
            {
                if (x + 1 <= 8 && y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 1][y + 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 1;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
                if (x - 1 >= 0 && y + 2 <= 9)
                {
                    if (!isSameColor(chess, board[x - 1][y + 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x - 1;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (y - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x][y - 1] == none)  //�ж��·���û�б���ס���
            {
                if (x + 1 <= 8 && y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 1][y - 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 1;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
                if (x - 1 >= 0 && y - 2 >= 0)
                {
                    if (!isSameColor(chess, board[x - 1][y - 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x - 1;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x + 1 <= 8)  //�ж������û�г����߽�
        {
            if (board[x + 1][y] == none)  //�ж������û�б���ס���
            {
                if (x + 2 <= 8 && y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y + 1]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y + 1;
                        (*num)++;
                    }
                }
                if (x + 2 <= 8 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x + 2][y - 1]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y - 1;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x - 1][y] == none)  //�ж��Ҳ���û�б���ס���
            {
                if (x - 2 >= 0 && y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y + 1]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y + 1;
                        (*num)++;
                    }
                }
                if (x - 2 >= 0 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x - 2][y - 1]))  //�ж��Ƿ��ܳ�
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
        for (i = x + 1; i <= 8; i++)  //��������������λ��
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
            else  //�ж��Ƿ��ܳ�
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
        for (i = x - 1; i >= 0; i--)  //���������Ҳ����λ��
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
            else  //�ж��Ƿ��ܳ�
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
        for (i = y + 1; i <= 9; i++)  //���������Ϸ�����λ��
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
            else  //�ж��Ƿ��ܳ�
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
        for (i = y - 1; i >= 0; i--)  //���������·�����λ��
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
            else  //�ж��Ƿ��ܳ�
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
        if (y <= 4)  //δ����ʱ
        {
            if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        else  //����ʱ
        {
            if (y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
                {
                    moverableList[(*num)][0] = x;
                    moverableList[(*num)][1] = y + 1;
                    (*num)++;
                }
            }
            if (x + 1 <= 8)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
                {
                    moverableList[(*num)][0] = x + 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
            if (x - 1 >= 0)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
                {
                    moverableList[(*num)][0] = x - 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
        }
        break;
    case bbing:
        if (y >= 5)  //δ����ʱ
        {
            if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        else  //����ʱ
        {
            if (y - 1 >= 0)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
                {
                    moverableList[(*num)][0] = x;
                    moverableList[(*num)][1] = y - 1;
                    (*num)++;
                }
            }
            if (x + 1 <= 8)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
                {
                    moverableList[(*num)][0] = x + 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
            if (x - 1 >= 0)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
                {
                    moverableList[(*num)][0] = x - 1;
                    moverableList[(*num)][1] = y;
                    (*num)++;
                }
            }
        }
        break;
    case rxiang:
        if (x + 1 <= 8 && y + 1 <= 4)  //�ж������û�г����߽�
        {
            if (board[x + 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y + 2 <= 4)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 4)  //�ж������û�г����߽�
        {
            if (board[x - 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y + 2 <= 4)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x + 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x - 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //�ж��Ƿ��ܳ�
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
        if (x + 1 <= 8 && y + 1 <= 9)  //�ж������û�г����߽�
        {
            if (board[x + 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 9)  //�ж������û�г����߽�
        {
            if (board[x - 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x - 2;
                        moverableList[(*num)][1] = y + 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 5)  //�ж������û�г����߽�
        {
            if (board[x + 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y - 2 >= 5)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //�ж��Ƿ��ܳ�
                    {
                        moverableList[(*num)][0] = x + 2;
                        moverableList[(*num)][1] = y - 2;
                        (*num)++;
                    }
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 5)  //�ж������û�г����߽�
        {
            if (board[x - 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y - 2 >= 5)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //�ж��Ƿ��ܳ�
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
        if (x + 1 <= 5 && y + 1 <= 2)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y + 1 <= 2)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5 && y - 1 >= 0)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y - 1 >= 0)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        break;
    case bshi:
        if (x + 1 <= 5 && y + 1 <= 9)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y + 1 <= 9)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5 && y - 1 >= 7)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x - 1 >= 3 && y - 1 >= 7)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //�ж��Ƿ��ܳ�
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
            else if (board[x][i] == bjiang)  //�ж��Ƿ���Է�ɱ��
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
        if (y + 1 <= 2)  //�ж��Ϸ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (y - 1 >= 0)  //�ж��·��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5)  //�ж�����Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
        }
        if (x - 1 >= 3)  //�ж��Ҳ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x - 1;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
        }
        break;
    case bjiang:
        for (i = y - 1; i >= 0; i--)  //���������·�����λ��
        {
            if (board[x][i] == none)
            {
                continue;
            }
            else if (board[x][i] == rjiang)  //�ж��Ƿ���Է�ɱ��
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
        if (y + 1 <= 9)  //�ж��Ϸ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y + 1;
                (*num)++;
            }
        }
        if (y - 1 >= 7)  //�ж��·��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x;
                moverableList[(*num)][1] = y - 1;
                (*num)++;
            }
        }
        if (x + 1 <= 5)  //�ж�����Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
            {
                moverableList[(*num)][0] = x + 1;
                moverableList[(*num)][1] = y;
                (*num)++;
            }
        }
        if (x - 1 >= 3)  //�ж��Ҳ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
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
// ������ģʽ������������������ͣ�����x���꣬����y���꣬���̣��������λ������
{
    int i;
    switch (chess)
    {
    case rche:
    case bche:
        for (i = x + 1; i <= 8; i++)  //��������������λ��
        {
            if (board[i][y] == none)
                (*num)++;
            else if (!isSameColor(chess, board[i][y]))  //�ж��ܲ��ܳ�
                (*num)++;
            else
            {

                break;
            }
        }
        for (i = x - 1; i >= 0; i--)  //���������Ҳ����λ��
        {
            if (board[i][y] == none)
                (*num)++;
            else if (!isSameColor(chess, board[i][y]))  //�ж��ܲ��ܳ�
                (*num)++;
            else
            {
                break;
            }
        }
        for (i = y + 1; i <= 9; i++)  //���������Ϸ�����λ��
        {
            if (board[x][i] == none)
                (*num)++;
            else if (!isSameColor(chess, board[x][i]))  //�ж��ܲ��ܳ�
                (*num)++;
            else
            {
                break;
            }
        }
        for (i = y - 1; i >= 0; i--)  //���������·�����λ��
        {
            if (board[x][i] == none)
                (*num)++;
            else if (!isSameColor(chess, board[x][i]))  //�ж��ܲ��ܳ�
                (*num)++;
            else
            {
                break;
            }
        }
        break;
    case rma:
    case bma:
        if (y + 1 <= 9)  //�ж������û�г����߽�
        {
            if (board[x][y + 1] == none)  //�ж��Ϸ���û�б���ס���
            {
                if (x + 1 <= 8 && y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 1][y + 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
                if (x - 1 >= 0 && y + 2 <= 9)
                {
                    if (!isSameColor(chess, board[x - 1][y + 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (y - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x][y - 1] == none)  //�ж��·���û�б���ס���
            {
                if (x + 1 <= 8 && y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 1][y - 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
                if (x - 1 >= 0 && y - 2 >= 0)
                {
                    if (!isSameColor(chess, board[x - 1][y - 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x + 1 <= 8)  //�ж������û�г����߽�
        {
            if (board[x + 1][y] == none)  //�ж������û�б���ס���
            {
                if (x + 2 <= 8 && y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y + 1]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
                if (x + 2 <= 8 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x + 2][y - 1]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x - 1][y] == none)  //�ж��Ҳ���û�б���ס���
            {
                if (x - 2 >= 0 && y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y + 1]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
                if (x - 2 >= 0 && y - 1 >= 0)
                {
                    if (!isSameColor(chess, board[x - 2][y - 1]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        break;
    case rpao:
    case bpao:
        bool isAttack;
        isAttack = false;
        for (i = x + 1; i <= 8; i++)  //��������������λ��
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
            else  //�ж��Ƿ��ܳ�
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
        for (i = x - 1; i >= 0; i--)  //���������Ҳ����λ��
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
            else  //�ж��Ƿ��ܳ�
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
        for (i = y + 1; i <= 9; i++)  //���������Ϸ�����λ��
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
            else  //�ж��Ƿ��ܳ�
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
        for (i = y - 1; i >= 0; i--)  //���������·�����λ��
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
            else  //�ж��Ƿ��ܳ�
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
        if (y <= 4)  //δ����ʱ
        {
            if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        else  //����ʱ
        {
            if (y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
                    (*num)++;
            }
            if (x + 1 <= 8)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
                    (*num)++;
            }
            if (x - 1 >= 0)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
                    (*num)++;
            }
        }
        break;
    case bbing:
        if (y >= 5)  //δ����ʱ
        {
            if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        else  //����ʱ
        {
            if (y - 1 >= 0)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
                    (*num)++;
            }
            if (x + 1 <= 8)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
                    (*num)++;
            }
            if (x - 1 >= 0)  //�ж��Ƿ񳬳��߽�
            {
                if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
                    (*num)++;
            }
        }
        break;
    case rxiang:
        if (x + 1 <= 8 && y + 1 <= 4)  //�ж������û�г����߽�
        {
            if (board[x + 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y + 2 <= 4)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 4)  //�ж������û�г����߽�
        {
            if (board[x - 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y + 2 <= 4)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x + 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[x - 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        break;
    case bxiang:
        if (x + 1 <= 8 && y + 1 <= 9)  //�ж������û�г����߽�
        {
            if (board[x + 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y + 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y + 1 <= 9)  //�ж������û�г����߽�
        {
            if (board[x - 1][y + 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y + 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x + 1 <= 8 && y - 1 >= 5)  //�ж������û�г����߽�
        {
            if (board[x + 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x + 2 <= 8 && y - 2 >= 5)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x + 2][y - 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        if (x - 1 >= 0 && y - 1 >= 5)  //�ж������û�г����߽�
        {
            if (board[x - 1][y - 1] == none)  //�ж�������û�б���ס���
            {
                if (x - 2 >= 0 && y - 2 >= 5)  //�ж��Ƿ񳬳��߽�
                {
                    if (!isSameColor(chess, board[x - 2][y - 2]))  //�ж��Ƿ��ܳ�
                        (*num)++;
                }
            }
        }
        break;
    case rshi:
        if (x + 1 <= 5 && y + 1 <= 2)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x - 1 >= 3 && y + 1 <= 2)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x + 1 <= 5 && y - 1 >= 0)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x - 1 >= 3 && y - 1 >= 0)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        break;
    case bshi:
        if (x + 1 <= 5 && y + 1 <= 9)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y + 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x - 1 >= 3 && y + 1 <= 9)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y + 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x + 1 <= 5 && y - 1 >= 7)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y - 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x - 1 >= 3 && y - 1 >= 7)  //�ж������Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y - 1]))  //�ж��Ƿ��ܳ�
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
            else if (board[x][i] == bjiang)  //�ж��Ƿ���Է�ɱ��
                (*num)++;
            else
            {
                break;
            }
        }
        if (y + 1 <= 2)  //�ж��Ϸ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (y - 1 >= 0)  //�ж��·��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x + 1 <= 5)  //�ж�����Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x - 1 >= 3)  //�ж��Ҳ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        break;
    case bjiang:
        for (i = y - 1; i >= 0; i--)  //���������·�����λ��
        {
            if (board[x][i] == none)
            {
                continue;
            }
            else if (board[x][i] == rjiang)  //�ж��Ƿ���Է�ɱ��
                (*num)++;
            else
            {
                break;
            }
        }
        if (y + 1 <= 9)  //�ж��Ϸ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y + 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (y - 1 >= 7)  //�ж��·��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x][y - 1]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x + 1 <= 5)  //�ж�����Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x + 1][y]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        if (x - 1 >= 3)  //�ж��Ҳ��Ƿ񳬳��߽�
        {
            if (!isSameColor(chess, board[x - 1][y]))  //�ж��Ƿ��ܳ�
                (*num)++;
        }
        break;
    default:
        break;
    }
}

int move(const int chess, const int ox, const int oy, const int tx, int const ty, int board[9][10], int valid)
//�ƶ�һ�����ӣ�����������������࣬����ԭx���꣬����ԭy���꣬����Ŀ��x���꣬����Ŀ��y���꣬���̣��Ƿ���֤�Ϸ���(Ĭ��Ϊ0)
{
    if (valid)
    {
        int i;
        int moverableList[20][2] = { 0 };
        int num = 0;
        moverablePosition(chess, ox, oy, board, moverableList, &num);  //�ƶ���Ϸ�
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
//��������Ӫ��ʽ�ж���Ϸ�Ƿ����
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
//��ȡ��ǰ����˫�����߷�����
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
