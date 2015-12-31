#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE "Usage: puller <directory1...directory2>"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_GREEN "\x1b[32m"
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
}
