#include "include/parser.h"
#include <stdio.h>

void addToken(TokenArray *arr, Token t) {
  if(arr->size >= arr->capacity) {
    size_t tempCapacity = 2 * arr->capacity;
    arr->data = realloc(arr->data, tempCapacity * sizeof(Token));
    if(arr->data) /*if successfull*/ {
      arr->capacity = tempCapacity;
    } else {
      fprintf(stderr, "Failed to reallocate memory\n");
      exit(0);
    }
  }
  arr->data[arr->size++] = t;
}

void initToken(TokenArray *arr) {
  arr->data = malloc(sizeof(Token) * 4);
  if(!arr->data) /*if unsuccessful*/ {
      fprintf(stderr, "Failed to allocate memory\n");
      exit(0);
  }
  arr->size = 0;
  arr->capacity = 4;
}

//must receive a string containing user's commands or tokens themselves
void Tokenize(char *iString) {
 //assuming we get user string itself
  TokenArray tokens;
  initToken(&tokens);

  char *buffer = strtok(iString, " ");

  for(int i = 0; buffer; i++) {
    char *temp = malloc(strlen(buffer) +1);
    strcpy(temp, buffer);
    if(strcmp(temp, "&") == 0){
      addToken(&tokens, (Token){.token = temp, .size = strlen(buffer),.type = TOKEN_AND});
    } else if(strcmp(temp, "|") == 0) {
      addToken(&tokens, (Token){.token = temp, .size = strlen(buffer),.type = TOKEN_PIPE});
    } else{
      addToken(&tokens, (Token){.token = temp, .size = strlen(buffer),.type = TOKEN_WORD});
    }
    buffer = strtok(NULL, " ");
  }
  //call create commands from token
  CreateCommandsFromToken(&tokens); //pass the token lists 
  //freeup tokens
  for(size_t i = 0; i < tokens.size; i++){
      free(tokens.data[i].token);
  }
  free(tokens.data);
}

void initCommand(command_t *cmd) {
  cmd->argv = malloc(sizeof(char *) * 4);
  if(!cmd->argv) {
    fprintf(stderr, "Failed to print memory\n");
    exit(0);
  }
  cmd->argc = 0;
  cmd->argv_capacity = 4;
  cmd->infile = NULL;
  cmd->outfile = NULL;
  cmd->argv[0] = NULL;
}

void addArg(command_t *cmd, char *word) {
  if((size_t)(cmd->argc+1) >= cmd->argv_capacity) {
    size_t tempCap = 2 * cmd->argv_capacity;
    char **tempArgv = realloc(cmd->argv, tempCap *sizeof(char *));
    if(tempArgv) {
      cmd->argv = tempArgv;
      cmd->argv_capacity = tempCap;
    } else {
      fprintf(stderr, "failed to reallocate memory for the arguments");
      exit(0);
    }
  }
  char *copy = malloc(strlen(word) + 1);
  if(!copy) {
    fprintf(stderr, "failed to allocated memory\n");
    exit(0);
  }
  strcpy(copy, word);
  cmd->argv[cmd->argc++] = copy;
  cmd->argv[cmd->argc] = NULL;
}


void initCommandArray(CmdArray *arr) {
  arr->data = malloc(sizeof(command_t) * 4);
  if(!arr->data) {
    fprintf(stderr, "Failed to allocate mem\n");
    exit(0);
  }
  arr->size = 0;
  arr->capacity = 4;
}


void addCommand(CmdArray *arr, command_t cmd) {
  if(arr->size >= arr->capacity) {
    size_t tempCapacity = 2 * arr->capacity;
    command_t *tempData = realloc(arr->data, tempCapacity * sizeof(command_t));
    if(tempData) {
      arr->data = tempData;
      arr->capacity = tempCapacity;
    } else {
      fprintf(stderr, "failed to realloc memory\n");
      exit(0);
    }
  }
  arr->data[arr->size++] = cmd;
}

void freeCommand(command_t *cmd) {
  for(int i = 0; i < cmd->argc; i++) {
    free(cmd->argv[i]);
  }
  free(cmd->argv);
}

void freeCommandArray(CmdArray *arr) {
  for(size_t i = 0; i < arr->size; i++) {
    freeCommand(&arr->data[i]);
  }
  free(arr->data);
}

void printCommand(command_t *cmd, int index) {
  printf("Command %d: argc=%d\n", index, cmd->argc);
  for(int i = 0; i < cmd->argc; i++) {
    printf("  argv[%d] = \"%s\"\n", i, cmd->argv[i]);
  }
  printf("  argv[%d] = NULL\n", cmd->argc);   // confirms the terminator is actually there
  printf("  infile  = %s\n", cmd->infile ? cmd->infile : "(none)");
  printf("  outfile = %s\n", cmd->outfile ? cmd->outfile : "(none)");
}

void printCommandArray(CmdArray *arr) {
  printf("Total commands: %zu\n", arr->size);
  for(size_t i = 0; i < arr->size; i++) {
    printCommand(&arr->data[i], (int)i);
  }
}

void CreateCommandsFromToken(TokenArray *token) {
  CmdArray commands;
  initCommandArray(&commands);

  command_t cur;
  initCommand(&cur);
  for(size_t i = 0; i < token->size; i++) {
    if(token->data[i].type == TOKEN_WORD) {
      addArg(&cur, token->data[i].token);
    } else if(token->data[i].type == TOKEN_PIPE || token->data[i].type == TOKEN_AND) {
      addCommand(&commands, cur);
      initCommand(&cur);
    } else {
      fprintf(stderr, "Invalid token...\n");
      exit(0);
    }
  }
  addCommand(&commands, cur);
  printCommandArray(&commands);
  freeCommandArray(&commands);
  
}
