#ifndef ABSTRACT_MAP_H
#define ABSTRACT_MAP_H

#include "parser.h"

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t (*fun_ptr)(PARSED_DATA_T*);
typedef struct
{
  const char* fun_name;
  fun_ptr ptr;
  uint8_t argument_count;
  uint8_t secound_argument_count;
  uint8_t arguments_max_value;
}MAP_T;

uint8_t exec_mapper(MAP_T* mapper_ptr, PARSED_DATA_T* data);
uint8_t exec_mapper_with_auto_resend(MAP_T* mapper_ptr, PARSED_DATA_T* data);

void check_arguments_count(MAP_T map, PARSED_DATA_T* data);
void check_max_arguments_value(MAP_T map, PARSED_DATA_T* data);

#endif // !ABSTRACT_MAP_H
