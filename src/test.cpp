/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "utopk.h"
#include "ukrank.h"
#include "indenputopk.h"
#include "indenpukrank.h"
#include <string>
#include <sstream>
#include <fstream>


int main(int argc, char *argv[]){

    Engine::Source source;
    Engine::Rules r; 
    std::string data(argv[1]);
    std::string rule(argv[2]);

    std::ifstream fin(data.c_str(), std::ios::in);
    string line;

    while(getline(fin, line)){
        Tuple tuple;
        
        std::istringstream iss(line);

        int a, b; double c;
        iss >> a >> b >> c;
        tuple.modify_id(a);
        tuple.modify_score(b);
        tuple.modify_confidence(c);
        
        source.push_back(tuple);
    
    }
    fin.close();
    
    std::ifstream ru(rule.c_str(), std::ios::in);
    ;

    while(getline(ru, line)){
        
        std::set<int> s;
        std::istringstream iss(line);
        int a;
        while(iss >>a) {
            s.insert(a);
        }
    
        r.push_back(s);
    }
    
    Utopk utopk;
    State sta = utopk.topk(r, source, 2);
    sta.print_state();

    return 0; 
}
