#ifndef PARSER_ABSTRACT_H
#define PARSER_ABSTRACT_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
  char* command_ptr;
  char function[20];
  char other[50];
  char command_cpy[75];
  uint8_t arguments[15];
  uint8_t arguments_count;
  uint8_t err;
}PARSED_DATA_T;

enum ERRORS_E
{
  __all_is_good,
  __bad_count_off_arguments,
  __argument_is_not_int,
  __bad_argument_value=4,
  __cant_find_equal_char,
};

PARSED_DATA_T* parse_at_command(char* command);
bool compare_functions(char* function);
void to_upper(char* cstr);

#endif // !PARSER_ABSTRACT_H
