#include <stdio.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 20

typedef struct block {
    int x, y, value;
} Block;

int type;         //Shape of the block
int position = 0; //Current position
int x_pos, y_pos; //Place in the board
Block piece[2][4];

int speed = 200;
int board[HEIGHT][WIDTH];

void draw_screen();
void time_stream();
void deploy_block();
void set_values();
void key_listener();

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

    set_values();

    printf("%c", 218);
    for(i=0; i < WIDTH*2 + 1; i++)
        printf("%c", 196);
    printf("%c\n", 191);

    for(i=0; i < HEIGHT; i++) {
        for(j=0; j < WIDTH; j++) {
            if(j == 0)
                printf("%c ", 179);

            switch(board[i][j]) {

                case 0:
                    printf("  ");
                    break;

                case 1:
                    printf("%c ", 43);
                    break;

                case 2:
                    printf("%c ", 254);
                    break;

                default:
                    break;
            }

            if(j == WIDTH-1)
                printf("%c", 179);
        }
        printf("\n");
    }

    printf("%c", 192);
    for(i=0; i < WIDTH*2 + 1; i++)
        printf("%c", 196);
    printf("%c", 217);

}

void time_stream() {
    Sleep(speed);
    system("cls");
}

void deploy_block() {

    int i, j;

    srand(time(NULL));
    type = rand() % 7;

    x_pos = 0;
    y_pos = rand() % (WIDTH-4);

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

void key_listener() {

    char ch = '=';

    if(kbhit())
        ch = tolower(getch());

    switch(ch) {
        case '=':
            x_pos++;
            break;

        case 'a':

            break;

        case 'd':

            break;

        case ' ':
            speed = 0.1;
            break;

        case 'q':

            break;

        case 'e':

            break;

        case 'p':

        default:
            break;
    }

}