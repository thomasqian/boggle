#include "boggleplayer.h"
#include <iostream>

void BogglePlayer::buildLexicon(const set<string>& word_list) {
    if (lex) delete lex;
    lex = new MTrie();

    set<string>::iterator it;
    for (it = word_list.begin(); it != word_list.end(); ++it) {
        lex->insert(*it);
    }
}

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {
    boggle = new Board(rows, cols, diceArray);
    boggle->setNeighbors();
}

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
    if (!boggle || !lex) return false;

    boggle->getWords(minimum_word_length, words, lex);

    return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
    if (!lex) return false;
    return lex->find(word_to_check);
}

vector<int> BogglePlayer::isOnBoard(const string& word) {
    vector<int> result;
    if (!boggle) return result;

    string temp(word);
    boggle->isOnBoardHelper(boggle->faces, temp, result);
    
    return result;
}


void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

