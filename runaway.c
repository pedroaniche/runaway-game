#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "runaway.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;
int havepill = 0;

int ended() {
    POSITION p;
    int livinghero = findonmap(&m, &p, HERO);
    return !livinghero;
}

int ghostvalidmove(int xcurrent, int ycurrent, int* xdestiny, int* ydestiny) {
    int option[4][2] = {
        {xcurrent, ycurrent +1},
        {xcurrent +1, ycurrent},
        {xcurrent, ycurrent -1},
        {xcurrent -1, ycurrent}
    };
    srand(time(0));
    for(int i = 0; i < 10; i++) {
        int space = rand() % 4;
        if(canwalk(&m, GHOST, option[space][0], option[space][1])) {
            *xdestiny = option[space][0];
            *ydestiny = option[space][1];
            return 1;
        }
    }
    return 0;
}

void moveghost() {
    MAP copy;
    copymap(&copy, &m);
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.columns; j++) {
            if(copy.matrix[i][j] == GHOST) {
                int xdestiny;
                int ydestiny;
                int validdirection = ghostvalidmove(i, j, &xdestiny, &ydestiny);
                if(validdirection) {
                    walk(&m, i, j, xdestiny, ydestiny);
                }
            }

        }
    }
    closemap(&copy);
}

int herovalidmove(char direction) {
   return direction == UP || direction == DOWN || direction == RIGHT || direction == LEFT;
}

void movehero(char direction) {
    if(!herovalidmove(direction))
        return;
    int nextx = hero.x;
    int nexty = hero.y;
    switch(direction) {
        case UP:
            nextx--;
            break;
        case DOWN:
            nextx++;
            break;
        case RIGHT:
            nexty++;
            break;
        case LEFT:
            nexty--;
            break;
    }
    if(!canwalk(&m, HERO, nextx, nexty))
        return;
    if(isacharacter(&m, PILL, nextx, nexty)) {
        havepill++;
    }
    walk(&m, hero.x, hero.y, nextx, nexty);
    hero.x = nextx;
    hero.y = nexty;
}

void explodepill() {

    if(!havepill) return;
    
    explodepill2(hero.x, hero.y, 0, 1, 3);
    explodepill2(hero.x, hero.y, 0, -1, 3);
    explodepill2(hero.x, hero.y, 1, 0, 3);
    explodepill2(hero.x, hero.y, -1, 0, 3);

    havepill--;
}

void explodepill2(int x, int y, int sumx, int sumy, int amount) {
    if(amount == 0) return;

    int newx = x + sumx;
    int newy = y + sumy;

    if(!insidemap(&m, newx, newy)) return;
    if(isawall(&m, newx, newy)) return;

    m.matrix[newx][newy] = EMPTY;
    explodepill2(newx, newy, sumx, sumy, amount-1);
}

int main() {
    scanmap(&m);
    findonmap(&m, &hero, HERO);
    do {
        printf("Acquired pill: %s\n", (havepill ? "YES" : "NO"));
        printmap(&m);
        char command;
        scanf(" %c", &command);
        movehero(command);
        if(command == BOMB) explodepill(hero.x, hero.y, 3);
        moveghost();
    } while(!ended());
    closemap(&m);
}