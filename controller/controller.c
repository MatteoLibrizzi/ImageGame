#include <stdio.h>
#include "controller.h"
#include "../model/model.h"
#include "../view/view.h"
#include "../types.h"

int run_controller() {
    int stop = 0;
    BoardPtr board = board_init();

    /*shuffleBoard(board,10);*/

    MLV_execute_at_exit(exit_function,&stop);
    view_start(board);
    MLV_Keyboard_button key = 0;

    while (!stop) {
        MLV_wait_keyboard_or_seconds(&key, NULL, NULL, 1);

        if (!stop && key!=0 && isValidKey(key)) {
            handleKey(board, key);
            key = 0;
            view_update(board);
        }
        /*
        if (isGameOver(board)) {
            exit_function(&stop);
        }
        */
    }
    freeStuff();

    return 0;
}