#ifndef _RUNAWAY_H_
#define _RUNAWAY_H_

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define BOMB 'b'

void movehero(char direction);
int herovalidmove(char direction);

void moveghost();
int ghostvalidmove(int xcurrent, int ycurrent, int* xdestiny, int* ydestiny);

void explodepill();
void explodepill2(int x, int y, int sumx, int sumy, int amount);

int ended();

#endif