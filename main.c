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
int score = 0;
int level = 1;
int board[HEIGHT][WIDTH];

void draw_screen();
void time_stream();
void deploy_block();
void set_values();
void key_listener();
int check_collision();
void build_ground();
void spin(int dir);
int check_spin_collision();
int check_row_fill();
void clear_row(int row);

int main()
{
    int row;

    deploy_block();

    while(1) {
        draw_screen();
        key_listener();
        if(check_collision() == 0) {
            build_ground();
            deploy_block();
        }
        row = check_row_fill();
        if(row != -1) {
            clear_row(row);
            deploy_block();
        }
        time_stream();
    }
}

void draw_screen() {

    int i, j;

    set_values();

    printf("Score: %d\nLevel: %d\n\n", score, level);

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
            if(check_collision() != -1)
                y_pos--;
            break;

        case 'd':
            if(check_collision() != 1)
                y_pos++;
            break;

        case ' ':
            speed = 0.1;
            break;

        case 'q':
            if(!check_spin_collision())
                spin(-1); //Spin left
            break;

        case 'e':
            if(!check_spin_collision())
                spin(1); //Spin right
            break;

        case 'p':

        default:
            break;
    }

}

int check_collision() {

    int i, j;

    for(i=0; i<2; i++) {
        for(j=0; j<4; j++) {
            if(piece[i][j].value == 1 && (piece[i][j].x == HEIGHT-1 || board[piece[i][j].x+1][piece[i][j].y] == 2))
                return 0; //Bottom collision*/
        }
    }

    for(i=0; i<2; i++) {
        for(j=0; j<4; j++) {
            if(piece[i][j].value == 1 && (piece[i][j].y == WIDTH-1 || board[piece[i][j].x][piece[i][j].y+1] == 2))
                return 1; //Right side collision
        }
    }

    for(i=0; i<2; i++) {
        for(j=0; j<4; j++) {
            if(piece[i][j].value == 1 && (piece[i][j].y == 0 || board[piece[i][j].x][piece[i][j].y-1] == 2))
                return -1; //Left side collision
        }
    }

    return 2; //No collision
}

void build_ground() {

    int i, j;

    for(i=0; i<2; i++) {
        for(j=0; j<4; j++) {
            if(piece[i][j].value == 1)
                board[piece[i][j].x][piece[i][j].y] = 2;
        }
    }

    score += 2;
}

void spin(int dir) {

    int positions;

    if(type < 2)
        positions = type;
    else
        positions = 3;

    position += dir;
    if(position == positions + 1)
        position = 0;
    else {
        if(position == -1)
            position = positions;
    }

}

int check_spin_collision() {

    if((piece[1][1].y == 0 || piece[1][1].y == WIDTH-1) || (type == 1 && (piece[0][1].y == 0 || piece[0][1].y == WIDTH-1)))
        return 1;
    else
        return 0;

}

int check_row_fill() {

    int i, j, aux;

    for(i=0; i < HEIGHT; i++) {
        aux = 0;
        for(j=0; j < WIDTH; j++) {
            if(board[i][j] == 2)
                aux++;
        }
        if(aux == WIDTH)
            return i;
    }

    return -1;
}

void clear_row(int row) {

    int i, j, tmp;

    for(i=row; i>=0; i--) {
        for(j=WIDTH-1; j>=0; j--) {
            if(i>0) {
                tmp = board[i-1][j];
                board[i-1][j] = board[i][j];
                board[i][j] = tmp;
            } else
                board[i][j] = 0;
        }
    }
    score += 10;
}