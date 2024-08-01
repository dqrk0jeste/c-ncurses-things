#define FIELD_H

#define NCURSES_WIDECHAR 1

#define BACKSPACE 127
#define RETURN 10

#define MAX_INPUT_LENGTH 128
#define FIRST_PRINTABLE_ASCII 32
#define LAST_PRINTABLE_ASCII 126

typedef struct {
  char *name;
  int x, y, width;
} field;

field *new_field(char *name, int y, int x, int width);

void free_field(field *f);

int get_actual_width(field *f);

char *handle_input(field *f);
