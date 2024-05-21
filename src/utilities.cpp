#include <Arduino.h>
#include "utilities.hpp"

void float_to_str(char* str, float value){
  char buf[512];
  memset(buf,0,sizeof(buf));
  int counter = 0;
  int num = value;
  while(num){
   int digit = num % 10;
    buf[counter++] = digit + '0';
    num /= 10;
  }
  for(int i = 0; i < counter; ++i){
    str[i] = buf[counter-i-1];
  }
  str[counter] = '.';
  value *= 10;
  str[counter + 1] = ((int)value % 10) + '0'; 
  value *= 10;
  str[counter + 2] = ((int)value % 10) + '0';
}
