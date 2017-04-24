/*
 * main.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */
#include "main.h"
#include "menu.h"

int independent = 1;
// generation rules of dependent tuples, 2: exclusive every 2 tuples;
//4: exclusive every 4 tuples;  8: exclusive every 8 tuples
int g_gen_rule;

// correlation coefficient of score and confidence values;
double g_corr_coeff;

// distribution of "confidence", 1: uniformly distributed;
// 2: normally distributed;  3: exponentially distributed
int g_confi_distr;

// mean value for normally and exponentially distribution
double g_mean;

// tuple numbers
int g_tuple_num;

// which graph to load, from 0 to 14 (according to the paper)
int graph_seq = 6;

// when creating graph, what would be the Y-axis, 0: time, 1: depth
int y_axis = 1;

// uncertain top-k semantics, 0: UTopk, including IndepU-Topk/OPTU-Topk
// 1:UkRanks, including IndepU-kRanks/OPTU-kRanks
int u_semantics = 0;

// when creating graph of single data set, store the k value, time and depth values
// (typically 4 groups), the purpose of using array instead vector is MATLAB
std::vector<std::vector<double>> mono_data;

// dataset vector to be displayed
std::vector<std::vector<std::string>> current_dataset;
// scroe-ranked dataset from mysql
std::vector<std::vector<std::string>> ranked_dataset;
// query result to be shown
std::vector<std::vector<std::string>> current_result;

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

	SimpleMenu *menu = new SimpleMenu(wxT("Top-k Query of Uncertain Databases"));
	menu->Show(true);

    return true;
}



