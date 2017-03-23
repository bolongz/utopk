/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#ifndef _UTOPK_
#define _UTOPK_

#include "tuple.h"
#include "state.h"
#include "engine.h"
#include <queue>


//auto cmp= [](State left, State right) {return left.prob() < right.prob();};

class Utopk{

    //typedef std::vector<Tuple> Source; //source tuple ranked with socre
    public:
        typedef std::vector<Tuple> Seen; // seen tuples 
        typedef size_t Deepth; //scan deepth 
        typedef int Length; // state length 
        typedef size_t Last;  // last seen tuples 
        typedef int Querylength;
    private:
 //       std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
        State state; // empty state with length 0, and prob 1.0
        Deepth deep; // scan deepth;
        Length length; // state length = 0;
        Last last;
       // Source source; 
       // Querylength k; // query length 
       Seen seen_tuples; // define the tuples already seen 

    public:
        Utopk();

        State topk(const Engine::Rules &R, const Engine::Source &source, const Querylength &k);    
};



#endif
