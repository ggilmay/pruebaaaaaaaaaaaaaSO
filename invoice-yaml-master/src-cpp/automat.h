#include "automata.h"

class transporte {
  public:
    string in;
    string next;
};

class delts {
  public:
    string node;
    vector<transporte> trans;
};

class automat {
 public:
  int id;
  string description;
  vector<string>  aplha;
  vector<string> states;
  string start;
  vector<string> final;
  vector<delts> delte;
};



