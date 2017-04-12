/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "utopk.h"
#include "ukrank.h"
#include "indenputopk.h"
#include "indenpukrank.h"
#include "caller.h"
#include <string>
#include <sstream>
#include <fstream>
#include "caller.h"

int main(int argc, char *argv[]){

    Engine::Source source;
    Engine::Rules r;
    if(argc < 2){
        
        std::cout << "Run syntax:" << std::endl;
        std::cout << "topk <type> <k> <source> <rule> " << std::endl;
        std::cout << "For indenpent processing, we do not have rule file" << std::endl;
        
        exit(1);
    
    }
    std::string type(argv[1]);
    /* for the type:
     *  utopk: represents u topk processing 
     *  ukrank: represents u krank processing
     *  iutopk: represents indenpent u topk processing 
     *  iukrank: represents indenpent u krank processing 
     */
    
    std::string kk(argv[2]);
    
    std::istringstream ik(kk);
    int k;
    ik >> k;
    string data, rule;
    if(type == "utopk" || type == "ukrank"){
        if(argc < 5) exit(1);
        std::string _data(argv[3]);
        std::string _rule(argv[4]);
        data = _data;
        rule = _rule;

    }else{
        std::string _data(argv[3]);
        data = _data;
    }
    
    std::ifstream fin(data.c_str(), std::ios::in);
    string line;



    while(getline(fin, line)){
        Tuple tuple;
        
        std::istringstream iss(line);

        std::string a; int  b; double c;
        iss >> a >> b >> c;
        tuple.modify_id(a);
        tuple.modify_score(b);
        tuple.modify_confidence(c);
        
        source.push_back(tuple);
    
    }
    fin.close();
   
    if(argc > 4) {
        std::ifstream ru(rule.c_str(), std::ios::in);

        while(getline(ru, line)){
        
            std::set<int> s;
            std::istringstream iss(line);
            int a;
            while(iss >>a) {
                s.insert(a);
            }
    
            r.push_back(s);
        }
        ru.close();
    }
    
    Caller caller;

    caller.start(source, r);
    if(type == "utopk"){
        caller.processing_utopk(k);
    }else if(type == "ukrank"){
        caller.processing_ukrank(k);
    }else if(type == "iutopk"){
        caller.processing_indenputopk(k);
    }else if(type == "iukrank"){
        caller.processing_indenpukrank(k);
    }else{
        std::cout << "Wrong Type" << std::endl;
    }
    
    return 0; 
}
