#include <ctype.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "expr.h"
#define DEFINE 100
#define TEST 101
#define COMMENT 102
#define NUMINT 103
#define MCINT 104
Expression * defineExpression(
    const char * expr_line,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it,
    bool param_allowed);
void calculate_numint(
    std::string & linecontent,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc);
void calculate_mcint(
    std::string & linecontent,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc);
//This function below takes in from define command line, all the id's after the first (, and before t//he last ). modifies the func_name, and param_names. Does not check if >=1 param id
void defineIdentifiers(std::string & defparam,
                       std::string & func_name,
                       std::vector<std::string> & param_names) {
  if (defparam.find_first_of("#") != std::string::npos) {  //should not be a pound symbol in define
    std::cerr << "Cannot have a # symbol in the define part" << std::endl;
    exit(EXIT_FAILURE);
  }
  bool name_declared = false;
  size_t id_index = 0;                    //index for defparam string
  while (id_index < defparam.length()) {  //while end is not reached
    if (defparam[id_index] == ' ') {      // if equal to space
      id_index++;
    }
    else {                                      //if not equal to space
      if (name_declared == false) {             // first find name
        while (defparam[id_index] != ' ') {     // as long as id_ptr is not space&terminator
          if (id_index == defparam.length()) {  // if reach end
            return;
          }
          func_name.append(1, defparam[id_index]);
          id_index++;
        }
        //if id_ptr is space, this ends and gets incremented in the next run
        name_declared = true;
      }
      else {  //name already declared
        std::string curr_param;
        while (defparam[id_index] != ' ') {  //guaranteed to run at least once
          if (defparam[id_index] == '\0') {
            break;  // stop if ( is found
          }
          if (id_index ==           //This part might be trivial with the \0 check
              defparam.length()) {  //if reached the last character, add what we have in hand
            param_names.push_back(curr_param);
            return;
          }
          curr_param.append(1, defparam[id_index]);
          id_index++;
        }  //Need to check if param's all chars are integer. If so, reject DODO
        //std::cout << "Current param to be added is " << curr_param << std::endl;
        if (curr_param.find_first_not_of("0123456789") == std::string::npos) {
          std::cerr << "Please do not put a param with only digits" << std::endl;
          exit(EXIT_FAILURE);
        }
        if (curr_param.find_first_of("()") != std::string::npos) {
          std::cerr << "Please do not put a param with brackets -( or )- in it" << std::endl;
          exit(EXIT_FAILURE);
        }
        param_names.push_back(curr_param);
      }
    }
  }
}

std::string defineFunction(
    std::string & linecontent,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc) {
  if (linecontent.find_first_of("=") == std::string::npos) {  //if no equals found
    std::cerr << "Your define line should have a = sign" << std::endl;
    exit(EXIT_FAILURE);
  }
  else if (linecontent.find_first_of("=") !=
           linecontent.find_last_of("=")) {  //if it has more than one eqs sign
    std::cerr << "Please do not provide a variable name with =" << std::endl;
    exit(EXIT_FAILURE);
  }
  else {  //valid define case

    std::size_t firstparenthesis = linecontent.find_first_of("(");
    std::size_t lastparenthesis = linecontent.find_last_of(")", linecontent.find_first_of("="));
    if ((firstparenthesis == std::string::npos) || (lastparenthesis == std::string::npos)) {
      std::cerr << "Please provide proper define brackets" << std::endl;
      exit(EXIT_FAILURE);
    }

    std::string defparam =  //new string, with only the fname and param  ids
        linecontent.substr(firstparenthesis + 1, lastparenthesis - firstparenthesis - 1);
    std::string func_name;                 // current func name
    std::vector<std::string> param_names;  //curr param names
    defineIdentifiers(defparam, func_name, param_names);

    if (param_names.size() == 0) {  //Checking if valid func, can be abstracted
      std::cerr << "You at least need to provide one parameter to the function" << std::endl;
      exit(EXIT_FAILURE);
    }
    //Now, check if func_name already defined or not
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
    it = userDefinedFunc.find(func_name);
    if (it != userDefinedFunc.end()) {
      std::cerr << "Function already defined, exiting" << std::endl;
      exit(EXIT_FAILURE);
    }
    //All tests passed, now add to map
    std::pair<std::vector<std::string>, Expression *> param_expr_pair(
        param_names, NULL);  //EXPR is null yet, will be added when expr is created
    std::pair<std::string, std::pair<std::vector<std::string>, Expression *> > curr_pair(
        func_name, param_expr_pair);  //add to map
    std::pair<std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator,
              bool>
        ret;  //ret's second param checks if inserted correctly
    ret = userDefinedFunc.insert(curr_pair);
    if (ret.second == false) {
      std::cerr << "Function and value pair not added correctly, terminating" << std::endl;
      exit(EXIT_FAILURE);
    }
    return func_name;  //returning the func name, so expr can be linked to the func
  }
  return NULL;
}
void printTest(std::string & print_test_contents) {
  size_t name_beginning =
      print_test_contents.find_first_not_of(" ", 1);  //first non whitespace, after (
  size_t end_of_name = print_test_contents.find_first_of(
      " ", name_beginning);    // points at the whitespace after the ending of name
  std::string curr_func_name;  //name of the func
  curr_func_name.insert(0, print_test_contents, name_beginning, end_of_name - name_beginning);

  size_t param_values_begin = print_test_contents.find_first_not_of(" ", end_of_name);
  size_t param_values_end = print_test_contents.find_last_of(")");
  // std::cout << print_test_contents << std::endl;
  // std::cout << "Begin and end " << param_values_begin << " and " << param_values_end << std::endl;
  std::string param_values_list;  //contains string of params
  param_values_list.insert(
      0, print_test_contents, param_values_begin, param_values_end - param_values_begin);
  std::cout << curr_func_name << "(" << param_values_list << ")";
}
double readNumberforTest(std::string & read_num) {
  if (read_num.find_last_of(")") ==
      read_num.size() - 1) {  //This foolproofs the next. Not in terms of correctness, but bug
    std::cerr << "You need to provide a number" << std::endl;
    exit(EXIT_FAILURE);
  }
  read_num.erase(0, read_num.find_last_of(")") + 1);
  char * val_cstr = new char[read_num.length() + 1];
  char * delete_ptr = val_cstr;  // keep to delete
  std::strcpy(val_cstr, read_num.c_str());
  int num_count = 0;
  char * endp;
  double value_from_test = strtod(val_cstr, &endp);
  while (endp != val_cstr) {
    num_count++;
    val_cstr = endp;
    strtod(val_cstr, &endp);
  }
  if (num_count == 0) {
    std::cerr << "Please provide a number" << std::endl;
    exit(EXIT_FAILURE);
  }
  else if (num_count > 1) {
    std::cerr << "Provide a single number to test, not more" << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    //std::cout << "Value read is " << value_from_test << std::endl;
    delete[] delete_ptr;
    return value_from_test;
  }
}
void testSuites(
    std::string & linecontent,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc) {
  //std::cout << linecontent << "is test" << std::endl;
  if (linecontent.find_first_of("(") == std::string::npos ||
      linecontent.find_last_of(")") == std::string::npos) {
    std::cerr << "Please provide a proper test case - like test(f 1 2 3) 15" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string to_be_expression = linecontent;
  to_be_expression.erase(0, to_be_expression.find_first_of("("));
  to_be_expression.erase(to_be_expression.find_last_of(")") + 1, std::string::npos);
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
  //Param not allowed, as no new params can be generated.
  Expression * evaluate_expr =
      defineExpression(to_be_expression.c_str(), userDefinedFunc, it, false);
  //std::vector<double> is trivial here, as it simply points at a NumExpr
  std::vector<double> trivial_vector;
  double actual_value = evaluate_expr->evaluate(trivial_vector);
  delete evaluate_expr;
  //std::cout << "Value calculated is " << actual_value << std::endl;
  std::string read_num = linecontent;
  size_t comment_pos =
      read_num.find_first_of("#", read_num.find_last_of(")"));  //if comment after )
  if (comment_pos != std::string::npos) {  // if comment, delete commented section
    read_num.erase(comment_pos, std::string::npos);
  }
  double expected_value = readNumberforTest(read_num);
  printTest(to_be_expression);
  std::cout << " = " << actual_value;
  if (std::abs(expected_value - actual_value) < 0.0000000000001) {
    std::cout << " [correct]" << std::endl;
  }
  else {
    std::cout << " [INCORRECT: expected " << expected_value << "]" << std::endl;
  }
}

int decideCommand(std::string & command) {
  std::size_t defineLine = command.find("define");
  std::size_t testLine = command.find("test");
  std::size_t numintLine = command.find("numint");
  std::size_t mcintLine = command.find("mcint");
  if (defineLine != std::string::npos) {
    //std::cout << "Command is definition" << std::endl;
    return DEFINE;
  }
  else if (testLine != std::string::npos) {
    //std::cout << "Command is test" << std::endl;
    return TEST;
  }
  else if (command[0] == '#') {
    return COMMENT;
  }
  else if (numintLine != std::string::npos) {
    return NUMINT;
  }
  else if (mcintLine != std::string::npos) {
    return MCINT;
  }
  else {
    std::cerr << "Invalid input, please provide define/test at pos0 of the line" << std::endl;
    exit(EXIT_FAILURE);
  }
}
int main(int argc, char ** argv) {
  if (argc > 1) {  //checking if input put properly, but does not check if stdin is empty
    std::cerr << "Please provide valid input in stdin, after" << argv[0] << ", terminating"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string command_argument(*argv);
  char * line = NULL;
  size_t sz;
  /* 
  Main data structure to store the userdefined functions. Best described with this
                 userDefinedFunc
                    /      \
                  key        value
                 /               \
  func_name(std::string)          std::pair
                                 /        \
  param_names(std::vector<std::string>)    Expression * 
  */
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> > userDefinedFunc;

  while (getline(&line, &sz, stdin) != -1) {
    std::string linecontent;  //declare each time to avoid prev string remains staying
    linecontent.append(line);
    std::string firstCommand;
    firstCommand.insert(0, linecontent, 0, 6);  // This way, only checks at beginning instead of
    // the whole thing, this way if id with define/test, does not confuse
    int command_type = decideCommand(firstCommand);
    if (command_type == DEFINE) {  //found to be define
      std::string func_name = defineFunction(
          linecontent, userDefinedFunc);  //so the expr can be added(corresponding func_name)
      //function defined, now evaluate expression
      //If it can pass through defineFunc, it can only have 1 =. So valid input to next funcs
      size_t equals_pos = linecontent.find_first_of("=");  // from here until #
      size_t command_pos = linecontent.find_first_of("#");
      if (command_pos != std::string::npos) {  //if comment is there
        linecontent.erase(command_pos);        //first get rid of the part after #
      }
      linecontent.erase(0, equals_pos + 1);  //+1 to get rid of =
      char * cstr = new char[linecontent.length() + 1];
      std::strcpy(cstr, linecontent.c_str());
      std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
      it = userDefinedFunc.find(func_name);  //current func key/value pair iterator
      if (it == userDefinedFunc.end()) {     //extra check to see whether added as we want
        std::cerr << "Function not added to the map properly" << std::endl;
        exit(EXIT_FAILURE);
      }
      bool param_allowed = true;
      Expression * r_expr = defineExpression(
          cstr, userDefinedFunc, it, param_allowed);  // in expr.cpp file, Expression defined
      //it pointing at current key/value pair (to check params
      //Pass in the param list to create accordingly paramExprs
      //Before we do this, EXPR will be NULL. Can use this to check whether current definition is
      //pointing at itself(which is invalid)
      it->second.second = r_expr;                   //assigns the expr found
      std::cout << "defined " << func_name << "(";  // now.printing correct output
      for (size_t i = 0; i < it->second.first.size() - 1; i++) {
        std::cout << it->second.first[i] << " ";
      }
      std::cout << it->second.first[it->second.first.size() - 1] << ")" << std::endl;
      //std::cout << "Expr assigned" << std::endl;
      delete[] cstr;
    }
    else if (command_type == TEST) {
      testSuites(linecontent, userDefinedFunc);  //found to be test
    }
    else if (command_type == COMMENT) {  // comment line, has no effect
      continue;
    }
    else if (command_type == NUMINT) {  //numint ( Pass in current line and the map
      calculate_numint(linecontent, userDefinedFunc);
    }
    else {  //Found to be mcint
      calculate_mcint(linecontent, userDefinedFunc);
    }
  }
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
  for (it = userDefinedFunc.begin(); it != userDefinedFunc.end(); ++it) {
    delete it->second.second;  //Delete each expression
  }
  // also, delete expressions in the tree(traverse, and delete head of each)
  return EXIT_SUCCESS;
}
