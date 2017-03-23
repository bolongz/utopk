/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#ifndef _UTOPK_
#define _UTOPK_

#include "tuple.h"
#include "state.h"
#include "engine.h"
#include <queue>


class Utopk{

    //typedef std::vector<Tuple> Source; //source tuple ranked with socre
    typedef std::vector<Tuple> Seen; // seen tuples 
    typedef int Deepth; //scan deepth 
    typedef int Length; // state length 
    typedef int Last;  // last seen tuples 
    //typedef int Querylength;
    private:
        auto cmp= [](State left, State Right) return{ left.prob() < right.prob();}
        typedef std::priority_queue<State, std::Vector<State>, decltype(cmp)> Q(cmp);

        State state; // empty state with length 0, and prob 1.0
        Deepth deep; // scan deepth;
        Length length; // state length = 0;

       // Source source; 
       // Querylength k; // query length 
       Seen seen_tuples; // define the tuples already seen 

    public:
        Utopk();

        

    
    
    


}



#endif
