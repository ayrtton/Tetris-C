#include <stdio.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 20

typedef struct block {
    int x, y, value;
} Block;

int type;         //Shape of the block
Block piece[2][4];

int speed = 200;

void draw_screen();
void time_stream();
void deploy_block();
void set_values();

int main()
{
    deploy_block();

    while(1) {
        draw_screen();
        time_stream();
    }
}

void draw_screen() {

    int i, j;

    for(i=0; i < WIDTH+2; i++)
        printf("* ");
    printf("\n");

    for(i=0; i < HEIGHT; i++) {
        for(j=0; j < WIDTH; j++) {
            if(j == 0)
                printf("* ");
            printf("  ");
            if(j == WIDTH-1)
                printf("* ");
        }
        printf("\n");
    }

    for(i=0; i < WIDTH+2; i++)
        printf("* ");

}

void time_stream() {
    Sleep(speed);
    system("cls");
}

void deploy_block() {

    int i, j;

    srand(time(NULL));
    type = rand() % 7;

    switch(type) {

        case 0:                                    //O-block
            for(i=0; i<2; i++)
                for(j=0; j<4; j++)
                    piece[i][j].value = (j < 2);
            break;

        case 1:                                     //I-block
            for(i=0; i<2; i++)
                for(j=0; j<4; j++)
                    piece[i][j].value = (i == 0);
            break;

        case 2:                                    //J-block
            for(i=0; i<2; i++)
                for(j=0; j<4; j++)
                    piece[i][j].value = (i == j || (i == 1 && j < 3));
            break;

        case 3:                                    //L-block
            for(i=0; i<2; i++)
                for(j=0; j<4; j++)
                    piece[i][j].value = (j == 2 || (i == 1 && j < 3));
            break;

        case 4:                                    //S-block
            for(i=0; i<2; i++)
                for(j=0; j<4; j++)
                    piece[i][j].value = (i+j > 0 && i+j < 3);
            break;

        case 5:                                    //Z-block
            for(i=0; i<2; i++)
                for(j=0; j<4; j++)
                    piece[i][j].value = ((i == 0 && j < 2) || (i == 1 && j > 0 && j < 3));
            break;

        case 6:                                    //T-block
            for(i=0; i<2; i++)
                for(j=0; j<4; j++)
                    piece[i][j].value = ((j == 1) || (i == 1 && j < 3));
            break;

        default:
            break;

    }

}

void set_values() {
    int i, j;

    for(i=0; i < HEIGHT; i++)
        for(j=0; j < WIDTH; j++)
            if(board[i][j] != 2)
                board[i][j] = 0;

    switch(position) {

        case 0:
            for(i = 0; i<2; i++) {
                for(j = 0; j<4; j++) {
                    piece[i][j].y = j + y_pos;
                    piece[i][j].x = i + x_pos;
                }
            }
            break;

        case 1:
            for(i=0; i<2; i++) {
                for(j=0; j<4; j++) {
                    piece[i][j].y = 2-i + y_pos;
                    piece[i][j].x = j + x_pos;
                }
            }
            break;

        case 2:
            for(i=0; i<2; i++) {
                for(j=0; j<4; j++) {
                    piece[i][j].y = 2-j + y_pos;
                    piece[i][j].x = 2-i + x_pos;
                }
            }
            break;

        case 3:
            for(i=0; i<2; i++) {
                for(j=0; j<4; j++) {
                    piece[i][j].y = i + y_pos;
                    piece[i][j].x = 2-j + x_pos;
                }
            }
            break;

        default:
            break;

    }

    for(i=0; i<2; i++) {
        for(j=0; j<4; j++) {
            if(piece[i][j].value == 1)
                board[piece[i][j].x][piece[i][j].y] = 1;
        }
    }
}

