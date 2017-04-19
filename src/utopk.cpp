/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "utopk.h"
#include <ctime>
/*constructor */
Utopk::Utopk():deep(-1), length{0},last(-1){}

Utopk::Utopk(const Utopk &t){

   state = t.get_state();
   deep = t.get_depth();
   length = t.get_length();
   last = t.get_last();
   seen_tuples = t.get_seen();

}

Utopk::Utopk(Utopk &&t){

   state = t.get_state();
   deep = t.get_depth();
   length = t.get_length();
   last = t.get_last();
   seen_tuples = t.get_seen();
   t.~Utopk();

}   

const Utopk &Utopk::operator=(const Utopk &t){
   
   if(this == &t){
   
        return *this;
   }
   state = t.get_state();
   deep = t.get_depth();
   length = t.get_length();
   last = t.get_last();
   seen_tuples = t.get_seen();

   return *this;
}   

Utopk &Utopk::operator=(Utopk &&t){
   
   if(this == &t){
   
        return *this;
   }
   state = t.get_state();
   deep = t.get_depth();
   length = t.get_length();
   last = t.get_last();
   seen_tuples = t.get_seen();
   t.~Utopk();
   return *this;
}   

Utopk::~Utopk(){
    Seen().swap(seen_tuples);
    deep = -1;
    length = 0;
    last = -1;
    
}
/* Processing topk */
State Utopk::topk(const Launch &engine, const Launch::Source &source, const Utopk::Querylength &k) {
      
    auto cmp= [](State left, State right) {return left.prob() < right.prob();};
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    
    Q.push(state); // put the initial state into Q
    deep = -1;
    int _size = int(source.size());
    while( deep < _size || !Q.empty()){
        
        State s1 = Q.top();
        State *s = &s1;
        Q.pop();
        last = s->end();
        if(int(s->length()) == k){
            
            return (*s);
       
        }else{
            
            if(last == deep){
                if(deep == _size -1 ) continue;
                deep += 1;     
                last = deep;
            }else{
                last = last + 1;
            }
            
       
            State state1 = *s;
            State state2 = *s;
        
            state1.extend(last, true);  // positive 
            state2.extend(last, false); //negative 
        
            double prob1 = engine.computing_state_probability(state1);
            double prob2 = engine.computing_state_probability(state2);
        
            state1.update_probability(prob1);
            state2.update_probability(prob2);
        
            Q.push(state1);
            Q.push(state2);
        }
        
   
    }
    return Q.top();

}
