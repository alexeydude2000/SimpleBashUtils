#include "s21_grep.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int result = 0;
  flags settings = {0};

  parser(&settings, argc, argv);
  process_files(&settings, argc, argv);

  return result;
}