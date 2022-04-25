#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

void copymap(MAP* destiny, MAP* origin) {
    destiny->rows = origin->rows;
    destiny->columns = origin->columns;
    allocatemap(destiny);
    for(int i = 0; i < origin->rows; i++) {
        strcpy(destiny->matrix[i], origin->matrix[i]);
    }
}

int isawall(MAP* m, int x, int y) {
    return m->matrix[x][y] == VERTICAL_WALL || m->matrix[x][y] == HORIZONTAL_WALL;
}

int isacharacter(MAP* m, char character, int x, int y) {
    return m->matrix[x][y] == character;
}

int canwalk(MAP* m, char character, int x, int y) {
    return insidemap(m, x, y) && !isawall(m, x, y) && !isacharacter(m, character, x, y);
}

void walk(MAP* m, int xorigin, int yorigin, int xdestiny, int ydestiny) {
    char character = m->matrix[xorigin][yorigin];
    m->matrix[xdestiny][ydestiny] = character;
    m->matrix[xorigin][yorigin] = EMPTY;
}

int insidemap(MAP* m, int x, int y) {
    if(x >= m->rows)
        return 0;
    if(y >= m->columns)
        return 0;
    return 1;
}

int findonmap(MAP* m, POSITION* p, char c) {
    for(int i = 0; i < m->rows; i++) {
        for(int j = 0; j < m->columns; j++) {
            if(m->matrix[i][j] == c) {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}

void closemap(MAP* m) {
    for(int i = 0; i < m->rows; i++) {
        free(m->matrix[i]);
    }
    free(m->matrix);
}

void allocatemap(MAP* m) {
    m->matrix = malloc(sizeof(char*) * m->rows);
    for(int i = 0; i < m->rows; i++) {
        m->matrix[i] = malloc(sizeof(char) * (m->columns+1));
    }
}

void scanmap(MAP* m) {
    FILE* f = fopen("map.txt", "r");
    if(f == 0) {
        printf("Map reading error\n");
        exit(1);
    }
    fscanf(f, "%d %d", &(m->rows), &(m->columns));
    allocatemap(m);
    for(int i = 0; i < m->rows; i++) {
        fscanf(f, "%s", m->matrix[i]);
    }
    fclose(f);
}