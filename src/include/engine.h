/*Author: Bolong Zhang */
/*Email: blzhang.m@gmail.com */

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

        /* Constructors */
        Engine();
        Engine(const Engine &e);
        Engine(Engine &&e);
        const Engine &operator=(const Engine &e);
        Engine &operator=(Engine &&e);
        Engine(const Rules &R, const Source &S);
       
        ~Engine();
        
        void start(const Rules &R, const Source &S);

        Source source() const { return _source;}
        Binary rules()const {return _rules;}
        Union unio()const {return _union;}
        Size size()const {return _size;}
        
        /* Calculating the state probability */ 
        Prob computing_state_probability(const State &s) const;

};


#endif
