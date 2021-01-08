#include "chess_engine.h"

typedef struct mark {
    position chess_pos;
    position move_to;
    int grade = 0;
}mark;

void copyBoard(chessman* in_board[9][10], chessman* out_board[9][10], chessman medium_board[9][10]);

mark search(colors ctrl_col, chessman* ori_board[9][10], int search_depth, int current_depth = 1);
