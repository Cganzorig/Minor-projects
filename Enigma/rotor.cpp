/* Implementation file "Rotor.cpp" */

#include "rotor.h"

using namespace std;

Rotor::Rotor(const vector<int> &config_numbers, const vector<int> &notch_position):
  config_numbers(config_numbers), notch_position(notch_position), count_rotation(0) {}

bool Rotor::is_notch_aligned() {
  for(unsigned int i = 0; i < notch_position.size(); i++)
    if(notch_position[i] == count_rotation)
      return true;
  return false;
}

int Rotor::initialise_rotor(const char* filename, Rotor** rotor)
{
  int number;
  vector<int> config_numbers;
  vector<int> notch_position;
  int count = 0;
  
  ifstream in_stream;
  in_stream.open(filename);
  
  if(in_stream.fail()) {
    cerr << "Error opening rotor configuration file" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  while((in_stream >> number) && !in_stream.eof()) {  
    if(number < 0 || number >= ALPHABET_SIZE) {
      cerr << "Invalid index in rotor file" << endl;
      return INVALID_INDEX;
    }
    //Checking if a number in rotor file is connected to itself
    if(config_numbers.size() < ALPHABET_SIZE && is_repeated(config_numbers, number)) {
      cerr << "Invalid mapping of input " << count << " to output " << number << " (output " << number << " is already mapped to from input "  << config_numbers[number] + 1 << ") in " << endl;
      return INVALID_ROTOR_MAPPING;
    }
    
    if(config_numbers.size() < ALPHABET_SIZE)
      config_numbers.push_back(number);
    else
      notch_position.push_back(number);
    
    count++;
  }

  if(!in_stream.eof()) {
     cerr << "Non-numeric character for mapping in rotor file rotor.rot" << endl;
    return NON_NUMERIC_CHARACTER;
  }
  
  if(config_numbers.size() != ALPHABET_SIZE) {
     cerr << "Not all inputs mapped in rotor file: rotor.rot" << endl;
    return INVALID_ROTOR_MAPPING;
  }

  *rotor = new Rotor(config_numbers, notch_position);
  in_stream.close();
  return NO_ERROR;
}

void Rotor::set_initial_position(int number_of_rotations) {
  bool is_notch_active = false;
  for(int i = 0; i < number_of_rotations; i++)
    rotate(is_notch_active);
}

int Rotor::mapping(const int& letter) {
  return (config_numbers[(letter + count_rotation) % ALPHABET_SIZE] - count_rotation + ALPHABET_SIZE) % ALPHABET_SIZE;
}

int Rotor::mapBack(const int& letter) {
  for(unsigned int i = 0; i < config_numbers.size(); i++) {
    if(config_numbers[i] == (letter + count_rotation) % ALPHABET_SIZE)
      return (i - count_rotation + ALPHABET_SIZE) % ALPHABET_SIZE;
  }
  return NO_ERROR;
}

void Rotor::rotate(bool is_notch_active) {
  count_rotation = (count_rotation + 1) % ALPHABET_SIZE;

  //If the position is zero, previous rotor will rotate
  if(is_notch_active && is_notch_aligned() && previous != NULL)
    previous->rotate(is_notch_active);
}
