#include "headers.h"

queue < struct coordinates > snake; 
struct coordinates apple;
int main()
{
    initscr();
    keypad(stdscr, true); //typing arrows enable
    int rows;
    int columns;
    getmaxyx(stdscr, rows, columns);
    if(rows < 35 || columns < 100) printw("Window size must be at least 45x110!\n");
    else
    {
      int points = 0;
      bool alive = true;
      create_field();
      snake = create_snake(snake);
      apple = create_apple(apple, snake);
      mvprintw(0,35,"Press arrow to start!");
      mvprintw(5,90,"Press 'w' to quit!");
      mvprintw(10,90,"Points: ");
      display_points(points);
      move(34,1);


      int key = getch();
      while(key != DOWN_ARROW && key != UP_ARROW && key != LEFT_ARROW && key != RIGHT_ARROW) //pressing arrow to start
      {
         key = getch();
      }
      int direction = key;
      nodelay(stdscr, TRUE);

      while(alive)
      {
       usleep(70000); //how fast snake is moving
       snake =  snake_move(direction,snake,apple);
       if(snake.back().x == apple.x && snake.back().y == apple.y) //snake ate apple
       {
         apple = create_apple(apple, snake);
         points++;
         display_points(points);
       }
       if(snake.back().y == 1 || snake.back().y == 32 || snake.back().x == 11 || snake.back().x == 81) alive = false; //snake hit border
       if(hit_himself(snake) == true) alive = false;

       key = getch();
       if(key == DOWN_ARROW || key == UP_ARROW || key == LEFT_ARROW || key == RIGHT_ARROW)
       {
        if(     direction == DOWN_ARROW  && key == UP_ARROW)    alive = false; // snake turn back
        else if(direction == UP_ARROW    && key == DOWN_ARROW)  alive = false;
        else if(direction == RIGHT_ARROW && key == LEFT_ARROW)  alive = false;
        else if(direction == LEFT_ARROW  && key == RIGHT_ARROW) alive = false;
        direction = key;
       }
       if(key == 119)break; //pressing 'w'
      }

    }
    move(34,30);
    printw("YOU ARE DEAD!\n");
    move(35,30);
    printw("Press any key to close!\n");
    nodelay(stdscr, FALSE);
    getch(); //czekanie na naciśnięcie

  endwin(); 
  return 0;
}