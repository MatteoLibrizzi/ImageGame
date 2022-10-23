#ifndef _model_
#define _model_

#include "../types.h"
#include <MLV/MLV_all.h>

BoardPtr board_init();
void printBoard(BoardPtr b);
void handleKey(BoardPtr b, MLV_Keyboard_button key);
int isGameOver(BoardPtr b);
void shuffleBoard(BoardPtr b, int n);
int isValidKey(MLV_Keyboard_button key);

#endif