#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
typedef enum {
  TOKEN_WORD,
  TOKEN_PIPE,
  TOKEN_AND,
  TOKEN_EOF,
}TokenType;

typedef struct {
  char *token;
  size_t size;
  TokenType type;
} Token;

typedef struct {
  Token *data;
  size_t size;
  size_t capacity;
} TokenArray;

typedef struct Command{
  char **argv;
  int argc;
  char *infile;
  char *outfile;
  size_t argv_capacity;
}command_t;

typedef struct commandArrray{
  command_t *data;
  size_t size;
  size_t capacity;
}CmdArray;


void Tokenize(char *iString);
void CreateCommandsFromToken(TokenArray *tokens);
void addToken(TokenArray *arr, Token t);
void initToken(TokenArray *arr);
void initCommand(command_t *cmd);
void addArg(command_t *cmd, char *word);
void initCommandArray(CmdArray *arr);
void addCommand(CmdArray *arr, command_t cmd);
void freeCommand(command_t *cmd);
void freeCommandArray(CmdArray *arr);
void printCommand(command_t *cmd, int index);
void printCommandArray(CmdArray *arr);
#endif //PARSER_H
