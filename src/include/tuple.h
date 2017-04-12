/* Author: Bolong Zhang
 * email: blzhang.m@gmail.com
 */

#ifndef _TUPLE_H_
#define _TUPLE_H_


#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include <iostream>

/*
 * Tuple class definition to store the independent tuple 
 * 
 */
class Tuple{
    public:

        typedef std::string TupleID;
        typedef int Score;
        typedef double Confidence;
        typedef int Tag; 

    private:
       
        TupleID _id;
        Tag _tag;
        Score _score;
        Confidence _confidence;
    
    public:
        /*constructor */
        Tuple(); // default zero constructor 
        Tuple(const Tuple &tuple); // copy constructor
        Tuple(Tuple &&tuple); //move constructor
        const Tuple &operator=(const Tuple &tuple); //copy assignment operator
        Tuple &operator=(Tuple &&tuple); // move assignment operator 

        ~Tuple();
        
        /*get elements */
        TupleID id() const ;
        Score score() const ;
        Tag tag() const ;
        Confidence confidence() const;

        /*modify elements */
        void modify_id(const TupleID &newid);
        void modify_score(const Score &newscore);
        void modify_tag(const Tag &newtag);
        void modify_confidence(const Confidence &newconf);
};
/*
bool operator==(const Tuple &l, const Tuple &r){

    if(l.id() == r.id() && l.score()==r.score() && 
       l.tag() == r.tag() && l.confidence() == r.confidence()){

        return true;
    }
    return false;
}

bool operator!=(const Tuple &l, const Tuple &r){
    return !(operator==(l,r));
}

std::ostream &operator<< (std::ostream &os, const Tuple &t){
    os << t.id() <<" " << t.tag() <<" " << t.score() << " " << t.confidence() << std::endl;
    return os;
}
*/
#endif
