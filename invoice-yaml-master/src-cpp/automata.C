#include "automata.h"

tran::tran() { }

tran::~tran() { }

string tran::getIn() const {
  return in;
}

string tran::getNext() const {
  return next;
}

void tran::setIn(string& in) {
  this->in = in;
}

void tran::setNext(string& next) {
  this->next = next;
}


delt::delt() 
  : trans() { }

delt::~delt() { }

void delt::addTran(tran i) {
  trans.push_back(i);
}

string delt::getNodes() const {
  return nodes;
}

i_trans delt::getTrans() {
  return trans.begin();
}

i_trans delt::getLastTran() {
  return trans.end();
}

void delt::setNodes(string& nodes) {
  this->nodes = nodes;
}

automata::automata() 
  : id(0), delta() { }

automata::~automata() {
}

void automata::addDelta(delt i) {
  delta.push_back(i);
}

string&
automata::getDescription() const {
  return *(new string(this->description));
}

int
automata::getId() const {
  return this->id;
}

vector<string>
automata::getAlpha() const {
  return this->alpha;
}

vector<string>
automata::getStates() const {
  return this->states;
}

string&
automata::getStart() const {
  return *(new string(this->start));
}

vector<string>
automata::getFinal() const {
  return this->final;
}

i_delta automata::getDelta() {
  return delta.begin();
}

i_delta automata::getLastDelta() {
  return delta.end();
}

void automata::setDescription(string& description) {
  this->description = description;
}

void automata::setStart(string& start) {
  this->start = start;
}

void automata::setAlpha(vector<string> alpha1) {
  this->alpha = alpha1;
}

void automata::setStates(vector<string> states) {
  this->states = states;
}

void automata::setFinal(vector<string> final) {
  this->final = final;
}

void automata::setId(string& id) {
  istringstream in(id);
  int val;
  in >> val;
  this->id = val;
}
