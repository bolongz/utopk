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
        typedef int End;
    private:
        Current _current; // store the current state if the element is negative means cannot show
        Current _negative; // means the element must not in the mbstate_tus
        Prob _prob; // probability 
        Length _length; //state length;
        End _end;// Last seen tuple;
        End _rank;    
   
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
        
        End ranki() const {return _rank;}
        //void extend(const Length &e, const Last &l);//keep length extension 
        void extend(const Sta &s,  const bool &flag); // extension length
        //void extend_length(const Sta &s, const Length &e, const Last &l); // extension length
        
        void update_probability(const Prob & newp);

        void print_state(){
            std::cout << "exist tuples: ";
            for(size_t i=0; i < _current.size(); i++){
                std::cout <<_current[i] <<" ";
            }
            std::cout << std::endl << "absent tuples: ";
            for(size_t i=0; i < _negative.size(); i++){
                std::cout <<_negative[i] <<" ";
            }
            std::cout <<std::endl;
        }
        
        void exist_tuples(){
            std::cout << "exist tuples: ";
            for(size_t i=0; i < _current.size(); i++){
                std::cout <<_current[i] <<" ";
            }
            std::cout <<std::endl;
        }
        
        void absent_tuples(){
            
            for(size_t i=0; i < _negative.size(); i++){
                std::cout <<_negative[i] <<" ";
            }
            std::cout <<std::endl;
        }
        
};


#endif
