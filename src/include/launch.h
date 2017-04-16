/*Author: Bolong Zhang */
/*Email: blzhang.m@gmail.com */

#ifndef _LAUNCH_H_
#define _LAUNCH_H_

#include "state.h"
#include <cassert>
#include <set>

class Launch{

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
        Launch();
        Launch(const Launch &e);
        Launch(Launch &&e);
        const Launch &operator=(const Launch &e);
        Launch &operator=(Launch &&e);
        Launch(const Rules &R, const Source &S);
       
        ~Launch();
        
        
        void start(const Rules &R, const Source &S);

        Source source() const { return _source;}
        Binary rules()const {return _rules;}
        Union unio()const {return _union;}
        Size size()const {return _size;}
        
        
        /* Calculating the state probability */ 
        Prob computing_state_probability(const State &s) const;

};


#endif
