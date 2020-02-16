/* Header file "Plugboard.h" */

#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "plugboard.h"
#include "rotor.h"
#include "reflector.h"
#include "helper.h"
#include "errors.h"
#include "constants.h"

using namespace std;

class Enigma
{
 private:
  Plugboard* plugboard;
  Reflector* reflector;
  vector<Rotor*> rotors;  
  int number_of_rotors;
  void encrypt_char(char& ch);
  static void rotor_connection(vector<Rotor*> &rotors); //Connecting to previous rotor
  static int set_rotor_position(vector<Rotor*> &rotors, const char* filename); //Setting rotor's initial position
 public:
  Enigma(Plugboard* plugboard, Reflector* reflector, const vector<Rotor*> &rotors); //Constructor
  ~Enigma(); //Destructor
  int encrypt_message(string& message);
  static int initialise_enigma(int argc, char** argv, int number_of_rotors, Enigma** enigma);
};

#endif
