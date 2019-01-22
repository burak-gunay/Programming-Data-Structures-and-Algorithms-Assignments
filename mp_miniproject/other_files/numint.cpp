#include <ctype.h>

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
Expression * defineExpression(
    const char * expr_line,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it,
    bool param_allowed);
void valid_numint(size_t func_name_begin, size_t func_name_end) {
  if (func_name_begin == std::string::npos) {
    std::cerr << "Please provide some parameters" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (func_name_end == std::string::npos) {
    std::cerr << "You gotta provide provide more than one argument" << std::endl;
    exit(EXIT_FAILURE);
  }
}
void calculate_numint(
    std::string & linecontent,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc) {
  //Know that the first 6 chars are numint. So, look for the func name now
  if (linecontent.size() == 7) {
    std::cerr << "Provide more than just numint" << std::endl;
    exit(EXIT_FAILURE);
  }
  size_t func_name_begin =
      linecontent.find_first_not_of(" ", 6);  //pointing at the beginning of funcname
  size_t func_name_end = linecontent.find_first_of(" ", func_name_begin);
  valid_numint(func_name_begin, func_name_end);  //check if parameter provided , and more than one
  std::string func_name;
  func_name.insert(0, linecontent, func_name_begin, func_name_end - func_name_begin);
  if (userDefinedFunc.find(func_name) == userDefinedFunc.end()) {  // if func not found
    std::cerr << "This is not defined func" << std::endl;
    exit(EXIT_FAILURE);
  }
  //now, check for numbers. If any non number(strtod reject) shows up, its an error anyway
  std::string number_params = linecontent;
  number_params.erase(0, func_name_end);  // delete until only nums and end (hopefully) left
  char * cstr = new char[number_params.length() + 1];
  char * delete_ptr = cstr;  // ptr to delete(doesnt change value)
  std::strcpy(cstr, number_params.c_str());

  std::vector<double> params_read;  // keep the parameters read from numint
  double curr_value;
  char * endp;
  double width = strtod(cstr, &endp);
  while (cstr != endp) {
    cstr = endp;
    curr_value = strtod(cstr, &endp);
    if (cstr == endp) {  // if failed
      break;
    }
    params_read.push_back(curr_value);
  }
  //std::cout << "Width found" << width << std::endl;
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
  it = userDefinedFunc.find(func_name);
  if (params_read.size() !=
      (it->second.first.size()) * 2) {  // if params of the func and numint do not match
    std::cerr << "Provide 2 parameters per func param" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::vector<size_t> rep_per_param;                       // keeps how many reps needed per param
  for (size_t i = 0; i < params_read.size(); i = i + 2) {  //reason for +2, calculate for each pair
    size_t curr_range = params_read[i + 1] - params_read[i];
    if (curr_range <= 0 || curr_range < width) {
      std::cerr << "Provide an incrementing pair OR the width is greater than the range"
                << std::endl;
      exit(EXIT_FAILURE);
    }
    //std::cout << "This many" << curr_range / width << "reps for" << i << std::endl;
    rep_per_param.push_back(curr_range / width);  // this equates to num of reps
  }
  double numint_w = 0;
  double cum_sum = 0;
  double temp_val = 0;
  double numint = params_read[0];
  for (size_t i = 0; i < rep_per_param[0]; i++) {  //hardcoding for single variable
    numint_w = numint + width;                     //Now, got the values we need for the defineExpr
    std::string numint_str;
    numint_str.insert(0, "(");
    numint_str.insert(1, func_name);  // std::string is now (f
    numint_str.push_back(' ');
    std::string numint_w_str = numint_str;
    std::ostringstream numint_sstr;
    std::ostringstream numint_w_sstr;
    numint_sstr << numint;
    numint_w_sstr << numint_w;
    numint_str.insert(3, numint_sstr.str());      //insert the param
    numint_w_str.insert(3, numint_w_sstr.str());  //insert the param
    numint_str.push_back(')');
    numint_w_str.push_back(')');

    Expression * temp_expr = defineExpression(numint_str.c_str(), userDefinedFunc, it, false);
    std::vector<double> trivial_vector;
    temp_val = temp_expr->evaluate(trivial_vector);
    cum_sum = cum_sum + temp_val;
    delete temp_expr;
    Expression * temp_expr2 = defineExpression(numint_w_str.c_str(), userDefinedFunc, it, false);
    temp_val = temp_expr2->evaluate(trivial_vector);
    cum_sum = cum_sum + temp_val;
    delete temp_expr2;
    std::cout << "Cum sum is " << cum_sum << std::endl;

    numint = numint + width;  //prep for next
  }
  cum_sum *= pow(width, rep_per_param.size());  //1 at this case
  cum_sum /= pow(2, rep_per_param.size());
  std::cout << "Integral found to be " << cum_sum << std::endl;
  delete[] delete_ptr;
}
