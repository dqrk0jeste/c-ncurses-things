#define NCURSES_WIDECHAR 1 

#include <locale.h>
#include <ncurses.h>

#include "field.h"
#include "select_field.h"


int main()
{
  setlocale(LC_ALL, "");

  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  char *question = "are you a unicorn?";
  char *choices[] = {
    "yes",
    "no",
    "maybe",
    "maybe not"
  };

  select_field *s = new_select_field(question, choices, 4, 1, 1);

  draw_select_field(s);
  int selected = handle_selection(s);

  // field *test_field = new_field("this is a test", 3, 4, 30);
  // draw_field(test_field);
  //
  // move(test_field->y + 1, test_field->x + 1);
  // refresh();
  //
  // char current;
  // while((current = getch()) != RETURN) {
  //   append_to_field(test_field, current);
  //   refresh();
  // }
  //

  endwin();

  printf("your answer was:\n%s\n", s->choices[selected]);

  free_select_field(s);

  // free_field(test_field);
  return 0;
}
