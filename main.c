#include <stdio.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 20

int speed = 200;

void draw_screen();
void time_stream();

int main()
{
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