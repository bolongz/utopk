/* Author: Bolong Zhang 
 * email: blzhang.m@gmail.com
 */

#ifndef _UKRANK_H_
#define _UKRANK_H_

#include "tuple.h"
#include "state.h"
#include "launch.h"

class Ukrank{

    public:
        typedef std::vector<int> Answer;
        typedef std::vector<double> Ubounds;
        typedef std::vector<double> AnswerProbability;
        typedef std::vector<bool> Flag;
        typedef size_t Reported;
        typedef size_t Depth;
        typedef std::vector<State> Space;
        typedef size_t Querylength;

    private:

        Answer answer;
        Ubounds ubounds;
        AnswerProbability ap; //answer probability 
        Flag rflag;//store if the answer has already reported;
        Depth depth;
        Space space;
        Reported reported;

    public:

        Ukrank();
        Ukrank(const Ukrank &t);
        Ukrank(Ukrank &&t);
        const Ukrank &operator=(const Ukrank &t);
        Ukrank &operator=(Ukrank &&t);
       
        ~Ukrank();
        
        Answer get_answer() const {return answer; }
        Ubounds get_ubounds()const {return ubounds;}
        AnswerProbability get_ap()const {return ap;}
        Flag get_flag() const {return rflag;}
        Depth get_depth() const {return depth;}
        Space get_space() const {return space;}
        Reported get_reported() const {return reported;}

        //ukrank functon return the final krank results 
        Answer ukrank(const Launch &engine, const Launch::Source &source, const Querylength &k);
};

#endif
