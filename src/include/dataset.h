/*
 * dataset.h
 *
 *  Created on: Apr 2, 2017
 *      Author: tao
 */

#ifndef DATASET_H_
#define DATASET_H_

#include <vector>
#include <string>
//#include <mysql.h>

class Dataset {
public:
	Dataset();
	~Dataset();
	void get_dataset_value(std::vector<std::vector<std::string>> &v);
	//bool get_independent_value();
	int get_gen_rule();
	double get_corr_coeff();
	int get_confi_distr();
	double get_mean();

	//void set_independent_value(bool b);
	void set_gen_rule(int i);
	void set_corr_coeff(double d);
	void set_confi_distr(int i);
	void set_mean(double d);

	void clear();
	bool isempty();

	//if corr_coeff != 0, generate corresponding dataset
	void generate_cor_data(int tuple_num, double corr, double mean);

	// generate data-set with the following parameters: total tuple number, "k" value,
	// tuples are dependent or not, generation rules(XOR), correlation coefficiency
	// between score and confidence, confidence distribution
	bool generate_dataset(int tuple_num);

	// put dataset "v" into mysql database of local host, return true if succeed, return
	// false if fail.
	//bool dataset_into_mysql(std::vector<std::vector<std::string>> &v);

private:
	// tuples of selected dataset are independant or not
	//bool independent;

	// generation rules of dependent tuples, 2: exclusive every 2 tuples;
	//4: exclusive every 4 tuples;  8: exclusive every 8 tuples
	int gen_rule;

	// correlation coefficient of score and confidence values;
	double corr_coeff;

	// distribution of "confidence", 1: uniformly distributed;
	// 2: normally distributed;  3: exponentially distributed
	int confi_distr;

	// mean value for normally and exponentially distribution
	double mean;

	// dataset vector to be displayed
	std::vector<std::vector<std::string>> v_dataset;
};

#endif /* DATASET_H_ */
