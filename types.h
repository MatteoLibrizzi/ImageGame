#ifndef _types_
#define _types_
#include <MLV/MLV_all.h>

#define IMAGESIDESIZE 512
#define NCOL 4
#define NROW 4

typedef struct square {
    int row;
    int col;
} Square;
typedef Square* SquarePtr;

typedef struct board {
    SquarePtr squares[NROW][NCOL];
    SquarePtr emptySquare;
} Board;
typedef Board * BoardPtr;

typedef void (*keyHandlingFunction)(BoardPtr);

#endif