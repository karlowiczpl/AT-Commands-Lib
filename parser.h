#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef struct 
{ 
  uint8_t sizeOfStates;
  uint16_t* states;
  const char* function;
  const char* other;
  uint8_t error;
}ParsedData;

ParsedData parse_c_string(const char* at_command);
int to_int(const char* c , ParsedData* p1);

#endif // !PARSER_H
