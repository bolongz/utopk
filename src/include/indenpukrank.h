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
        Indenpukrank(const Indenpukrank &t);
        Indenpukrank(Indenpukrank &&t);
        const Indenpukrank &operator=(const Indenpukrank &t);
        Indenpukrank &operator=(Indenpukrank &&t);

        ~Indenpukrank();

        Results get_results() const { return results;}
        Dynamic get_matrix() const {return M;}
        
        //indenpdent krank seeking function 
        Results indenpukrank(const Engine::Source &source, size_t k);
        
};



#endif
