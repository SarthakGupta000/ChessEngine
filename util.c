#include "util.h"

char *convert = "0123456789";

int getNum(char letter) {
    int var;
    for (int i = 0; i < 10; i++) {
        if (convert[i] == letter) {
            var = i;
            return var;
        }
    }
    return -1;
}

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
            game->board[y][x] = board[y][x];
        }
    }
    game->turn = 1;
    return game;
}

void destroyGame(struct GameState *game) {
    if (game == NULL) {
        return;
    }
    free(game);
}

struct StringArray getPawnMoves(struct GameState *game) { // does not handle pawn promotions right now
    int numOfMoves = 0;
    if (game->turn == 1) {
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (game->turn == game->board[y][x]) {
                    if (getOutOfBound(x, y - 1) == 0) {
                        if (game->board[(y - 1)][x] == 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(x, y - 2) == 0) {
                        if (game->board[(y - 1)][x] == 0 && game->board[(y - 2)][x] == 0 && y == 6) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(x - 1, y - 1) == 0) {
                        if (game->board[(y - 1)][(x - 1)] < 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(x + 1, y - 1) == 0) {
                        if (game->board[(y - 1)][x + 1] < 0) {
                            numOfMoves++;
                        }
                    }
                }
            }
        }
        struct StringArray moves;
        moves.size = numOfMoves;
        moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
        for (int i = 0; i < numOfMoves; i++) {
            moves.arr[i] = (char *) malloc(sizeof(char) * 6);
        }
        int next = 0;
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (game->turn == game->board[y][x]) {
                    if (getOutOfBound(x, y - 1) == 0) {
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
                    if (getOutOfBound(x, y - 2) == 0) {
                        if (game->board[(y - 1)][x] == 0 && game->board[(y - 2)][x] == 0 && y == 6) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y - 2)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(x - 1, y - 1) == 0) {
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
                    if (getOutOfBound(x + 1, y - 1) == 0) {
                        if (game->board[(y - 1)][x + 1] < 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + 1)];
                            moves.arr[next][4] = convert[(y - 1)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                }
            }
        }
        return moves;
    }
    else {
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (game->turn == game->board[y][x]) {
                    if (getOutOfBound(x, y + 1) == 0) {
                        if (game->board[(y + 1)][x] == 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(x, y + 2) == 0) {
                        if (game->board[(y + 1)][x] == 0 && game->board[(y + 2)][x] == 0 && y == 1) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(x - 1, y + 1) == 0) {
                        if (game->board[(y + 1)][(x - 1)] > 0) {
                            numOfMoves++;
                        }
                    }
                    if (getOutOfBound(x + 1, y + 1) == 0) {
                        if (game->board[(y + 1)][x + 1] > 0) {
                            numOfMoves++;
                        }
                    }
                }
            }
        }
        struct StringArray moves;
        if (numOfMoves == 0) {
            moves.arr = NULL;
            moves.size = 0;
            return moves;
        }
        moves.size = numOfMoves;
        moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
        for (int i = 0; i < numOfMoves; i++) {
            moves.arr[i] = (char *) malloc(sizeof(char) * 6);
        }
        int next = 0;
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (game->turn == game->board[y][x]) {
                    if (getOutOfBound(x, y + 1) == 0) {
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
                    if (getOutOfBound(x, y + 2) == 0) {
                        if (game->board[(y + 1)][x] == 0 && game->board[(y + 2)][x] == 0 && y == 1) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[x];
                            moves.arr[next][4] = convert[(y + 2)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                    if (getOutOfBound(x - 1, y + 1) == 0) {
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
                    if (getOutOfBound(x + 1, y + 1) == 0) {
                        if (game->board[(y + 1)][x + 1] > 0) {
                            moves.arr[next][0] = 'p';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + 1)];
                            moves.arr[next][4] = convert[(y + 1)];
                            moves.arr[next][5] = '\0';
                            next++;
                        }
                    }
                }
            }
        }
        return moves;
    }
}

struct StringArray getRookMoves(struct GameState *game) { // can be simplified a lot
    int numOfMoves = 0;
    int offsets[4][2] = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 5 == game->board[y][x]) {
                for (int i = 0; i < 4; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 1) {
                            break;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0)) {
                            break;
                        }
                        if (game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] == 0) {
                            numOfMoves++;
                            scale++;
                            continue;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0)) {
                            numOfMoves++;
                            break;
                        }
                    }
                }
            }
        }
    }
    struct StringArray moves;
    if (numOfMoves == 0) {
        moves.arr = NULL;
        moves.size = 0;
        return moves;
    }
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 5 == game->board[y][x]) {
                for (int i = 0; i < 4; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 1) {
                            break;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0)) {
                            break;
                        }
                        if (game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] == 0) {
                            moves.arr[next][0] = 'R';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + (offsets[i][0] * scale))];
                            moves.arr[next][4] = convert[(y + (offsets[i][1] * scale))];
                            moves.arr[next][5] = '\0';
                            next++;
                            scale++;
                            continue;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0)) {
                            moves.arr[next][0] = 'R';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + (offsets[i][0] * scale))];
                            moves.arr[next][4] = convert[(y + (offsets[i][1] * scale))];
                            moves.arr[next][5] = '\0';
                            next++;
                            break;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

struct StringArray getKnightMoves(struct GameState *game) {
    int numOfMoves = 0;
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
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 3 == game->board[y][x]) {
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = y + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 0) {
                        if (game->board[currenty][currentx] == 0 || (((game->board[currenty][currentx] > 0) && (game->turn < 0)) || ((game->board[currenty][currentx] < 0) && (game->turn > 0)))) {
                            numOfMoves++;
                        }
                    }
                }
            }
        }
    }
    struct StringArray moves;
    if (numOfMoves == 0) {
        moves.arr = NULL;
        moves.size = 0;
        return moves;
    }
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 3 == game->board[y][x]) {
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = y + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 0) {
                        if (game->board[currenty][currentx] == 0 || (((game->board[currenty][currentx] > 0) && (game->turn < 0)) || ((game->board[currenty][currentx] < 0) && (game->turn > 0)))) {
                            moves.arr[next][0] = 'N';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[currentx];
                            moves.arr[next][4] = convert[currenty];
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

struct StringArray getBishopMoves(struct GameState *game) {
    int numOfMoves = 0;
    int offsets[4][2] = {
        {-1, -1},
        {1, 1},
        {-1, 1},
        {1, -1}
    };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 4 == game->board[y][x]) {
                for (int i = 0; i < 4; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 1) {
                            break;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0)) {
                            break;
                        }
                        if (game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] == 0) {
                            numOfMoves++;
                            scale++;
                            continue;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0)) {
                            numOfMoves++;
                            break;
                        }
                    }
                }
            }
        }
    }
    struct StringArray moves;
    if (numOfMoves == 0) {
        moves.arr = NULL;
        moves.size = 0;
        return moves;
    }
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 4 == game->board[y][x]) {
                for (int i = 0; i < 4; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 1) {
                            break;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0)) {
                            break;
                        }
                        if (game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] == 0) {
                            moves.arr[next][0] = 'B';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + (offsets[i][0] * scale))];
                            moves.arr[next][4] = convert[(y + (offsets[i][1] * scale))];
                            moves.arr[next][5] = '\0';
                            next++;
                            scale++;
                            continue;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0)) {
                            moves.arr[next][0] = 'B';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + (offsets[i][0] * scale))];
                            moves.arr[next][4] = convert[(y + (offsets[i][1] * scale))];
                            moves.arr[next][5] = '\0';
                            next++;
                            break;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

struct StringArray getQueenMoves(struct GameState *game) {
    int numOfMoves = 0;
    int offsets[8][2] = {
        {-1, -1},
        {1, 1},
        {-1, 1},
        {1, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 9 == game->board[y][x]) {
                for (int i = 0; i < 8; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 1) {
                            break;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0)) {
                            break;
                        }
                        if (game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] == 0) {
                            numOfMoves++;
                            scale++;
                            continue;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0)) {
                            numOfMoves++;
                            break;
                        }
                    }
                }
            }
        }
    }
    struct StringArray moves;
    if (numOfMoves == 0) {
        moves.arr = NULL;
        moves.size = 0;
        return moves;
    }
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 9 == game->board[y][x]) {
                for (int i = 0; i < 8; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 1) {
                            break;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0)) {
                            break;
                        }
                        if (game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] == 0) {
                            moves.arr[next][0] = 'Q';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + (offsets[i][0] * scale))];
                            moves.arr[next][4] = convert[(y + (offsets[i][1] * scale))];
                            moves.arr[next][5] = '\0';
                            next++;
                            scale++;
                            continue;
                        }
                        if ((game->turn > 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] < 0) || (game->turn < 0 && game->board[(y + (offsets[i][1] * scale))][(x + (offsets[i][0] * scale))] > 0)) {
                            moves.arr[next][0] = 'Q';
                            moves.arr[next][1] = convert[x];
                            moves.arr[next][2] = convert[y];
                            moves.arr[next][3] = convert[(x + (offsets[i][0] * scale))];
                            moves.arr[next][4] = convert[(y + (offsets[i][1] * scale))];
                            moves.arr[next][5] = '\0';
                            next++;
                            break;
                        }
                    }
                }
            }
        }
    }
    return moves;
}

struct StringArray getKingMoves(struct GameState *game) {
    int numOfMoves = 0;
    int offsets[8][2] = {
        {-1, -1},
        {1, 1},
        {-1, 1},
        {1, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 10 == game->board[y][x]) { // this is the king
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = y + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 1) {
                        continue;
                    }
                    if (game->board[currenty][currentx] == 0) {
                        numOfMoves++;
                        continue;
                    }
                    if ((game->board[currenty][currentx] > 0 && game->board[y][x] < 0) || (game->board[currenty][currentx] < 0 && game->board[y][x] > 0)) {
                        numOfMoves++;
                    }
                }
            }
        }
    }
    struct StringArray moves;
    if (numOfMoves == 0) {
        moves.arr = NULL;
        moves.size = 0;
        return moves;
    }
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 10 == game->board[y][x]) {
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = y + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 1) {
                        continue;
                    }
                    if (game->board[currenty][currentx] == 0) {
                        moves.arr[next][0] = 'K';
                        moves.arr[next][1] = convert[x];
                        moves.arr[next][2] = convert[y];
                        moves.arr[next][3] = convert[(x + (offsets[i][0]))];
                        moves.arr[next][4] = convert[(y + (offsets[i][1]))];
                        moves.arr[next][5] = '\0';
                        next++;
                        continue;
                    }
                    if ((game->board[currenty][currentx] > 0 && game->board[y][x] < 0) || (game->board[currenty][currentx] < 0 && game->board[y][x] > 0)) {
                        moves.arr[next][0] = 'K';
                        moves.arr[next][1] = convert[x];
                        moves.arr[next][2] = convert[y];
                        moves.arr[next][3] = convert[(x + (offsets[i][0]))];
                        moves.arr[next][4] = convert[(y + (offsets[i][1]))];
                        moves.arr[next][5] = '\0';
                        next++;
                    }
                }
            }
        }
    }
    return moves;
}

struct StringArray addRawMoves(struct GameState *game) {
    struct StringArray kingMoves = getKingMoves(game);
    struct StringArray queenMoves = getQueenMoves(game);
    struct StringArray bishopMoves = getBishopMoves(game);
    struct StringArray knightMoves = getKnightMoves(game);
    struct StringArray pawnMoves = getPawnMoves(game);
    struct StringArray rookMoves = getRookMoves(game);

    int total = kingMoves.size + queenMoves.size + bishopMoves.size + knightMoves.size + pawnMoves.size + rookMoves.size;
    struct StringArray moves;
    moves.arr = (char **) malloc(sizeof(char *) * total);
    moves.size = total;
    for (int i = 0; i < total; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int i = 0; i < kingMoves.size; i++) {
        if (kingMoves.size == 0) {
            break;
        }
        (void) strcpy(moves.arr[next], kingMoves.arr[i]);
        next++;
    }
    for (int i = 0; i < queenMoves.size; i++) {
        if (queenMoves.size == 0) {
            break;
        }
        (void) strcpy(moves.arr[next], queenMoves.arr[i]);
        next++;
    }
    for (int i = 0; i < bishopMoves.size; i++) {
        if (bishopMoves.size == 0) {
            break;
        }
        (void) strcpy(moves.arr[next], bishopMoves.arr[i]);
        next++;
    }
    for (int i = 0; i < knightMoves.size; i++) {
        if (knightMoves.size == 0) {
            break;
        }
        (void) strcpy(moves.arr[next], knightMoves.arr[i]);
        next++;
    }
    for (int i = 0; i < pawnMoves.size; i++) {
        if (pawnMoves.size == 0) {
            break;
        }
        (void) strcpy(moves.arr[next], pawnMoves.arr[i]);
        next++;
    }
    for (int i = 0; i < rookMoves.size; i++) {
        if (rookMoves.size == 0) {
            break;
        }
        (void) strcpy(moves.arr[next], rookMoves.arr[i]);
        next++;
    }

    for (int i = 0; i < kingMoves.size; i++) {
        if (kingMoves.size == 0) {
            break;
        }
        free(kingMoves.arr[i]);
        if (i == kingMoves.size - 1) {
            free(kingMoves.arr);
        }
    }
    for (int i = 0; i < queenMoves.size; i++) {
        if (queenMoves.size == 0) {
            break;
        }
        free(queenMoves.arr[i]);
        if (i == queenMoves.size - 1) {
            free(queenMoves.arr);
        }
    }
    for (int i = 0; i < bishopMoves.size; i++) {
        if (bishopMoves.size == 0) {
            break;
        }
        free(bishopMoves.arr[i]);
        if (i == bishopMoves.size - 1) {
            free(bishopMoves.arr);
        }
    }
    for (int i = 0; i < knightMoves.size; i++) {
        if (knightMoves.size == 0) {
            break;
        }
        free(knightMoves.arr[i]);
        if (i == knightMoves.size - 1) {
            free(knightMoves.arr);
        }
    }
    for (int i = 0; i < pawnMoves.size; i++) {
        if (pawnMoves.size == 0) {
            break;
        }
        free(pawnMoves.arr[i]);
        if (i == pawnMoves.size - 1) {
            free(pawnMoves.arr);
        }
    }
    for (int i = 0; i < rookMoves.size; i++) {
        if (rookMoves.size == 0) {
            break;
        }
        free(rookMoves.arr[i]);
        if (i == rookMoves.size - 1) {
            free(rookMoves.arr);
        }
    }
    return moves;
}

// returns 1 if the game turn is in check
// otherwise 0
int getCheck(struct GameState *game) {
    game->turn *= -1;
    struct StringArray moves = addRawMoves(game);
    game->turn *= -1;
    int kingx;
    int kingy;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 10 == game->board[y][x]) {
                kingx = x;
                kingy = y;
            }
        }
    }
    for (int i = 0; i < moves.size; i++) {
        int x = getNum(moves.arr[i][3]);
        int y = getNum(moves.arr[i][4]);
        if (x == kingx && y == kingy) {
            for (int j = 0; j < moves.size; j++) {
                free(moves.arr[j]);
            }
            free(moves.arr);
            return 1;
        }
    }
    for (int j = 0; j < moves.size; j++) {
        free(moves.arr[j]);
    }
    free(moves.arr);
    return 0;
}

void makeMove(int board[8][8], char *move) {
    int posx = getNum(move[1]);
    int posy = getNum(move[2]);
    int tox = getNum(move[3]);
    int toy = getNum(move[4]);
    board[toy][tox] = board[posy][posx];
    board[posy][posx] = 0;
}

struct StringArray getAllMoves(struct GameState *game) {
    struct StringArray moves = addRawMoves(game);
    struct GameState *gamecpy = createGame();
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            gamecpy->board[y][x] = game->board[y][x];
        }
    }
    gamecpy->turn = game->turn;
    int numOfMoves = 0;
    for (int i = 0; i < moves.size; i++) {
        makeMove(gamecpy->board, moves.arr[i]);
        if (getCheck(gamecpy) == 0) {
            numOfMoves++;
        }
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                gamecpy->board[y][x] = game->board[y][x];
            }
        }
    }
    struct StringArray totalMoves;
    if (numOfMoves == 0) {
        totalMoves.arr = NULL;
        if (getCheck(game) == 1) {
            totalMoves.size = 1000; // mate
        } else {
            totalMoves.size = 2000; // stalemate
        }
        for (int i = 0; i < moves.size; i++) {
            free(moves.arr[i]);
        }
        free(moves.arr);
        destroyGame(gamecpy);
        return totalMoves;
    }
    totalMoves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    totalMoves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        totalMoves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int i = 0; i < moves.size; i++) {
        makeMove(gamecpy->board, moves.arr[i]);
        if (getCheck(gamecpy) == 0) {
            (void) strcpy(totalMoves.arr[next], moves.arr[i]);
            next++;
        }
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                gamecpy->board[y][x] = game->board[y][x];
            }
        }
    }
    for (int i = 0; i < moves.size; i++) {
        free(moves.arr[i]);
    }
    free(moves.arr);
    destroyGame(gamecpy);
    return totalMoves;
}

void cpyAllMoves(struct StringArray *moves, struct GameState *game) {
    struct StringArray newMoves = getAllMoves(game);
    for (int i = 0; i < moves->size; i++) {
        free(moves->arr[i]);
        if (i == moves->size - 1) {
            free(moves->arr);
        }
    }
    moves->size = newMoves.size;
    if (newMoves.arr == NULL) {
        moves->arr = NULL;
        return;
    }
    moves->arr = malloc(sizeof(char *) * moves->size);
    for (int i = 0; i < moves->size; i++) {
        moves->arr[i] = malloc(sizeof(char) * 6);
        strcpy(moves->arr[i], newMoves.arr[i]);
    }
    for (int i = 0; i < newMoves.size; i++) {
        free(newMoves.arr[i]);
    }
    free(newMoves.arr);
}

void clearStdout() {
    printf("\033[H\033[J");
    fflush(stdout);
}

void printBoard(int board[8][8]) {
    clearStdout();
    for (int y = 0; y < 8; y++) {
        printf("%d ", y);
        for (int x = 0; x < 8; x++) {
            if (board[y][x] < 0) {
                printf("B");
            }
            else if (board[y][x] == 0) {
                printf(".  ");
                continue;
            } else {
                printf("W");
            }
            if (abs(board[y][x]) == 1) {
                printf("p ");
            }
            if (abs(board[y][x]) == 3) {
                printf("N ");
            }
            if (abs(board[y][x]) == 4) {
                printf("B ");
            }
            if (abs(board[y][x]) == 5) {
                printf("R ");
            }
            if (abs(board[y][x]) == 9) {
                printf("Q ");
            }
            if (abs(board[y][x]) == 10) {
                printf("K ");
            }
        }
        printf("\n");
    }
    printf("  0  1  2  3  4  5  6  7\n");
}

void run() {
    struct GameState *game = createGame();
    struct StringArray moves = getAllMoves(game);
    cpyAllMoves(&moves, game);
    while (1) {
        printBoard(game->board);
        if (moves.size == 1000) {
            printf("Mate\n");
            goto jump;
        } 
        if (moves.size == 2000) {
            printf("Stalemate\n");
            goto jump;
        }
        char move[6];
        printf("Move -> ");
        scanf("%5s", move);
        move[5] = '\0';
        int val = -1;
        for (int i = 0; i < moves.size; i++) {
            if (strcmp(move, moves.arr[i]) == 0) {
                val = i;
                break;
            }
        }
        if (val == -1) {
            printf("Illegal move\n");
            goto jump;
        }
        makeMove(game->board, move);
        game->turn *= -1;
        cpyAllMoves(&moves, game);
    }
    jump:;
    destroyGame(game);
}