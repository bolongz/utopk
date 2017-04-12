/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "engine.h"
#include <bitset>
#include <cmath>
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
//    std::cout << _size << std::endl;
    /* get union for all the rules */
    Iterator it;
    for(size_t i = 0; i  < R.size() ; i++){
        int s = 0; //empty set at first 
        for(it = R[i].begin(); it != R[i].end(); ++it){
            _union.insert(*it);
            s = s | 1 << (*it);
        }
        _rules.push_back(s);
    }
    
}

Engine::~Engine(){
    
    Source().swap(_source);
    Binary().swap(_rules);
    Union().swap(_union);
    _size = -1;

}

void Engine::start(const Engine::Rules & R, const Engine::Source &S){
    
    _source = S;
    _size = S.size();
//    std::cout << _size << std::endl;
    /* get union for all the rules */
    Iterator it;
    for(size_t i = 0; i  < R.size() ; i++){
        int s = 0; //empty set at first 
        for(it = R[i].begin(); it != R[i].end(); ++it){
            _union.insert(*it);
            s = s | 1 << (*it);
        }
        _rules.push_back(s);
    }
    
}
Engine::Prob Engine::computing_state_probability(const State &s) const{
   
    /* Length with prob 0 */
    //if(s.length() == 0) return 1.0;

    int current = 0;;
    bool flag = true;
    double prob = 1.0, sum = 0.0;
    for(size_t i = 0; i < s.current().size();i++){
        current = current | 1 << s.current()[i];
//        std::cout << "SCURRENT " << s.current()[i] <<" " << current ;
    }
//    std::cout << std::endl << "SIZE " << _size << " " << _rules.size() <<  std::endl;
    for(int sub = 0; sub < 1 << _size; sub++){
        flag = true; 
        /* check the rules */
        for(size_t i = 0 ; i < _rules.size(); i++){
            
            int inter = sub & _rules[i]; // intersection of two set 
//            std::cout <<"RULE " << inter <<" " << _rules[i] <<std::endl;
            if( inter == 0 || (inter & (inter - 1)) != 0){
                flag = false; 
                break;
            }
        }
        if(flag){
            //std::cout << "SUB " << sub  <<" " << current << std::endl;
            int _sub = sub;
            int inter = _sub & current;
            if( inter == current && current != 0){
                bool contain = false;
                for(size_t i = 0; i < s.negative().size(); i++){
//                    std::cout << "NEGATIVE " << s.negative()[i] << std::endl;
                    if(_sub >> s.negative()[i] & 1){
                        contain = true;
                        break;
                        //_sub = _sub &~(1 << s.negative()[i]);
                    }
                }
                if(contain) continue;
//                std::cout << "INSIDE " << inter  << " " << sub << std::endl;

                int count = 0;
           
                while(count < _size && _sub >= 0){
                    int bits = _sub & 1;
                
                    if(_union.find(count) != _union.end()){
                        if(bits == 1){
                            prob = prob * _source[count].confidence();
                        }else{
                            prob = prob * 1.0;
                        }
                
                    }else{
                        if(bits == 1){
                            prob = prob * _source[count].confidence();
                        }else{
                            prob = prob * (1.0 - _source[count].confidence());
                        }
                    }
//                    std::cout << "prob " << prob << " " << _sub << std::endl;
                    count = count + 1;
                    _sub = _sub >> 1;

                }
//                std::cout << "PROB FIRST " << prob << std::endl;
            }else if(current == 0){
                
//                std::cout << "CURRENT is zero " << current << " " << sub <<std::endl;
                
                if(sub == 0 && _rules.size() == 0){
                    
                    for(size_t i = 0 ; i < _source.size(); i++){
                        prob = prob * (1- _source[i].confidence());
                        
                    }
                   
                }else if(sub != 0){
                    bool  _contain = false;

                    for(size_t i = 0; i < s.negative().size(); i++){
                        if(_sub >> s.negative()[i] & 1){
                            _contain = true;
                            break;
                        }
                    //_sub = _sub &~(1 << s.negative()[i]);
                    }
                    if(_contain) continue;

                    int count = 0;
           
                    while(count < _size && _sub >= 0){
                        int bits = _sub & 1;
                
                         if(_union.find(count) != _union.end()){
                                if(bits == 1){
                                    prob = prob * _source[count].confidence();
                                }else{
                                    prob = prob * 1.0;
                                }
                
                        }else{
                            if(bits == 1){
                                prob = prob * _source[count].confidence();
                            }else{
                                prob = prob * (1.0 - _source[count].confidence());
                        
                            }   
                        }
                        count = count + 1;
                        _sub = _sub >> 1;
                   
                    }    
                
                }
            }
            if(fabs(prob - 1.0) < 0.000001) continue;
            sum = sum +  prob;
//            std::cout << "SUM acc " << sum <<" " << prob << std::endl; 
            prob = 1.0;

        } 
    
    }
 //   std::cout << "PROB : " << sum << std::endl;
    return sum;

}
