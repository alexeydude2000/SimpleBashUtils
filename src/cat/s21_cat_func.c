#include <stdio.h>
#include <string.h>

#include "s21_cat.h"

void parser(flags *flag, char *argv) {
  if (argv[0] == '-') {
    if (strcmp(argv, "--number-nonblank") == 0) {
      flag->b = 1;
      flag->parser = 1;
    } else if (strcmp(argv, "--number") == 0) {
      flag->n = 1;
      flag->parser = 1;
    } else if (strcmp(argv, "--squeeze-blank") == 0) {
      flag->s = 1;
      flag->parser = 1;
    } else {
      switch (argv[1]) {
        case 'b':
          flag->b = 1;
          flag->parser = 1;
          break;
        case 'e':
          flag->e = 1;
          flag->parser = 1;
          break;
        case 'n':
          flag->n = 1;
          flag->parser = 1;
          break;
        case 's':
          flag->s = 1;
          flag->parser = 1;
          break;
        case 't':
          flag->t = 1;
          flag->parser = 1;
          break;
        default:
          flag->red_flag = 1;
          printf(
              "cat: illegal option -- %c\nusage: cat [-belnstuv] [file ...]\n",
              argv[1]);
      }
    }
  }
}

int output(flags *flag, char *filename) {
  if (flag->red_flag == 1) return 0;
  FILE *cat = fopen(filename, "rb");

  int last_sim = '\n';
  int count = 1;
  int null_str = 0;

  if (cat != NULL) {
    while (feof(cat) == 0) {
      int c = fgetc(cat);

      if (c != EOF) {
        int rflag = 0;

        if (flag->e == 1) {
          if (c == '\n') {
            printf("$\n");
          } else
            invis(c);
        }

        if (flag->b == 1 && last_sim == '\n' && c != '\n')
          printf("%6d\t", count++);

        if (flag->n == 1 && last_sim == '\n') printf("%6d\t", count++);

        if (flag->s == 1 && c == '\n' && last_sim == '\n') {
          null_str++;
          if (null_str > 1) rflag = 1;
        } else
          null_str = 0;

        if (!rflag) {
          if (flag->t == 1) {
            if (c == '\t') {
              printf("^I");
            } else
              invis(c);
          }
          if (flag->t == 0 && flag->e == 0) printf("%c", c);
          last_sim = c;
        }
      }
    }
    fclose(cat);
  } else
    printf("cat: %s: No such file or directory\n", filename);
  return 0;
}

void invis(int c) {
  if (c < 32 && c != '\t' && c != '\n') {
    printf("^%c", c + 64);
  } else if (c > 127 && c < 160) {
    printf("M-^%c", c - 64);
  } else if (c == 127) {
    printf("^?");
  } else if (c == 173) {
    printf("M-%c", c - 128);
  } else {
    printf("%c", c);
  }
}