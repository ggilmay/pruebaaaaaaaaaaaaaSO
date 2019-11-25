#include <iostream>
#include <iomanip>
#include <fstream>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <map>
#include <string> 
#include <thread>
#include <pthread.h> 
#include <semaphore.h>
#include <algorithm> 
#include "automata.h"
#include "automat.h"
#include "sisctrl.h"

using namespace std;

vector<automat> ats;
int y;
sem_t mutex;
map<string, string> m;
map<string, string> msg;

void operator >> (const YAML::Node& node, tran& tran) {
  string in;
  string next;
  node["in"] >> in;
  node["next"] >> next;

  tran.setIn(in);
  tran.setNext(next);
}

void operator >> (const YAML::Node& node, delt& delt) {
  string nodes;
  node["node"] >> nodes;
  delt.setNodes(nodes);
  const YAML::Node& trans = node["trans"];

  for (unsigned i = 0; i < trans.size(); i++) {
    tran it; 
    trans[i] >> it;
    delt.addTran(it);
  }
}

void operator >> (const YAML::Node& node, automata &automata) {
  string id;
  node["automata"] >> id;
  string description;
  node["description"] >> description;
  vector<string> alpha;
  node["alpha"] >> alpha;
  vector<string> states;
  node["states"] >> states;
  string start;
  node["start"] >> start;
  vector<string> final;
  node["final"] >> final;
  automata.setId(id);
  automata.setDescription(description);
  automata.setAlpha(alpha);
  automata.setStates(states);
  automata.setStart(start);
  automata.setFinal(final);
  const YAML::Node& delta = node["delta"];
  
  for (unsigned i = 0; i < delta.size(); i++) {
    delt it; 
    delta[i] >> it;
    automata.addDelta(it);
  }
}

automatas&
parserAutomatasFile(char *filename) {
  ifstream fin(filename);

  automatas* auts = new automatas();

  YAML::Parser parser(fin);
  YAML::Node doc;

  parser.GetNextDocument(doc);
  for (unsigned i = 0; i < doc.size(); i++) {
    automata aut;
    doc[i] >> aut;
    auts->push_back(aut);
  }
  return *auts;
}

void
readParser(automatas& inv) {
  for(i_automatas it = inv.begin(); it != inv.end(); ++it) {
    //if(ids == (*it).getId()){
      automat automatss;
      automatss.id = (*it).getId();
      automatss.description = (*it).getDescription();
      automatss.start = (*it).getStart();

      for (int i = 0; i<(*it).getAlpha().size(); i++){
        automatss.aplha.push_back((*it).getAlpha().at(i));
      }

      for (int i = 0; i<(*it).getStates().size(); i++){
        automatss.states.push_back((*it).getStates().at(i));
      }

      for (int i = 0; i<(*it).getFinal().size(); i++){
        automatss.final.push_back((*it).getFinal().at(i));
      }

      for(i_delta delt = (*it).getDelta(); delt != (*it).getLastDelta(); ++delt) {
        delts deltass;
        deltass.node = delt->getNodes();
        for(i_trans tran = (*delt).getTrans(); tran != (*delt).getLastTran(); ++tran){
          transporte transport;
          transport.in = tran->getIn();
          transport.next = tran->getNext();
          deltass.trans.push_back(transport);
        }
        automatss.delte.push_back(deltass);
      }
      ats.push_back(automatss);
    //}
  }
}

void
usage(const char* name) {
  cerr << "Usage: " << name << " <yamlfile>.yaml" << endl;
  exit(0);
}

void*
checkStates(void* ) {
  sem_wait(&mutex);
  cout << "Padre:  "<< getppid() << endl; 
  for(int i=0;i<ats.at(y).delte.size();i++) // loop will run n times (n=5) 
    { 
        if(fork() == 0) 
        { 
            cout << "- node: " << ats.at(y).delte.at(i).node << endl;
            cout << "  pid: " << getpid() << endl;
            exit(0); 
        } 
    } 
    y++;
    sem_post(&mutex); 
}

string removeSpacess(string str)  
{ 
    
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
} 

void readMessage() {
  string name;
  string mensajes[2];
  int i = 0;
  //std::cout << "Please, enter your full name: ";
  getline (cin,name);
  stringstream x(name);
  getline(x, name, ':');
  getline(x, name, ' ');
  name = removeSpacess(name);
  getline(x, name, ','); 
  m["cmd"] = name;
  getline(x, name, ':');
  getline(x, name, ' ');
  getline(x, name, '}');
  m["msg"] = name;
}

int
main(int argc, char *argv[]) {

  sem_init(&mutex, 0, 1);
  //int ids = 0;
  //cin >> ids;
  if (argc != 2) {
    usage(argv[0]);
  }
  automatas& inv = parserAutomatasFile(argv[1]);
  readParser(inv);
  readMessage();
  cout << m["cmd"] << endl;
  cout << m["msg"] << endl;
  pthread_t hiloAutomatas[ats.size()];
  for(int i=0;i<ats.size();i++) // loop will run n times (n=5) 
    { 
      if(pthread_create(&hiloAutomatas[i],NULL,checkStates,NULL) != 0) {
        cerr << "No se pudo crear hilo: " << errno << endl;
      _exit(1); 
      }
      //pthread_join(hiloAutomatas[i], 0);
    }
  for (int i=0;i<ats.size();i++) {
    pthread_join(hiloAutomatas[i], NULL);
  } 
  //for(int i = 0; i<ats.size(); i++) {
  //}
  //cout << ats.at(1).delte.at(1).node << endl;
  return 0;
}
