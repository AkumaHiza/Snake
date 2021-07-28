#include "headers.h"

/*
Creates a frame made of #
*/
void create_field()
{
    attron(A_BOLD);
    printw("\n");
    for(int i = 0; i < 10; i++) printw( " " ); 
    for(int i = 0; i < 72; i++) printw( "#" ); // length = 70
    printw( "\n" );
    for(int i = 0; i < 30; i++) ///high = 30
    {
        for(int j = 0; j < 10; j++) printw( " " );
        printw( "#" );
        for(int j = 0; j < 70; j++) printw( " " );
        printw( "#\n" );
    }
    for(int i = 0; i < 10; i++) printw( " " );
    for(int i = 0; i < 72; i++) printw( "#" );
    printw( "\n" );

    attroff(A_BOLD);
}
/* Create snake
   Here you can change starting position */
queue <struct coordinates> create_snake(queue <struct coordinates> snake)
{
    mvprintw(25,40,"O");
    mvprintw(26,40,"O");
    move(34,1); //move cursor out of play field
    struct coordinates place;
    place.x = 40;
    place.y = 26;
    snake.push(place);
    place.y = 25;
    snake.push(place);
    return snake;
}

/* Display apple on random place */
struct coordinates create_apple(struct coordinates apple, queue <struct coordinates> snake)
{
   int draw_again = true;
   int y,x;
   while(draw_again)
   {
    y = rand() % 30;
    x = rand() % 70;
    draw_again = false; 
    apple.x = x + 12;
    apple.y = y + 2;
    while(!snake.empty())
    {
      if(snake.front().x == apple.x && snake.front().y == apple.y) draw_again = true;
      snake.pop();
    }
   }
   mvprintw(y+2,x+12,"o");
   move(34,1);
   return apple;
}

/* Display new element and delete last element on screen */
void change_snake_picture(queue <struct coordinates> snake, struct coordinates place)
{
    struct coordinates new_part = snake.back();
    mvprintw(new_part.y,new_part.x,"O");
    mvprintw(place.y, place.x," ");
    move(34,1);
}

/* Add a new snake element according to the direction
   Delete the last element*/
queue <struct coordinates> snake_move(int direction,queue <struct coordinates> snake, struct coordinates apple)
{
  struct coordinates place = snake.back();
  if     (direction == UP_ARROW)    place.y--;
  else if(direction == DOWN_ARROW)  place.y++;
  else if(direction == LEFT_ARROW)  place.x--;
  else if(direction == RIGHT_ARROW) place.x++;

  snake.push(place);
  if(snake.back().x != apple.x || snake.back().y != apple.y)
  {
    place =  snake.front();
    snake.pop();
  }
  else //delete empty place if snake increase after eating apple
  {
      place.x = 0;
      place.y = 0;
  }
  change_snake_picture(snake,place);
  return snake;
}

/* Display points on screen */
void display_points(int points)
{
      string points_str = to_string(points);
      const char *points_char = points_str.c_str();
      mvprintw(10,98,points_char);
      move(34,1);
}

/* TRUE if snake hit his body
   FALSE if snake doesn't hit */
bool hit_himself(queue <struct coordinates> snake) 
{
  struct coordinates head = snake.back();
  while(!snake.empty())
  {
      if(snake.front().x == head.x && snake.front().y == head.y && snake.size() > 1) return true;
      snake.pop();
  } 
  return false;
}