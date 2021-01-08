#define none 0
#define bjiang 1
#define bche 2
#define bma 3
#define bpao 4
#define bshi 5
#define bxiang 6
#define bbing 7
#define rjiang 8
#define rche 9
#define rma 10
#define rpao 11
#define rshi 12
#define rxiang 13
#define rbing 14

#define red 8
#define black 1

extern int checkerboard[9][10];

void initialize();

int isSameColor(const int a, const int b);

void moverablePosition(const int chess, const int x, const int y, const int board[9][10], int moverableList[20][2], int* num);

void moverablePositionCount(const int chess, const int x, const int y, const int board[9][10], int* num);

int move(const int chess, const int ox, const int oy, const int tx, int const ty, int board[9][10], int valid = 0);

int isGameOver(const int board[9][10]);

int getChessNumber(const int board[9][10]);

int getMoverableNumber(const int board[9][10]);

int isSameBoard(const int boardA[9][10], const int boardB[9][10]);
