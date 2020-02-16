#include "helper.h"

using namespace std;

bool is_repeated(vector<int> vector, int number) {
  if(find(vector.begin(), vector.end(), number) != vector.end())
    return true;
  else
    return false;
}
int char_to_int(char ch) {
  return ch - LETTER_CAPITAL_A;
}
char int_to_char(int ch) {
  return ch + LETTER_CAPITAL_A;
}
