/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


int main(int argc, char *argv[]){

    /* for the type:
     *  utopk: represents u topk processing 
     *  ukrank: represents u krank processing
     *  iutopk: represents indenpent u topk processing 
     *  iukrank: represents indenpent u krank processing 
     */
    
    std::string kk(argv[1]);

    std::istringstream ik(kk);
    int k;
    ik >> k;
    
    std::string data(argv[2]);
    
    std::ifstream fin(data.c_str(), std::ios::in);
    std::string line;
    std::vector<std::string> name;

    while(getline(fin, line)){
        
        std::istringstream iss(line);
        std::string a , b, c;
        iss >> a >> b >> c;
        
        name.push_back(a);
    }
    
    fin.close();

    for(size_t i = 0; i < name.size();i++){
    
        std::string _name = "name" + std::to_string(i);
  //      std::cout << _name  <<" " << name[i] <<" " << _name.size() << " " << name[i].size()<< std::endl;    
        for(int j =0; j < name.size();j++){
            if(name[j] == _name) std::cout << j << " ";
        }
        
        if((i + 1) % k ==0) std::cout << std::endl;
    
    }

    return 0; 
}
