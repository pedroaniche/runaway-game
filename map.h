#ifndef _MAP_H_
#define _MAP_H_

#define HERO '@'
#define GHOST 'G'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'

struct map {
    char** matrix;
    int rows;
    int columns;
};

typedef struct map MAP;

struct position {
    int x;
    int y;
};

typedef struct position POSITION;

void scanmap(MAP* m);
void allocatemap(MAP* m);
void closemap(MAP* m);

int canwalk(MAP* m, char character, int x, int y);
int insidemap(MAP* m, int x, int y);
int isawall(MAP* m, int x, int y);
int isacharacter(MAP* m, char character, int x, int y);

void copymap(MAP* destiny, MAP* origin);
void walk(MAP* m, int xorigin, int yorigin, int xdestiny, int ydestiny);

int findonmap(MAP* m, POSITION* p, char c);

#endif