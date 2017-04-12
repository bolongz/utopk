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
    
    private:

        Engine::Source source;
       // Engine::Rules r; 
        Engine engine;
        Utopk utopk; // utopk object;
        Ukrank ukrank;//ukrank object;
        Indenputopk itopk; //indenputopk object;
        Indenpukrank krank; //indenpurank object;
    
    
    public:
    
        Caller();
        void start(const Engine::Source &source, const Engine::Rules &r);
        void processing_utopk(int k);
        void processing_ukrank(int k);
        void processing_indenputopk(int k);
        void processing_indenpukrank(int k);
};

#endif
