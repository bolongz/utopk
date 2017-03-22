#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "state.h"

#include <set>

class Engine{

    public:
        typedef std::vector<std::set<Tuple>> Rules;
        typedef std::vector<Tuple> Source;  
        typedef std::vector<int> Binary;
        typedef double Prob;
        typedef std::set<int> Union;
    private:
        //Rules _rules; //store the rules 
        Source _source; // store the source 
        Binary _rules; // convert the rules into binary format
        Union _union; 
    public:
        /* Constructor */
        Engine();
        Engine(const Rules &R, const Source &S);

        /* Calculating the state probability */ 
        
        Prob prob()
            


}


#endif
