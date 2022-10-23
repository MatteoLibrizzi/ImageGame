#include <MLV/MLV_all.h>
#include <stdio.h>
#include "view.h"
#include "../types.h"
#include "../model/model.h"

#define NSPACESTOADD (NROW-1)
#define SIZESPACESTOADD 6

static int width = IMAGESIDESIZE + ((NSPACESTOADD) * SIZESPACESTOADD), height = IMAGESIDESIZE + ((NSPACESTOADD) * SIZESPACESTOADD);
static MLV_Image *image, *darkImage;
static int stop = 0;
static int partialWidth, partialHeigth;

void calculatePartialImageOutputOffset(int i, int j, int* x, int* y) {
    *x = (i * (IMAGESIDESIZE / NROW)) + (i %NROW) * SIZESPACESTOADD ;/*in the output offset we need to add the spaces!*/
    *y = (j * (IMAGESIDESIZE / NCOL)) + (j%NROW) * SIZESPACESTOADD ;
}

void calculatePartialImageInputOffset(int i, int j, int* x, int* y) {
    *x = i * (IMAGESIDESIZE / NROW);/*in the input offset we don't need the spaces*/
    *y = j * (IMAGESIDESIZE / NCOL);
}

void calculatePartialImageSize(int* width, int* heigth) {
    *width = IMAGESIDESIZE / NCOL;
    *heigth = IMAGESIDESIZE / NROW;
}

void freeStuff() {
    MLV_free_image(image);
    MLV_free_image(darkImage);
    MLV_free_window();
}

void exit_function(void* data) {
    int* stop = (int*) data;
    *stop = 1;
}

void drawDarkSquare (BoardPtr board) {
    int xOffset, yOffset;
    calculatePartialImageOutputOffset(board->emptySquare->col, board->emptySquare->row, &xOffset, &yOffset);
    printf("Params: %d %d %d %d %d %d\n", 0,0,partialWidth,partialHeigth,xOffset,yOffset);
            
    MLV_draw_partial_image(darkImage, 0, 0, partialWidth, partialHeigth, xOffset, yOffset);
}

int view_start(BoardPtr board) {

    MLV_create_window( "TP4", "TP4" , width, height );
    image = MLV_load_image( "imageFull.jpg" );
    darkImage = MLV_load_image( "black.jpg" );
    int yOutputOffset, xOutputOffset;
    int yOutputImage, xOutputImage;
    int yInputOffset, xInputOffset;
    calculatePartialImageSize(&partialWidth,&partialHeigth);

    
    for(yOutputImage=0;yOutputImage<NROW;yOutputImage++) {
        for(xOutputImage=0;xOutputImage<NCOL;xOutputImage++) {
            int yInputImage = board->squares[yOutputImage][xOutputImage]->row;
            int xInputImage = board->squares[yOutputImage][xOutputImage]->col;
            calculatePartialImageOutputOffset(xOutputImage, yOutputImage, &xOutputOffset, &yOutputOffset);

            calculatePartialImageInputOffset(xInputImage, yInputImage, &xInputOffset, &yInputOffset);

            MLV_draw_partial_image(image,xInputOffset,yInputOffset,partialWidth,partialHeigth,xOutputOffset,yOutputOffset);
        }
    }

    drawDarkSquare(board);
    MLV_actualise_window();
    return 0;
}

int view_update(BoardPtr board) {
    int yOutputOffset, xOutputOffset;
    int yOutputImage, xOutputImage;
    int yInputOffset, xInputOffset;
    for(yOutputImage=0;yOutputImage<NROW;yOutputImage++) {
        for(xOutputImage=0;xOutputImage<NCOL;xOutputImage++) {
            int yInputImage = board->squares[yOutputImage][xOutputImage]->row;
            int xInputImage = board->squares[yOutputImage][xOutputImage]->col;
            calculatePartialImageOutputOffset(xOutputImage, yOutputImage, &xOutputOffset, &yOutputOffset);

            calculatePartialImageInputOffset(xInputImage, yInputImage, &xInputOffset, &yInputOffset);
            printf("Params: %d %d %d %d %d %d\n", xInputOffset,yInputOffset,partialWidth,partialHeigth,xOutputOffset,yOutputOffset);
            
            
            MLV_draw_partial_image(image,xInputOffset,yInputOffset,partialWidth,partialHeigth,xOutputOffset,yOutputOffset);
            
        }
    }
    
    drawDarkSquare(board);
    MLV_actualise_window();
    return 0;
}
