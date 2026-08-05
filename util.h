#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
-5 -3 -4 -9 -10 -4 -3 -5
-1 -1 -1 -1 -1 -1 -1 -1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1
5 3 4 9 10 4 3 5
*/
struct GameState {
    int board[8][8];
    int turn; // 1 for white and -1 for black
};

struct StringArray {
    char **arr;
    size_t size;
};

int getNum(char letter);

int getOutOfBound(int x, int y);

struct GameState *createGame();

void destroyGame(struct GameState *game);

struct StringArray getPawnMoves(struct GameState *game);

struct StringArray getRookMoves(struct GameState *game);

struct StringArray getKnightMoves(struct GameState *game);

struct StringArray getBishopMoves(struct GameState *game);

struct StringArray getQueenMoves(struct GameState *game);

struct StringArray getKingMoves(struct GameState *game);

struct StringArray addRawMoves(struct GameState *game); // compiles all moves into one string array

// 0 if no check
// 1 if white is in check
// -1 if black is in check
int getCheck(struct GameState *game);

struct StringArray getAllMoves(struct GameState *game); // returns the NULL struct if checkmate

void run();