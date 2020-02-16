/*Enigma machine to encrypt and decrypt messages*/

#include "enigma.h"

using namespace std;

int main(int argc, char** argv)
{ 
  Enigma* enigma;
  int good = NO_ERROR;
  int number_of_rotors;
  string str;

  //checking the number of command line arguments
  if(argc < 3) {
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  if(argc == 3)
    number_of_rotors = 0;
  else
    number_of_rotors = argc - 4;

  good = enigma->initialise_enigma(argc, argv, number_of_rotors, &enigma);
  
  if(good)
    return good;
  
  good = enigma->encrypt_message(str);
  if(good) {
    delete enigma;
    return good;
  }
  
  delete enigma;
  return NO_ERROR;	
}
