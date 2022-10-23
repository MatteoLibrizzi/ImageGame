#include "../types.h"
#include <stdlib.h>
#include <stdio.h>

static SquarePtr emptySquare;
static keyHandlingFunction* keyHandlingFunctions;

#define KEYOFFSET 273
enum keyHandling {UP, DOWN, RIGHT, LEFT};

void downArrow (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->row != NROW-1) {
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row +1][emptySquare->col];
        board->squares[emptySquare->row +1][emptySquare->col] = temp;
        emptySquare->row += 1;
    }
}

void upArrow (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->row != 0) {
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row -1][emptySquare->col];
        board->squares[emptySquare->row -1][emptySquare->col] = temp;
        emptySquare->row -= 1;
    }
}

void leftArrow (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->col != 0) {
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row][emptySquare->col -1];
        board->squares[emptySquare->row][emptySquare->col -1] = temp;
        emptySquare->col -= 1;
    }
}

void rightArrow (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->col != NCOL-1) {
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row][emptySquare->col +1];
        board->squares[emptySquare->row][emptySquare->col +1] = temp;
        emptySquare->col += 1;
    }
}

BoardPtr board_init() {
    BoardPtr board = (BoardPtr)malloc(sizeof(Board));
    int i, j;

    for (i=0;i<NROW;i++) {
        for (j=0;j<NCOL;j++) {
            ((board->squares)[i][j]) = (SquarePtr)malloc(sizeof(Square));
            ((board->squares)[i][j])->row = i;
            ((board->squares)[i][j])->col = j;
        }
    }

    board->emptySquare = (SquarePtr)malloc(sizeof(Square));
    board->emptySquare->col = NCOL-1;
    board->emptySquare->row = NROW-1;

    keyHandlingFunctions = malloc(sizeof(keyHandlingFunction)*4);

    keyHandlingFunctions[DOWN] = &downArrow;
    keyHandlingFunctions[UP] = &upArrow;
    keyHandlingFunctions[LEFT] = &leftArrow;
    keyHandlingFunctions[RIGHT] = &rightArrow;
    return board;
}

void printBoard(BoardPtr board) {
    int i, j;
    for (i=0;i<NROW;i++) {
        for (j=0;j<NCOL;j++) {
            printf("%d,%d   ",board->squares[i][j]->row,board->squares[i][j]->col);
        }
        printf("\n");
    }
}

int isValidKey(MLV_Keyboard_button key) {
    int k = key - KEYOFFSET;
    if (k>=UP && k<=LEFT)
        return 1;
    return 0;
}


void handleKey(BoardPtr board, MLV_Keyboard_button key) {
    keyHandlingFunction f = keyHandlingFunctions[(key - KEYOFFSET)];
    f(board);
}

int isGameOver (BoardPtr board) {
    int i, j;
    for (i=0;i<NROW;i++) {
        for (j=0;j<NCOL;j++) {
            if (((board->squares)[i][j])->row == i && ((board->squares)[i][j])->col == j)
                continue;
            else
                return 0;
        }
    }
    return 1;
}

void shuffleBoard (BoardPtr board, int n) {
    if (n>0) {
        int i, rnd;
        for (i=0;i<n;i++) {
            rnd = MLV_get_random_integer(UP,LEFT);
            handleKey(board, rnd + KEYOFFSET);
        }
        if (isGameOver(board)) 
            shuffleBoard(board, n);
    }
}