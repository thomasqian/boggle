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

struct strlencmp {
    bool operator() (const string& lhs, const string& rhs) const {
        const size_t lhsLen = lhs.length();
        const size_t rhsLen = rhs.length();

        if (lhsLen == rhsLen) return lhs < rhs;

        return (lhsLen < rhsLen);
    }
};

int main (int argc, char* argv[]) {

  if (argc != 2) {
      std::cout << "Usage: ./boggle min_length" << std::endl;
      return -1;
  }

  BaseBogglePlayer * p = new BogglePlayer();
  set<string> lex;

  string buffer;
  string input[4][4];
  int n;

  for (int i = 0; i < 4; ++i) {
    std::getline(std::cin, buffer);
    if (buffer.size() == 0) return 0;
    n = -1;
    for (int j = 0; j < 4; ++j) {
      n++;
      while (buffer.at(n) != ' ') {
          input[i][j] += buffer.at(n);
          ++n;
          if (n == buffer.size()) break;
      }
    }
  }

  string* board2[] = {input[0], input[1], input[2], input[3]};

  /*for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
          std::cout << board2[i][j];
      }
      std::cout << std::endl;
  }*/

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
  //std::cout << "read: " << lex.size() << std:: endl;
  infile.close();

  p->buildLexicon(lex);

  p->setBoard(4,4,board2);

  p->getAllValidWords(atoi(argv[1]), &words);

  //sort by len
  set<string, strlencmp> sorted;
  std::set<string>::iterator it;
  for (it = words.begin(); it != words.end(); ++it) {
      sorted.insert(*it);
  }

  int count = 0;
  std::cout << "Found words: " << std::endl;
  std::set<string, strlencmp>::iterator itt;
  for (itt = sorted.begin(); itt != sorted.end(); ++itt) {
      std::cout << *itt << std::endl;
      count++;
  }

  std::cout << "Found " << count << " words." << std::endl;

  delete p;
  return 0;
}
