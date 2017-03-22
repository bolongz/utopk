/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#ifndef _STATE_H_
#define _STATE_H_

#include "tuple.h"

/* define the state class */
/* State is the vector of the tuples */
class State{

    public:
        typedef int Sta; // state element status 
        typedef std::vector<Sta> Current;
        typedef double Prob;
        typedef int Length;
        typedef int Last;
    private:
        Current _current; // store the current state
        Prob _prob; // probability 
        Length _length; //state length;
        Last _last;// Last seen tuple;
    
    public:
        
        /* constructor */
        State();
        State(const Current &cu, const Prob &_p, const Length &_l, const &_la);
        
        /* Access elements */ 
        Prob prob() const{return _prob;}
        Length length() const {return _length;}
        Last last() const {return _last;}
        Current current() const {return _current;}

        void extend(const Sta &s, const Length &e, const Last &l);
};


#endif
