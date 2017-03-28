/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "ukrank.h"

Ukrank::Ukrank():depth{1}, reported{0}{}

Ukrank::Ukrank(const Ukrank &t){

    answer = t.get_answer();
    ubounds = t.get_ubounds();
    ap = t.get_ap();
    rflag = t.get_flag();
    depth =t.get_depth();
    space = t.get_space();
    reported = t.get_reported();

}

Ukrank::Ukrank(Ukrank &&t){

    answer = t.get_answer();
    ubounds = t.get_ubounds();
    ap = t.get_ap();
    rflag = t.get_flag();
    depth =t.get_depth();
    space = t.get_space();
    reported = t.get_reported();

    t.~Ukrank();
}

const Ukrank &Ukrank::operator=(const Ukrank &t){

    if(this == &t){
        
        return *this;
   
    }

    answer = t.get_answer();
    ubounds = t.get_ubounds();
    ap = t.get_ap();
    rflag = t.get_flag();
    depth =t.get_depth();
    space = t.get_space();
    reported = t.get_reported();

    return *this;
}

Ukrank &Ukrank::operator=(Ukrank &&t){

    if(this == &t){
        return *this;
   
    }

    answer = t.get_answer();
    ubounds = t.get_ubounds();
    ap = t.get_ap();
    rflag = t.get_flag();
    depth =t.get_depth();
    space = t.get_space();
    reported = t.get_reported();
    t.~Ukrank();
    return *this;
}

Ukrank::~Ukrank(){

    Answer().swap(answer);
    Ubounds().swap(ubounds);
    AnswerProbability().swap(ap);
    Flag().swap(rflag);
    Space().swap(space);
    depth = 1;
    reported = 0;
}
Ukrank::Answer Ukrank::ukrank(const Engine::Rules &R, const Engine::Source &source, const Ukrank::Querylength &k){

    answer.resize(k, 0);
    ap.resize(k, 0);
    ubounds.resize(k, -1);
    rflag.resize(k, false);

    Engine engine(R, source);
    while((depth <= source.size()) & (reported < k)){
        
        size_t t = depth -1; //next tuples from source
        size_t _min = std::min(k, depth);
        
        for(size_t i = 1; i <= _min; i++ ){

            State state1, state2;
            if(!space.empty()){
                for(size_t j = 0; j < space.size(); j++){
                    
                    state1 = space[j];
                    state2 = space[j];
                
                }
            }
            
            state1.extend(t, true); //state extension
            state2.extend(t,false);

            space.push_back(state1); //insert the state into space
            space.push_back(state2);
            /* calculting probability */
            double prob1 = engine.computing_state_probability(state1);                      
            double prob2 = engine.computing_state_probability(state2); 
            /* calculting probability */
            state1.update_probability(prob1);
            state2.update_probability(prob2);
            
            /*calculting P_t,i */
            double prob = 0.0;
            for(size_t j = 0; j < space.size(); j++){
            
                if(space[i].length() == i && space[i].end() == t){
                        prob = prob + space[i].prob();
                }
            }

            double ub = 0.0;    

            for(size_t j = 0; j < space.size(); j++){
            
                if(space[i].length() == i - 1){
                        ub = ub + space[i].prob();
                }
            }

            ubounds[i] = ub;
            if(rflag[i] == true) continue;
            
            if(prob > ap[i]){
                answer[i] = t;
                ap[i] = prob;
                if(ap[i] > ubounds[i]){
                
                    rflag[i] = true;
                    reported += reported;

                }
            }

        }
        depth = depth + 1;
    }
    return answer;
}
