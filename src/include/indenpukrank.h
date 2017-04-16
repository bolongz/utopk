/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */


#ifndef _INDENPUKRANK_H_
#define _INDENPUKRANK_H_


#include "tuple.h"
#include "state.h"
#include "launch.h"
#include <vector>


class Indenpukrank{

    public:
        typedef std::vector<int> Results;
        typedef std::vector<std::vector<double>> Dynamic;
        typedef int Depth;    
    
    private:
        Results results;
        Dynamic M;
        Depth depth;

    public:

        Indenpukrank();
        Indenpukrank(const Indenpukrank &t);
        Indenpukrank(Indenpukrank &&t);
        const Indenpukrank &operator=(const Indenpukrank &t);
        Indenpukrank &operator=(Indenpukrank &&t);

        ~Indenpukrank();

        Results get_results() const { return results;}
        Dynamic get_matrix() const {return M;}
        Depth get_depth() const{return depth;}
        //indenpdent krank seeking function 
        Results indenpukrank(const Launch::Source &source, size_t k);
        
};



#endif
