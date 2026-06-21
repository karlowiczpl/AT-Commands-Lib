#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"

void exec_mapper(MAP_T* mapper_ptr, PARSED_DATA_T* data)
{
  for(uint8_t i = 0; mapper_ptr[i].fun_name[0] != 0; i++)
  {
    if(strcmp(mapper_ptr[i].fun_name, data->function) == 0)
    {
      check_arguments_count(mapper_ptr[i], data);
      check_max_arguments_value(mapper_ptr[i], data);

      mapper_ptr[i].ptr(data);
    }
  }
}

void check_arguments_count(MAP_T map, PARSED_DATA_T* data)
{
  if(map.argument_count != data->arguments_count - 1 && map.secound_argument_count != data->arguments_count - 1)
  {
    data->err = __bad_count_off_arguments;
  }
}

void check_max_arguments_value(MAP_T map, PARSED_DATA_T* data)
{
  uint8_t max_value = map.arguments_max_value;

  for(uint8_t i = 0; i < data->arguments_count; i++)
  {
    if(data->arguments[i] > max_value)    data->err = __bad_argument_value;
  }
}
