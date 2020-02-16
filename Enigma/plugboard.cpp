/* Impelementation file "Plugboard.cpp" */

#include "plugboard.h"

using namespace std;

Plugboard::Plugboard(vector<int> config_numbers): config_numbers(config_numbers) {}

int Plugboard::initialise_plugboard(const char* filename, Plugboard** plugboard)
{
  int number;
  vector<int> config_numbers;

  ifstream in_stream;
  in_stream.open(filename);

  if(in_stream.fail()) {
    cerr << "Error opening configuration file plugboard.pb" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  while((in_stream >> number) && !in_stream.eof()) {
    if(number < 0 || number >= ALPHABET_SIZE) {
      cerr << "Invalid index in plugboard file plugboard.pb" << endl;
      return INVALID_INDEX;
    }
      
    if(config_numbers.size() >= ALPHABET_SIZE) {
      cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    //Checking if a number in plugboard is connected to itself
    if(is_repeated(config_numbers, number)) {
      cerr << "Impossible plugboard configuration in file plugboard.pb" << endl;
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
      
    config_numbers.push_back(number);
  }
  
  if(!in_stream.eof()) {
    cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
    return NON_NUMERIC_CHARACTER;
    }

  if(config_numbers.size() % 2 == 1) {
    cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  
  *plugboard = new Plugboard(config_numbers);
  in_stream.close();
  return NO_ERROR;
}

int Plugboard::mapping(const int& letter)
{
  for(int i = 0; i < static_cast<signed>(config_numbers.size()); i++) {
    if(config_numbers[i] == letter) {
      if(i % 2 == 0)
	return config_numbers[i+1];
      else
	return config_numbers[i-1];
    }
  }
  return letter;
}
