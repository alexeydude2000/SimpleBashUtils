#ifndef S21_CAT_H
#define S21_CAT_H

typedef struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int red_flag;
  int parser;
} flags;
void parser(flags *flag, char *argv);
int output(flags *flag, char *filename);
void invis(int c);

#endif