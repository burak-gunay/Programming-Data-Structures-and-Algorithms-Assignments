#include <ctype.h>
#include <time.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "expr.h"
void valid_int(size_t func_name_begin, size_t func_name_end);
Expression * defineExpression(
    const char * expr_line,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it,
    bool param_allowed);
double randGenerator(double min, double max) {
  double random_coefficient =
      (double)rand() / RAND_MAX;  // Returns a random coefficient, between 0 and 1
  return max * random_coefficient - min * random_coefficient + min;
  // If 0, return min. If 1, return max. Any other value, any other value in between
}
double mcint_helper(  // here we pass in values and calculate
    double trials,
    std::vector<std::pair<double, double> > & minmax_pairs,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::string & func_name) {
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;  //trivial
  std::vector<double> trivial_vector;
  double temp_val = 0;
  double cum_sum = 0;
  for (size_t i = 0; i < trials; i++) {  // add as many trials we have
    std::ostringstream mcint_sstr;
    mcint_sstr << "( " << func_name << " ";                 // now add, the params found
    for (size_t j = 0; j < minmax_pairs.size() - 1; j++) {  //-1 to avoid extra space
      mcint_sstr << randGenerator(minmax_pairs[j].first, minmax_pairs[j].second) << " ";
    }
    mcint_sstr << randGenerator(minmax_pairs[minmax_pairs.size() - 1].first,  // add the final
                                minmax_pairs[minmax_pairs.size() - 1].second)
               << ")";
    std::string mcint_str(mcint_sstr.str());

    Expression * temp_expr = defineExpression(mcint_str.c_str(), userDefinedFunc, it, false);
    temp_val = temp_expr->evaluate(trivial_vector);
    cum_sum = cum_sum + temp_val;
    delete temp_expr;
  }
  cum_sum = cum_sum / trials;  // now, multiply by each range
  for (size_t y = 0; y < minmax_pairs.size(); y++) {
    cum_sum = cum_sum * (minmax_pairs[y].second - minmax_pairs[y].first);
  }
  return cum_sum;
}
void calculate_mcint(
    std::string & linecontent,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc) {
  srand(time(NULL));  //Initialize rand generator with proper seed
  if (linecontent.size() == 6) {
    std::cerr << "Provide more than just numint" << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t func_name_begin =
      linecontent.find_first_not_of(" ", 5);  //pointing at the beginning of funcname
  size_t func_name_end = linecontent.find_first_of(" ", func_name_begin);
  valid_int(func_name_begin, func_name_end);  //check if parameter provided , and more than one
  std::string func_name;
  func_name.insert(0, linecontent, func_name_begin, func_name_end - func_name_begin);
  if (userDefinedFunc.find(func_name) == userDefinedFunc.end()) {  // if func not found
    std::cerr << "This is not defined func" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string number_params = linecontent;
  number_params.erase(0, func_name_end);  // delete until only nums and end (hopefully) left
  char * cstr = new char[number_params.length() + 1];
  char * delete_ptr = cstr;  // ptr to delete(doesnt change value)
  std::strcpy(cstr, number_params.c_str());

  std::vector<double> params_read;  // keep the parameters read from numint
  double curr_value;
  char * endp;
  const double trials = strtod(cstr, &endp);  // so accidently dont get changed
  while (cstr != endp) {
    cstr = endp;
    curr_value = strtod(cstr, &endp);
    if (cstr == endp) {  // if failed
      break;
    }
    std::cout << "Pushing " << curr_value << std::endl;
    params_read.push_back(curr_value);
  }
  if ((fmod(trials, 1) != 0) || trials <= 0) {  // if not int
    std::cerr << "Please provide a valid positive number of trials" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
  it = userDefinedFunc.find(func_name);
  if (params_read.size() !=
      (it->second.first.size()) * 2) {  // if params of the func and mcint do not match
    std::cerr << "Provide 2 parameters per func param" << std::endl;
    exit(EXIT_FAILURE);
  }
  //create a vector of pairs
  std::vector<std::pair<double, double> > minmax_pairs;
  for (size_t i = 0; i < params_read.size(); i = i + 2) {  //reason for +2, calculate for each pair
    minmax_pairs.push_back(std::pair<double, double>(params_read[i], params_read[i + 1]));

    if (params_read[i + 1] <= params_read[i]) {
      std::cerr << "Provide an incrementing pair OR the width is greater than the range"
                << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  double cum_sum = mcint_helper(trials, minmax_pairs, userDefinedFunc, func_name);
  std::cout << "Cum sum is " << cum_sum << std::endl;

  delete delete_ptr;
}
