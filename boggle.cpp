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
#include <utility>
#include <unordered_map>

struct strlencmp {
    bool operator() (const string& lhs, const string& rhs) const {
        const size_t lhsLen = lhs.length();
        const size_t rhsLen = rhs.length();

        if (lhsLen == rhsLen) return lhs < rhs;

        return (lhsLen < rhsLen);
    }
};

typedef std::unordered_map<char,int> dict;
static dict getWeights() {
    dict weights;
    weights['a'] = 1;
    weights['b'] = 4;
    weights['c'] = 4;
    weights['d'] = 2;
    weights['e'] = 1;
    weights['f'] = 1;
    weights['g'] = 3;
    weights['h'] = 4;
    weights['i'] = 1;
    weights['j'] = 8;
    weights['k'] = 5;
    weights['l'] = 1;
    weights['m'] = 3;
    weights['n'] = 1;
    weights['o'] = 1;
    weights['p'] = 4;
    weights['q'] = 10;
    weights['r'] = 1;
    weights['s'] = 1;
    weights['t'] = 1;
    weights['u'] = 2;
    weights['v'] = 4;
    weights['w'] = 4;
    weights['x'] = 8;
    weights['y'] = 4;
    weights['z'] = 10;

    return weights;
}

typedef std::pair<string,int> ruzWord;
struct ruzWordCmp {
    bool operator() (const ruzWord& lhs, const ruzWord& rhs) const {
        if (lhs.second == rhs.second) return lhs.first.compare(rhs.first);
        return lhs.second < rhs.second;
    }
};

int getValue(std::string s, dict& d) {
    int val = 0;
    for (int i = 0; i < s.length(); ++i) {
        val += d[s[i]];
    }

    val += (s.length() - 4) * 5;

    return val;
}

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

  /*
  //sort by len
  set<string, strlencmp> sorted;
  std::set<string>::iterator it;
  for (it = words.begin(); it != words.end(); ++it) {
      sorted.insert(*it);
  }*/

  set<ruzWord, ruzWordCmp> sorted;
  std::set<string>::iterator it;
  dict d = getWeights();
  for (it = words.begin(); it != words.end(); ++it) {
      sorted.insert(ruzWord(*it, getValue(*it, d)));
  }

  int count = 0;
  std::cout << "Found words: " << std::endl;
  //std::set<string, strlencmp>::iterator itt;
  std::set<ruzWord, ruzWordCmp>::iterator itt;
  for (itt = sorted.begin(); itt != sorted.end(); ++itt) {
      //std::cout << *itt << std::endl;
      std::cout << (*itt).first << " " << (*itt).second << std::endl;
      count++;
  }

  std::cout << "Found " << count << " words." << std::endl;

  delete p;
  return 0;
}
