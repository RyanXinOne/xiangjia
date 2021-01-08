
#include "chess_engine.h"

//�����������̵�λ
chessman reset;
//����
chessman* checkerboard[9][10];

//�����ƶ�
int chessman::move(position target, chessman* operate_board[9][10])
{
    int i;
    moverable_position(operate_board);  //�ƶ���Ϸ�
    for (i = 0; i < num; i++)
    {
        if (target.x == next_moverable[i].x && target.y == next_moverable[i].y)
        {
            operate_board[target.x][target.y] = this;
            operate_board[pos.x][pos.y] = &reset;
            pos.x = target.x;
            pos.y = target.y;
            if (species == types::bing_)  //�����жϹ��ӱ���������
            {
                if (colour == colors::red)
                {
                    if (pos.y >= 5)
                    {
                        value = 2;
                    }
                }
                else
                {
                    if (pos.y <= 4)
                    {
                        value = 2;
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}

void chessman::moverable_position(chessman* board[9][10])
{
    if (species == types::che_)
    {
        num = 0;
        int i;
        for (i = pos.x + 1; i <= 8; i++)  //��������������λ��
        {
            if (board[i][pos.y]->species == types::none)
            {
                next_moverable[num].x = i;
                next_moverable[num].y = pos.y;
                num++;
            }
            else if (board[i][pos.y]->colour != colour)  //�ж��ܲ��ܳ�
            {
                next_moverable[num].x = i;
                next_moverable[num].y = pos.y;
                num++;
                break;
            }
            else
            {

                break;
            }
        }
        for (i = pos.x - 1; i >= 0; i--)  //���������Ҳ����λ��
        {
            if (board[i][pos.y]->species == types::none)
            {
                next_moverable[num].x = i;
                next_moverable[num].y = pos.y;
                num++;
            }
            else if (board[i][pos.y]->colour != colour)  //�ж��ܲ��ܳ�
            {
                next_moverable[num].x = i;
                next_moverable[num].y = pos.y;
                num++;
                break;
            }
            else
            {
                break;
            }
        }
        for (i = pos.y + 1; i <= 9; i++)  //���������Ϸ�����λ��
        {
            if (board[pos.x][i]->species == types::none)
            {
                next_moverable[num].x = pos.x;
                next_moverable[num].y = i;
                num++;
            }
            else if (board[pos.x][i]->colour != colour)  //�ж��ܲ��ܳ�
            {
                next_moverable[num].x = pos.x;
                next_moverable[num].y = i;
                num++;
                break;
            }
            else
            {
                break;
            }
        }
        for (i = pos.y - 1; i >= 0; i--)  //���������·�����λ��
        {
            if (board[pos.x][i]->species == types::none)
            {
                next_moverable[num].x = pos.x;
                next_moverable[num].y = i;
                num++;
            }
            else if (board[pos.x][i]->colour != colour)  //�ж��ܲ��ܳ�
            {
                next_moverable[num].x = pos.x;
                next_moverable[num].y = i;
                num++;
                break;
            }
            else
            {
                break;
            }
        }
    }
    else if (species == types::ma_)
    {
        num = 0;
        if (pos.y + 1 <= 9)  //�ж������û�г����߽�
        {
            if (board[pos.x][pos.y + 1]->species == types::none)  //�ж��Ϸ���û�б���ס���
            {
                if (pos.x + 1 <= 8 && pos.y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x + 1][pos.y + 2]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x + 1;
                        next_moverable[num].y = pos.y + 2;
                        num++;
                    }
                }
                if (pos.x - 1 >= 0 && pos.y + 2 <= 9)
                {
                    if (board[pos.x - 1][pos.y + 2]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x - 1;
                        next_moverable[num].y = pos.y + 2;
                        num++;
                    }
                }
            }
        }
        if (pos.y - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[pos.x][pos.y - 1]->species == types::none)  //�ж��·���û�б���ס���
            {
                if (pos.x + 1 <= 8 && pos.y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x + 1][pos.y - 2]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x + 1;
                        next_moverable[num].y = pos.y - 2;
                        num++;
                    }
                }
                if (pos.x - 1 >= 0 && pos.y - 2 >= 0)
                {
                    if (board[pos.x - 1][pos.y - 2]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x - 1;
                        next_moverable[num].y = pos.y - 2;
                        num++;
                    }
                }
            }
        }
        if (pos.x + 1 <= 8)  //�ж������û�г����߽�
        {
            if (board[pos.x + 1][pos.y]->species == types::none)  //�ж������û�б���ס���
            {
                if (pos.x + 2 <= 8 && pos.y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x + 2][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x + 2;
                        next_moverable[num].y = pos.y + 1;
                        num++;
                    }
                }
                if (pos.x + 2 <= 8 && pos.y - 1 >= 0)
                {
                    if (board[pos.x + 2][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x + 2;
                        next_moverable[num].y = pos.y - 1;
                        num++;
                    }
                }
            }
        }
        if (pos.x - 1 >= 0)  //�ж������û�г����߽�
        {
            if (board[pos.x - 1][pos.y]->species == types::none)  //�ж��Ҳ���û�б���ס���
            {
                if (pos.x - 2 >= 0 && pos.y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x - 2][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x - 2;
                        next_moverable[num].y = pos.y + 1;
                        num++;
                    }
                }
                if (pos.x - 2 >= 0 && pos.y - 1 >= 0)
                {
                    if (board[pos.x - 2][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x - 2;
                        next_moverable[num].y = pos.y - 1;
                        num++;
                    }
                }
            }
        }
    }
    else if (species == types::pao_)
    {
        num = 0;
        int i;
        bool isAttack;
        isAttack = false;
        for (i = pos.x + 1; i <= 8; i++)  //��������������λ��
        {
            if (!isAttack)
            {
                if (board[i][pos.y]->species == types::none)
                {
                    next_moverable[num].x = i;
                    next_moverable[num].y = pos.y;
                    num++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //�ж��Ƿ��ܳ�
            {
                if (board[i][pos.y]->species != types::none)
                {
                    if (board[i][pos.y]->colour != colour)
                    {
                        next_moverable[num].x = i;
                        next_moverable[num].y = pos.y;
                        num++;
                    }
                    break;
                }
            }
        }
        isAttack = false;
        for (i = pos.x - 1; i >= 0; i--)  //���������Ҳ����λ��
        {
            if (!isAttack)
            {
                if (board[i][pos.y]->species == types::none)
                {
                    next_moverable[num].x = i;
                    next_moverable[num].y = pos.y;
                    num++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //�ж��Ƿ��ܳ�
            {
                if (board[i][pos.y]->species != types::none)
                {
                    if (board[i][pos.y]->colour != colour)
                    {
                        next_moverable[num].x = i;
                        next_moverable[num].y = pos.y;
                        num++;
                    }
                    break;
                }
            }
        }
        isAttack = false;
        for (i = pos.y + 1; i <= 9; i++)  //���������Ϸ�����λ��
        {
            if (!isAttack)
            {
                if (board[pos.x][i]->species == types::none)
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = i;
                    num++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //�ж��Ƿ��ܳ�
            {
                if (board[pos.x][i]->species != types::none)
                {
                    if (board[pos.x][i]->colour != colour)
                    {
                        next_moverable[num].x = pos.x;
                        next_moverable[num].y = i;
                        num++;
                    }
                    break;
                }
            }
        }
        isAttack = false;
        for (i = pos.y - 1; i >= 0; i--)  //���������·�����λ��
        {
            if (!isAttack)
            {
                if (board[pos.x][i]->species == types::none)
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = i;
                    num++;
                }
                else
                {
                    isAttack = true;
                }
            }
            else  //�ж��Ƿ��ܳ�
            {
                if (board[pos.x][i]->species != types::none)
                {
                    if (board[pos.x][i]->colour != colour)
                    {
                        next_moverable[num].x = pos.x;
                        next_moverable[num].y = i;
                        num++;
                    }
                    break;
                }
            }
        }
    }
    else if (species == types::bing_)
    {
        num = 0;
        if (colour == colors::red)
        {
            if (pos.y <= 4)  //δ����ʱ
            {
                if (board[pos.x][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = pos.y + 1;
                    num++;
                }
            }
            else  //����ʱ
            {
                if (pos.y + 1 <= 9)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x;
                        next_moverable[num].y = pos.y + 1;
                        num++;
                    }
                }
                if (pos.x + 1 <= 8)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x + 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x + 1;
                        next_moverable[num].y = pos.y;
                        num++;
                    }
                }
                if (pos.x - 1 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x - 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x - 1;
                        next_moverable[num].y = pos.y;
                        num++;
                    }
                }
            }
        }
        else if (colour == colors::black)
        {
            if (pos.y >= 5)  //δ����ʱ
            {
                if (board[pos.x][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = pos.y - 1;
                    num++;
                }
            }
            else  //����ʱ
            {
                if (pos.y - 1 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x;
                        next_moverable[num].y = pos.y - 1;
                        num++;
                    }
                }
                if (pos.x + 1 <= 8)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x + 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x + 1;
                        next_moverable[num].y = pos.y;
                        num++;
                    }
                }
                if (pos.x - 1 >= 0)  //�ж��Ƿ񳬳��߽�
                {
                    if (board[pos.x - 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                    {
                        next_moverable[num].x = pos.x - 1;
                        next_moverable[num].y = pos.y;
                        num++;
                    }
                }
            }
        }
    }
    else if (species == types::xiang_)
    {
        num = 0;
        if (colour == colors::red)
        {
            if (pos.x + 1 <= 8 && pos.y + 1 <= 4)  //�ж������û�г����߽�
            {
                if (board[pos.x + 1][pos.y + 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x + 2 <= 8 && pos.y + 2 <= 4)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x + 2][pos.y + 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x + 2;
                            next_moverable[num].y = pos.y + 2;
                            num++;
                        }
                    }
                }
            }
            if (pos.x - 1 >= 0 && pos.y + 1 <= 4)  //�ж������û�г����߽�
            {
                if (board[pos.x - 1][pos.y + 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x - 2 >= 0 && pos.y + 2 <= 4)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x - 2][pos.y + 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x - 2;
                            next_moverable[num].y = pos.y + 2;
                            num++;
                        }
                    }
                }
            }
            if (pos.x + 1 <= 8 && pos.y - 1 >= 0)  //�ж������û�г����߽�
            {
                if (board[pos.x + 1][pos.y - 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x + 2 <= 8 && pos.y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x + 2][pos.y - 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x + 2;
                            next_moverable[num].y = pos.y - 2;
                            num++;
                        }
                    }
                }
            }
            if (pos.x - 1 >= 0 && pos.y - 1 >= 0)  //�ж������û�г����߽�
            {
                if (board[pos.x - 1][pos.y - 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x - 2 >= 0 && pos.y - 2 >= 0)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x - 2][pos.y - 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x - 2;
                            next_moverable[num].y = pos.y - 2;
                            num++;
                        }
                    }
                }
            }
        }
        else if (colour == colors::black)
        {
            if (pos.x + 1 <= 8 && pos.y + 1 <= 9)  //�ж������û�г����߽�
            {
                if (board[pos.x + 1][pos.y + 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x + 2 <= 8 && pos.y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x + 2][pos.y + 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x + 2;
                            next_moverable[num].y = pos.y + 2;
                            num++;
                        }
                    }
                }
            }
            if (pos.x - 1 >= 0 && pos.y + 1 <= 9)  //�ж������û�г����߽�
            {
                if (board[pos.x - 1][pos.y + 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x - 2 >= 0 && pos.y + 2 <= 9)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x - 2][pos.y + 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x - 2;
                            next_moverable[num].y = pos.y + 2;
                            num++;
                        }
                    }
                }
            }
            if (pos.x + 1 <= 8 && pos.y - 1 >= 5)  //�ж������û�г����߽�
            {
                if (board[pos.x + 1][pos.y - 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x + 2 <= 8 && pos.y - 2 >= 5)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x + 2][pos.y - 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x + 2;
                            next_moverable[num].y = pos.y - 2;
                            num++;
                        }
                    }
                }
            }
            if (pos.x - 1 >= 0 && pos.y - 1 >= 5)  //�ж������û�г����߽�
            {
                if (board[pos.x - 1][pos.y - 1]->species == types::none)  //�ж�������û�б���ס���
                {
                    if (pos.x - 2 >= 0 && pos.y - 2 >= 5)  //�ж��Ƿ񳬳��߽�
                    {
                        if (board[pos.x - 2][pos.y - 2]->colour != colour)  //�ж��Ƿ��ܳ�
                        {
                            next_moverable[num].x = pos.x - 2;
                            next_moverable[num].y = pos.y - 2;
                            num++;
                        }
                    }
                }
            }
        }
    }
    else if (species == types::shi_)
    {
        num = 0;
        if (colour == colors::red)
        {
            if (pos.x + 1 <= 5 && pos.y + 1 <= 2)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x + 1][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x + 1;
                    next_moverable[num].y = pos.y + 1;
                    num++;
                }
            }
            if (pos.x - 1 >= 3 && pos.y + 1 <= 2)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x - 1][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x - 1;
                    next_moverable[num].y = pos.y + 1;
                    num++;
                }
            }
            if (pos.x + 1 <= 5 && pos.y - 1 >= 0)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x + 1][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x + 1;
                    next_moverable[num].y = pos.y - 1;
                    num++;
                }
            }
            if (pos.x - 1 >= 3 && pos.y - 1 >= 0)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x - 1][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x - 1;
                    next_moverable[num].y = pos.y - 1;
                    num++;
                }
            }
        }
        else if (colour == colors::black)
        {
            if (pos.x + 1 <= 5 && pos.y + 1 <= 9)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x + 1][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x + 1;
                    next_moverable[num].y = pos.y + 1;
                    num++;
                }
            }
            if (pos.x - 1 >= 3 && pos.y + 1 <= 9)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x - 1][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x - 1;
                    next_moverable[num].y = pos.y + 1;
                    num++;
                }
            }
            if (pos.x + 1 <= 5 && pos.y - 1 >= 7)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x + 1][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x + 1;
                    next_moverable[num].y = pos.y - 1;
                    num++;
                }
            }
            if (pos.x - 1 >= 3 && pos.y - 1 >= 7)  //�ж������Ƿ񳬳��߽�
            {
                if (board[pos.x - 1][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x - 1;
                    next_moverable[num].y = pos.y - 1;
                    num++;
                }
            }
        }
    }
    else if (species == types::jiang_)
    {
        num = 0;
        int i;
        if (colour == colors::red)
        {
            for (i = pos.y + 1; i <= 9; i++)
            {
                if (board[pos.x][i]->species == types::none)
                {
                    continue;
                }
                else if (board[pos.x][i]->species == types::jiang_)  //�ж��Ƿ���Է�ɱ��
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = i;
                    num++;
                    break;
                }
                else
                {
                    break;
                }
            }
            if (pos.y + 1 <= 2)  //�ж��Ϸ��Ƿ񳬳��߽�
            {
                if (board[pos.x][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = pos.y + 1;
                    num++;
                }
            }
            if (pos.y - 1 >= 0)  //�ж��·��Ƿ񳬳��߽�
            {
                if (board[pos.x][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = pos.y - 1;
                    num++;
                }
            }
            if (pos.x + 1 <= 5)  //�ж�����Ƿ񳬳��߽�
            {
                if (board[pos.x + 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x + 1;
                    next_moverable[num].y = pos.y;
                    num++;
                }
            }
            if (pos.x - 1 >= 3)  //�ж��Ҳ��Ƿ񳬳��߽�
            {
                if (board[pos.x - 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x - 1;
                    next_moverable[num].y = pos.y;
                    num++;
                }
            }
        }
        else if (colour == colors::black)
        {
            for (i = pos.y - 1; i >= 0; i--)  //���������·�����λ��
            {
                if (board[pos.x][i]->species == types::none)
                {
                    continue;
                }
                else if (board[pos.x][i]->species == types::jiang_)  //�ж��Ƿ���Է�ɱ��
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = i;
                    num++;
                    break;
                }
                else
                {
                    break;
                }
            }
            if (pos.y + 1 <= 9)  //�ж��Ϸ��Ƿ񳬳��߽�
            {
                if (board[pos.x][pos.y + 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = pos.y + 1;
                    num++;
                }
            }
            if (pos.y - 1 >= 7)  //�ж��·��Ƿ񳬳��߽�
            {
                if (board[pos.x][pos.y - 1]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x;
                    next_moverable[num].y = pos.y - 1;
                    num++;
                }
            }
            if (pos.x + 1 <= 5)  //�ж�����Ƿ񳬳��߽�
            {
                if (board[pos.x + 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x + 1;
                    next_moverable[num].y = pos.y;
                    num++;
                }
            }
            if (pos.x - 1 >= 3)  //�ж��Ҳ��Ƿ񳬳��߽�
            {
                if (board[pos.x - 1][pos.y]->colour != colour)  //�ж��Ƿ��ܳ�
                {
                    next_moverable[num].x = pos.x - 1;
                    next_moverable[num].y = pos.y;
                    num++;
                }
            }
        }
    }
    else
    {

    }
}


//�����ʼ��
void initialize()
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 10; j++)
        {
            checkerboard[i][j] = &reset;
        }
    }
    checkerboard[0][0] = new che(colors::red);
    checkerboard[0][0]->pos.x = 0;
    checkerboard[0][0]->pos.y = 0;
    checkerboard[8][0] = new che(colors::red);
    checkerboard[8][0]->pos.x = 8;
    checkerboard[8][0]->pos.y = 0;
    checkerboard[8][9] = new che(colors::black);
    checkerboard[8][9]->pos.x = 8;
    checkerboard[8][9]->pos.y = 9;
    checkerboard[0][9] = new che(colors::black);
    checkerboard[0][9]->pos.x = 0;
    checkerboard[0][9]->pos.y = 9;
    checkerboard[1][0] = new ma(colors::red);
    checkerboard[1][0]->pos.x = 1;
    checkerboard[1][0]->pos.y = 0;
    checkerboard[7][0] = new ma(colors::red);
    checkerboard[7][0]->pos.x = 7;
    checkerboard[7][0]->pos.y = 0;
    checkerboard[7][9] = new ma(colors::black);
    checkerboard[7][9]->pos.x = 7;
    checkerboard[7][9]->pos.y = 9;
    checkerboard[1][9] = new ma(colors::black);
    checkerboard[1][9]->pos.x = 1;
    checkerboard[1][9]->pos.y = 9;
    checkerboard[1][2] = new pao(colors::red);
    checkerboard[1][2]->pos.x = 1;
    checkerboard[1][2]->pos.y = 2;
    checkerboard[7][2] = new pao(colors::red);
    checkerboard[7][2]->pos.x = 7;
    checkerboard[7][2]->pos.y = 2;
    checkerboard[7][7] = new pao(colors::black);
    checkerboard[7][7]->pos.x = 7;
    checkerboard[7][7]->pos.y = 7;
    checkerboard[1][7] = new pao(colors::black);
    checkerboard[1][7]->pos.x = 1;
    checkerboard[1][7]->pos.y = 7;
    checkerboard[8][3] = new bing(colors::red);
    checkerboard[8][3]->pos.x = 8;
    checkerboard[8][3]->pos.y = 3;
    checkerboard[6][3] = new bing(colors::red);
    checkerboard[6][3]->pos.x = 6;
    checkerboard[6][3]->pos.y = 3;
    checkerboard[4][3] = new bing(colors::red);
    checkerboard[4][3]->pos.x = 4;
    checkerboard[4][3]->pos.y = 3;
    checkerboard[2][3] = new bing(colors::red);
    checkerboard[2][3]->pos.x = 2;
    checkerboard[2][3]->pos.y = 3;
    checkerboard[0][3] = new bing(colors::red);
    checkerboard[0][3]->pos.x = 0;
    checkerboard[0][3]->pos.y = 3;
    checkerboard[8][6] = new bing(colors::black);
    checkerboard[8][6]->pos.x = 8;
    checkerboard[8][6]->pos.y = 6;
    checkerboard[6][6] = new bing(colors::black);
    checkerboard[6][6]->pos.x = 6;
    checkerboard[6][6]->pos.y = 6;
    checkerboard[4][6] = new bing(colors::black);
    checkerboard[4][6]->pos.x = 4;
    checkerboard[4][6]->pos.y = 6;
    checkerboard[2][6] = new bing(colors::black);
    checkerboard[2][6]->pos.x = 2;
    checkerboard[2][6]->pos.y = 6;
    checkerboard[0][6] = new bing(colors::black);
    checkerboard[0][6]->pos.x = 0;
    checkerboard[0][6]->pos.y = 6;
    checkerboard[6][0] = new xiang(colors::red);
    checkerboard[6][0]->pos.x = 6;
    checkerboard[6][0]->pos.y = 0;
    checkerboard[2][0] = new xiang(colors::red);
    checkerboard[2][0]->pos.x = 2;
    checkerboard[2][0]->pos.y = 0;
    checkerboard[6][9] = new xiang(colors::black);
    checkerboard[6][9]->pos.x = 6;
    checkerboard[6][9]->pos.y = 9;
    checkerboard[2][9] = new xiang(colors::black);
    checkerboard[2][9]->pos.x = 2;
    checkerboard[2][9]->pos.y = 9;
    checkerboard[5][0] = new shi(colors::red);
    checkerboard[5][0]->pos.x = 5;
    checkerboard[5][0]->pos.y = 0;
    checkerboard[3][0] = new shi(colors::red);
    checkerboard[3][0]->pos.x = 3;
    checkerboard[3][0]->pos.y = 0;
    checkerboard[5][9] = new shi(colors::black);
    checkerboard[5][9]->pos.x = 5;
    checkerboard[5][9]->pos.y = 9;
    checkerboard[3][9] = new shi(colors::black);
    checkerboard[3][9]->pos.x = 3;
    checkerboard[3][9]->pos.y = 9;
    checkerboard[4][0] = new jiang(colors::red);
    checkerboard[4][0]->pos.x = 4;
    checkerboard[4][0]->pos.y = 0;
    checkerboard[4][9] = new jiang(colors::black);
    checkerboard[4][9]->pos.x = 4;
    checkerboard[4][9]->pos.y = 9;
}

colors isGameOver(chessman* board[9][10])
{
    int i, j;
    colors vic_r, vic_b;
    vic_r= colors::red;
    vic_b = colors::black;
    for (i = 3; i <= 5; i++)
    {
        for (j = 0; j <= 9; j++)
        {
            if (j == 3)
            {
                j = 6;
                continue;
            }
            if (board[i][j]->species == types::jiang_ && board[i][j]->colour == colors::red)
            {
                vic_b = colors::none;
            }
            if (board[i][j]->species == types::jiang_ && board[i][j]->colour == colors::black)
            {
                vic_r = colors::none;
            }
        }
    }
    if (vic_r == colors::red)
    {
        return colors::red;
    }
    else if (vic_b == colors::black)
    {
        return colors::black;
    }
    else
    {
        return colors::none;
    }
}
