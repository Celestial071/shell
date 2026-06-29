#ifndef EXECUTE_H
#define EXECUTE_H

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_builtin(char *cmd);
void executeCommands(char **argv);

int builtin_cd(char **argv);

#endif //EXecute_H
