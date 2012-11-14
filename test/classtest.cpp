#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define NMAX 10
#define NSUB 4

struct Subcell
{
  int u, v;
};

class Cell
{
  public:
  int x, y;

  Subcell subcell[NSUB];

  Cell();

  void print();
};

Cell::Cell(): x(0), y(0)
{
  for(int i = 0; i < NSUB; i++)
  {
    subcell[i].u = 0;
    subcell[i].v = 0;
  }
}

void Cell::print()
{
  printf("(%d %d)", x, y);

  printf("\t(%d %d) (%d %d)\n", subcell[0].u, subcell[0].v, subcell[1].u, subcell[1].v);
  printf("\t(%d %d) (%d %d)\n", subcell[2].u, subcell[2].v, subcell[3].u, subcell[3].v);
}

int main(void)
{
  Cell cell[NMAX*NMAX];

  for(int i = 0; i < NMAX; i++)
  {
    for(int j = 0; j < NMAX; j++)
    {
      int offset = i + NMAX*j;
      cell[offset].x = i;
      cell[offset].y = j;

      cell[offset].subcell[0].u = cell[offset].x;
      cell[offset].subcell[0].v = cell[offset].y;

      cell[offset].subcell[1].u = cell[offset].x;
      cell[offset].subcell[1].v = cell[offset].y + 1;

      cell[offset].subcell[2].u = cell[offset].x + 1;
      cell[offset].subcell[2].v = cell[offset].y;

      cell[offset].subcell[3].u = cell[offset].x + 1;
      cell[offset].subcell[3].v = cell[offset].y + 1;

      cell[offset].print();
    }
  }
}
