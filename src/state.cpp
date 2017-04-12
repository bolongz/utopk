/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "state.h"
#include <cassert>

State::State(): _prob{1.0}, _length{0}, _end{-1},_rank{-1}{}

State::State(const State &cu){

    _current = cu.current();
    _negative = cu.negative();
    _prob = cu.prob();
    _length = cu.length();
    _end = cu.end();

}

State::State(State &&cu){
    
    _current = cu.current();
    _negative = cu.negative();
    _prob = cu.prob();
    _length = cu.length();
    _end = cu.end();

    cu.~State();

}

const State &State::operator=(const State &state){

   if(this == &state){
    
       return *this;
   }
    
   _current = state.current();
    _negative =state.negative();
    _prob = state.prob();
    _length = state.length();
    _end =state.end();

    return *this;
}

State &State::operator=(State &&state){

    if(this == &state){
        return *this;
    
    }
   
    _current = state.current();
    _negative = state.negative();
    _prob = state.prob();
    _length =state.length();
    _end = state.end();

    state.~State();
    
    return *this;
}
//State::State(const State::Current &cu, const State::Prob &_p, const State::Length &_l){
//    _current = cu;
//    _prob = _p;
//    _length = _l;
//}

//void State::extend(const Length &e, const Last &l){
    //keep length extension }
//void extend_length(const Sta &s, const Length &e, const Last &l); // extension length

State::~State(){
    
    Current().swap(_current);
    Current().swap(_negative);
    _prob = 1.0;
    _length = 0.0;
    _end = -1;
    _rank = -1;
}

void State::extend(const State::Sta &s, const bool &positive){ // extension length
    
    if(positive){
        _current.push_back(s);
        _length = _length + 1;
        _rank = s;
    }else{
        _negative.push_back(s);
    }
    _end = s;
}

void State::update_probability(const State::Prob &newp){
   // assert(_prob >= newp);
    _prob = newp;
}


