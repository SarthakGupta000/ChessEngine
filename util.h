#include <stdlib.h>
#include <stdio.h>

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

int getOutOfBound(int x, int y);

struct GameState *createGame();

void destroyGame(struct GameState *game);

struct StringArray getPawnMoves(struct GameState *game);

struct StringArray getRookMoves(struct GameState *game);

struct StringArray getKnightMoves(struct GameState *game);

struct StringArray getBishopMoves(struct GameState *game);

struct StringArray getQueenMoves(struct GameState *game);

struct StringArray getKingMoves(struct GameState *game);

char *getCheck(struct GameState *game); // returns "0" if not and the piece if the king is in check

struct StringArray getAllMoves(struct GameState *game); // returns the NULL struct if checkmate

void run();