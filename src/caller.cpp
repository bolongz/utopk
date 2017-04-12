/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "utopk.h"
#include "ukrank.h"
#include "indenputopk.h"
#include "indenpukrank.h"
#include "caller.h"
#include <string>
#include <sstream>
#include <fstream>


Caller::Caller(){};

void Caller::start(const Engine::Source &_source, const Engine::Rules &r){
    
    engine.start(r, _source);
    source = _source;
}

void Caller::processing_utopk(int k){

    State sta = utopk.topk(engine, source, k);
    //sta.exist_tuples();
    
    for(size_t i = 0; i < sta.current().size(); i++){
        std::cout << source[sta.current()[i]].id() <<" ";
    
    }
    std::cout<<std::endl;
}

void Caller::processing_ukrank(int k){

    std::vector<int> res = ukrank.ukrank(engine, source, k);
    
    for(size_t i = 0; i < res.size(); i++){
        std::cout << source[res[i]].id() <<" ";
    
    }
    std::cout<<std::endl;
    

}

void Caller::processing_indenputopk(int k){

    State sta = itopk.indenputopk(source, k);
    for(size_t i = 0; i < sta.current().size(); i++){
        std::cout << source[sta.current()[i]].id() <<" ";
    
    }
    std::cout<<std::endl;

}

void Caller::processing_indenpukrank(int k){
    
    std::vector<int> res  = krank.indenpukrank(source, k);
    
    
    for(size_t i = 0; i < res.size(); i++){
        std::cout << source[res[i]].id() <<" ";
    
    }
    std::cout<<std::endl;
}
