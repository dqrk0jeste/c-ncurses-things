#define NCURSES_WIDECHAR 1 

#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>

#include "field.h"
#include "util.h"

 // This is a full list of ncurses colour constants:
 //
 //    COLOR_BLACK
 //    COLOR_RED
 //    COLOR_GREEN
 //    COLOR_YELLOW
 //    COLOR_BLUE
 //    COLOR_MAGENTA
 //    COLOR_CYAN
 //    COLOR_WHITE


// return a field pointer; caller needs to call free_field
field* new_field(char* name, int y, int x, int width) {
  char *input_text = (char*)calloc(MAX_INPUT_LENGTH + 1, sizeof(char));
  field *f = (field*)malloc(sizeof(field));

  f->name = name;
  f->x = x;
  f->y = y;
  f->width = width;
  f->input_text = input_text;
  f->is_drawn = false;

  return f;
}


void free_field(field *f) {
  if(f == NULL) {
    return;
  }
  if(f->input_text != NULL) {
    free(f->input_text);
  }
  free(f);
}


int get_actual_width(field *f) {
  if(f->width <= 4 + strlen(f->name)) {
    return 4 + strlen(f->name);
  }
  return f->width;
}


bool move_to_field(field *f) {
  if(!f->is_drawn) {
    return false;
  }

  move(f->y + 1, f->x + 1 + strlen(f->input_text));
  return true;
}



void draw_input_text(field *f) {
  if(!f->is_drawn) {
    return;
  }

  if(strlen(f->input_text) >= get_actual_width(f) - 3) {
    for(int i = 0; i < get_actual_width(f) - 3; i++) {
      mvaddch(
        f->y + 1,
        f->x + 1 + i,
        f->input_text[i + strlen(f->input_text) - get_actual_width(f) + 3]
      );
    }
    return;
  }

  for(int i = 0; i < strlen(f->input_text); i++) {
    mvaddch(
      f->y + 1,
      f->x + 1 + i,
      f->input_text[i]
    );
  }

  for(int i = strlen(f->input_text); i < get_actual_width(f) - 3; i++) {
    mvaddch(
      f->y + 1,
      f->x + 1 + i,
      ' '
    );
  }
  move(f->y + 1, f->x + 1 + strlen(f->input_text));
}


bool append_to_field(field *f, char c) {
  if(strlen(f->input_text) >= MAX_INPUT_LENGTH) {
    return false;
  }

  if(c == BACKSPACE && strlen(f->input_text) != 0) {
    f->input_text[strlen(f->input_text) - 1] = '\0';
  } else if(c >= FIRST_PRINTABLE_ASCII && c <= LAST_PRINTABLE_ASCII) {
    f->input_text[strlen(f->input_text)] = c;
  }

  if(f->is_drawn) {
    draw_input_text(f);
  }
  return true;
}


void draw_field(field *f) {
  int actual_width = get_actual_width(f);
  wchar_t top_border[actual_width + 1];
  top_border[0] = L'╭';
  top_border[1] = L'─';

  wchar_t text_as_wstr[strlen(f->name) + 1];
  mbstowcs(text_as_wstr, f->name, strlen(f->name) + 1);

  for(size_t i = 0; i < wcslen(text_as_wstr); i++) {
    top_border[2 + i] = text_as_wstr[i];
  }

  for(size_t i = 2 + wcslen(text_as_wstr); i < actual_width - 1; i++) {
    top_border[i] = L'─';
  }

  top_border[actual_width - 1] = L'╮';
  top_border[actual_width] = L'\0';

  wchar_t input_field[actual_width + 1];
  input_field[0] = L'│';
  for(int i = 1; i < actual_width - 1; i++) {
    input_field[i] = L' ';
  }
  input_field[actual_width - 1] = L'│';
  input_field[actual_width] = L'\0';

  wchar_t bottom_border[actual_width + 1];
  bottom_border[0] = L'╰';

  for(int i = 1; i < actual_width - 1; i++) {
    bottom_border[i] = L'─';
  }
  
  bottom_border[actual_width - 1] = L'╯';
  bottom_border[actual_width] = L'\0';

  mvaddwstr(f->y, f->x, top_border);
  mvaddwstr(f->y + 1, f->x, input_field);
  mvaddwstr(f->y + 2, f->x, bottom_border); 

  f->is_drawn = true;
}

