#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"

PARSED_DATA_T data;

#define complited 0
#define error 1

bool split_command();
bool arguments_to_int(char** cstrs);
char** create_cstr_from_arguments(char** cstrs);

PARSED_DATA_T* parse_at_command(char* command)
{
  data.err = 0;

  data.command_ptr = command;
  strcpy(data.command_cpy, command);

  if(split_command())     
  {
    data.err = __cant_find_equal_char;
    return &data;
  }
  char* split_buffor[15];
  create_cstr_from_arguments(split_buffor);
  if(arguments_to_int(split_buffor))
  {
    data.err = __argument_is_not_int;
    return &data;
  }
  
  return &data;
}

bool split_command()
{
  char* delimiter = strchr(data.command_cpy, '=');
  if(delimiter == NULL)     return error;

  *delimiter = '\0';
  strcpy(data.function, data.command_cpy); strcpy(data.other, delimiter + 1);
  return complited;
}
bool compare_functions(char* function)
{
  return !strcmp(data.function, function);
}
char** create_cstr_from_arguments(char** cstrs)
{
  uint8_t counter = 1;
  cstrs[0] = data.other;
  for(uint8_t i = 0; data.other[i] != '\0'; i++)
  {
    if(data.other[i] == ',')    
    {
      data.other[i] = '\0';

      cstrs[counter++] = &data.other[i + 1];     
    }
  }
  cstrs[counter] = NULL;

  return cstrs;
}

bool arguments_to_int(char** cstrs)
{
  int result = 0;
  uint8_t counter = 0;
  for(uint8_t i = 0; cstrs[i] != NULL; i++)
  {
    char* arg = cstrs[i];
    int len = strlen(arg);
    while(len > 0 && (arg[len-1] == '\n' || arg[len-1] == '\r' || arg[len-1] == ' ')) {
      arg[len-1] = '\0';
      len--;
    }

    for(uint8_t j = 0; arg[j] != '\0'; j++)
    {
      if(arg[j] < '0' || arg[j] > '9') return error;
    }

    result = atoi(arg);
    if(result < 0 || result > 255) return error;
    data.arguments[counter++] = result;
  }
  data.arguments_count = counter;

  return complited;
}
