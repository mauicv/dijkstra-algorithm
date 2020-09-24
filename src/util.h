/*
  file: util.h

	Util functions:
    get_random: returns a random double value in between lower and upper.
*/

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <time.h>

double get_random(double lower, double upper){
  double range_size = upper - lower;
  return lower + (rand() / (RAND_MAX + 1.))*range_size;
}

#endif /* UTILS_H */
