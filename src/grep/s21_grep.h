#ifndef S21_GREP_H
#define S21_GREP_H

#include <regex.h>

#define MAX_LENGTH 8192

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int multi;
  char filename[MAX_LENGTH];
  char str_arg[MAX_LENGTH];
  char str[MAX_LENGTH];
} flags;

void parser(flags *flag, int argc, char *argv[]);
void process_files(flags *flag, int argc, char *argv[]);
void flag_f(flags *flag);
void process_file(flags *flag, const char *filename, regex_t *regex);
void print_match_o(flags *flag, const char *filename, int line_number,
                   regex_t *regex, const char *line_copy);
void print_regular_line(flags *flag, const char *filename, int line_number,
                        const char *line);

#endif