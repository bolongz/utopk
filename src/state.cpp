/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "state.h"
#include <cassert>

State::State():_current{{0}}, _prob{1.0}, _length{0}, _end{1000000}{}

State::State(const State::Current &cu, const State::Prob &_p, const State::Length &_l){
    _current = cu;
    _prob = _p;
    _length = _l;
}

//void State::extend(const Length &e, const Last &l){
    //keep length extension }
//void extend_length(const Sta &s, const Length &e, const Last &l); // extension length

void State::extend(const State::Sta &s, const bool &positive){ // extension length
    
    if(positive){
        _current.push_back(s);
        _length = _length + 1;
        _end = s;
    }else{
        _negative.push_back(s);
    }
}

void State::update_probability(const State::Prob &newp){
    assert(_prob >= newp);
    _prob = newp;
}


