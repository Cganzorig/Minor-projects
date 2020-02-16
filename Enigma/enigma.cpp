/* Impelementation file "Enigma.cpp"  */

#include "enigma.h"

using namespace std;

Enigma::Enigma(Plugboard* plugboard, Reflector* reflector, const vector<Rotor*> &rotors):
  plugboard(plugboard), reflector(reflector), rotors(rotors), number_of_rotors(rotors.size()) {}

Enigma::~Enigma() {
  delete plugboard;
  delete reflector;
  for(unsigned int i = 0; i < rotors.size(); i++)
    delete rotors[i];
}

//Encrypting each character of message
void Enigma::encrypt_char(char& ch) {
  bool is_notch_active = true;
  int letter = char_to_int(ch);
  
  letter = plugboard->mapping(letter);
  
  if(number_of_rotors > 0)
    rotors[number_of_rotors - 1]->rotate(is_notch_active);
  
  for(int i = number_of_rotors - 1; i >= 0; i--)
    letter = rotors[i]->mapping(letter);	
  
  letter = reflector->mapping(letter);
  
  for(int i = 0; i < number_of_rotors ; i++)
    letter = rotors[i]->mapBack(letter);
  
  letter = plugboard->mapping(letter);
  
  ch = int_to_char(letter);
}

void Enigma::rotor_connection(vector<Rotor*> &rotors) {
  if(rotors.size() > 0) {
    rotors[0]->previous = NULL;
    for(unsigned int i = 1; i < rotors.size(); i++)
	rotors[i]->previous = rotors[i - 1];	
  }
}

int Enigma::set_rotor_position(vector<Rotor*> &rotors, const char* filename) {
  int number;

  vector<int> position_number;

  ifstream in_stream;
  in_stream.open(filename);

  //Checking errors
  if(in_stream.fail()) {
    cerr << "Error opening rotor position file" << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  while((in_stream >> number) && !in_stream.eof()) {
    if(number < 0 || number >= ALPHABET_SIZE) {
      cerr << "Invalid index in rotor position file" << endl;
      return INVALID_INDEX;
    }
    position_number.push_back(number);	
  }

  if(!in_stream.eof()) {
    cerr << "Non-numeric character in rotor positions file rotor.pos" << endl;
    return NON_NUMERIC_CHARACTER;
  }

  if(position_number.size() != rotors.size()) {
    cerr << "No starting position for rotor 0 in rotor position file: rotor.pos"  << endl;
    return NO_ROTOR_STARTING_POSITION;
  }

  for(unsigned int i = 0; i < rotors.size(); i++)
    rotors[i]->set_initial_position(position_number[i]);
  
  in_stream.close();
  return NO_ERROR;	
}

//Encrypting message
int Enigma::encrypt_message(string& message)
{
    string str;
    while (!cin.eof()) {
      cin >> ws  >> str;
      for(unsigned int i = 0; i < str.length(); i++) {
	if(!(isupper(str[i]) || str[i] == 9 || str[i] == 10 || str[i] == 13 || str[i] == 32)) {
	    cerr << str[i] << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
	    return INVALID_INPUT_CHARACTER;
	}
	encrypt_char(str[i]);
	cout << str[i];
      }
      message.append(str);
      cin >> ws;
    }
    cout << " " << endl;
    return NO_ERROR;
}

int Enigma::initialise_enigma(int argc, char** argv, int number_of_rotors, Enigma** enigma)
{
  int good;
  char* plugboard_file = argv[1];
  char* reflector_file = argv[2];
  char* rotor_position_file;

  //Creating plugboard, reflector and rotors using pointers
  vector<char*> rotor_file;
  Plugboard* plugboard;
  Reflector* reflector;
  vector<Rotor*> rotors(number_of_rotors);
  
  for(int i = 3; i < argc - 1; i++)
    rotor_file.push_back(argv[i]);

  if(argc > 3)
    rotor_position_file = argv[argc - 1];

  good = plugboard->initialise_plugboard(plugboard_file, &plugboard);

  if(good)
    return good;
  
  good = reflector->initialise_reflector(reflector_file, &reflector);

  if(good) {
    delete plugboard;
    return good;
  }

  for(int i = 0; i < number_of_rotors; i++) {
    good = Rotor::initialise_rotor(rotor_file[i], &rotors[i]);
      if(good) {
	delete reflector;
	delete plugboard;
	return good;
      }
  }

  if(number_of_rotors > 0) {
    rotor_connection(rotors);
    good = set_rotor_position(rotors, rotor_position_file);
    if(good) {	
      for(int i = 0; i < number_of_rotors; i++)
	delete rotors[i];
      delete reflector;
      delete plugboard;
      return good;
    }
  }

  *enigma = new Enigma(plugboard, reflector, rotors);
  return NO_ERROR;
}
