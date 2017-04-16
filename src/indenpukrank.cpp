/* Author: Bolong Zhang */
/* Email: blzhang.m@gmail.com */

#include "indenpukrank.h"
#include <map>


Indenpukrank::Indenpukrank(){}

Indenpukrank::Indenpukrank(const Indenpukrank &t){

    results = t.get_results();
    M = t.get_matrix();
}

Indenpukrank::Indenpukrank(Indenpukrank &&t){

    results = t.get_results();
    M = t.get_matrix();
    t.~Indenpukrank();
}

const Indenpukrank &Indenpukrank::operator=(const Indenpukrank &t){

    if(this == &t){
    
        return *this;
    }

    results = t.get_results();
    M = t.get_matrix();
    
    return *this;
}

Indenpukrank &Indenpukrank::operator=(Indenpukrank &&t){

    if(this == &t){
    
        return *this;
    }

    results = t.get_results();
    M = t.get_matrix();
    t.~Indenpukrank();
    
    return *this;
}

Indenpukrank::~Indenpukrank(){

    Results().swap(results);
    Dynamic().swap(M);

}


Indenpukrank::Results Indenpukrank::indenpukrank(const Launch::Source &source, size_t k){

    size_t _size = source.size();

    results.resize(k);
    M.resize(k);
    for(size_t i = 0; i < k; i++){
        M[i].resize(_size);
    }
    std::vector<double> maxval(k,-1);
    std::vector<double> accumulative(_size,1.0);
    Results maxloc(k,-1);
    std::vector<double> reminder(k,1.0);
    size_t current  = 0, i;
    size_t reported = 0;
    
    //    std::map<int, bool> check;
    while(current < _size){

        
        
        //M[0].push_back( source[current].confidence());
        M[0][current] = ( source[current].confidence());
        
        for(size_t j = 0; j < current; j++){
            
            M[0][current] = M[0][current] * (1.0 - source[j].confidence());
        }

        for(size_t i = 1; i < k; i++){
    
                double mij = source[current].confidence();
                double _p = 0.0;
             
            /*   for(size_t m = 0; m < current; m++){
                    double __p = 1.0; 
                    for(size_t h = m + 1; h < current; h++){
                        __p = __p * (1.0 - source[h].confidence()); 
                    }
                    __p = __p * M[i-1][m];
                    _p = _p + __p;
                
                }
            */
                if(current == 0) {
                    _p = 0.0;
                }else{
                    if(i == 1){
                        for(size_t h = 1; h < current; h++){
                            accumulative[h] = accumulative[h] * (1.0 -source[current-1].confidence());
                            _p = _p + accumulative[h] * M[i-1][h-1];
                        }
                        _p = _p + accumulative[current] * M[i-1][current -1];
                
                    }else{
                        
                        for(size_t h = 1; h < current; h++){
                            _p = _p + accumulative[h] * M[i-1][h-1];
                        }
                        _p = _p + accumulative[current] * M[i-1][current -1];
                    
                    }
                }
                M[i][current] = ( mij * _p);
    
        }
        size_t  temp = reported;
       /* for(i = 0; i < k ; i++){
            for(size_t j = 0; j < M[i].size(); j++){
                std::cout << M[i][j] << " ";
            }
            std::cout << std::endl;
        }
            std::cout << std::endl;
        */for(i = reported; i < k ; i++){
            //for(size_t j = current; j < M[i].size(); j++){
            //    std::cout << M[i][j] << " ";
                size_t   j  = current;
                reminder[i] = reminder[i] - M[i][j];
                if(maxval[i] < M[i][j]){
                    maxval[i] = M[i][j];
                    maxloc[i] = j;
                }
            //}
           // std::cout << std::endl;
          //  std::cout << "CURRENT " << current << " " << i << " " << maxval[i] <<" " << reminder[i] << std::endl;
            if(maxval[i] > reminder[i]){
         //       if(check.find(maxloc[i]) == check.end()){
                    temp = reported + 1;
            //         std::cout << "REPORT " << reported << " " << maxloc[i] << std::endl;
                    results[i] = maxloc[i]; 
         //           check[maxloc[i]] = true;
              //  }
            }
        }
        current = current + 1;     
        depth = current;
        reported = temp;
        if(reported == k) break;
    }
    return results;

} 
