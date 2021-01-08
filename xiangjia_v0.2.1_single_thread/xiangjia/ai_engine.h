#include "chess_engine.h"

typedef struct {
	int cx;
	int cy;
	int tx;
	int ty;
	int score;
}mark;

void copyBoard(const int from[9][10], int to[9][10]);

mark MaxMin(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth);

mark AlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, mark alpha, mark beta, int* count);

mark ShieldAlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, mark alpha, mark beta, int* count, mark shield);

mark OrderlyAlphaBeta(const int ctrl_col, const int board[9][10], const int searchDepth, const int currentDepth, mark alpha, mark beta, int* count);
