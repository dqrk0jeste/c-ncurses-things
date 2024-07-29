#define NCURSES_WIDECHAR 1 

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>

#include "field.h"


int main()
{
  setlocale(LC_ALL, "");

  initscr();
  raw();
  noecho();

  field *test_field = new_field("this is a test", 3, 4, 30);
  draw_field(test_field);

  move(test_field->y + 1, test_field->x + 1);
  refresh();

  char current;
  while((current = getch()) != RETURN) {
    append_to_field(test_field, current);
    refresh();
  }

  endwin();

  printf("your input was:\n%s\n", test_field->input_text);

  free_field(test_field);
  return 0;
}
