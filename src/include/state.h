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
        typedef size_t Length;
        typedef size_t End;
    private:
        Current _current; // store the current state if the element is negative means cannot show
        Current _negative; // means the element must not in the mbstate_tus
        Prob _prob; // probability 
        Length _length; //state length;
        End _end;// Last seen tuple;
    
    public:
        
        /* constructor */
        State();
        State(const State &cu);
        State(State &&cu);
        const State &operator=(const State &state);
        State &operator=(State &&state);

        ~State();
        
        /* Access elements */ 
        Prob prob() const{return _prob;}
        Length length() const {return _length;}
        End end() const {return _end;}
        Current current() const {return _current;}
        Current negative() const {return _negative;}

        //void extend(const Length &e, const Last &l);//keep length extension 
        void extend(const Sta &s,  const bool &flag); // extension length
        //void extend_length(const Sta &s, const Length &e, const Last &l); // extension length
        
        void update_probability(const Prob & newp);
};


#endif
