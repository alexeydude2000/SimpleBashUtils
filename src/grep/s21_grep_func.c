#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep.h"

void parser(flags *flag, int argc, char *argv[]) {
  int opt;
  int pattern_set = 0;

  flag->str_arg[0] = '\0';
  flag->filename[0] = '\0';

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        flag->e = 1;
        if (flag->str_arg[0] != '\0') {
          strcat(flag->str_arg, "|");
        }
        strcat(flag->str_arg, optarg);
        pattern_set = 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        if (strlen(optarg) < MAX_LENGTH) {
          strcpy(flag->filename, optarg);
        }
        pattern_set = 1;
        break;
      case 'o':
        flag->o = 1;
        break;
      default:
        exit(1);
    }
  }

  if (flag->f) {
    flag_f(flag);
  }

  if (!pattern_set && optind < argc) {
    if (flag->str_arg[0] != '\0') {
      strcat(flag->str_arg, "|");
    }
    strcat(flag->str_arg, argv[optind]);
    optind++;
  }

  if (flag->str_arg[0] == '\0') {
    if (!flag->s) {
      fprintf(stderr, "grep: pattern required\n");
    }
    exit(1);
  }

  if (argc - optind > 1) {
    flag->multi = 1;
  }

  if (flag->v) {
    flag->o = 0;
  }
}

void flag_f(flags *flag) {
  FILE *fgrep = fopen(flag->filename, "r");
  if (fgrep == NULL) {
    if (!flag->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", flag->filename);
    }
    return;
  }

  char buffer[MAX_LENGTH];
  int first_pattern = 1;

  while (fgets(buffer, MAX_LENGTH, fgrep) != NULL) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
      len--;
    }

    if (len == 0) {
      continue;
    }

    if (!first_pattern) {
      if (strlen(flag->str_arg) + 1 < MAX_LENGTH) {
        strcat(flag->str_arg, "|");
      }
    }

    if (strlen(flag->str_arg) + len < MAX_LENGTH) {
      strcat(flag->str_arg, buffer);
    }

    first_pattern = 0;
  }

  fclose(fgrep);
}

void process_files(flags *flag, int argc, char *argv[]) {
  regex_t regex;
  int regex_flags = REG_EXTENDED;

  if (flag->i) {
    regex_flags |= REG_ICASE;
  }

  int regcomp_result = regcomp(&regex, flag->str_arg, regex_flags);
  if (regcomp_result != 0) {
    if (!flag->s) {
      fprintf(stderr, "grep: invalid regular expression\n");
    }
    return;
  }

  int file_count = 0;
  for (int i = optind; i < argc; i++) {
    process_file(flag, argv[i], &regex);
    file_count++;
  }

  if (file_count == 0) {
    process_file(flag, "-", &regex);
  }

  regfree(&regex);
}

void print_match_o(flags *flag, const char *filename, int line_number,
                   regex_t *regex, const char *line_copy) {
  char *ptr = (char *)line_copy;
  int offset = 0;
  regmatch_t pmatch;
  int match_found = 0;

  while (regexec(regex, ptr + offset, 1, &pmatch, 0) == 0) {
    if (pmatch.rm_so == -1) {
      break;
    }

    match_found = 1;

    if (flag->multi && !flag->h && strcmp(filename, "-") != 0) {
      printf("%s:", filename);
    }

    if (flag->n) {
      printf("%d:", line_number);
    }

    printf("%.*s\n", (int)(pmatch.rm_eo - pmatch.rm_so),
           ptr + offset + pmatch.rm_so);

    offset += pmatch.rm_eo;

    if (pmatch.rm_eo == 0) {
      offset++;
      if (ptr[offset] == '\0') {
        break;
      }
    }
  }

  if (!match_found && !flag->v) {
    print_regular_line(flag, filename, line_number, line_copy);
  }
}

void print_regular_line(flags *flag, const char *filename, int line_number,
                        const char *line) {
  if (flag->multi && !flag->h && strcmp(filename, "-") != 0) {
    printf("%s:", filename);
  }

  if (flag->n) {
    printf("%d:", line_number);
  }

  printf("%s\n", line);
}

void process_file(flags *flag, const char *filename, regex_t *regex) {
  FILE *file = NULL;

  if (strcmp(filename, "-") == 0) {
    file = stdin;
  } else {
    file = fopen(filename, "r");
  }

  if (file == NULL) {
    if (!flag->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    }
    return;
  }

  int line_number = 0;
  int match_count = 0;
  int file_has_match = 0;
  char line[MAX_LENGTH];

  while (fgets(line, MAX_LENGTH, file) != NULL) {
    line_number++;

    char line_copy[MAX_LENGTH];
    strcpy(line_copy, line);
    size_t len = strlen(line_copy);
    if (len > 0 && line_copy[len - 1] == '\n') {
      line_copy[len - 1] = '\0';
    }

    int regex_result = regexec(regex, line_copy, 0, NULL, 0);
    int match = (regex_result == 0);

    int should_output = 0;
    if (flag->v) {
      should_output = !match;
    } else {
      should_output = match;
    }

    if (!should_output) {
      continue;
    }

    match_count++;
    file_has_match = 1;

    if (flag->l || flag->c) {
      continue;
    }

    if (flag->o && !flag->v) {
      print_match_o(flag, filename, line_number, regex, line_copy);
    } else {
      print_regular_line(flag, filename, line_number, line_copy);
    }
  }

  if (flag->c) {
    if (flag->l && match_count > 0) {
      match_count = 1;
    }

    if (flag->multi && !flag->h && strcmp(filename, "-") != 0) {
      printf("%s:", filename);
    }

    printf("%d\n", match_count);
  }

  if (flag->l && file_has_match) {
    printf("%s\n", filename);
  }

  if (file != stdin) {
    fclose(file);
  }
}