#ifndef _model_
#define _model_

#include "../types.h"
#include <MLV/MLV_all.h>

BoardPtr model_board_init();
void model_handle_key(BoardPtr b, MLV_Keyboard_button key);
int model_is_game_over(BoardPtr b);
void model_shuffle_board(BoardPtr b, int n);
int model_is_valid_key(MLV_Keyboard_button key);
void model_free(BoardPtr b);

#endif