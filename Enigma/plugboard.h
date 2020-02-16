/* Header file "Plugboard.h" */

#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include <iostream>
#include <fstream>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "constants.h"

using namespace std;

class Plugboard
{	
 private:
  vector<int> config_numbers;
 public:
  Plugboard(vector<int> config_numbers);
  int mapping(const int& letter);
  static int initialise_plugboard(const char* filename, Plugboard** plugboard);
};

#endif
