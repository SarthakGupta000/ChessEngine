#include "util.h"

char convert[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int getOutOfBound(int x, int y) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
        return 1; // yes, it is out of bounds
    }
    return 0; // not really
}

struct GameState *createGame() {
    struct GameState *game = (struct GameState *) malloc(sizeof(struct GameState));
    if (game == NULL) {
        return NULL;
    }
    int board[8][8] = {
        {-5, -3, -4, -9, -10, -4, -3, -5},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {5, 3, 4, 9, 10, 4, 3, 5}
    };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            game->board[y][x] = game->board;
        }
    }
    game->turn = 1;
}

void destroyGame(struct GameState *game) {
    if (game == NULL) {
        return;
    }
    free(game);
}

struct StringArray getPawnMoves(struct GameState *game) { // does not handle pawn promotions right now
    int numOfMoves = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->board[y][x] == game->turn) { // detects pawn
                if (game->turn == 1) {
                    if (getOutOfBound(y - 1, x) == 0) {
                        if (game->board[(y - 1)][x] == 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y - 2, x) == 0) {
                        if (game->board[(y - 2)][x] == 0 && y == 6) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y - 1, x + 1) == 0) {
                        if (game->board[(y - 1)][(x + 1)] != 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y - 1, x - 1) == 0) {
                        if (game->board[(y - 1)][(x - 1)] != 0) {
                            numOfMoves++;
                        }
                    }
                }
                if (game->turn == -1) {
                    if (getOutOfBound(y + 1, x) == 0) {
                        if (game->board[(y + 1)][x] == 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y + 2, x) == 0) {
                        if (game->board[(y + 2)][x] == 0 && y == 1) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y + 1, x + 1) == 0) {
                        if (game->board[(y + 1)][(x + 1)] != 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y + 1, x - 1) == 0) {
                        if (game->board[(y + 1)][(x - 1)] != 0) {
                            numOfMoves++;
                        }
                    }
                }
            }
        }
    }
    struct StringArray moves;
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 5); // atleast till pawn promotion is added
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->board[y][x] == game->turn) { // detects pawn
                if (game->turn == 1) {
                    if (getOutOfBound(y - 1, x) == 0) {
                        if (game->board[(y - 1)][x] == 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y - 1)];
                            next++;
                        }
                    }
                    if (getOutOfBound(y - 2, x) == 0) {
                        if (game->board[(y - 2)][x] == 0 && y == 6) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y - 2)];
                            next++;
                        }
                    }
                    if (getOutOfBound(y - 1, x + 1) == 0) {
                        if (game->board[(y - 1)][(x + 1)] != 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + 1)];
                            moves.arr[next][4] = convert[(y - 1)];
                            next++;
                        }
                    }
                    if (getOutOfBound(y - 1, x - 1) == 0) {
                        if (game->board[(y - 1)][(x - 1)] != 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x - 1)];
                            moves.arr[next][4] = convert[(y - 1)];
                            next++;
                        }
                    }
                }
                if (game->turn == -1) {
                    if (getOutOfBound(y + 1, x) == 0) {
                        if (game->board[(y + 1)][x] == 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y + 1)];
                            next++;
                        }
                    }
                    if (getOutOfBound(y + 2, x) == 0) {
                        if (game->board[(y + 2)][x] == 0 && y == 1) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y + 1)];
                            next++;
                        }
                    }
                    if (getOutOfBound(y + 1, x + 1) == 0) {
                        if (game->board[(y + 1)][(x + 1)] != 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + 1)];
                            moves.arr[next][4] = convert[(y + 1)];
                            next++;
                        }
                    }
                    if (getOutOfBound(y + 1, x - 1) == 0) {
                        if (game->board[(y + 1)][(x - 1)] != 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x - 1)];
                            moves.arr[next][4] = convert[(y + 1)];
                            next++;
                        }
                    }
                }
            }
        }
    }
    return moves;
}