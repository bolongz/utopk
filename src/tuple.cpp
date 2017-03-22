/* Author: Bolong Zhang
 * email: blzhang.m@gmail.com
 */

#include "tuple.h"


/* Implementation of the Tuple class */
Tuple::Tuple():_id{0},_tag{0},_score{0},_confidence{0.0}{}

Tuple::Tuple(const Tuple &tuple){
    _id = tuple.id();
    _tag = tuple.tag();
    _score = tuple.score();
    _confidence = tuple.confidence();
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
void Tuple::modify_score(const Score &newscore){
    _score = newscore;
}
void Tuple::modify_confidence(const Confidence &newconf){
    _confidence = newconf;
}
