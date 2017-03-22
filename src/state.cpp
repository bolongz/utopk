/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "state.h"

State::State(): _current{{0}}, _prob{1.0}, _length{0}, _last{0}{}

State(const Current &cu, const Prob &_p, const Length &_l, const &_la){
    _current = cu;
    _prob = _p;
    _length = _l;
    _last = _la;
}


