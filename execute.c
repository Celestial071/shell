#include "include/execute.h"


void executeCommands(char **argv) {
  pid_t pid = fork();

  if(pid < 0) {
    perror("fork failed");
    return;
  }

  if(pid == 0) {
    execvp(argv[0], argv);
    perror("execvp failed");
    exit(1);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }
}
