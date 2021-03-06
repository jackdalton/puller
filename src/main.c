#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE "Usage: puller [options] <directory1...directory2>"
#define VERSION "0.2.5"

#include "puller.yucc"
#include "colors.h"
#include "repo_exists.h"
#include "safe_dir_name.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf(ANSI_COLOR_RED USAGE ANSI_COLOR_RESET "\n");
    return 0;
  }

  yuck_t argp[1];
  yuck_parse(argp, argc, argv);
  yuck_free(argp);
  // if(argp->whatever_flag) {
  //
  //   yuck_free(argp);
  // }

  int i;

  for (i = 1; i < argc; i++) { // first arg is exec
    char *dirname = argv[i];

    if (!repo_exists(safe_dir_name(dirname))) {
      printf(ANSI_COLOR_RED "puller v" VERSION ": Repo %s doesn't exist!" ANSI_COLOR_RESET "\n", dirname);
      continue;
    }

    char base_command[1024] = "";
    strcat(base_command, "cd ");
    strcat(base_command, dirname);
    strcat(base_command, " && git pull && cd ../");
    printf(ANSI_COLOR_BLUE "puller v" VERSION ": Pulling repository in " ANSI_COLOR_GREEN "\"%s\"" ANSI_COLOR_BLUE "..." ANSI_COLOR_RESET "\n", dirname);
    system(base_command);
    printf(ANSI_COLOR_BLUE "puller v" VERSION ": Finished pulling " ANSI_COLOR_GREEN "\"%s\"" ANSI_COLOR_BLUE "." ANSI_COLOR_RESET "\n", dirname);
  }

  int success_repos = 0;

  for (i = 1; i < argc; i++) {
    if (repo_exists(safe_dir_name(argv[i]))) {
      success_repos++;
    }
  }

  int fail_repos = argc - 1 - success_repos;
  char *dir_ending = (argc == 2 && success_repos != 0) ? "y" : "ies";
  char *fail_dir_ending = (fail_repos == 1 && argc - 1 - success_repos != 0) ? "y" : "ies";
  printf(ANSI_COLOR_BLUE "\n------PULLER SUMMARY------" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_GREEN " %d" ANSI_COLOR_YELLOW " repositor%s up to date:" ANSI_COLOR_RESET "\n", success_repos, dir_ending);

  for (i = 1; i < argc; i++) {
    if (repo_exists(safe_dir_name(argv[i]))) {
      printf(ANSI_COLOR_YELLOW "\t* %s" ANSI_COLOR_RESET "\n", argv[i]);
    }
  }

  if (success_repos != argc - 1) {

    printf(ANSI_COLOR_RED "* Failed to pull repositories in" ANSI_COLOR_GREEN " %d" ANSI_COLOR_RED" director%s:" ANSI_COLOR_RESET "\n", fail_repos, fail_dir_ending);
    for (i = 1; i < argc; i++) {
      if (!repo_exists(safe_dir_name(argv[i]))) {
        printf(ANSI_COLOR_RED "\t* %s" ANSI_COLOR_RESET "\n", argv[i]);
      }
    }
  }

  printf(ANSI_COLOR_BLUE "--------------------------" ANSI_COLOR_RESET "\n");
  return 0;
}
