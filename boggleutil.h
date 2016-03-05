#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

//Data structures for lexicon and board should reside in this file.
//All of the operations your data structures support should be declared within your data structures.

class MNode {
    friend class MTrie;
    public:
    MNode();
    ~MNode();

    private:
    MNode *children[26];
    bool end;
};

class MTrie {
    public:
    MTrie();
    ~MTrie();

    bool find(string s);
    void insert(string s);
    bool isPrefix(string s);

    private:
    MNode *root;
    void deleteAll(MNode *root);
};

class Tile {
    friend class Board;
    public:
    Tile();
    Tile(int row, int col, string data);
    ~Tile();

    private:
    int row, col;
    string data;
    bool used;
    vector<Tile*> nb;
};

class Board {
    public:
    Board(int rows, int cols, string** data);
    ~Board();

    vector<Tile*> faces;
    void setNeighbors();
    int isOnBoardHelper(vector<Tile*>& v, string toFind, vector<int>& result);
    void getWords(const int min, set<string>* words, MTrie* lex);

    private:
    int rows, cols;
    Tile ***board;
    void getWordsHelper(Tile* t, const int min, string s, set<string>* words, MTrie* lex);
};

int getInt(string s, int i);

#endif
