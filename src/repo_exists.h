#pragma once

#include <stdbool.h>
#include <sys/stat.h>

bool repo_exists(char* dir) {
  char git_dir[1024] = "";
  strcat(git_dir, dir);
  strcat(git_dir, ".git/");
  struct stat gdd;
  if (!stat(git_dir, &gdd) && S_ISDIR(gdd.st_mode)) {
    return true;
  } else {
    return false;
  }
}
