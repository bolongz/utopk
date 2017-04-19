/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "launch.h"
#include <bitset>
#include <cmath>
Launch::Launch():_size(-1){}; //empty constructor

Launch::Launch(const Launch &e){
    
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
}

Launch::Launch(Launch &&e){
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
    e.~Launch();
}
const Launch &Launch::operator=(const Launch &e){
    if(this == &e){
    
        return *this;
    
    }    
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
    
    return *this;
}

Launch &Launch::operator=(Launch &&e){
    
    if(this == &e){
    
        return *this;
    }
    _source = e.source();
    _rules = e.rules();
    _union = e.unio();
    _size = e.size();
    e.~Launch();

    return *this; 

}
Launch::Launch(const Launch::Rules & R, const Launch::Source &S){
    
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

Launch::~Launch(){
    
    Source().swap(_source);
    Binary().swap(_rules);
    Union().swap(_union);
    _size = -1;

}

void Launch::start(const Launch::Rules & R, const Launch::Source &S){
    
    _source = S;
    _size = S.size();
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
Launch::Prob Launch::computing_state_probability(const State &s) const{
   
    /* Length with prob 0 */

    long long int current = 0;;
    bool flag = true;
    double prob = 1.0, sum = 0.0;
    for(size_t i = 0; i < s.current().size();i++){
        current = current | 1 << s.current()[i];
    }
    for(long long int sub = 0; sub < 1 << _size; sub++){
        flag = true; 
        /* check the rules */
        for(size_t i = 0 ; i < _rules.size(); i++){
            
            int inter = sub & _rules[i]; // intersection of two set 
            if( inter == 0 || (inter & (inter - 1)) != 0){
                flag = false; 
                break;
            }
        }
        if(flag){
            int _sub = sub;
            int inter = _sub & current;
            if( inter == current && current != 0){
                bool contain = false;
                for(size_t i = 0; i < s.negative().size(); i++){
                    if(_sub >> s.negative()[i] & 1){
                        contain = true;
                        break;
                    }
                }
                if(contain) continue;

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
            }else if(current == 0){
                
                
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
            prob = 1.0;

        } 
    
    }
    return sum;

}
