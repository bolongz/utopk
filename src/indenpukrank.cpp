/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "indenpukrank.h"

Indenpukrank::Indenpukrank(){}

Indenpukrank::Results Indenpukrank::indenpukrank(const Engine::Source &source, size_t k){

    size_t _size = source.size();

    results.resize(k);
    M.resize(k);
    
    for(size_t i= 0; i < k; i++){
        M[i].resize(_size);
    }
    
    for(size_t i = 0; i < _size; i++){
        
        M[0][i] = source[i].confidence();

        for(size_t j = 0; j < i; j++){
            
            M[0][i] = M[0][i] * (1.0 - source[j].confidence());
        
        }
    
    }

    for(size_t i = 1; i < k; i++){
    
       for(size_t j = 0; j < _size; j++){
       
            M[i][j] = source[j].confidence();
            double _p = 0.0;
            for(size_t k = 0; k < j; k++){
                double __p = 1.0; 
                for(size_t h = j + 1; h < k; h++){
                    __p = __p * (1.0 - source[h].confidence()); 
                }
                _p = _p + __p;
                
            }

            M[i][j] = M[i][j] * _p * M[i-1][j];
       } 
    
    }

    return {1};


} 
