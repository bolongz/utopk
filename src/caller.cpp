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

void Caller::start(const Launch::Source &_source, const Launch::Rules &r){
    
    engine.start(r, _source);
    source = _source;
}

void Caller::processing_utopk(int k, Caller::DB &results){

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
}

void Caller::processing_ukrank(int k, Caller::DB &results){
    
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

}

void Caller::processing_indenputopk(int k, Caller::DB &results){
    clock_t start = clock();
    State sta = itopk.indenputopk(source, k);
    clock_t end = clock();
    _time = (double)(end-start)/CLOCKS_PER_SEC;
    _depth = itopk.get_depth();
    std::cout <<"DEPTH: " << _depth << std::endl;
   
    DB().swap(results); 
    for(size_t i = 0; i < sta.current().size(); i++){
        DBtype db = source[sta.current()[i]].tuple_to_dbtype();
        results.push_back(db);
    }

}

void Caller::processing_indenpukrank(int k, Caller::DB &results){
    
    clock_t start = clock();
    std::vector<int> res  = krank.indenpukrank(source, k);
    clock_t end = clock();
    _time = (double)(end-start)/CLOCKS_PER_SEC;
    _depth = krank.get_depth();
    DB().swap(results); 
    for(size_t i = 0; i < res.size(); i++){
        DBtype db = source[res[i]].tuple_to_dbtype();
        results.push_back(db);
    }
    
}

void Caller::db_to_source(const Caller::DB &db, Launch::Source &_s){

    if (_s.size() != db.size()){
        _s.resize(db.size());
    }
    Tuple tuple;
    for(size_t i = 0; i < db.size(); i++){
    
        tuple.parse_string(db[i]);
        _s[i] = tuple;
    }

}
