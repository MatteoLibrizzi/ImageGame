#include <stdio.h>
#include "controller.h"
#include "../model/model.h"
#include "../view/view.h"
#include "../types.h"

int controller_run(unsigned int difficulty) {
    int stop = 0;/*stopping when ==1*/
    BoardPtr board = model_board_init();

    /*model_shuffle_board(board,difficulty);/*shuffling the board according to requirements*/

    MLV_execute_at_exit(view_exit_function,&stop);/*binding the function to execute at exit (in view.c)*/
    view_start(board);/*view element start*/

    MLV_Keyboard_button key = 0;/*last pressed key*/
    while (!stop) {
        MLV_wait_keyboard_or_seconds(&key, NULL, NULL, 1);

        if (!stop && key!=0 && model_is_valid_key(key)) {/*if the key is valid and the game is on*/
            model_handle_key(board, key);/*handle the key*/
            key = 0;/*set the key as handled*/
            view_update(board);/*update the board*/
            if (model_is_game_over(board)) {/*check if the game is over*/
                view_exit_function(&stop);/*if so exit*/
                printf("Congratulations!\n");
            }
        }
        
    }
    view_free();/*free the view*/
    model_free(board);/*free the board*/

    return 0;
}