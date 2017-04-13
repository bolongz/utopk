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

    clock_t start = clock();
    State sta = utopk.topk(engine, source, k);
    clock_t end = clock();
    _time = (double)(end-start)/CLOCKS_PER_SEC;
    _depth = utopk.get_depth();
    //sta.exist_tuples();
    DB().swap(results); 
    for(size_t i = 0; i < sta.current().size(); i++){
        DBtype db = source[sta.current()[i]].tuple_to_dbtype();
        results.push_back(db);
    }
    /*
    for(size_t i = 0; i < sta.current().size(); i++){
        std::cout << source[sta.current()[i]].id() <<" ";
    
    }
    std::cout<<std::endl;
    */
}

void Caller::processing_ukrank(int k){
    
    clock_t start = clock();
    std::vector<int> res = ukrank.ukrank(engine, source, k);
    clock_t end = clock();
    _time = (double)(end-start)/CLOCKS_PER_SEC;
    _depth = ukrank.get_depth();
    DB().swap(results); 
    for(size_t i = 0; i < res.size(); i++){
        DBtype db = source[res[i]].tuple_to_dbtype();
        results.push_back(db);
    }
        
    /*
    for(size_t i = 0; i < res.size(); i++){
        std::cout << source[res[i]].id() <<" ";
    
    }
    std::cout<<std::endl;
    */
    

}

void Caller::processing_indenputopk(int k){
    clock_t start = clock();
    State sta = itopk.indenputopk(source, k);
    clock_t end = clock();
    _time = (double)(end-start)/CLOCKS_PER_SEC;
    _depth = itopk.get_depth();
   
    DB().swap(results); 
    for(size_t i = 0; i < sta.current().size(); i++){
        DBtype db = source[sta.current()[i]].tuple_to_dbtype();
        results.push_back(db);
    }
    /*for(size_t i = 0; i < sta.current().size(); i++){
    
        std::cout << source[sta.current()[i]].id() <<" ";
    
    }
    std::cout<<std::endl;
    */

}

void Caller::processing_indenpukrank(int k){
    
    clock_t start = clock();
    std::vector<int> res  = krank.indenpukrank(source, k);
    clock_t end = clock();
    _time = (double)(end-start)/CLOCKS_PER_SEC;
    _depth = source.size();
    DB().swap(results); 
    for(size_t i = 0; i < res.size(); i++){
        DBtype db = source[res[i]].tuple_to_dbtype();
        results.push_back(db);
    }
    
   /* 
    for(size_t i = 0; i < res.size(); i++){
        std::cout << source[res[i]].id() <<" ";
    
    }
    std::cout<<std::endl;
    */
}

void Caller::db_to_source(const Caller::DB &db, Engine::Source &_s){

    if (_s.size() != db.size()){
        _s.resize(db.size());
    }
    Tuple tuple;
    for(size_t i = 0; i < db.size(); i++){
    
        tuple.parse_string(db[i]);
        _s[i] = tuple;
    }

}
