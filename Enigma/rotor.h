/* Header file "Rotor.h" */

#ifndef ROTOR_H
#define ROTOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include "helper.h"
#include "errors.h"
#include "constants.h"

using namespace std;

class Rotor
{
 private:
  vector<int> config_numbers;
  vector<int> notch_position;
  int count_rotation;
  bool is_notch_aligned();

 public:
  Rotor(const vector<int> &config_numbers, const vector<int> &notch_position);
  Rotor* previous; //Pointer to previous rotor
  void set_initial_position(int number_of_rotations); //Setting rotor to initial position
  int mapping(const int& letter); //Right to left
  int mapBack(const int& letter); //left to right
  void rotate(bool is_notch_active);
  static int initialise_rotor(const char* filename, Rotor** rotor);
};

#endif
