/*
 * main.h
 *
 *  Created on: Mar 28, 2017
 *      Author: tao
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <wx/wx.h>
#include <vector>
#include <string>

extern int independent;
extern int g_gen_rule;
extern double g_corr_coeff;
extern int g_confi_distr;
extern double g_mean;
extern int g_tuple_num;
extern int graph_seq;
extern int y_axis;
extern int u_semantics;
extern std::vector<std::vector<double>> mono_data;
extern std::vector<std::vector<std::string>> current_dataset;
extern std::vector<std::vector<std::string>> ranked_dataset;
extern std::vector<std::vector<std::string>> current_result;

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();

};



#endif /* MAIN_H_ */
