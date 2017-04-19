/* Author: Bolong Zhang */
/* email. blzhang.m@gmail.com */

#include "indenputopk.h"
#include <algorithm>



bool state_compare(const State &s1, const State &s2){
    return s1.prob() < s2.prob();
}

Indenputopk::Indenputopk(){}

Indenputopk::Indenputopk(const Indenputopk &t){
    
    maintained = t.get_maintained();
    answer = t.get_answer();

}

Indenputopk::Indenputopk(Indenputopk &&t){
    
    maintained = t.get_maintained();
    answer = t.get_answer();

    t.~Indenputopk();

}

const Indenputopk &Indenputopk::operator=(const Indenputopk &t){
    
    if(this == &t){
        
        return *this;
    }
    maintained = t.get_maintained();
    answer = t.get_answer();
    
    return *this;
}   

Indenputopk &Indenputopk::operator=(Indenputopk &&t){
    
    if(this == &t){
    
        return *this;
    }
    maintained = t.get_maintained();
    answer = t.get_answer();

    t.~Indenputopk();
    
    return *this;
}

Indenputopk::~Indenputopk(){

    Maintained().swap(maintained);
    answer.~State();
}

State Indenputopk::indenputopk(const Launch::Source &source, const Indenputopk::Querylength k){

    maintained.resize(k + 1);
    size_t current = 0;
    
    std::vector<bool> flag(k + 1,false);

    size_t start = 0, longest = 1, temp = 0;

    /* main loop for the indenpedent topk */

    double maxval = 0.0;
    while(current < source.size()){ 
        for(size_t i = start; i < longest;i++){
        
            if( i == 0 && maintained[i].size() == 0 && flag[i] == false){
                State state1, state2;
                state1.extend(current,true);
                double _newp = state1.prob() * source[current].confidence();
                
                state1.update_probability(_newp);
                maintained[i+1].push_back(state1); 
                if( i == longest - 1 && longest < k) temp = longest + 1;
                

                state2.extend(current, false);
                double _newp2 = state2.prob() * (1 - source[current].confidence());
                state2.update_probability(_newp2);
                maintained[i].push_back(state2);
                
            }else{
                if(i < k && flag[i] == false){
                    
                    State state1 = *(maintained[i].begin());
                    state1.extend(current,true);
                    double _newp = state1.prob() * source[current].confidence();
                    state1.update_probability(_newp);
                    maintained[i+1].push_back(state1); 
                    if( i == longest - 1 && longest < k) temp = longest + 1;
                    
                    maintained[i].begin()->extend(current,false);
                    double _newp2 = maintained[i].begin()->prob() * (1 - source[current].confidence());
                    maintained[i].begin()->update_probability(_newp2);
                    
                    if(i > 0 && maintained[i].size() > 1){
                        maintained[i].sort(state_compare); 
                            
                            maintained[i].erase(maintained[i].begin());
                        
                    
                    } 
                    
                
                
                }
            
            }

        
        }
        
        if(longest == k){
            if(maintained[k].size() > 1){
                    
                    maintained[k].sort(state_compare);
                    maintained[k].erase(maintained[k].begin());
                    
            }//else

        }

        size_t maxloc = 0;
        for(size_t i = 0; i < k + 1; i++){
            if(flag[i] == false){
                maxloc = i;
                break;
            }
        
        }
        if(maxloc == k) return *(maintained[k].begin());
        for(size_t i = maxloc + 1; i < longest + 1; i++){
            
            if(flag[i] == false){
                if((maintained[i].begin())->prob()  > (maintained[maxloc].begin())->prob() ){
                    maintained[i].erase((maintained[maxloc].begin()));
                    flag[maxloc] = true;
                    maxloc = i;
                    break;
                }
            
            }
        }
        
        maxval = maintained[maxloc].begin()->prob();

        for(size_t i = maxloc + 1; i < longest + 1; i++){

            if(flag[i] == false){
                if((maintained[i].begin())->prob()  > maxval){
                    maxval = maintained[i].begin()->prob();
                    maxloc = i;
                }
            
            }
        }
        current = current + 1;
        depth = current;
        if(maxval == k) return *(maintained[k].begin());
        if(temp > 0){
            longest = temp;
        }
    
    }
    return *(maintained[k].begin());

}

