/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */


#ifndef _INDENPUKRANK_H_
#define _INDENPUKRANK_H_


#include "tuple.h"
#include "state.h"
#include "engine.h"
#include <vector>


class Indenpukrank{

    public:
        typedef std::vector<int> Results;
        typedef std::vector<std::vector<double>> Dynamic;
    
    private:

        Results results;
        Dynamic M;

    public:

        Indenpukrank();

        Results indenpukrank(const Engine::Source &source, size_t k);
        
};



#endif
