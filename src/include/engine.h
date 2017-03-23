#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "state.h"
#include <cassert>
#include <set>

class Engine{

    public:
    
        typedef std::vector<std::set<int>> Rules;
        typedef std::vector<Tuple> Source;  
        typedef std::vector<int> Binary;
        typedef double Prob;
        typedef std::set<int> Union;
        typedef std::set<int>::iterator Iterator;
        typedef int Size; 
    private:
        //Rules _rules; //store the rules 
        Source _source; // store the source 
        Binary _rules; // convert the rules into binary format
        Union _union; 
        Size _size; 
    
    public:

        /* Constructor */
        Engine();
        Engine(const Rules &R, const Source &S);
        /* Calculating the state probability */ 
        Prob computing_state_probability(const State &s);

};


#endif