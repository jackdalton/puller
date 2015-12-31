#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE "Usage: puller <directory1...directory2>"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("%s\n", USAGE);
    return 0;
  }
  int i;
  for (i = 1; i < argc; i++) { // first arg is exec
    char base_command[1024] = "";
    strcat(base_command, "cd ");
    strcat(base_command, argv[i]);
    strcat(base_command, " && git pull && cd ../");
    printf(ANSI_COLOR_BLUE "puller: Pulling repository in " ANSI_COLOR_GREEN "\"%s\"" ANSI_COLOR_BLUE "..." ANSI_COLOR_RESET "\n", argv[i]);
    system(base_command);
  }
  printf(ANSI_COLOR_BLUE "\n------PULLER SUMMARY------" ANSI_COLOR_RESET "\n");
  char *dir_ending = (argc == 2) ? "y" : "ies";
  printf(ANSI_COLOR_YELLOW "* Pulled repositories in" ANSI_COLOR_GREEN " %d" ANSI_COLOR_YELLOW " director%s:" ANSI_COLOR_RESET "\n", argc - 1, dir_ending);
  for (i = 1; i < argc; i++) {
    printf(ANSI_COLOR_YELLOW "\t* %s" ANSI_COLOR_RESET "\n", argv[i]);
  }
  printf(ANSI_COLOR_BLUE "--------------------------" ANSI_COLOR_RESET "\n");
}
