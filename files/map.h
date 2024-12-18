#include "parser.h"
#include <stdint.h>

typedef void (*FUN_PTR_T)(ParsedData*);
typedef void (*ERR_PTR_T)(uint8_t);

typedef struct  
{
  const char* function;
  const FUN_PTR_T fun_ptr;
  const int frameLength;
  const int* maxStatesValues;
}MAPPER_T;

enum Error_types 
{
  _invalid_character = 1,
  _incorrect_frame_length,
  _out_off_scope,
};

void setupMapper(MAPPER_T* inst , int size , ERR_PTR_T error_function);
void inputMessage(ParsedData* p1);
