#ifndef _INDENPUTOPK_
#define _INDENPUTOPK_

#include "tuple.h"
#include "state.h"
#include "engine.h"
#include <vector>

using namespace std;

class Indenputopk{

    public:
        typedef std::vector<std::vector<State>>  Maintained; //store the maintained state.
        typedef State Answer;
        typedef State Max; // store the current max state 
        typedef size_t Querylength; // Querylength 
        typedef int Current; //store the index for the current index 
    private:
        Maintained maintained; //with length k + 1 // start with zero
        Answer answer; //store the answer
        

    public:
        
        Indenputopk();
    
        State indenputopk(const Engine::Source &source, const Querylength k);

};

#endif
