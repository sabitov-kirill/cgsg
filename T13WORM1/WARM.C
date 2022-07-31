#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "WARM.h"

/* Structure storing x and y coordinate of smth */
typedef struct
{
  int x, y;
} POS;

/* Enum of cell types */
typedef enum
{
  CELL_FREE,
  CELL_WARM,
  CELL_SHROOM,
  CELL_MAGICSHROOM
} CELL;

/* Field Size*/
#define FIELD_H 24
#define FIELD_W 42

/* Cell type of every point if field */
static CELL Field[FIELD_H][FIELD_W];

/* Position of head and every part of tail */
POS head, tail[FIELD_H * FIELD_H], newpos;

/* Tail lenth and direction */
int tail_len, dir;

/* Current and max score */
int score, high_score;

/* Boolean variable indicating whether the game is over */
int is_game_go;

/* The coordinates of the change in the position of the worm */
POS mov[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} }; 

/* Frame time */
double frame_time = 0.1;

/* Delay creating function */
void Wait( double delay )
{
  double goal;
  goal = delay * CLOCKS_PER_SEC + clock();
  while (goal > clock())
    ;
}

/* Field clearing function */
void ClearField( void )
{
  int x, y;
  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
      Field[y][x] = CELL_FREE;
}

/* Setting up food on the field function */
void FoodInit( int Amount )
{
  int i, x, y, chance;
 
  for (i = 0; i < Amount; i++)
    {
      do
      {
          x = rand() % FIELD_W;
          y = rand() % FIELD_H;
      } while (Field[y][x] != CELL_FREE);

      chance = rand() % 100;

      if (chance < 30)
        Field[y][x] = CELL_MAGICSHROOM;
      else
        Field[y][x] = CELL_SHROOM;
    }
}

/* Game starting function */
void GameStart( void )
{
  FILE* score_f;

  /* Loading previous max score from file */
  score_f = fopen("score.bin", "a+b");
  fscanf(score_f, "%d", &high_score);
  
  is_game_go = 1;

  tail_len = 1;
  dir = 1;
  score = 1;

  head.x = 2;
  head.y = 1;

  tail[0].x = 1;
  tail[0].y = 1;

  FoodInit(1);
}

/* Game pause function */
void GamePause( void )
{
  if (is_game_go == 1)
    DrawStr("PAUSE", 464, FIELD_H * ELEMENT_H, 235, 239, 0);
  if (is_game_go == 0)
    ClearChars(464, FIELD_H * ELEMENT_H, 5);
  is_game_go = !is_game_go;
}

/* Game ending function */
void GameOver( void )
{
  FILE* score_f;
  
  is_game_go = 0;

  /* Writing new max score in file */
  if (score > high_score)
  {
    high_score = score;
    score_f = fopen("score.bin", "wb");
    fprintf(score_f, "%d", high_score);
  }

  DrawStr("GAME IS OVER! 'R' TO RESTART", 280, FIELD_H * ELEMENT_H, 255, 0, 0);
}

/* Game restarting function */
void GameRestart( void )
{
  ClearField();

  ClearChars(280, FIELD_H * ELEMENT_H, 29);
  
  GameStart();
}

/* Score and maximum score initialisation function */
void ScoreInit( void )
{
  DrawStr("SCORE:", 0, FIELD_H * ELEMENT_H, 255, 255, 255);
  ClearChars(48, FIELD_H * ELEMENT_H, 6);
  DrawNum(score, 6, 48, FIELD_H * ELEMENT_H, 255, 255, 255);

  DrawStr("HIGHSCORE:", 104, FIELD_H * ELEMENT_H, 255, 255, 255);
  ClearChars(184, FIELD_H * ELEMENT_H, 6);
  DrawNum(high_score, 6, 184, FIELD_H * ELEMENT_H, 255, 255, 255);
}

/* Warm possition changing function */
void WarmMoving( void )
{
  int i;
  
  Wait(frame_time);

  /* Setting Up nest pos of warm */
  newpos.x = (head.x + mov[dir].x);
  newpos.y = (head.y + mov[dir].y);

  newpos.x = newpos.x > FIELD_W ? 0           :
    newpos.x < 0                ? FIELD_W - 1 :
    newpos.x;
  newpos.y = newpos.y > FIELD_H ? 0           :
    newpos.y < 0                ? FIELD_H - 1 :
    newpos.y;

  /*Осомтр следующей позиции червя*/
  switch (Field[newpos.y][newpos.x])
  {
  case CELL_FREE:
    break;
  case CELL_SHROOM:
    FoodInit(1);
    tail_len += 2;
    score += 16;
    break;
  case CELL_MAGICSHROOM:
    FoodInit(1);
    tail_len += 6;
    score += 32;
    break;
  case CELL_WARM:
    GameOver();
    return;
  }
  
  for (i = tail_len - 1; i >= 0; i--)
  {
    if (i == tail_len - 1)
    {
      Field[tail[i].y][tail[i].x] = CELL_FREE;
      tail[i] = tail[i - 1];
    }

    if (i == 0)
      tail[i] = head;
    else
      tail[i] = tail[i - 1];
  }

  head.x = newpos.x;
  head.y = newpos.y;

  Field[head.y][head.x] = CELL_WARM;
}

/* Keyboard processing function */
void WarmKeyboard( unsigned char Key )
{
  /* Change of direction */
  if (Key == 'w' && dir != 2 && is_game_go == 1)
    dir = 0;
  if (Key == 'd' && dir != 3 && is_game_go == 1)
    dir = 1;
  if (Key == 's' && dir != 0 && is_game_go == 1)
    dir = 2;
  if (Key == 'a' && dir != 1 && is_game_go == 1)
    dir = 3;
  
  /* Pause */
  if (Key == 'p')
    GamePause();

  /* Restart if game is over */
  if (Key == 'r' && is_game_go == 0)
    GameRestart();
}

/* Field drawing function */
void FieldInit( void )
{
  int x, y;

  if(is_game_go == 0)
    return;

  WarmMoving();

  for (y = 0; y < FIELD_H; y++)
    for (x = 0; x < FIELD_W; x++)
      switch (Field[y][x])
      {
      case CELL_FREE:
        PutElement(x * ELEMENT_W, y * ELEMENT_H, 90, 110, 100);
        break;
      case CELL_WARM:
        PutElement(x * ELEMENT_W, y * ELEMENT_H, 35, 140, 45);
        break;
      case CELL_SHROOM:
        PutElement(x * ELEMENT_W, y * ELEMENT_H, 155, 40, 40);
        break;
      case CELL_MAGICSHROOM:
        PutElement(x * ELEMENT_W, y * ELEMENT_H, rand() % 255, rand() % 255, rand() % 255);
        break;
      }

  ScoreInit();
}