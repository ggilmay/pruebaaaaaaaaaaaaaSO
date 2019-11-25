#ifndef AUTOMATA_H 
#define AUTOMATA_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class tran {
 public:
  tran();
  ~tran();
  string getIn() const;
  string getNext() const;
  void setIn(string& in);
  void setNext(string& next);
 private:
  string in;
  string next; 
};

typedef vector< tran > trans_t;
typedef vector< tran >::iterator i_trans;

class delt {
 public:
  delt();
  ~delt();
  void addTran(tran);
  i_trans getTrans();
  i_trans getLastTran();
  string getNodes() const;
  void setNodes(string& nodes);
 private:
  string nodes;
  trans_t trans;
  
};

typedef vector< delt > delta_t;
typedef vector< delt >::iterator i_delta;

class automata {
 public:
  automata();
  ~automata();
  void addDelta(delt);
  i_delta getDelta();
  i_delta getLastDelta();
  vector<string> getAlpha() const;
  vector<string> getStates() const;
  vector<string> getFinal() const;
  int getId() const;
  string& getDescription() const;
  string& getStart() const;
  void setDescription(string& description);
  void setStart(string& start);
  void setId(string& id);
  void setAlpha(vector<string> alpha);
  void setStates(vector<string> states);
  void setFinal(vector<string> final);
 private:
  int id;
  string description;
  string start;
  delta_t delta;
  vector<string> alpha;
  vector<string> states;
  vector<string> final;
};

typedef vector< automata > automatas;
typedef vector< automata >::iterator i_automatas;

#endif
