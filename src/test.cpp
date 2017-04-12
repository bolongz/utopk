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
        std::cout << a <<" " <<  b << " "  <<c << std::endl;
        tuple.modify_id(a);
        tuple.modify_score(b);
        tuple.modify_confidence(c);
        
        source.push_back(tuple);
    
    }
    fin.close();
    
    std::ifstream ru(rule.c_str(), std::ios::in);

    while(getline(ru, line)){
        
        std::set<int> s;
        std::istringstream iss(line);
        int a;
        while(iss >>a) {
            s.insert(a);
            std::cout << a << std::endl;
        }
    
        r.push_back(s);
    }
    ru.close(); 
    Utopk utopk;
    Engine engine(r, source);
    //std::cout <<"source main: " << source.size() << std::endl;
    //State sta = utopk.topk(engine, source, 6);

    //std::cout <<"RESULT" << std::endl;
    //vsta.print_state();
    
    Ukrank ukrank;
    
    std::vector<int> res = ukrank.ukrank(engine, source, 2);
    
    for(int i = 0 ; i < res.size(); i++){
        std::cout << res[i] <<" ";
    }
    std::cout << std::endl;
    return 0; 
}
