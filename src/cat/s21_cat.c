#include "s21_cat.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  flags settings = {0};
  for (int i = 1; i < argc; i++) {
    parser(&settings, argv[i]);
    if (settings.parser == 0) output(&settings, argv[i]);
    settings.parser = 0;
  }
  return 0;
}