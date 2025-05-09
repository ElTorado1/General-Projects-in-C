#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
int grid[4][4] = {0};
int values[] = {2,2,2,2,2,2,2,4,4,4,4}; // possibilites for number ups

void draw_screen();
void swipe_the_screen(const char a);
void add_random_tile(const char a);
int finished();
int main() {
    srand(time(NULL));
    grid[0][0] = values[rand() % 11]; // for the first appearance
    while (1) {
        draw_screen(); //update the screen while (1)
        int ch;
        ch = _getch();
        if (ch == 27)break;
        if (ch == 224) { //swiping screen and adding new numbers randomly
            ch = _getch();
            if (ch == 72) {
                swipe_the_screen('u');
                add_random_tile('u');
            }
            if (ch == 80) {
                swipe_the_screen('d');
                add_random_tile('d');
            }
            if (ch == 75) {
                swipe_the_screen('l');
                add_random_tile('l');
            }
            if (ch == 77){
                swipe_the_screen('r');
                add_random_tile('r');
            }
        }
        if (finished() == 1) { // if user reaches the 2048 the game ends.
            system("cls");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOU WOOON !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            break;
        }
    }
}

void draw_screen() {//drawing screen and demonstrating a simple table
    system("cls");
    printf("---------------------\n");
    for (int i = 0; i < 4; i++) {
        printf("|");
        for (int j = 0; j < 4; j++) {
            printf("%4d|",grid[i][j]);
        }
        printf("\n---------------------\n");
    }
}

void swipe_the_screen(const char a) {
    if (a == 'r') {
        for (int i = 0; i < 4; i++) {

            int temp_line[4] = {0}; // creates a {0,0,0,0}
            int index = 3;
            for (int j = 3; j>= 0; j--) {
                if (grid[i][j] != 0) {
                    temp_line[index--] = grid[i][j]; //It updates the line and lies to the right according to corresponding numbers like {2,0,4,0} --> {0,0,2,4}
                }
            }
            for (int j = 3; j > 0; j--) {
                if (temp_line[j] == temp_line[j - 1]) {
                    temp_line[j] *= 2; //It updates the sum of the most right equal numbers like {2,2,4,4} --> {0,4,0,8} 
                    temp_line[j-1] = 0;
                }
            }
            int final_line[4] = {0};
            int indx = 3;
            for (int j = 3; j >= 0; j--) {
                if (temp_line[j] != 0) {
                    final_line[indx--] = temp_line[j]; // It again lies it to the right like {0,4,0,8} --> {0,0,4,8}
                }
            }
            for (int j = 0; j < 4; j++) {
                grid[i][j] = final_line[j]; // Then writes over the line
            }
        }
    }
    if (a == 'l') {
        for (int i = 0; i < 4; i++) {

            int temp_line[4] = {0};
            int index = 0;
            for (int j = 0; j < 4; j++) {
                if (grid[i][j] != 0) {
                    temp_line[index++] = grid[i][j];
                }
            }
            for (int j = 0; j < 3; j++) {
                if (temp_line[j] == temp_line[j + 1]) {
                    temp_line[j] *= 2;
                    temp_line[j+1] = 0;
                }
            }
            int final_line[4] = {0};
            int indx = 0;
            for (int j = 0; j < 4; j++) {
                if (temp_line[j] != 0) {
                    final_line[indx++] = temp_line[j];
                }
            }
            for (int j = 0; j < 4; j++) {
                grid[i][j] = final_line[j];
            }
        }
    }
    if (a == 'u') {
        for (int i = 0; i < 4; i++) {

            int temp_line[4] = {0};
            int index = 0;
            for (int j = 0; j < 4; j++) {
                if (grid[j][i] != 0) {
                    temp_line[index++] = grid[j][i];
                }
            }
            for (int j = 0; j < 3; j++) {
                if (temp_line[j] == temp_line[j + 1]) {
                    temp_line[j] *= 2;
                    temp_line[j+1] = 0;
                }
            }
            int final_line[4] = {0};
            int indx = 0;
            for (int j = 0; j < 4; j++) {
                if (temp_line[j] != 0) {
                    final_line[indx++] = temp_line[j];
                }
            }
            for (int j = 0; j < 4; j++) {
                grid[j][i] = final_line[j];
            }
        }
    }
    if (a == 'd') {
        for (int i = 0; i < 4; i++) {
            int temp_col[4] = {0};
            int index = 3;
            for (int j = 3; j >= 0; j--) {
                if (grid[j][i] != 0) {
                    temp_col[index--] = grid[j][i];
                }
            }
            for (int j= 3; j > 0; j--) {
                if (temp_col[j] == temp_col[j - 1]) {
                    temp_col[j] *= 2;
                    temp_col[j - 1] = 0;
                }
            }
            int final_col[4] = {0};
            int indx = 3;
            for (int j = 3; j >= 0; j--) {
                if (temp_col[j] != 0) {
                    final_col[indx--] = temp_col[j];
                }
            }
            for (int j = 0; j < 4; j++) {
                grid[j][i] = final_col[j];
            }
        }
    }
}
void add_random_tile(const char a) {
    if (a == 'r') {
        for (int i = 0; i < 4; i++) {
            int count = 0;
            int empty_cells[4];
            for (int j = 0; j < 4; j++) {
                if (grid[i][j] == 0) {
                    empty_cells[count++] = j;
                }
            }
            if (count > 0) {
                int rand_index = rand() % count;
                grid[i][empty_cells[rand_index]] = values[rand() % 11];
            }
        }
    }
    if (a == 'l') {
        for (int i = 0; i < 4; i++) {
            int count = 0;
            int empty_cells[4];
            for (int j = 0; j < 4; j++) {
                if (grid[i][j] == 0) {
                    empty_cells[count++] = j;
                }
            }
            if (count > 0) {
                int rand_index = rand() % count;
                grid[i][empty_cells[rand_index]] = values[rand() % 11];
            }
        }
    }
    if (a == 'd') {
        for (int i = 0; i < 4; i++) {
            int count = 0;
            int empty_cells[4];
            for (int j = 0; j < 4; j++) {
                if (grid[j][i] == 0) {
                    empty_cells[count++] = j;
                }
            }
            if (count > 0) {
                int rand_index = rand() % count;
                grid[empty_cells[rand_index]][i] = values[rand() % 11];
            }
        }
    }
    if (a == 'u') {
        for (int i = 0; i < 4; i++) {
            int count = 0;
            int empty_cells[4];
            for (int j = 0; j < 4; j++) {
                if (grid[j][i] == 0) {
                    empty_cells[count++] = j;
                }
            }
            if (count > 0) {
                int rand_index = rand() % count;
                grid[empty_cells[rand_index]][i] = values[rand() % 11];
            }
        }
    }
}
int finished() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 2048) return 1;
        }
    }
    return 0;
}
