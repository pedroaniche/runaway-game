#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "map.h"

char drawwall[4][7] = {
    {"......"},
    {"......"},
    {"......"},
    {"......"}
};

char drawghost[4][7] = {
    {" .-.  "},
    {"| 00| "},
    {"|   | "},
    {"'^^^' "}
};

char drawhero[4][7] = {
    {" .--. "},
    {"/ _.-'"},
    {"\\  '-."},
    {" '--' "}
};

char drawpill[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char drawempty[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void printpiece(char draw[4][7], int piece) {
    printf("%s", draw[piece]);
}

void printmap(MAP* m) {
    for(int i = 0; i < m->rows; i++) {
        for(int piece = 0; piece < 4; piece++) {
            for(int j = 0; j < m->columns; j++) {
                switch (m->matrix[i][j]) {
                    case GHOST:
                        printpiece(drawghost, piece);
                        break;
                    case HERO:
                        printpiece(drawhero, piece);
                        break;
                    case PILL:
                        printpiece(drawpill, piece);
                        break;
                    case VERTICAL_WALL:
                    case HORIZONTAL_WALL:
                        printpiece(drawwall, piece);
                        break;
                    case EMPTY:
                        printpiece(drawempty, piece);
                        break;
                }
            }
            printf("\n");
        }
    }
}