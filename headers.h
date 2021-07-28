#ifndef HEADERS_H_
#define HEADERS_H_

#include <iostream>
#include <ncurses.h>
#include <unistd.h> //linux library to use sleep()
#include <queue>

#define DOWN_ARROW 258
#define UP_ARROW 259
#define LEFT_ARROW 260
#define RIGHT_ARROW 261

using namespace std;

void create_field();
queue <struct coordinates> create_snake(queue <struct coordinates>);
struct coordinates create_apple(struct coordinates apple, queue <struct coordinates>);
queue <struct coordinates> snake_move(int, queue <struct coordinates>, struct coordinates);
void change_snake_picture(queue <struct coordinates>, struct coordinates);
void display_points(int);
bool hit_himself(queue <struct coordinates>);

struct coordinates
{
  int x;
  int y;
};

#endif // HEADERS_H_