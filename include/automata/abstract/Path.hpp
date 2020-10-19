#ifndef Path_hpp
#define Path_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <set>
#include <map>
#include <vector>
#include "./State.hpp"
#include "./Word.hpp"

namespace llvmadt{


class Path
{
protected:
    std::vector<State*> stemStates;
    std::vector<State*> loopStates;
    Word* word;
    std::map<std::string, int> varIndex;
    std::vector<std::map<std::string, int>&> varIndexArray;
    /* data */
public:
    Path(/* args */);
    Path(Alphabet* alpha);
    Path(Word* word);
    ~Path();
    std::vector<State*>& getStemStates();
    State* getStemState(int pos);
    void appendStemLetter(Letter* letter);
    void appendStemState(State* state);
    Word* getWord();
    std::vector<Letter*>& getStemLetters();
    std::vector<Letter*>& getLoopLetters();
    Letter* getStemLetter(int position);
    Letter* getLoopLetter(int position);


    std::vector<State*>& getLoopStates();
    State* getLoopState(int pos);
    void appendLoopLetter(Letter* letter);
    void appendLoopState(State* state);
    Word* getLoopWord();

    std::map<std::string, int>& getVarIndex();
    void insertVarIndex(std::string varName);
    int getVarIndexVarName(std::string varName);
    std::map<std::string, int> getCurrentVarIndex(int length);
    std::vector<std::map<std::string, int>&>& getVarIndexArray();
    void appendVarIndexArray(std::map<std::string, int>& currentVarIndex);

    std::string toString();
};
}


#endif