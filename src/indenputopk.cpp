/* Author: Bolong Zhang */
/* email. blzhang.m@gmail.com */

#include "indenputopk.h"
#include <algorithm>



bool state_compare(const State &s1, const State &s2){
    return s1.prob() < s2.prob();
}

Indenputopk::Indenputopk(){}

State Indenputopk::indenputopk(const Engine::Source &source, const Indenputopk::Querylength k){

    maintained.resize(k);
    size_t current = 0;

    size_t start = 0, longest = 0, temp = 0;

    /* main loop for the indenpedent topk */

    while(current < source.size()){ 
        
        for(size_t i = start ; i < longest; i++){
            
            if(i < k - 1){

                State state1 = maintained[i][0];        
                state1.extend(current, true);
                double _newp = state1.prob() * source[current].confidence();
                state1.update_probability(_newp);
                maintained[i+1].push_back(state1);
                if( i == longest - 1) temp = longest + 1;
            
            }
            
            State state2 = maintained[i][0];        
            state2.extend(current, true);
            double _newp2 = state2.prob() * (1 - source[current].confidence());
            state2.update_probability(_newp2);
            maintained[i].push_back(state2);
        
        }
        if(temp > 0){
            longest = temp;
        }
        
        for(size_t i = start; i < longest; i++){
            
            sort(maintained[i].begin(), maintained[i].end(), state_compare);
            maintained[i].erase(maintained[i].begin(), maintained[i].end()-1);
            if(i == start + 1){
                if(maintained[i][0].prob() > maintained[i-1][0].prob()){
                    start = start + 1;
                }
            
            }
        }
        bool _answer = true;
        if(longest == k -1 ){
            for(size_t i = start; i < longest - 1; i++){
                if(maintained[k-1][0].prob() < maintained[i][0].prob() ){
                    _answer = false;
                }
            }
            if(_answer) break;
        }
        current = current + 1;
    
    }
    return maintained[k-1][0];

}

