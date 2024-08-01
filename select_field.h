#define SELECT_FIELD_H

#include <stdbool.h>

typedef struct {
  char *question;
  char **choices;
  int choice_index;
  int choice_count;
  int x, y;
  bool is_drawn;
} select_field;

select_field* new_select_field(
  char *question,   
  char **choices,
  int choice_count,
  int y, 
  int x
);

void free_select_field(select_field *s);

char* choose(select_field *s, int choice_index);

void draw_select_field(select_field *s);

int handle_selection(select_field *s);

