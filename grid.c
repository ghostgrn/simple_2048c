#include "grid.h"
#include <math.h>


struct _grid
{
  int x;
  int y;
  int * data;
};

Grid * newGrid(int x, int y)
{
  if(x<=0||y<=0)
    {
      return NULL;
    }
  Grid * g = malloc(sizeof(Grid));
  g->x = x;
  g->y = y;
  g->data = malloc(x*y*sizeof(int));

  for(int i=0;i<x*y;i++)
    {
      g->data[i] = 0;
    }
  return g;
}

int getTile(Grid * g, int x, int y)
{
  if(!g)
    {
      return -1;
    }
  int x_dim = g->x;
  int req_num = ((y-1)*x_dim) + (x-1);
  return g->data[req_num];
}

void setTile(Grid * g, int x, int y, int val)
{
  if(!g)
    {
      return;
    }
  int x_dim = g->x;
  int req_num = ((y-1)*x_dim) + (x-1);
  g->data[req_num] = val;
}


int printGrid(Grid * g)
{
  if(!g)
    {
      return -1;
    }
  printf("-----------------------\n");
  int x_dim = g->x;
  int y_dim = g->y;
  for(int i = 1; i<= y_dim; i++)
  {
    for(int j = 1; j<= x_dim; j++)
    {
      int temp = getTile(g,j,i);
      if(temp != 0)
      {
        printf("%5d",temp);
      }
      else
      {
        printf("%5c",' ');
      }
    }
    printf("\n");
  }
  printf("-----------------------\n");
  return 0;
}

int countEmpty(Grid const * g)
{
  if(!g)
  {
    return -1;
  }
  int count=0;
  int size = g->x * g->y;
  for(int i =0; i<size; i++)
  {
    if(g->data[i] == 0)
    {
      count++;
    }
  }
  //printf("empty=%d\n",count);
  return count;
}

//failed

/*void list_sample(int * in, int n, int k, int * out)
{
  int i;
  int * res = malloc(k*sizeof(int));
  for(int i =0; i< k;i++)
  {
    res[i] = in[i];
  }
  for(int i = 0; i<k;i++)
  {
    printf("res =%d ",res[i]);
    //out[i] =
  }
  for(;i < n;i++)
  {
    int j = rand()%(i+1);
    if(j < k)
    {
      res[j] = in[i];
    }
  }
  for(int i = 0; i<k;i++)
  {
    printf("res =%d ",res[i]);
    //out[i] = res[i];
  }

  out = res;
  free(res);
}*/


int rdm(int size)
{
  int i,n;
  int numNums  =0;
  int *numArr = NULL;
  if(size >=0)
  {
    if(numArr != NULL)
    {
      free(numArr);
    }
    if((numArr = (int*)malloc(sizeof(int)*size)) ==  NULL)
    {
      return -2;
    }
    for(i=0;i<size;i++)
    {
      numArr[i] = i;
    }
    numNums = size;
  }
  if(numNums ==0)
  {
    return -1;
  }
  n = rand()%numNums;
  i = numArr[n];
  numArr[n] = numArr[numNums-1];
  numNums--;
  if(numNums == 0)
  {
    free(numArr);
    numArr = 0;
  }
  return i;
}

void sample(int range, int k, int *out)
{
  int i;
  i=rdm(range);   //range = 20 , out = 0-19
  for(int j =0;j<k;j++)
  {
    out[j] = i;
    i = rdm(range);
  }
}


void spawnTile(Grid * g, float rate)
{
  if(!g)
  {
    return;
  }
  int empty = countEmpty(g);
  if(empty == 0)
  {
    return;
  }
  int should_fill = (int)(ceil((double)(empty * rate)));
  //printf("should_fill=%d\n",should_fill);
  int size = g->x * g->y;
  if(empty == 1)
  {
    for(int i =0 ; i<size; i++)
    {
      if(g->data[i] == 0 )
      {
        g->data[i] = 2;
      }
    }
    return;
  }
  int empty_list[empty];
  int empty_list_counter=0;
  for(int i=0;i < size;i++)
  {
    if(g->data[i] == 0)
    {
      empty_list[empty_list_counter] = i;
      empty_list_counter++;
    }
  }
  int chosen_tile[should_fill];   //index of empty_list
  //printf("cp1\n");
  sample(empty,should_fill,chosen_tile);
  //list_sample(empty_list,empty,should_fill,chosen_tile);
  //printf("cp2\n");
  printf("\n");
  for(int c =0 ; c<should_fill;c++)
  {
    //printf("change %d to 2\n",chosen_tile[c]);
    g->data[empty_list[chosen_tile[c]]] = 2;
  }
}

//failed

  /*for(int fill_count = 1; fill_count <= should_fill; fill_count ++)
  {
    int random_choose = (rand() % (empty))+1;
    printf("random_choose=%d\n",random_choose);
    int empty_count = 0;
    for(int i =0 ; i<size; i++)
    {
      if(g->data[i] == 0 )
      {
        empty_count++;
      }
      printf("empty_count=%d\n",empty_count);
      if(empty_count == random_choose)
      {
        printf("setting %d to 2\n",i);
        g->data[i] = 2;
        break;
      }
    }
  }*/


int checkLoss(Grid * g)
{
  int is_loss = 1;    //init as true(loss)
  for(int i = 1 ; i<=g->x;i++)
  {
    for(int j = 1; j<=g->y; j++)
    {
      int temp = getTile(g,i,j);
      if(i-1<1 && j-1<1)    //top left corner
      {
        int down = getTile(g,i,j+1);
        int right = getTile(g,i+1,j);
        if(temp == down || temp == right || down == 0 || right == 0)
        {
          is_loss = 0;
        }
      }

      if(i+1>g->x && j-1<1)    //top right corner
      {
        int down = getTile(g,i,j+1);
        int left = getTile(g,i-1,j);
        if(temp == down || temp == left || down == 0 || left == 0)
        {
          is_loss = 0;
        }
      }

      if(i-1<1 && j+1>g->y)    //bottom left corner
      {
        int up = getTile(g,i,j-1);
        int right = getTile(g,i+1,j);
        if(temp == up || temp == right || up == 0 || right == 0)
        {
          is_loss = 0;
        }
      }

      if(i+1>g->x && j+1>g->y)    //bottom right corner
      {
        int up = getTile(g,i,j-1);
        int left = getTile(g,i-1,j);
        if(temp == up || temp == left || up == 0 || left == 0)
        {
          is_loss = 0;
        }
      }

      if(i-1<1 && j-1>=1 && j+1<=g->y)   //left most column
      {
        int up = getTile(g,i,j-1);
        int down = getTile(g,i,j+1);
        int right = getTile(g,i+1,j);
        if(temp == up || temp == down || temp == right
            || down == 0 || right == 0 || up == 0)
        {
          is_loss = 0;
        }
      }

      if(i+1>g->x && j-1>=1 && j+1<=g->y)   //right most column
      {
        int up = getTile(g,i,j-1);
        int down = getTile(g,i,j+1);
        int left = getTile(g,i-1,j);
        if(temp == up || temp == down || temp == left
            || down == 0 || left == 0 || up == 0)
        {
          is_loss = 0;
        }
      }

      if(j == 1 && i+1<=g->x && i>=2)   //up most row
      {
        int left = getTile(g,i-1,j);
        int down = getTile(g,i,j+1);
        int right = getTile(g,i+1,j);
        if(temp == left || temp == down || temp == right
            || down == 0 || right == 0 || left == 0)
        {
          is_loss = 0;
        }
      }

      if(j == g->y && i+1<=g->x && i>=2)   //down most row
      {
        int up = getTile(g,i,j-1);
        int left = getTile(g,i-1,j);
        int right = getTile(g,i+1,j);
        if(temp == up || temp == left || temp == right
            || left == 0 || right == 0 || up == 0)
        {
          is_loss = 0;
        }
      }

      if(i+1 <= g->x && i>=2 && j>=2 && j+1<=g->y)   // middle
      {
        int up = getTile(g,i,j-1);
        int down = getTile(g,i,j+1);
        int left = getTile(g,i-1,j);
        int right = getTile(g,i+1,j);
        if(temp == up || temp == down || temp == left || temp == right
            || down == 0 || right == 0 || up == 0 || left == 0)
        {
          is_loss = 0;
        }
      }
    }
  }
  return is_loss;
}

void fill_to_loss(Grid * g)
{
  int count = 1;
  for(int i =1;i<=g->x;i++)
  {
    for(int j=1;j<=g->y;j++)
    {
      setTile(g,i,j,count);
      count++;
    }
  }
}

void swap_in_row(Grid *g, int x, int y1, int y2)
{
  int temp = getTile(g,x,y1);
  setTile(g,x,y1,getTile(g,x,y2));
  setTile(g,x,y2,temp);
}

void moveUp(Grid * g) //column by column
{
  for(int i=1;i<=g->x;i++)   //column scan
  {
    int position = 1;
    for(int j=1;j<=g->y;j++)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,i,position,getTile(g,i,j));
        if(position != j)
        {
          setTile(g,i,j,0);
        }
        position++;
      }
    }
    //zeros are moved up. Then look for same number that is adjacent
    //finding matches
    for(int j=1;j<=g->y - 1;j++)
    {
      if(getTile(g,i,j) == getTile(g,i,j+1))   //combine
      {
        setTile(g,i,j,getTile(g,i,j)+getTile(g,i,j+1));
        setTile(g,i,j+1,0);
      }
    }
    //all same numbers are combined
    //move the zeros down again
    position = 1; //reset the position
    for(int j=1;j<=g->y;j++)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,i,position,getTile(g,i,j));
        if(position != j)
        {
          setTile(g,i,j,0);
        }
        position++;
      }
    }
  }
}

void moveDown(Grid * g)
{
  for(int i=1;i<=g->x;i++)   //column scan
  {
    int position = g->y;
    for(int j=g->y;j>=1;j--)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,i,position,getTile(g,i,j));
        if(position != j)
        {
          setTile(g,i,j,0);
        }
        position--;
      }
    }
    //zeros are moved up. Then look for same number that is adjacent
    //finding matches
    for(int j=g->y;j>=2;j--)
    {
      if(getTile(g,i,j) == getTile(g,i,j-1))   //combine down to up
      {
        setTile(g,i,j,getTile(g,i,j)+getTile(g,i,j-1));
        setTile(g,i,j-1,0);
      }
    }
    //all same numbers are combined
    //move the zeros down again
    position = g->y; //reset the position
    for(int j=g->y;j>=1;j--)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,i,position,getTile(g,i,j));
        if(position != j)
        {
          setTile(g,i,j,0);
        }
        position--;
      }
    }
  }
}

void moveLeft(Grid * g)
{
  for(int j=1;j<=g->y;j++)   //row scan
  {
    int position = 1;
    for(int i=1;i<=g->x;i++)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,position,j,getTile(g,i,j));
        if(position != i)
        {
          setTile(g,i,j,0);
        }
        position++;
      }
    }
    //zeros are moved up. Then look for same number that is adjacent
    //finding matches
    for(int i=1;i<=g->x - 1;i++)
    {
      if(getTile(g,i,j) == getTile(g,i+1,j))   //combine
      {
        setTile(g,i,j,getTile(g,i,j)+getTile(g,i+1,j));
        setTile(g,i+1,j,0);
      }
    }
    //all same numbers are combined
    //move the zeros down again
    position = 1; //reset the position
    for(int i=1;i<=g->x;i++)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,position,j,getTile(g,i,j));
        if(position != i)
        {
          setTile(g,i,j,0);
        }
        position++;
      }
    }
  }
}

void moveRight(Grid * g)
{
  for(int j=1;j<=g->y;j++)   //row scan
  {
    int position = g->x;
    for(int i=g->x;i>=1;i--)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,position,j,getTile(g,i,j));
        if(position != i)
        {
          setTile(g,i,j,0);
        }
        position--;
      }
    }
    //zeros are moved up. Then look for same number that is adjacent
    //finding matches
    for(int i=g->x;i>=2;i--)
    {
      if(getTile(g,i,j) == getTile(g,i-1,j))   //combine
      {
        setTile(g,i,j,getTile(g,i,j)+getTile(g,i-1,j));
        setTile(g,i-1,j,0);
      }
    }
    //all same numbers are combined
    //move the zeros down again
    position = g->x; //reset the position
    for(int i=g->x;i>=1;i--)
    {
      if(getTile(g,i,j) != 0)
      {
        setTile(g,position,j,getTile(g,i,j));
        if(position != i)
        {
          setTile(g,i,j,0);
        }
        position--;
      }
    }
  }
}
