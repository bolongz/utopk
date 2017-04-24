/*
 * dataset.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: tao
 */

#include "dataset.h"
#include "main.h"
#include "show_list.h"
#include "engine.h"		//MATLAB
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <sstream>
#include <stdlib.h>     /* srand, rand */

Dataset::Dataset(){
	//independent = 1;
	gen_rule = 2;
	corr_coeff = 0;
	confi_distr = 1;
	mean = 0.5;
	std::vector<std::vector<std::string>> v_dataset;
}

Dataset::~Dataset(){
	clear();
}

void Dataset::get_dataset_value(std::vector<std::vector<std::string>> &v){
	std::vector<std::string> v_temp;

	if (v_dataset.size() == 0) return;
	v.clear();
	for (unsigned int i = 0; i < v_dataset.size(); i++){
		for (unsigned int j = 0 ;j < v_dataset[0].size(); j++){
			v_temp.push_back(v_dataset[i][j]);
		}
		v.push_back(v_temp);
		v_temp.clear();
	}
}

int Dataset::get_gen_rule(){
	return gen_rule;
}

double Dataset::get_corr_coeff(){
	return corr_coeff;
}

int Dataset::get_confi_distr(){
	return confi_distr;
}

double Dataset::get_mean(){
	return mean;
}

void Dataset::set_gen_rule(int i){
	gen_rule = i;
}

void Dataset::set_corr_coeff(double d){
	corr_coeff = d;
}

void Dataset::set_confi_distr(int i){
	confi_distr = i;
}

void Dataset::set_mean(double d){
	mean = d;
}

void Dataset::clear(){
	v_dataset.clear();
}

bool Dataset::isempty(){
	return v_dataset.empty();
}

void Dataset::generate_cor_data(int tuple_num, double corr, double mean){
	int M =2;
	int N = 4;
	// Define MATLAB engine pointer
	Engine *ep;
	if (!(ep=engOpen("\0"))) //if start successfully, the pointer ep will not be NULL.
	{
		std::cout<< "Can't start MATLAB engine!"<<std::endl;
		return;
	}
	// define 2-D array
	double cArray[M][N] = { { (double)tuple_num, mean, 0.04, 0.04*corr },
				{ 0.0,mean, 0.04*corr, 0.04 } };

	//define mxArray，as array of N rows, M columns (reverse of C array)
	mxArray *xx = mxCreateDoubleMatrix(N, M, mxREAL);
	//copy cArray value into mxArray
	memcpy(mxGetPr(xx), cArray, M*N*sizeof(double));
	//write into MATLAB's work space
	engPutVariable(ep, "input_data", xx);
	// call MATLAB function "myFunc"
	engEvalString(ep, "RESULT=bivarate_normal(input_data);"); // 1. the computation result is set to RESULT
	mxArray *result = engGetVariable(ep, "RESULT");  // 2. get the result
	double *p = mxGetPr(result); //return the result into a double array
	double cResult[tuple_num][2];
	for (int i = 0; i < tuple_num; i++){
		cResult[i][0] = p[i];
		cResult[i][1] = p[tuple_num + i];
	}

	//release memory
	mxDestroyArray(xx);
	mxDestroyArray(result);
	engClose(ep); //close MATLAB engine

	for (int i = 0; i < tuple_num; i++){
		std::vector<std::string> v_temp;
		std::stringstream ss, ss1;
		std::string str, str1;;
		ss << "name" << i;
		ss >> str;
		v_temp.push_back(str);
		ss1 << cResult[i][0];
		ss1 >> str1;
		v_temp.push_back(str1);
		double x = cResult[i][1];
		if (x > 1) x = 1;
		if (x < 0.01) x = 0.01;
		v_temp.push_back(std::to_string (x));
		v_dataset.push_back(v_temp);
	}
}

bool Dataset::generate_dataset(int tuple_num){
	v_dataset.clear();
	if (independent == 0){						// tuples are dependent
		//if (tuple_num > 30) return false;
		if (corr_coeff == 0){					// score and confidence are not correlated
				int remainder = tuple_num % gen_rule;
				int quotient = tuple_num / gen_rule;
				std::random_device rd1;
				std::mt19937 gen1(rd1());
				std::uniform_real_distribution<> dist1(0.0,1.0);
				std::random_device rd2;
				std::mt19937 gen2(rd2());
				for (int i = 0; i < quotient; i++){
					std::vector<std::string> v_temp;
					//std::stringstream ss;
					std::string str;
					double sum_temp = 0.0;
					int j = 0;
					for (j = 0; j < gen_rule - 1; j++){
						std::stringstream ss;
						double x = dist1(gen1);
						std::uniform_real_distribution<> dist2(0.0,1.0 - sum_temp);
						double y = dist2(gen2);
						//std::cout << "confidence: " << y << std::endl;
						sum_temp += y;
						ss << "name" << gen_rule*i + j;
						ss >> str;
						v_temp.push_back(str);
						v_temp.push_back(std::to_string (x));
						v_temp.push_back(std::to_string (y));
						v_dataset.push_back(v_temp);
						v_temp.clear();
						str.clear();
					}
					double y = 1.0 - sum_temp;			//process the last one in XOR N
					//std::cout << "confidence: " << y << std::endl;
					double x = dist1(gen1);
					std::stringstream ss;
					ss << "name" << gen_rule*i + j;
					ss >> str;
					v_temp.push_back(str);
					v_temp.push_back(std::to_string (x));
					v_temp.push_back(std::to_string (y));
					v_dataset.push_back(v_temp);
				}
				if (remainder != 0){
					for (int i = 0; i < remainder; i++){
						std::vector<std::string> v_temp;
						std::string str;
						std::stringstream ss;
						std::uniform_real_distribution<> dist2(0.0,1.0);
						double x = dist1(gen1);
						double y = dist2(gen2);
						ss << "name" << gen_rule*quotient + i;
						ss >> str;
						v_temp.push_back(str);
						v_temp.push_back(std::to_string (x));
						v_temp.push_back(std::to_string (y));
						v_dataset.push_back(v_temp);
					}
				}
		}
		else{							// score and confidence are correlated
			int remainder = tuple_num % gen_rule;
			int quotient = tuple_num / gen_rule;
			std::random_device rd1;
			std::mt19937 gen1(rd1());
			double rho = corr_coeff;
			for (int i = 0; i < quotient; i++){
				std::vector<std::string> v_temp;
				std::string str;
				double sum_temp = 0.0;
				int j = 0;
				for (j = 0; j < gen_rule - 1; j++){
					std::stringstream ss;
					std::uniform_real_distribution<> dist1(0.0,1.0 - sum_temp);
					double y = dist1(gen1);
					double alpha = 1 - cbrt((1-rho) /2); //
					double x;
					if (y <= alpha){
						x = y;
					}
					else{
						x = 1 + alpha - y;
					}
					sum_temp += y;
					ss << "name" << gen_rule*i + j;
					ss >> str;
					v_temp.push_back(str);
					v_temp.push_back(std::to_string (x));
					v_temp.push_back(std::to_string (y));
					v_dataset.push_back(v_temp);
					v_temp.clear();
					str.clear();
				}
				double y = 1.0 - sum_temp;			//process the last one in XOR N
				double alpha = 1 - cbrt((1-rho) /2); //
				double x;
				if (y <= alpha){
					x = y;
				}
				else{
					x = 1 + alpha - y;
				}
				std::stringstream ss;
				ss << "name" << gen_rule*i + j;
				ss >> str;
				v_temp.push_back(str);
				v_temp.push_back(std::to_string (x));
				v_temp.push_back(std::to_string (y));
				v_dataset.push_back(v_temp);
			}
			if (remainder != 0){
				for (int i = 0; i < remainder; i++){
					std::vector<std::string> v_temp;
					std::string str;
					std::stringstream ss;
					std::uniform_real_distribution<> dist1(0.0,1.0);
					double y = dist1(gen1);
					double alpha = 1 - cbrt((1-rho) /2);
					double x;
					if (y <= alpha){
						x = y;
					}
					else{
						x = 1 + alpha - y;
					}
					ss << "name" << gen_rule*quotient + i;
					ss >> str;
					v_temp.push_back(str);
					v_temp.push_back(std::to_string (x));
					v_temp.push_back(std::to_string (y));
					v_dataset.push_back(v_temp);
				}
			}
		}
	}
	else{								// tuples are independent
		if (corr_coeff == 0){			// score and confidence are uncorrelated
			if (confi_distr == 1){		//uu
				std::random_device rd1;
				std::mt19937 gen1(rd1());
				std::uniform_real_distribution<> dist1(0.0,1.0);
				std::random_device rd2;
				std::mt19937 gen2(rd2());
				std::uniform_real_distribution<> dist2(0.0,1.0);

				for (int i = 0; i < tuple_num; i++){
					std::vector<std::string> v_temp;
					std::stringstream ss;
					std::string str;
					double x = dist1(gen1);
					double y = dist2(gen2);
					ss << "name" << i;
					ss >> str;
					v_temp.push_back(str);
					v_temp.push_back(std::to_string (x));
					v_temp.push_back(std::to_string (y));
					v_dataset.push_back(v_temp);
				}
				//return true;
			}
			else if (confi_distr == 2){	//un
				std::random_device rd1;
				std::mt19937 gen1(rd1());
				std::uniform_real_distribution<> dist1(0.0,1.0);
				std::random_device rd2;
				std::mt19937 gen2(rd2());
				std::normal_distribution<> dist2(mean,0.2);

				for (int i = 0; i < tuple_num; i++){
					std::vector<std::string> v_temp;
					std::stringstream ss;
					std::string str;
					double x = dist1(gen1);
					double y = dist2(gen2);
					if (y < 0.01) y = 0.01;
					if (y > 1) y = 1;
					ss << "name" << i;
					ss >> str;
					v_temp.push_back(str);
					v_temp.push_back(std::to_string (x));
					v_temp.push_back(std::to_string (y));
					v_dataset.push_back(v_temp);
				}
			}
			else if (confi_distr == 3){ //ue
				std::random_device rd1;
				std::mt19937 gen1(rd1());
				std::uniform_real_distribution<> dist1(0.0,1.0);
				std::random_device rd2;
				std::mt19937 gen2(rd2());
				std::normal_distribution<> dist2(mean);

				for (int i = 0; i < tuple_num; i++){
					std::vector<std::string> v_temp;
					std::stringstream ss;
					std::string str;
					double x = dist1(gen1);
					double y = dist2(gen2);
					if (y < 0.01) y = 0.01;
					if (y > 1) y = 1;
					ss << "name" << i;
					ss >> str;
					v_temp.push_back(str);
					v_temp.push_back(std::to_string (x));
					v_temp.push_back(std::to_string (y));
					v_dataset.push_back(v_temp);
				}
			}
		}
		else{						// score and confidence are correlated
			generate_cor_data(tuple_num, corr_coeff, mean);
		}
	}
	g_gen_rule = gen_rule;
	g_corr_coeff= corr_coeff;
	g_confi_distr = confi_distr;
	g_mean = mean;
	g_tuple_num = tuple_num;
	return true;
}










