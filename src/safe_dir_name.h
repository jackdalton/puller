#pragma once
#include <stdio.h>
#include <string.h>

char *safe_dir_name(char *dirname) {
  size_t dn_len = strlen(dirname);
  char *dirname_safe = malloc(dn_len + 2);
  strcpy(dirname_safe, dirname);
  dirname_safe[dn_len] = *"/";
  dirname_safe[dn_len + 1] = *"\0";
  return dirname_safe;
  free(dirname_safe);
}
