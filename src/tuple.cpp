/* Author: Bolong Zhang
 * email: blzhang.m@gmail.com
 */

#include "tuple.h"


/* Implementation of the Tuple class */
Tuple::Tuple():_id{-1},_tag{-1},_score{-1},_confidence{-1}{}

Tuple::Tuple(const Tuple &tuple){
    _id = tuple.id();
    _tag = tuple.tag();
    _score = tuple.score();
    _confidence = tuple.confidence();
}

Tuple::Tuple(Tuple &&tuple){
    _id = tuple.id();
    _tag = tuple.tag();
    _score = tuple.score();
    _confidence = tuple.confidence();

    tuple.modify_id(-1);
    tuple.modify_score(-1);
    tuple.modify_tag(-1);
    tuple.modify_confidence(-1);
    
}

const Tuple &Tuple::operator=(const Tuple &tuple){

    if(this == &tuple){
        return *this; 
    }
    
    _id = tuple.id();
    _tag = tuple.tag();
    _score = tuple.score();
    _confidence = tuple.confidence();

    return *this;
}

Tuple &Tuple::operator=(Tuple &&tuple){

    if(this == &tuple){
        return *this; 
    }
    
    _id = tuple.id();
    _tag = tuple.tag();
    _score = tuple.score();
    _confidence = tuple.confidence();
    
    tuple.modify_id(-1);
    tuple.modify_score(-1);
    tuple.modify_tag(-1);
    tuple.modify_confidence(-1);

    return *this;
}


Tuple::~Tuple(){}

/* get elements*/
Tuple::TupleID Tuple::id() const {  
    return _id;
}
Tuple::Tag Tuple::tag() const {
    return _tag;
}
Tuple::Score Tuple::score() const{
    return _score;
}
Tuple::Confidence Tuple::confidence() const{
    return _confidence;
}

/*modify element */
void Tuple::modify_id(const TupleID & newid){
    _id = newid;
}
void Tuple::modify_tag(const Tag &newtag ){
    _tag = newtag;
}
void Tuple::modify_score(const Score &newscore ){
    _score = newscore;
}
void Tuple::modify_confidence(const Confidence &newconf){
    _confidence = newconf;
}
