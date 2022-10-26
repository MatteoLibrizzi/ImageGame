#include <MLV/MLV_all.h>
#include <stdio.h>
#include "view.h"
#include "../types.h"
#include "../model/model.h"

#define NSPACESTOADD (NROW-1)
#define SIZESPACESTOADD 6

static int width = IMAGESIDESIZE + ((NSPACESTOADD) * SIZESPACESTOADD), height = IMAGESIDESIZE + ((NSPACESTOADD) * SIZESPACESTOADD);
/*width and heigth depend on the image size*/
static MLV_Image *image, *darkImage;
static int partialWidth, partialHeigth;
/*width and heigth of the sub-images*/

void calculatePartialImageOutputOffset(int i, int j, int* x, int* y) {/*starting from row and col inside the image we get the position to draw the output image*/
    *x = (i * (IMAGESIDESIZE / NROW)) + (i % NROW) * SIZESPACESTOADD ;/*in the output offset we need to add the spaces!*/
    *y = (j * (IMAGESIDESIZE / NCOL)) + (j % NROW) * SIZESPACESTOADD ;
}

void calculatePartialImageInputOffset(int i, int j, int* x, int* y) {/*starting from row and col inside the image we get the position where the sub-image starts*/
    *x = i * (IMAGESIDESIZE / NROW);/*in the input offset we don't need the spaces*/
    *y = j * (IMAGESIDESIZE / NCOL);
}

void calculatePartialImageSize(int* width, int* heigth) {
    *width = IMAGESIDESIZE / NCOL;
    *heigth = IMAGESIDESIZE / NROW;
}

void view_free() {
    MLV_free_image(image);
    MLV_free_image(darkImage);
    MLV_free_window();
}

void view_exit_function(void* data) {
    int* stop = (int*) data;/*as in the example*/
    *stop = 1;
}

void drawDarkSquare (BoardPtr board) {/*drawing the dark square according to the board*/
    int xOffset, yOffset;
    calculatePartialImageOutputOffset(board->emptySquare->col, board->emptySquare->row, &xOffset, &yOffset);
            
    MLV_draw_partial_image(darkImage, 0, 0, partialWidth, partialHeigth, xOffset, yOffset);
}

int view_start(BoardPtr board) {
    MLV_create_window( "TP4", "TP4" , width, height );
    image = MLV_load_image( "assets/image.jpg" );
    darkImage = MLV_load_image( "assets/black.jpg" );/*loading the images*/

    int yOutputOffset, xOutputOffset;
    /*pixel x and y for the output (where to draw)*/
    int yOutputImage, xOutputImage;
    /*row and col for the output (where to draw)*/
    int yInputOffset, xInputOffset;
    /*pixel x and y for the input (where to read)*/
    calculatePartialImageSize(&partialWidth,&partialHeigth);
    
    for(yOutputImage=0;yOutputImage<NROW;yOutputImage++) {
        for(xOutputImage=0;xOutputImage<NCOL;xOutputImage++) {
            /*row and col for the inputImage*/
            int yInputImage = board->squares[yOutputImage][xOutputImage]->row;
            int xInputImage = board->squares[yOutputImage][xOutputImage]->col;

            /*calculating output coordinates*/
            calculatePartialImageOutputOffset(xOutputImage, yOutputImage, &xOutputOffset, &yOutputOffset);

            /*calculating input coordinates*/
            calculatePartialImageInputOffset(xInputImage, yInputImage, &xInputOffset, &yInputOffset);

            /*drawing the sub-image*/
            MLV_draw_partial_image(image,xInputOffset,yInputOffset,partialWidth,partialHeigth,xOutputOffset,yOutputOffset);
        }
    }

    /*finally drawing the dark square*/
    drawDarkSquare(board);

    /*updating window*/
    MLV_actualise_window();
    return 0;
}

int view_update(BoardPtr board) {
    int yOutputOffset, xOutputOffset;
    /*pixel x and y for the output (where to draw)*/
    int yOutputImage, xOutputImage;
    /*row and col for the output (where to draw)*/
    int yInputOffset, xInputOffset;
    /*pixel x and y for the input (where to read)*/
    calculatePartialImageSize(&partialWidth,&partialHeigth);
    
    for(yOutputImage=0;yOutputImage<NROW;yOutputImage++) {
        for(xOutputImage=0;xOutputImage<NCOL;xOutputImage++) {
            /*row and col for the inputImage*/
            int yInputImage = board->squares[yOutputImage][xOutputImage]->row;
            int xInputImage = board->squares[yOutputImage][xOutputImage]->col;

            /*calculating output coordinates*/
            calculatePartialImageOutputOffset(xOutputImage, yOutputImage, &xOutputOffset, &yOutputOffset);

            /*calculating input coordinates*/
            calculatePartialImageInputOffset(xInputImage, yInputImage, &xInputOffset, &yInputOffset);

            /*drawing the sub-image*/
            MLV_draw_partial_image(image,xInputOffset,yInputOffset,partialWidth,partialHeigth,xOutputOffset,yOutputOffset);
        }
    }

    /*finally drawing the dark square*/
    drawDarkSquare(board);

    /*updating window*/
    MLV_actualise_window();
    return 0;
}
