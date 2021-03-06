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

    Launch::Source source;
    Launch::Rules r;
    if(argc < 2){
        
        std::cout << "Run syntax:" << std::endl;
        std::cout << "topk <type> <k> <source> <rule> " << std::endl;
        std::cout << "For independent processing, we do not have rule file" << std::endl;
        
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

    std::vector<std::vector<std::string>> db;

    while(getline(fin, line)){
        Tuple tuple;
        
        std::istringstream iss(line);

        std::string a ,  b, c;
        iss >> a >> b >> c;
        
        std::vector<std::string> ss; // push the input into vector<string> 
        ss.push_back(a);
        ss.push_back(b);
        ss.push_back(c);
        
        db.push_back(ss);
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
    caller.db_to_source(db, source); //from db type to source 
    caller.start(source, r); // start engine;
    std::vector<std::vector<std::string>> results; //results 
    if(type == "utopk"){
        caller.processing_utopk(k, results);
        std::cout << "RUN TIME: " << caller.run_time() << std::endl;;
        std::cout << "Scan Depth: " << caller.scan_depth() << std::endl;;
    }else if(type == "ukrank"){
        caller.processing_ukrank(k, results);
        std::cout << "RUN TIME: " << caller.run_time() << std::endl;;
        std::cout << "Scan Depth: " << caller.scan_depth() << std::endl;;
    }else if(type == "iutopk"){
        caller.processing_indenputopk(k, results);

        std::cout << "RUN TIME: " << caller.run_time() << std::endl;;
        std::cout << "Scan Depth: " << caller.scan_depth() << std::endl;;
    }else if(type == "iukrank"){
        caller.processing_indenpukrank(k, results);
        std::cout << "RUN TIME: " << caller.run_time() << std::endl;;
        std::cout << "Scan Depth: " << caller.scan_depth() << std::endl;;
    }else{
        std::cout << "Wrong Type" << std::endl;
    }

    for(size_t i = 0; i < results.size(); i++){
    
        std::cout<<results[i][0] << " " << results[i][1] <<" " << results[i][2] << std::endl;
    
    }
    return 0; 
}
