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
Ukrank::Answer Ukrank::ukrank(const Launch &engine, const Launch::Source &source, const Ukrank::Querylength &k){

    answer.resize(k, -1);
    ap.resize(k, 0);
    ubounds.resize(k, 1);
    rflag.resize(k, false);
    
    while((depth <= source.size()) & (reported < k)){
        int t = depth - 1;
        int _min = std::min(k, depth);
         
        int _size = space.size();
        State state1, state2;
        int count1 = 0;
        int count = _size;;
        for(int i = 1; i <= _min; i++ ){
            double prob = 0.0; // P_t,i
            if(!space.empty()){
                for(auto iter = space.begin(); iter != space.end(); ){      
                    if(count == 0) break; 
                    if(iter->end() == t) break; 
                    if(iter->length() == (i - 1)){
                        state1 = *iter; //space[j];
                        state2 = *iter; //space[j];
                        
                        state1.extend(t, true); //state extension
                        state2.extend(t,false);

                        /* calculting probability */
                        double prob1 = engine.computing_state_probability(state1); 
                        double prob2 = engine.computing_state_probability(state2); 
                        /* calculting probability */
                        state1.update_probability(prob1);
                        state2.update_probability(prob2);
                        
                        space.push_back(state1); //insert the state into space
                        space.push_back(state2);
                        iter = space.erase(iter);
                        count1 = count1+1;
                        count = count -1;
                    
                    }else{
                        iter++;
                    
                    }
                    
                }
            }else{
            
                state1.extend(t, true); //state extension
                state2.extend(t,false);

            /* calculting probability */
                double prob1 = engine.computing_state_probability(state1);                      
                double prob2 = engine.computing_state_probability(state2); 
                /* calculting probability */
                state1.update_probability(prob1);
                state2.update_probability(prob2);
               
                space.push_back(state1); //insert the state into space
                space.push_back(state2);
            } 
            
            auto iter2 = space.begin();

            for(auto iter = iter2; iter!= space.end();iter++){ 
                if(iter->length() == i && iter->current()[iter->current().size()-1] == t){
                  prob = prob + iter->prob();
                }
            }

            double ub = 0.0;
            bool __flag = false;
            
            iter2 = space.begin();
            
            for(auto iter = iter2; iter!= space.end();iter++){ 
                  
                if(iter->length()== i-1){
                        ub = ub + iter->prob();
                        __flag = true;
                }
            }

            if(__flag) ubounds[i-1] = ub;
            if(rflag[i-1] == true) continue;
           

            if(prob >= ap[i-1]){
                answer[i-1] = t;
                ap[i-1] = prob;
                if(ap[i-1] > ubounds[i-1]){
                    rflag[i-1] = true;
                    reported += 1;

                }
            }

        }
        depth = depth + 1;
    }
    depth = depth - 1;
    return answer;
}
