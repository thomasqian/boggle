/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>

int main (int argc, char* argv[]) {

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;
  string wordA("a");
  string wordX("x");
  string swag("swag");
  string swwww("swwww");
  string sweer("sweer");
  string cit("cit");
  string astub("astub");
  string all("swagpblastneewwour");
  /*lex.insert(wordA);
  lex.insert(swag);
  lex.insert("swoop");
  lex.insert("swooper");
  lex.insert("blast");
  lex.insert("nub");
  lex.insert("wag");
  lex.insert("swap");
  lex.insert("rub");
  lex.insert("rob");
  lex.insert("z");*/
  string row0[] = {"D","C"};
  string row1[] = {"b","A"};
  string r0[] = {"s", "W", "a", "G"};
  string r1[] = {"w", "W", "o", "p"};
  string r2[] = {"e", "r", "u", "b"};
  string r3[] = {"E", "n", "ast", "l"};
  string* board[] = {row0,row1};
  string* board2[] = {r0, r1, r2, r3};
  set<string> words;
  vector<int> locations;

  std::ifstream infile;
  infile.open("boglex.txt");
  if (!infile.is_open()) {
      std::cout << "error opening file" << std::endl;
      exit(-1);
  }
  std::string word;
  int i = 0;
  while (infile.is_open() && infile.good()) {
      std::getline(infile, word);
      if (word.size() < 1) continue;
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
      lex.insert(word);
      i++;
  }
  std::cout << "read: " << lex.size() << std:: endl;
  infile.close();

  p->buildLexicon(lex);

  //p->setBoard(2,2,board);
  p->setBoard(4,4,board2);

  /*if(p->isInLexicon(wordX)) {
    std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
    return -1;
  }

  if(!p->isInLexicon(wordA)) {
    std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
    return -1;
  }*/

  if(!p->isInLexicon(swag)) {
    std::cerr << "Apparent problem with isInLexicon swag." << std::endl;
    return -1;
  }

  if(!p->isInLexicon("swoop")) {
    std::cerr << "Apparent problem with isInLexicon swoop." << std::endl;
    return -1;
  }

  if(!p->isInLexicon("swooper")) {
    std::cerr << "Apparent problem with isInLexicon swooper." << std::endl;
    return -1;
  }

  if(p->isInLexicon("swoope")) {
    std::cerr << "Apparent problem with isInLexicon swoope." << std::endl;
    return -1;
  }

  if(!p->isInLexicon("swoopers")) {
    std::cerr << "Apparent problem with isInLexicon swoopers." << std::endl;
    return -1;
  }

  /** isOnBoard tests **/

  if(p->isOnBoard(wordX).size() > 0) {
    std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
    return -1;
  }

  locations.clear();
  locations = p->isOnBoard(wordA);
  if(locations.size() != 1 || locations[0] != 2/*changed from 3*/) {
    std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
    return -1;
  }

  //adding
  
  locations.clear();
  locations = p->isOnBoard(swag);
  cout << "swag: ";
  for (int i = 0; i < locations.size(); ++i) cout << locations[i] << " ";
  cout << endl;

  locations.clear();
  locations = p->isOnBoard(swwww);
  cout << "swwww: ";
  for (int i = 0; i < locations.size(); ++i) cout << locations[i] << " ";
  cout << endl;

  locations.clear();
  locations = p->isOnBoard(sweer);
  cout << "sweer: ";
  for (int i = 0; i < locations.size(); ++i) cout << locations[i] << " ";
  cout << endl;

  locations.clear();
  locations = p->isOnBoard(cit);
  cout << "cit: ";
  for (int i = 0; i < locations.size(); ++i) cout << locations[i] << " ";
  cout << endl;

  locations.clear();
  locations = p->isOnBoard(astub);
  cout << "astub: ";
  for (int i = 0; i < locations.size(); ++i) cout << locations[i] << " ";
  cout << endl;

  locations.clear();
  locations = p->isOnBoard(all);
  cout << "all: ";
  for (int i = 0; i < locations.size(); ++i) cout << locations[i] << " ";
  cout << endl;

  //end
  
  
  if(!p->getAllValidWords(0,&words)) {
    std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
    return -1;
  };
  /**if(words.size() != 1 || words.count(wordA) != 1) {
    std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
    return -1;
  }*/

  std::cout << "Found words: " << std::endl;
  std::set<string>::iterator it;
  for (it = words.begin(); it != words.end(); ++it) {
      std::cout << *it << std::endl;
  }

  delete p;
  return 0;

}
