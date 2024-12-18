#include "map.h"

#include <error.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static ERR_PTR_T error_function = NULL;
static MAPPER_T* instance;
static uint8_t size;

uint8_t checkForErrors(ParsedData* p1 , MAPPER_T* m1);

void setupMapper(MAPPER_T* inst , int s , ERR_PTR_T err)
{
  instance = inst;
  size = s; 
  error_function = err;
}
void inputMessage(ParsedData* p1)
{
  for(uint8_t i = 0; i < size; i++)
  {
    if(!strcmp(instance[i].function , p1->function))
    {
      if(checkForErrors(p1 , &instance[i]))
      {
        FUN_PTR_T fun_ptr = instance[i].fun_ptr;
        fun_ptr(p1);
      }
      
    }
  }

  free((void*)p1->function);
  free((void*)p1->other);
}
uint8_t checkForErrors(ParsedData* p1 , MAPPER_T* m1)
{
  uint8_t error_code = 0;
  if(p1->sizeOfStates != m1->frameLength) 
  {
    error_function(_incorrect_frame_length);
    return 0;
  }
  if(p1->error)
  {
    error_function(_invalid_character);
    return 0;
  }
  for(uint8_t i = 0; i < p1->sizeOfStates; i++)
  {
    if(p1->states[i] > m1->maxStatesValues[i])
    {
      error_function(_out_off_scope);
      return 0;

    }
  }
  return 1;
}
