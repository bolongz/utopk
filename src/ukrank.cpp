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
Ukrank::Answer Ukrank::ukrank(const Engine &engine, const Engine::Source &source, const Ukrank::Querylength &k){

    answer.resize(k, -1);
    ap.resize(k, 0);
    ubounds.resize(k, 1);
    rflag.resize(k, false);
    
    int lastsize = 0; 
    while((depth <= source.size()) & (reported < k)){
       // std::cout << "-------------------------" << std::endl;
       // std::cout << "DEPTH: "  << depth << std::endl; 
        int t = depth -1; //next tuples from source
        int _min = std::min(k, depth);
         
        int _size = space.size(); 
       // std::cout << "SPACE:  " << _size << std::endl;
        State state1, state2;
        for(int i = 1; i <= _min; i++ ){
            double prob = 0.0; // P_t,i

            if(!space.empty()){
                for(int j = lastsize; j < _size; j++){
                    
                    if(space[j].length() == (i - 1)){
                    //    std::cout <<"LENGTH " << i-1 << " JJJJ " << j << " " << t <<  std::endl;
                        state1 = space[j];
                        state2 = space[j];
                        
                        state1.extend(t, true); //state extension
                        state2.extend(t,false);

                        /* calculting probability */
                        double prob1 = engine.computing_state_probability(state1);  
                        double prob2 = engine.computing_state_probability(state2); 
                        /* calculting probability */
                        state1.update_probability(prob1);
                        state2.update_probability(prob2);
                        
                       // std::cout<<"STATE " << state1.ranki() << " " << std::endl;
                        space.push_back(state1); //insert the state into space
                        space.push_back(state2);

                    
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
                /*calculting P_t,i */
            for(size_t j = _size; j < space.size(); j++){
                //std::cout <<"LENGTHHHH " << space.size() << " " << space[j].length() <<" " << space[j].ranki() <<" " <<t << " " << i << std::endl; 
                if(space[j].length() == (i) && space[j].current()[space[j].current().size()-1] == (t)){
                    prob = prob + space[j].prob();
                    //std::cout << "BCOMPARE " << prob <<" " << space[j].prob()  <<" " << j <<std::endl;
                }
            }

            double ub = 0.0;
            bool __flag = false;
            for(size_t j = _size; j < space.size(); j++){
            
                if(space[j].length() == (i - 1)){
                //if(space[j].length() == (i - 1) && space[j].end() != (t)){
                       // std::cout <<" CAL B " << i -1 << std::endl; 
                        ub = ub + space[j].prob();
                        __flag = true;
                }
            }

            if(__flag) ubounds[i-1] = ub;
            //std::cout <<"BOUND " << ubounds[i-1] << std::endl; 
            if(rflag[i-1] == true) continue;
           
            //std::cout << "COMPARE " << prob  << " " << ap[i-1] << std::endl;

            if(prob >= ap[i-1]){
                //std::cout << "ANSWER " << i << " " << t << " " << prob << std::endl;
                answer[i-1] = t;
                ap[i-1] = prob;
                if(ap[i-1] > ubounds[i-1]){
                    //std::cout << "UBOUNDS " << i << std::endl;  
                    rflag[i-1] = true;
                    reported += 1;

                }
            }

        }
        depth = depth + 1;
        lastsize = _size;
    }
    return answer;
}
