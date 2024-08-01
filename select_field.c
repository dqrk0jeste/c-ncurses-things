#include "select_field.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define RETURN 10
#define SPACEBAR 32

select_field* new_select_field(
  char *question,   
  char **choices,
  int choice_count,
  int y, 
  int x
) {
  select_field *s = (select_field*)malloc(sizeof(select));

  s->question = question;
  s->choices = choices;
  s->choice_count = choice_count;
  s->y = y;
  s->x = x;
  s->is_drawn = false;
  s->choice_index = -1;

  return s;
}

void free_select_field(select_field *s) {
  free(s);
}

char* choose(select_field *s, int choice_index) {
  s->choice_index = choice_index;
  return s->choices[choice_index];
}

void draw_select_field(select_field *s) {
  mvaddstr(s->y, s->x, s->question);

  for(int i = 0; i < s->choice_count; i++) {
    char line[5 + strlen(s->choices[i])];
    strcpy(line, "[ ] ");
    strcat(line, s->choices[i]);
    mvaddstr(s->y + 2 + i, s->x + 1, line);
  }

  s->is_drawn = true;
}

int handle_selection(select_field *s) {
  move(s->y + 2, s->x + 2);
  int hovering_index = 0;

  int c;
  while((c = getch()) != RETURN) {
    if(c == SPACEBAR && s->choice_index != hovering_index) {
      addch('x');
      if(s->is_drawn) {
        mvaddch(s->y + 2 + s->choice_index, s->x + 2, ' ');
        s->choice_index = hovering_index;
      }
    } else if((c == KEY_UP || c == 'k') && hovering_index > 0) {
      hovering_index--;
    } else if((c == KEY_DOWN || c == 'j') && hovering_index < s->choice_count - 1) {
      hovering_index++;
    }

    if(s->is_drawn) {
      move(s->y + 2 + hovering_index, s->x + 2);
      refresh();
    }
  }
  
  mvaddch(s->y + 1 + hovering_index, s->x + 1, 'x');
  refresh();

  return hovering_index;
}
