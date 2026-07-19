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

struct GameState *createGame();

void destroyGame(struct GameState *game);

struct StringArray getPawnMoves(struct GameState *game, int turn);

struct StringArray getRookMoves(struct GameState *game, int turn);

struct StringArray getKnightMoves(struct GameState *game, int turn);

struct StringArray getBishopMoves(struct GameState *game, int turn);

struct StringArray getQueenMoves(struct GameState *game, int turn);

struct StringArray getKingMoves(struct GameState *game, int turn);

char *getCheck(struct GameState *game, int turn); // returns "0" if not and the piece if the king is in check

struct StringArray getAllMoves(struct GameState *game, int turn); // returns the NULL struct if checkmate

void run();