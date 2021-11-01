#include "ai_engine.h"
#include <ctime>
#include <cstdlib>

int evaluate(colors ctrl_col, chessman* operate_board[9][10])
{
    //����÷���������
    int sum = 0;
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (operate_board[i][j]->colour == ctrl_col)
            {
                sum += operate_board[i][j]->value;
            }
            else
            {
                sum -= operate_board[i][j]->value;
            }
        }
    }
    return sum;
}

void copyBoard(chessman* in_board[9][10], chessman* out_board[9][10], chessman medium_board[9][10])
{
    //��in_board���������out_board����
    int a, b;
    for (a = 0; a <= 8; a++)  //���ԭ����
    {
        for (b = 0; b <= 9; b++)
        {   
            medium_board[a][b] = *in_board[a][b];
            out_board[a][b] = &medium_board[a][b];
        }
    }
}

mark search(colors ctrl_col, chessman* ori_board[9][10], int search_depth, int current_depth)
{
    int i, j;
    mark marks[120];  //����������������б�
    int condition_num = 0;  //�����������
    int n;
    chessman* fancy_board[9][10];
    chessman medium_board[9][10];
    position to;
    colors oppo_col;
    mark opponent;

    if (ctrl_col == colors::red)
    {
        oppo_col = colors::black;
    }
    else
    {
        oppo_col = colors::red;
    }
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (ori_board[i][j]->colour != ctrl_col)  //ֻ�ܲٿر���������
            {
                continue;
            }
            ori_board[i][j]->moverable_position(ori_board);  //���¸��������п���λ��
            for (n = 0; n < ori_board[i][j]->num; n++)  //�������������п���λ�ã�׼��ģ��һһ�߹�
            {
                copyBoard(ori_board, fancy_board, medium_board);
                //������ȫ������fancy_board����
                to.x = fancy_board[i][j]->next_moverable[n].x;
                to.y = fancy_board[i][j]->next_moverable[n].y;

                fancy_board[i][j]->move(to, fancy_board);  //�ƶ���һ������λ��

                marks[condition_num].chess_pos.x = i;
                marks[condition_num].chess_pos.y = j;
                marks[condition_num].move_to = to;

                if (isGameOver(fancy_board) != colors::none)  //ʤ���ж�
                {
                    //ʤ����
                    marks[condition_num].grade = 10000 - current_depth * 100;
                }
                else
                {
                    if (current_depth < search_depth)  //�����������
                    {
                        //δ�ﵽ������
                        opponent = search(oppo_col, fancy_board, search_depth, current_depth + 1);
                        marks[condition_num].grade = -opponent.grade;
                    }
                    else
                    {
                        //�ﵽ������
                        marks[condition_num].grade = evaluate(ctrl_col, fancy_board);  //��������
                    }
                }
                
                condition_num++;
            }
        }
    }

    //�÷�����
    mark tmp;
    for (i = 0; i < condition_num - 1; i++)
    {
        for (j = condition_num - 2; j >= i; j--)
        {
            if (marks[j].grade < marks[j + 1].grade)
            {
                tmp = marks[j];
                marks[j] = marks[j + 1];
                marks[j + 1] = tmp;
            }
        }
    }
    //���ѡ��÷���ͬ���߷�
    for (i = 0; i < condition_num - 1; i++)
    {
        if (marks[i].grade != marks[i + 1].grade)
        {
            break;
        }
    }
    srand((int)time(0));
    i = rand() % (i + 1);
    return marks[i];
}