#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "grid.h"

void help();
int main(int argc, const char * argv[])
{
  int x_dim,y_dim;
  float rate = 0.3;
  if(argc>1)
  {
    if(strcmp(argv[1],"-h") == 0)
    {
      help();
      return 0;
    }
    if(strcmp(argv[1],"-c") == 0)
    {
      if((sscanf(argv[2],"%d",&x_dim)+sscanf(argv[3],"%d",&y_dim)) != 2)
      {
        printf("\tInvalid input. See usage.\n");
        help();
        return 0;
      }
    }
  }
  else
  {
    printf("\tStart with default configuration.\n");
    x_dim = 4;
    y_dim = 4;
  }
  printf("\nEnter w,s,a,d to move the tiles up, down, left and right respectively.\n");
  printf("Enter r to start guided change of spawn rate of new tiles.\n");
  printf("Enter q to quit the game.\n");
  printf("#####################################\n");
  srand(time(NULL));
  Grid *g  = newGrid(x_dim,y_dim);
  printGrid(g);
  spawnTile(g,rate);
  printGrid(g);
  char c;
  while(1)
  {
    scanf("%c",&c);
    if(c == 'w')
    {
      moveUp(g);
      printGrid(g);
      printf("\tspawn:\n");
      spawnTile(g,rate);
      printGrid(g);
    }
    if(c == 's')
    {
      moveDown(g);
      printGrid(g);
      printf("\tspawn:\n");
      spawnTile(g,rate);
      printGrid(g);
    }
    if(c == 'a')
    {
      moveLeft(g);
      printGrid(g);
      printf("\tspawn:\n");
      spawnTile(g,rate);
      printGrid(g);
    }
    if(c == 'd')
    {
      moveRight(g);
      printGrid(g);
      printf("\tspawn:\n");
      spawnTile(g,rate);
      printGrid(g);
    }
    if(c == 'q')
    {
      printf("#####################################\n");
      break;
    }
    if(c == 'r')
    {
      printf("\tEnter a fraction between 0 and 1 to represent rate of spawn. Default is set to 0.3\n");
      float temp;
      scanf("%f",&temp);
      if(temp <=1 && temp >=0)
      {
        rate = temp;
        printf("Spawn rate changed.\n");
      }
      else
      {
        printf("Invalid input: spawn rate will not be changed.\n");
      }
    }
    if(checkLoss(g))
    {
      printf("OH NO! You lost the game!\n");
      printf("#####################################\n");
      break;
    }
  }
  return 0;
}

void help()
{
  printf("Usage: 2048c [OPTION] [VALUE]\n");
  printf("\t-h\t\tDisplay this usage list\n");
  printf("\t-c [x] [y]\tCreate a custom game of x by y\n");
  printf("\t[N/A]\t\tStart a default game of 4 by 4\n");
}
