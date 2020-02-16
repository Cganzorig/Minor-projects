/* Header file "Reflector.h" */

#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "constants.h"

using namespace std;

class Reflector
{
 private:
  vector<int> config_numbers;
 public:
  Reflector(vector<int> config_numbers);
  int mapping(const int& letter);
  static int initialise_reflector(const char* filename, Reflector** reflector);
};

#endif
