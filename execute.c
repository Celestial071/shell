#include "include/execute.h"


int is_builtin(char *cmd) {

  return  strcmp(cmd, "cd") == 0 || 
          strcmp(cmd, "exit") == 0 ||
          strcmp(cmd, "pwd") == 0;
}


void executeCommands(char **argv) {

  if(argv == NULL && argv[0] == NULL) return ;

  if(is_builtin(argv[0])) {
    if(strcmp(argv[0], "cd") == 0){
      builtin_cd(argv);
    } else if(strcmp(argv[0], "exit") == 0) {
      exit(0);
    }

  }else{ 
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
}


int builtin_cd(char **argv) {
  if(argv[1] == NULL) {
    fprintf(stderr, "cd: missing operand\n");
    return 1;
  }

  if(chdir(argv[1]) != 0 ) {
    perror("cd");
    return 1;
  }

  return 0;
}