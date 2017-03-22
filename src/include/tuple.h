/* Author: Bolong Zhang
 * email: blzhang.m@gmail.com
 */

#ifndef _TUPLE_H_
#define _TUPLE_H_


#include<string>
#include<vector>
#include<map>
#include<unordered_map>


/*
 * Tuple class definition to store the independent tuple 
 * 
 */
class Tuple{
    public:
        typedef int TupleID;
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
        Tuple();
        Tuple(const Tuple &tuple);
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

#endif
