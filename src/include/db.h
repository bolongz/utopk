/*
 * db.h
 *
 *  Created on: Apr 6, 2017
 *      Author: tao
 */

#ifndef DB_H_
#define DB_H_

#include "main.h"
//#include "show_list.h"
#include <iostream>
#include <vector>
#include <string>
//#include <random>
#include <cmath>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <mysql.h>
#include <fstream>

class Db{
public:
	Db();
	~Db();

	bool dataset_into_mysql(std::vector<std::vector<std::string>> &v);
	bool get_score_ranked_data(std::vector<std::vector<std::string>> &v);
	bool save_into_file(std::vector<std::vector<std::string>> v, const char *filename);
};


#endif /* DB_H_ */
