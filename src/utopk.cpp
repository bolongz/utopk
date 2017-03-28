/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "utopk.h"

/*constructor */
Utopk::Utopk():deep{0}, length{0},last(-1){}

Utopk::Utopk(const Utopk &t){

   state = t.get_state();
   deep = t.get_deep();
   length = t.get_length();
   last = t.get_last();
   seen_tuples = t.get_seen();

}

Utopk::Utopk(Utopk &&t){

   state = t.get_state();
   deep = t.get_deep();
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
   deep = t.get_deep();
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
   deep = t.get_deep();
   length = t.get_length();
   last = t.get_last();
   seen_tuples = t.get_seen();
   t.~Utopk();
   return *this;
}   

Utopk::~Utopk(){
    Seen().swap(seen_tuples);
    deep = 0;
    length = 0;
    last = -1;
    
}
/* Processing topk */
State Utopk::topk(const Engine::Rules &R, const Engine::Source &source, const Utopk::Querylength &k) {
   
    auto cmp= [](State left, State right) {return left.prob() < right.prob();};
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    
    Q.push(state); // put the initial state into Q
    
    Engine engine(R, source);
    while( deep <= source.size() && !Q.empty()){
    
        State *s = const_cast<State*>(&Q.top());
        if(s->length() == k){
            return (*s);
        }else{
            if(last == deep){
                deep += 1;     
            }
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

    }
    return Q.top();

}
