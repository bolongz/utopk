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
State Utopk::topk(const Engine &engine, const Engine::Source &source, const Utopk::Querylength &k) {
      
    auto cmp= [](State left, State right) {return left.prob() < right.prob();};
    std::priority_queue<State, std::vector<State>, decltype(cmp)> Q(cmp);
    
    Q.push(state); // put the initial state into Q
//    state.print_state();
    //Engine engine(R, source);
    deep = -1;
    int _size = int(source.size());
    //std::cout << deep <<" " << source.size() << " " << std::endl;
    while( deep < _size || !Q.empty()){
        
        State s1 = Q.top();
        State *s = &s1;
        //State *s = const_cast<State*>(&Q.top());
        //std::cout <<"XXXXQ: " << Q.size() << std::endl;
        Q.pop();
//        s->print_state();
        last = s->end();
        //std::cout << "----BEFORE: " <<Q.size() <<" " <<  s->length() <<" "  <<k << " "<< s->end()  << " " << deep << " " << s->prob() << std::endl;
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
            
       
            //std::cout << "XXX  " << last << " " << deep << std:: endl;
            State state1 = *s;
            State state2 = *s;
        
            state1.extend(last, true);  // positive 
            state2.extend(last, false); //negative 
        
            //std::cout << "STATE EXT " << std::endl;
   //         state1.print_state();
    //        state2.print_state();
            //std::cout << "STATE EXT " << std::endl;
        
            double prob1 = engine.computing_state_probability(state1);
            //std::cout <<" =++++++++++++++" << std::endl;
            double prob2 = engine.computing_state_probability(state2);
        
            //std::cout << "Prob: " << prob1 << "  " << prob2 << std::endl;
            state1.update_probability(prob1);
            state2.update_probability(prob2);
        
            Q.push(state1);
            Q.push(state2);
        }
        
   
    }
    return Q.top();

}
