#include "controller/controller.h"
#include <stdio.h>

#define DEFDIF 12

int main( int argc, char **argv){
    if (argc > 1) {
        int difficulty = strtol(argv[1], NULL, 10);
        if (difficulty < 1) {
            difficulty = 1;
            printf("Trust yourself! Setting the difficulty at %d\n",difficulty);
        }
        printf("Using difficulty: %d",difficulty);
        controller_run(difficulty * DEFDIF);
    } else {
        printf("Using default difficulty: 1\n");
        controller_run(DEFDIF);
    }
}