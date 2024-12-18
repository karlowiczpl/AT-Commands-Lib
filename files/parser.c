#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

void split(ParsedData* p1 , const char* at_command);
void parse_states(ParsedData* p1);

ParsedData parse_c_string(const char* at_command)
{
  ParsedData p1;

  split(&p1 , at_command);
  parse_states(&p1);

  return p1;
}
void parse_states(ParsedData* p1)
{
  char states[15][7];
  int8_t i = -1 , j = 0 , counter = 0;

  while( p1->other[++i] != '\0' )
  {
    if(p1->other[i] == ',') 
    {
      states[counter][j] = '\0';
      j = 0;
      counter++;
      continue;
    }
    states[counter][j] = p1->other[i];
    j++;
  }
  states[counter][j] = '\0';

  p1->sizeOfStates = counter + 1;
  p1->error = 0;
  uint16_t* states_tabble = (uint16_t*)malloc( p1->sizeOfStates * sizeof(uint16_t));

  for(int k = 0; k < p1->sizeOfStates; k++)
  {
    states_tabble[k] = to_int(states[k] , p1);
  }
  p1->states = states_tabble;
}
void split(ParsedData* p1 , const char* at_command)
{
  int8_t i = -1 , j;
  char function[15] , other[25];
  int8_t fun = 0;
  
  while( at_command[++i] != '\n')
  {
    if(!fun)
    {
      if(at_command[i] == '=')
      {
        fun = 1;
        function[i] = '\0';
        j = i;
        continue;
      }
      function[i] = at_command[i];
    }
    else
    {
      other[i - j - 1] = at_command[i];
    }
  }
  other[i - j - 1] = '\0';

  char* f_str = (char*)malloc( (j) * sizeof(char));
  strncpy(f_str , function , j);
  p1->function = f_str;

  char* o_str = (char*)malloc( (i - j - 1) * sizeof(char));
  strncpy(o_str , other , i - j - 1);
  p1->other = o_str;
}
int to_int(const char* c , ParsedData* p1)
{
  uint16_t x = 1 , converted = 0;
  for(int i = strlen(c) - 1; i >= 0; i--)
  {
    if(c[i] >= '0' && c[i] <= '9')
    {
      converted += (x * (c[i] - '0'));
      x *= 10;
    }
    else 
    {
      p1->error = 1;
      break;
    }
  }
  return converted;
}
