#ifndef _UKRANK_H_
#define _UKRANK_H_

#include "tuple.h"
#include "state.h"
#include "engine.h"

class Ukrank{

    public:
        typedef std::vector<int> Answer;
        typedef std::vector<double> Ubounds;
        typedef std::vector<double> AnswerProbability;
        typedef std::vector<bool> Flag;
        typedef size_t Reported;
        typedef size_t Depth;
        typedef std::vector<State> Space;
        typedef size_t Querylength;

    private:

        Answer answer;
        Ubounds ubounds;
        AnswerProbability ap;
        Flag rflag;//store if the answer has already reported;
        Depth depth;
        Space space;
        Reported reported;

    public:

        Ukrank();

        
        Answer ukrank(const Engine::Rules &R, const Engine::Source &source, const Querylength &k);
};

#endif
