/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "engine.h"

Engine::Engine():_size(-1){}; //empty constructor

Engine::Engine(const Engine &e){
    
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
}

Engine::Engine(Engine &&e){
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
    e.~Engine();
}
const Engine &Engine::operator=(const Engine &e){
    if(this == &e){
    
        return *this;
    
    }    
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
    
    return *this;
}

Engine &Engine::operator=(Engine &&e){
    
    if(this == &e){
    
        return *this;
    }
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
    e.~Engine();

    return *this; 

}
Engine::Engine(const Engine::Rules & R, const Engine::Source &S){
    
    _source = S;
    _size = S.size();
    /* get union for all the rules */
    Iterator it;
    size_t _size = 0;
    for(size_t i = 0; i  < R.size() ; i++){
        _size += R[i].size();
        int s = 0; //empty set at first 
        for(it = R[i].begin(); it != R[i].end(); ++it){
            _union.insert(*it);
            s = s | 1 << (*it);
        }
        _rules.push_back(s);
    }
    assert(_union.size() == _size); //error checking

}

Engine::~Engine(){
    
    Source().swap(_source);
    Binary().swap(_rules);
    Union().swap(_union);
    _size = -1;

}
Engine::Prob Engine::computing_state_probability(const State &s){
    
    int current = 0;;
    bool flag = true;
    double prob = 1.0, sum = 0.0;
    for(size_t i = 0; i < s.current().size();i++){
        current = current | 1 << s.current()[i];
    }
    for(int sub = 0; sub < 1 << _size; sub++){
        for(size_t i = 0 ; i < _rules.size(); i++){
            
            int inter = sub & _rules[i]; // intersection of two set 
            if((inter & (inter - 1)) != 0) flag = false; 
            break;
        }
        if(flag){
            int _sub = sub;
            int inter = _sub & current;
            if( inter == current){
                for(size_t i = 0; i < s.negative().size(); i++){
                    if(_sub >> s.negative()[i] & 1){
                        _sub = _sub &~(1 << s.negative()[i]);
                    }
                }

            }
            int count = 0;
            while(count < _size && _sub >= 0){

                int bits = _sub & 1;
                
                if(_union.find(count) != _union.end()){
                    if(bits == 1){
                        prob = prob * _source[count].confidence();
                    }else{
                        prob = prob * (1-_source[count].confidence());
                    }
                
                }else{
                    if(bits == 1){
                        prob = prob * _source[count].confidence();
                    }
                }
            }
            //s.update_probability(prob);
            sum = sum +  prob;

        } 
    
    }
    return sum;

}
