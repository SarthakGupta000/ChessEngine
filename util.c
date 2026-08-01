#include "util.h"

char convert[10] = "0123456789";

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
            if (game->turn * 4 == game->board[y][x]) {
                for (int i = 0; i < 4; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 0) {
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
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 0) {
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
                    if (getOutOfBound(currentx, currenty) == 0 && (game->board[currenty][currentx] == 0 || (((game->board[currenty][currentx] > 0) && (game->turn < 0)) || ((game->board[currenty][currentx] < 0) && (game->turn > 0))))) {
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
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = y + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 0&& (game->board[currenty][currentx] == 0 || (((game->board[currenty][currentx] > 0) && (game->turn < 0)) || ((game->board[currenty][currentx] < 0) && (game->turn > 0))))) {
                        moves.arr[next][0] = 'N';
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
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 0) {
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
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 0) {
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
        (0, -1)
    };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 4 == game->board[y][x]) {
                for (int i = 0; i < 8; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 0) {
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
    moves.arr = (char **) malloc(sizeof(char *) * numOfMoves);
    moves.size = numOfMoves;
    for (int i = 0; i < numOfMoves; i++) {
        moves.arr[i] = (char *) malloc(sizeof(char) * 6);
    }
    int next = 0;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 4 == game->board[y][x]) {
                for (int i = 0; i < 8; i++) {
                    int scale = 1;
                    while (1) {
                        if (getOutOfBound((x + (offsets[i][0] * scale)), (y + (offsets[i][1] * scale))) == 0) {
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
        (0, -1)
    };
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game->turn * 10 == game->board[y][x]) { // this is the king
                for (int i = 0; i < 8; i++) {
                    int currentx = x + offsets[i][0];
                    int currenty = x + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 0) {
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
                    int currenty = x + offsets[i][1];
                    if (getOutOfBound(currentx, currenty) == 0) {
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