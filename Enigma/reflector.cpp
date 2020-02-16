/*Implementation file "Reflector.cpp" */

#include "reflector.h"

using namespace std;

Reflector::Reflector(vector<int> config_numbers): config_numbers(config_numbers) {}

int Reflector::initialise_reflector(const char* filename, Reflector** reflector)
{
  int number;
  string line;
  vector<int> config_numbers;

  ifstream in_stream;
  in_stream.open(filename);

  if(in_stream.fail()) {
     cerr << "Error opening configuration file reflector.rf" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  while((in_stream >> number) && !in_stream.eof()) {
    if(number < 0 || number >= ALPHABET_SIZE) {
      cerr << "Invalid index in file reflector.rf" << endl;
      return INVALID_INDEX;
    }
    if(config_numbers.size() >= ALPHABET_SIZE) {
      cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    //Checking if a number in reflector file is connected to itself
    if(is_repeated(config_numbers, number)) {
      cerr << "Invalid mapping in reflector file reflector.rf" << endl;
      return INVALID_REFLECTOR_MAPPING;
    }
    config_numbers.push_back(number);
  }

  if(!in_stream.eof()) {
    cerr << "Non-numeric character in reflector file reflector.rf" << endl;
    return NON_NUMERIC_CHARACTER;
  }
  if(config_numbers.size() < ALPHABET_SIZE) {
    //checking if the number of reflectors is less than 13 or file contains odd number of parameters
    if(config_numbers.size() % 2 == 0) {
      cerr << "Insufficient number of mappings in reflector file: reflector.rf" << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    } else {
      cerr << "Incorrect (odd) number of parameters in reflector file reflector.rf" << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
  }

  *reflector = new Reflector(config_numbers);
  in_stream.close();
  return NO_ERROR;
}

int Reflector::mapping(const int& letter) {
  for(unsigned int i = 0; i < config_numbers.size(); i++) {
    if(config_numbers[i] == letter) {
      if(i % 2 == 0)
	return config_numbers[i+1];
      else
	return config_numbers[i-1];
    }
  }
  return NO_ERROR;
}
