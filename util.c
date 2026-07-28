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
                        if (game->board[(y - 2)][x] == 0 && y == 6 && game->board[(y - 1)][x] == 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y - 1, x + 1) == 0) {
                        if (game->board[(y - 1)][(x + 1)] < 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y - 1, x - 1) == 0) {
                        if (game->board[(y - 1)][(x - 1)] < 0) {
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
                        if (game->board[(y + 2)][x] == 0 && y == 1 && game->board[(y + 1)][x] == 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y + 1, x + 1) == 0) {
                        if (game->board[(y + 1)][(x + 1)] > 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(y + 1, x - 1) == 0) {
                        if (game->board[(y + 1)][(x - 1)] > 0) {
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
        moves.arr[i] = (char *) malloc(sizeof(char) * 6); // atleast till pawn promotion is added
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
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(y - 2, x) == 0) {
                        if (game->board[(y - 2)][x] == 0 && y == 6 && game->board[(y - 1)][x] == 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y - 2)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(y - 1, x + 1) == 0) {
                        if (game->board[(y - 1)][(x + 1)] < 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + 1)];
                            moves.arr[next][4] = convert[(y - 1)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(y - 1, x - 1) == 0) {
                        if (game->board[(y - 1)][(x - 1)] < 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x - 1)];
                            moves.arr[next][4] = convert[(y - 1)];
                            moves.arr[next][5] = '\0';
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
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(y + 2, x) == 0) {
                        if (game->board[(y + 2)][x] == 0 && y == 1 && game->board[(y + 1)][x] == 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y + 2)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(y + 1, x + 1) == 0) {
                        if (game->board[(y + 1)][(x + 1)] > 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + 1)];
                            moves.arr[next][4] = convert[(y + 1)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(y + 1, x - 1) == 0) {
                        if (game->board[(y + 1)][(x - 1)] > 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x - 1)];
                            moves.arr[next][4] = convert[(y + 1)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

struct StringArray getRookMoves(struct GameState *game) {
    int numOfMoves = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->board[y][x] == game->turn * 5) { // search for rooks
                int currentx = x + 1;
                while (getOutOfBound(currentx, y) == 0) {
                    if ((game->turn > 0 && game->board[y][currentx] > 0) || (game->turn < 0 && game->board[y][currentx] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[y][currentx] < 0) || (game->turn < 0 && game->board[y][currentx] > 0)) {
                        numOfMoves++; // captures
                        break;
                    }
                    numOfMoves++;
                    currentx++;
                }
                currentx = x - 1;
                while (getOutOfBound(currentx, y) == 0) {
                    if ((game->turn > 0 && game->board[y][currentx] > 0) || (game->turn < 0 && game->board[y][currentx] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[y][currentx] < 0) || (game->turn < 0 && game->board[y][currentx] > 0)) {
                        numOfMoves++; // captures
                        break;
                    }
                    numOfMoves++;
                    currentx--;
                }
                int currenty = y + 1;
                while (getOutOfBound(x, currenty) == 0) {
                    if ((game->turn > 0 && game->board[currenty][x] > 0) || (game->turn < 0 && game->board[currenty][x] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[currenty][x] < 0) || (game->turn < 0 && game->board[currenty][x] > 0)) {
                        numOfMoves++; // captures
                        break;
                    }
                    numOfMoves++;
                    currenty++;
                }
                currenty = y - 1;
                while (getOutOfBound(x, currenty) == 0) {
                    if ((game->turn > 0 && game->board[currenty][x] > 0) || (game->turn < 0 && game->board[currenty][x] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[currenty][x] < 0) || (game->turn < 0 && game->board[currenty][x] > 0)) {
                        numOfMoves++; // captures
                        break;
                    }
                    numOfMoves++;
                    currenty--;
                }
            }
        }
    }
    struct StringArray moves;
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    moves.size = numOfMoves;
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->board[y][x] == game->turn * 5) { // search for rooks
                int currentx = x + 1;
                while (getOutOfBound(currentx, y) == 0) {
                    if ((game->turn > 0 && game->board[y][currentx] > 0) || (game->turn < 0 && game->board[y][currentx] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[y][currentx] < 0) || (game->turn < 0 && game->board[y][currentx] > 0)) {
                        moves.arr[next][0] = 'R';
                        moves.arr[next][1] = convert[x];
                        moves.arr[next][2] = convert[y];
                        moves.arr[next][3] = convert[currentx];
                        moves.arr[next][4] = convert[y];
                        moves.arr[next][5] = '\0';
                        next++;
                        break;
                    }
                    moves.arr[next][0] = 'R';
                    moves.arr[next][1] = convert[x];
                    moves.arr[next][2] = convert[y];
                    moves.arr[next][3] = convert[currentx];
                    moves.arr[next][4] = convert[y];
                    moves.arr[next][5] = '\0';
                    next++;
                    currentx++;
                }
                currentx = x - 1;
                while (getOutOfBound(currentx, y) == 0) {
                    if ((game->turn > 0 && game->board[y][currentx] > 0) || (game->turn < 0 && game->board[y][currentx] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[y][currentx] < 0) || (game->turn < 0 && game->board[y][currentx] > 0)) {
                        moves.arr[next][0] = 'R';
                        moves.arr[next][1] = convert[x];
                        moves.arr[next][2] = convert[y];
                        moves.arr[next][3] = convert[currentx];
                        moves.arr[next][4] = convert[y];
                        moves.arr[next][5] = '\0';
                        next++;
                        break;
                    }
                    moves.arr[next][0] = 'R';
                    moves.arr[next][1] = convert[x];
                    moves.arr[next][2] = convert[y];
                    moves.arr[next][3] = convert[currentx];
                    moves.arr[next][4] = convert[y];
                    moves.arr[next][5] = '\0';
                    next++;
                    currentx--;
                }
                int currenty = y + 1;
                while (getOutOfBound(x, currenty) == 0) {
                    if ((game->turn > 0 && game->board[currenty][x] > 0) || (game->turn < 0 && game->board[currenty][x] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[currenty][x] < 0) || (game->turn < 0 && game->board[currenty][x] > 0)) {
                        moves.arr[next][0] = 'R';
                        moves.arr[next][1] = convert[x];
                        moves.arr[next][2] = convert[y];
                        moves.arr[next][3] = convert[x];
                        moves.arr[next][4] = convert[currenty];
                        moves.arr[next][5] = '\0';
                        next++;
                        break;
                    }
                    moves.arr[next][0] = 'R';
                    moves.arr[next][1] = convert[x];
                    moves.arr[next][2] = convert[y];
                    moves.arr[next][3] = convert[x];
                    moves.arr[next][4] = convert[currenty];
                    moves.arr[next][5] = '\0';
                    next++;
                    currenty++;
                }
                currenty = y - 1;
                while (getOutOfBound(x, currenty) == 0) {
                    if ((game->turn > 0 && game->board[currenty][x] > 0) || (game->turn < 0 && game->board[currenty][x] < 0)) {
                        break;
                    }
                    if ((game->turn > 0 && game->board[currenty][x] < 0) || (game->turn < 0 && game->board[currenty][x] > 0)) {
                        moves.arr[next][0] = 'R';
                        moves.arr[next][1] = convert[x];
                        moves.arr[next][2] = convert[y];
                        moves.arr[next][3] = convert[x];
                        moves.arr[next][4] = convert[currenty];
                        moves.arr[next][5] = '\0';
                        next++;
                        break;
                    }
                    moves.arr[next][0] = 'R';
                    moves.arr[next][1] = convert[x];
                    moves.arr[next][2] = convert[y];
                    moves.arr[next][3] = convert[x];
                    moves.arr[next][4] = convert[currenty];
                    moves.arr[next][5] = '\0';
                    next++;
                    currenty--;
                }
            }
        }
    }
    return moves;
}

struct StringArray getKnightMoves(struct GameState *game) {
    int numOfMoves = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 3 == game->board[y][x]) {
                int offsets[8][2] = {
                    {2, 1},
                    {2, -1},
                    {-2, -1},
                    {-2, 1},
                    {1, 2},
                    {-1, 2},
                    {1, -2},
                    {-1, -2}
                };
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = y + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 0) {
                        numOfMoves++;
                    }
                }
            }
        }
    }
    struct StringArray moves;
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 3 == game->board[y][x]) {
                int offsets[8][2] = {
                    {2, 1},
                    {2, -1},
                    {-2, -1},
                    {-2, 1},
                    {1, 2},
                    {-1, 2},
                    {1, -2},
                    {-1, -2}
                };
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = y + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 0) {
                        moves.arr[next][0] = 'K';
                        moves.arr[next][1] = convert[x];
                        moves.arr[next][2] = convert[y];
                        moves.arr[next][3] = convert[currentx];
                        moves.arr[next][4] = convert[currenty];
                        moves.arr[next][5] = '\0';
                    }
                }
            }
        }
    }
    return moves;
}