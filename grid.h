#ifndef GRID_H_
#define GRID_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct _grid Grid;
Grid * newGrid(int x, int y);
void setTile(Grid * g, int x, int y, int val);
void moveLeft(Grid * g);
void moveRight(Grid * g);
void moveUp(Grid * g);
void moveDown(Grid *g);
void spawnTile(Grid *g, float rate);
int checkLoss(Grid * g); // 1 -- loss 0 -- not loss
//void fill_to_loss(Grid * g);
int printGrid(Grid * g);

#endif
