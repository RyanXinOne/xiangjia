#pragma once

#include "chessEngine.h"
#include <climits>

//走子信息
struct mark {
	int cx;
	int cy;
	int tx;
	int ty;
	int score = INT_MIN;
};

int getChessValue(const int chess, const int x, const int y);
int getPositionValue(const int chess, const int x, const int y);
int getFlexibilityValue(const int chess, int num);
int evaluate(const int ctrl_col, const int board[9][10]);
void copyBoard(const int from[9][10], int to[9][10]);
int AlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, int alpha, int beta, int* count);
