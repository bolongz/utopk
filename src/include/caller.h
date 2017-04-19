/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */
#ifndef _CALLER_H_
#define _CALLER_H_

#include "utopk.h"
#include "ukrank.h"
#include "indenputopk.h"
#include "indenpukrank.h"
#include <string>
#include <sstream>
#include <fstream>

/* caller class */
class Caller{
    

    typedef std::vector<std::vector<std::string>> DB;
    typedef std::vector<std::string> DBtype;
    typedef int Depth;
    typedef double Time;
    private:
        
        Launch::Source source;
       // Launch::Rules r; 
        Launch engine;
        Utopk utopk; // utopk object;
        Ukrank ukrank;//ukrank object;
        Indenputopk itopk; //indenputopk object;
        Indenpukrank krank; //indenpurank object;
        
        Time _time;
        Depth _depth;
        

    public:
    
        Caller();
        void db_to_source(const DB &db, Launch::Source &_s);
        
        Time run_time() const {return _time;}
        Depth scan_depth() const{return _depth;}
//        DB get_results() const{ return results;}

        void start(const Launch::Source &source, const Launch::Rules &r);
        
        void processing_utopk(int k, DB &result);
        void processing_ukrank(int k, DB &result);
        void processing_indenputopk(int k, DB &results);
        void processing_indenpukrank(int k, DB &result);
};

#endif
