#include"boggleutil.h"

//In this file, implement all of the operations your data structures support (you have declared these operations in boggleutil.h).

Board::Board(int rows, int cols, string** data) {
    this->rows = rows;
    this->cols = cols;
    
    board = new Tile**[rows];
    
    for (int r = 0; r < rows; ++r) {
        board[r] = new Tile*[cols];
    }

    string str;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            str = data[i][j];
            transform(str.begin(), str.end(), str.begin(), ::tolower);
            board[i][j] = new Tile(i, j, str);
            faces.push_back(board[i][j]);
        }
    }
}

Board::~Board() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete board[i][j];
        }
        delete board[i];
    }
    delete board;
}

void Board::setNeighbors() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < 8; ++k) {
                if (k == 0 && i > 0) //0 
                    board[i][j]->nb.push_back(board[i-1][j]);
                if (k == 1 && i > 0 && j < cols - 1) //1 
                    board[i][j]->nb.push_back(board[i-1][j+1]);
                if (k == 2 && j < cols - 1) //2
                    board[i][j]->nb.push_back(board[i][j+1]);
                if (k == 3 && j < cols - 1 && i < rows - 1) //3 
                    board[i][j]->nb.push_back(board[i+1][j+1]);
                if (k == 4 && i < rows - 1) //4
                    board[i][j]->nb.push_back(board[i+1][j]);
                if (k == 5 && i < rows - 1 && j > 0) //5
                    board[i][j]->nb.push_back(board[i+1][j-1]);
                if (k == 6 && j > 0) //6
                    board[i][j]->nb.push_back(board[i][j-1]);
                if (k == 7 && j > 0 && i > 0) //7
                    board[i][j]->nb.push_back(board[i-1][j-1]);
            }
        }
    }

    /*for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << board[i][j]->data << ": ";
            for (int k = 0; k < board[i][j]->nb.size(); ++k) 
                cout << board[i][j]->nb[k]->data << " ";
            cout << endl;
        }
    }*/
}

int Board::isOnBoardHelper(vector<Tile*>& v, string toFind, vector<int>& result) {
    if (toFind.empty()) return 0;

    for (int i = 0; i < v.size(); ++i) {
        if (v[i]->used) continue;
        if (toFind.compare(0, v[i]->data.size(), v[i]->data) == 0) {
            result.push_back(v[i]->row*cols + v[i]->col);
            v[i]->used = true;
            if (isOnBoardHelper(v[i]->nb, toFind.substr(v[i]->data.size(), 
                toFind.size() - 1), result) == 0) {
                v[i]->used = false;
                return 0;
            } else {
                v[i]->used = false;
            }
        }
    }

    if(!result.empty()) result.pop_back();
    return -1;
}

void Board::getWords(const int min, set<string>* words, MTrie* lex) {
    string s;
    for (int i = 0; i < faces.size(); ++i) {
        getWordsHelper(faces[i], min, s, words, lex);
    }
}

void Board::getWordsHelper(Tile *t, const int min, string s, set<string>* words, MTrie* lex) {
    if (!t) return;
    if (t->used) return;
    s += t->data;
    t->used = true;
    if (s.size() >= min && lex->find(s) && (words->find(s) == words->end())) words->insert(s);
    
    if (lex->isPrefix(s)) {
        for (int i = 0; i < t->nb.size(); ++i) {
            getWordsHelper(t->nb[i], min, s, words, lex);
        }
    }
    t->used = false;
}

Tile::Tile() {}

Tile::Tile(int row, int col, string data) {
    this->row = row;
    this->col = col;
    this->data = data;
    used = false;
}

Tile::~Tile() {}

MTrie::MTrie() {
    root = 0;
}

bool MTrie::find(string s) {
    MNode *curr = root;

    for (int i = 0; i < s.size(); ++i) {
        if (curr == 0) return false;
        curr = curr->children[getInt(s, i)];
    }
    
    if (!curr) return false;
    if (curr->end) return true;
    return false;
}

void MTrie::insert(string s) {
    if (!root) root = new MNode();
    MNode *curr = root;
    int childNum;

    for (int i = 0; i < s.size(); ++i) {
        childNum = getInt(s, i);
        if (curr->children[childNum]) {
            curr = curr->children[childNum];
        } else {
            curr->children[childNum] = new MNode();
            curr = curr->children[childNum];
        }
    }
    curr->end = true;
}

bool MTrie::isPrefix(string s) {
    MNode *curr = root;

    for (int i = 0; i < s.size(); ++i) {
        if (curr == 0) return false;
        curr = curr->children[getInt(s, i)];
    }
    
    if (!curr) return false;

    for (int i = 0; i < 26; ++i) {
        if (curr->children[i]) return true;
    }

    return false;
}

MTrie::~MTrie() {
    //deleteAll(root);    
}

void MTrie::deleteAll(MNode *root) {
    if (root == 0) return;

    for (int i = 0; i < 26; ++i) {
        deleteAll(root->children[0]);
    }

    delete root;
}

MNode::MNode() {
    for (int i = 0; i < 26; ++i) children[i] = 0;
    end = false;
}

MNode::~MNode() {}

int getInt(string s, int i) {
    return s.at(i) - 97;
}
