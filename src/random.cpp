#include <Arduino.h>
#include "random.hpp"

int generate(int min, int max){
  return (rand() % (max - min + 1)) + min;
}

float generate_normal(){
  return (float)rand() / RAND_MAX; 
}

float generate_float(float min, float max){
  return generate_normal() * (max - min) + min;
}
