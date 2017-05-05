/**
* fifteen.c
*
* Implements Game of Fifteen (generalized to d x d).
*
* Usage: fifteen d
*
* whereby the board's dimensions are to be d x d,
* where d must be in [DIM_MIN,DIM_MAX]
*
* Note that usleep is obsolete, but it offers more granularity than
* sleep and is simpler to use than nanosleep; `man usleep` for more.
*/

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int emptyRow, int emptyCol, int moveRow, int moveCol, int tile);

/************************************************************************
**
** MAIN
**
************************************************************************/

int main(int argc, string argv[])
{
  // ensure proper usage
  if (argc != 2)
  {
    printf("Usage: fifteen d\n");
    return 1;
  }

  // ensure valid dimensions
  d = atoi(argv[1]);
  if (d < DIM_MIN || d > DIM_MAX)
  {
    printf("Board must be between %i x %i and %i x %i, inclusive.\n",
    DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
    return 2;
  }

  // open log
  FILE *file = fopen("log.txt", "w");
  if (file == NULL)
  {
    return 3;
  }

  // greet user with instructions
  greet();

  // initialize the board
  init();

  // accept moves until game is won
  while (true)
  {
    // clear the screen
    clear();

    // draw the current state of the board
    draw();

    // log the current state of the board (for testing)
    for (int i = 0; i < d; i++)
    {
      for (int j = 0; j < d; j++)
      {
        fprintf(file, "%i", board[i][j]);
        if (j < d - 1)
        {
          fprintf(file, "|");
        }
      }
      fprintf(file, "\n");
    }
    fflush(file);

    // check for win
    if (won())
    {
      printf("ftw!\n");
      break;
    }

    // prompt for move
    printf("Tile to move: ");
    //int tile = get_int();
    int tile = GetInt();

    // quit if user inputs 0 (for testing)
    if (tile == 0)
    {
      break;
    }

    // log move (for testing)
    fprintf(file, "%i\n", tile);
    fflush(file);

    // move if possible, else report illegality
    if (!move(tile))
    {
      printf("\nIllegal move.\n");
      usleep(500000);
    }

    // sleep thread for animation's sake
    usleep(500000);
  }

  // close log
  fclose(file);

  // success
  return 0;
}

/*************************************************************************************
**
** FUNCTIONS
**
**************************************************************************************/

/**
* Clears screen using ANSI escape sequences.
*/
void clear(void)
{
  printf("\033[2J");
  printf("\033[%d;%dH", 0, 0);
}

/**
* Greets player.
*/
void greet(void)
{
  clear();
  printf("WELCOME TO GAME OF FIFTEEN\n");
  usleep(2000000);
}

/**
* Initializes the game's board with tiles numbered 1 through d*d - 1
* (i.e., fills 2D array with values but does not actually print them).
*/
void init(void)
{
  int value = d*d-1;
  for (int row = 0; row < d; row++)
  {
    for (int col = 0; col < d; col++)
    {
      if (value == 2 && d%2 == 0)
        board[row][col] = 1;
      else if (value == 1 && d%2 == 0)
        board[row][col] = 2;
      else
        board[row][col] = value;
      value--;
    }
  }
}

/**
* Prints the board in its current state.
*/
void draw(void)
{
  // TODO
  for (int row = 0; row < d; row++)
  {
    for (int col = 0; col < d; col++)
    {
      if (board[row][col] == 0)
      printf("   ");
      else
      printf("%2i ", board[row][col]);
    }
    printf("\n");
  }
}

/**
* If tile borders empty space, moves tile and returns true, else
* returns false.
*/
bool move(int tile)
{
  // TODO

  // parse the game to find the empty tile and the tile to move
  //int value = d*d -1;
  int toMove[2];
  int emptyTile[2];
  for (int row = 0; row < d;  row++)
  {
    for (int col = 0; col < d; col++)
    {
      // if find tile, set tile to move position
      if (board[row][col] == tile)
      {
        toMove[0] = row;
        toMove[1] = col;
      }

      if (board[row][col] == 0)
      {
        emptyTile[0] = row;
        emptyTile[1] = col;
      }

    }
  }

  // check for proximity
  // is true => move the tile
  if ( ( toMove[0] == emptyTile[0]+1 || toMove[0] == emptyTile[0]-1 ) && toMove[1] == emptyTile[1] )
  {
    swap(emptyTile[0], emptyTile[1], toMove[0], toMove[1], tile);
    //board[][emptyTile[1]] = tile;
    //board[toMove[0]][toMove[1]] = 0;
    return true;
  }
  // is left or right
  else if ( toMove[0] == emptyTile[0] && ( toMove[1] == emptyTile[1]+1 || toMove[1] == emptyTile[1]-1 ) )
  {
    //board[emptyTile[0]][emptyTile[1]] = tile;
    //board[toMove[0]][toMove[1]] = 0;
    swap(emptyTile[0], emptyTile[1], toMove[0], toMove[1], tile);
    return true;
  }
  else
  return false;

}

/**
* Returns true if game is won (i.e., board is in winning configuration),
* else false.
*/
bool won(void)
{
  // TODO
  if (board[d-1][d-1] == 0 && board[d-1][d-2] == d*d-1)
  {
    int value = 1;
    for (int row = 0; row < d; row++)
    {
      for (int col = 0; col < d; col++)
      {
        if (value != board[row][col])
          return false;
        else if (value == d*d-1)
         return true;

         value++;
      }
    }
  }
  return false;
}

void swap(int emptyRow, int emptyCol, int moveRow, int moveCol, int tile)
{
  board[emptyRow][emptyCol] = tile;
  board[moveRow][moveCol] = 0;
}
