#include "../types.h"
#include <stdlib.h>
#include <stdio.h>

static SquarePtr emptySquare;/*keeping track of where the empty square is so we don't have to look for it every time*/
/*the empty square inside the board will always be NROW-1, NCOL-1 but here we track the position in the matrix*/
static keyHandlingFunction* keyHandlingFunctions;/*array of functions that binds the key to the function*/

#define KEYOFFSET 273
enum keyHandling {UP, DOWN, RIGHT, LEFT};/*enum used to handle the keys*/

#define NFUNCTIONS (LEFT+1)

void model_free(BoardPtr board) {
    free(keyHandlingFunctions);
    int i, j;
    for (i=0;i<NROW;i++) {
        for (j=0;j<NCOL;j++) {
            free((board->squares)[i][j]);
        }
    }
    free(board);
}

void move_down (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->row != NROW-1) {/*if it's not on the edge*/
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row +1][emptySquare->col];
        board->squares[emptySquare->row +1][emptySquare->col] = temp;
        /*we swap it and move the tracking of the emptySquare*/
        emptySquare->row += 1;
    }
}

void move_up (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->row != 0) {
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row -1][emptySquare->col];
        board->squares[emptySquare->row -1][emptySquare->col] = temp;
        emptySquare->row -= 1;
    }
}

void move_left (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->col != 0) {
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row][emptySquare->col -1];
        board->squares[emptySquare->row][emptySquare->col -1] = temp;
        emptySquare->col -= 1;
    }
}

void move_right (BoardPtr board) {
    SquarePtr emptySquare = board->emptySquare;
    if (emptySquare->col != NCOL-1) {
        SquarePtr temp = board->squares[emptySquare->row][emptySquare->col];
        board->squares[emptySquare->row][emptySquare->col] = board->squares[emptySquare->row][emptySquare->col +1];
        board->squares[emptySquare->row][emptySquare->col +1] = temp;
        emptySquare->col += 1;
    }
}

BoardPtr model_board_init() {
    BoardPtr board = (BoardPtr)malloc(sizeof(Board));
    int i, j;
    for (i=0;i<NROW;i++) {/*initializing the board*/
        for (j=0;j<NCOL;j++) {
            ((board->squares)[i][j]) = (SquarePtr)malloc(sizeof(Square));
            ((board->squares)[i][j])->row = i;
            ((board->squares)[i][j])->col = j;
        }
    }

    board->emptySquare = (SquarePtr)malloc(sizeof(Square));/*empty square always starts at NROW-1, NCOL-1*/
    board->emptySquare->col = NCOL-1;
    board->emptySquare->row = NROW-1;

    keyHandlingFunctions = malloc(sizeof(keyHandlingFunction) * NFUNCTIONS);/*key handling functions, only 4 of them*/
    keyHandlingFunctions[DOWN] = &move_down;
    keyHandlingFunctions[UP] = &move_up;
    keyHandlingFunctions[LEFT] = &move_left;
    keyHandlingFunctions[RIGHT] = &move_right;

    return board;
}

void print_board(BoardPtr board) {/*just a print function for debug reasons*/
    int i, j;
    for (i=0;i<NROW;i++) {
        for (j=0;j<NCOL;j++) {
            printf("%d,%d   ",board->squares[i][j]->row,board->squares[i][j]->col);
        }
        printf("\n");
    }
}

int model_is_valid_key(MLV_Keyboard_button key) {/*only handling arrow keys*/
    int k = key - KEYOFFSET;
    return k >= UP && k <= LEFT;
}


void model_handle_key(BoardPtr board, MLV_Keyboard_button key) {/*handling the key*/
    keyHandlingFunction f = keyHandlingFunctions[(key - KEYOFFSET)];/*looking up the binded function*/
    f(board);/*and calling it*/
}

int model_is_game_over (BoardPtr board) {/*game is over if all squares are in the right place*/
    int i, j;
    for (i=0;i<NROW;i++) {
        for (j=0;j<NCOL;j++) {
            if (((board->squares)[i][j])->row != i || ((board->squares)[i][j])->col != j)
                return 0;
        }
    }
    return 1;
}

void model_shuffle_board (BoardPtr board, unsigned int n) {/*shuffling*/
    int i, rnd;
    model_handle_key(board, UP + KEYOFFSET);/*placing the square in the center so it's more likely to be misplaced*/
    model_handle_key(board, LEFT + KEYOFFSET);
    for (i=0;i<n;i++) {
        rnd = MLV_get_random_integer(UP,LEFT);
        model_handle_key(board, rnd + KEYOFFSET);
    }
    if (model_is_game_over(board))/*ensuring the missplacement*/
        model_shuffle_board(board, n + 1);
    
}