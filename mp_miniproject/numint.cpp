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
void valid_int(size_t func_name_begin, size_t func_name_end) {
  if (func_name_begin == std::string::npos) {
    std::cerr << "Please provide some parameters" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (func_name_end == std::string::npos) {
    std::cerr << "You gotta provide provide more than one argument" << std::endl;
    exit(EXIT_FAILURE);
  }
}
double
recursiveInt(  //init_values are not a reference on purpose. They will be changed with each run
    size_t index_vector,
    const double width,
    std::vector<double> init_values,
    std::vector<size_t> & rep_per_param,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::string & func_name) {
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
  //base case= last param in init_values&rep_per_param .Calculate without more recursion
  if (index_vector == init_values.size() - 1) {  //Final index, simply calculate.
    double numint_w = 0;
    double cum_sum = 0;
    double temp_val = 0;
    size_t curr_param_rep = rep_per_param[index_vector];
    double numint = init_values[index_vector];

    std::vector<double> trivial_vector;
    for (size_t i = 0; i < curr_param_rep; i++) {
      numint_w = numint + width;  //replace the final one with this val
      std::ostringstream numint_sstr;
      std::ostringstream numint_w_sstr;
      numint_sstr << "( " << func_name << " ";
      numint_w_sstr << "( " << func_name << " ";
      for (size_t j = 0; j < init_values.size() - 1; j++) {
        numint_sstr << init_values[j] << " ";
        numint_w_sstr << init_values[j] << " ";
      }

      numint_sstr << numint << ")";
      numint_w_sstr << numint_w << ")";  //Now, insert back to string
      std::string numint_str(numint_sstr.str());
      std::string numint_w_str(numint_w_sstr.str());

      numint = numint + width;
      Expression * temp_expr = defineExpression(numint_str.c_str(), userDefinedFunc, it, false);
      Expression * temp_expr2 = defineExpression(numint_w_str.c_str(), userDefinedFunc, it, false);
      temp_val = temp_expr->evaluate(trivial_vector);
      cum_sum = cum_sum + temp_val;
      delete temp_expr;
      temp_val = temp_expr2->evaluate(trivial_vector);
      cum_sum = cum_sum + temp_val;
      delete temp_expr2;
    }
    return cum_sum;
  }
  else {  //iteratively increase this call's value, recursively call the smaller index
    size_t curr_rep = rep_per_param[index_vector];
    double cum_sum = 0;
    double temp_val = 0;
    double initial_val = init_values[index_vector];
    for (size_t i = 0; i < curr_rep; i++) {
      init_values[index_vector] = initial_val + i * width;
      temp_val = recursiveInt(
          index_vector + 1, width, init_values, rep_per_param, userDefinedFunc, func_name);
      cum_sum = cum_sum + temp_val;
    }
    return cum_sum;
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
  valid_int(func_name_begin, func_name_end);  //check if parameter provided , and more than one
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
  const double width = strtod(cstr, &endp);  // so accidently dont get changed
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

  std::vector<double> init_values;
  size_t params_read_size = params_read.size();
  for (size_t i = 0; i < params_read_size; i++) {
    if ((i % 2) == 0) {  // only first values, where they begin
      init_values.push_back(params_read[i]);
    }
  }  //Now , we only have initial start values
  double cum_sum = recursiveInt(0, width, init_values, rep_per_param, userDefinedFunc, func_name);
  //cum sum can be returned as well if needed
  cum_sum *= pow(width, rep_per_param.size());  //1 at this case
  cum_sum /= pow(2, rep_per_param.size());
  std::cout << "Integral found to be " << cum_sum << std::endl;
  delete[] delete_ptr;
}
