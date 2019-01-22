#include "expr.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#define PRE_SINGLE 1
#define PRE_MULTI 2
#define USER 3
Expression * makeExprSingle(std::string & func, Expression * value) {  //sin,cos,etc
  std::string sin("sin");
  std::string cos("cos");
  std::string sqrt("sqrt");
  std::string ln("ln");
  if (func.compare(sin) == 0) {
    return new SinExpression(value);
  }
  else if (func.compare(cos) == 0) {
    return new CosExpression(value);
  }
  else if (func.compare(sqrt) == 0) {
    return new SqrtExpression(value);
  }
  else if (func.compare(ln) == 0) {
    return new LnExpression(value);
  }
  else {
    std::cerr << "Could not initialize single param Expression, aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
}
Expression * makeExprMulti(std::string & func,
                           Expression * lhs,
                           Expression * rhs) {  //predeclared multi
  std::size_t found_pow = func.find("pow");
  if (func[0] == '+') {
    return new PlusExpression(lhs, rhs);
  }
  else if (func[0] == '-') {
    return new MinusExpression(lhs, rhs);
  }
  else if (func[0] == '*') {
    return new TimesExpression(lhs, rhs);
  }
  else if (func[0] == '/') {
    return new DivExpression(lhs, rhs);
  }
  else if (func[0] == '%') {
    return new ModExpression(lhs, rhs);
  }
  else if (found_pow != std::string::npos) {  // as pow is multi
    return new PowExpression(lhs, rhs);
  }
  else {
    std::cerr << "Could not initialize multi-param pre Expression, aborting" << std::endl;
    exit(EXIT_FAILURE);
  }
}
void skipSpace(const char ** strp) {
  while (isspace(**strp)) {
    *strp = *strp + 1;
  }
}
int isValidUserFuncCall(
    std::string & func_name,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc) {
  std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it;
  it = userDefinedFunc.find(func_name);  //check if key exists or not
  if (it == userDefinedFunc.end()) {
    std::cerr << "No such func exists. Aborted" << std::endl;
    exit(EXIT_FAILURE);
  }  // If it passes this, such func exists
  else {
    if (it->second.second == NULL) {
      std::cerr << "You cannot call a func that you are trying to declare" << std::endl;
      exit(EXIT_FAILURE);
    }             // If it passes this, expr is assigned
    return USER;  //use 1 if user_defined
  }
}
int isValidFuncCall(
    std::string & func_name,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc) {
  if (func_name.length() == 1) {  //single char ops, easier to begin with
    char c = func_name[0];
    if (strchr("+-*/%", c) != NULL) {  //if single char func is one of those
      return PRE_MULTI;
    }
    else {  //could be single char, and a declared function. Check with function abstraction
      return isValidUserFuncCall(func_name, userDefinedFunc);
    }
  }
  else {  //if not single char, little more complicated
    if (func_name.compare("sin") == 0) {
      return PRE_SINGLE;
    }
    else if (func_name.compare("cos") == 0) {
      return PRE_SINGLE;
    }
    else if (func_name.compare("sqrt") == 0) {
      return PRE_SINGLE;
    }
    else if (func_name.compare("ln") == 0) {
      return PRE_SINGLE;
    }
    else if (func_name.compare("pow") == 0) {  //not wrong, takes in two
      return PRE_MULTI;
    }
    else {  // Check with function abstraction
      return isValidUserFuncCall(func_name, userDefinedFunc);
    }
  }
  return 0;
}
Expression * parseExpression(
    const char ** strp,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it,
    bool param_allowed);  //declaration to solve scope issue
Expression * functionCall(
    const char ** strp,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it,
    bool param_allowed) {
  skipSpace(strp);  //now, pointer is at the OP(no guarantee only one char, check until next space
  std::string func_name;
  while (**strp != ' ') {
    func_name.append(1, **strp);
    *strp = *strp + 1;
  }
  int pre_or_userdefined;  //-1 if predefined, 0 if invalid, 1 if userdefined
  if ((pre_or_userdefined = isValidFuncCall(func_name, userDefinedFunc)) == 0) {
    std::cerr << "Invalid func: " << func_name << std::endl;
    exit(EXIT_FAILURE);
  }
  *strp = *strp + 1;
  if (pre_or_userdefined == PRE_MULTI) {  //predefined with multi input(single char ones)
    Expression * lhs = parseExpression(strp, userDefinedFunc, it, param_allowed);
    if (lhs == NULL) {  // if it fails to create lhs
      std::cerr << "Cannot create lhs for multi expression" << std::endl;
      delete lhs;
      return NULL;
    }
    Expression * rhs;
    rhs = parseExpression(strp, userDefinedFunc, it, param_allowed);
    if (rhs == NULL) {
      std::cerr << "Cannot create rhs for multi expression" << std::endl;
      delete rhs;
      return NULL;
    }
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return makeExprMulti(func_name, lhs, rhs);
    }
  }
  else if (pre_or_userdefined == PRE_SINGLE) {  //sin, cos, etc
    Expression * value = parseExpression(strp, userDefinedFunc, it, param_allowed);
    if (value == NULL) {
      std::cerr << "Cannot create single expression " << std::endl;
      delete value;
      return NULL;
    }
    skipSpace(strp);
    if (**strp == ')') {
      *strp = *strp + 1;
      return makeExprSingle(func_name, value);
    }
    std::cerr << "Failed to find ending )" << std::endl;
    return NULL;  //would fail if it didn't find ) anyway
  }
  else {  //userdeclared, create single NumExpression(value if evaluate() at that instant
    std::vector<double> param_values;
    Expression * curr_expr = parseExpression(strp, userDefinedFunc, it, false);
    while (curr_expr != NULL) {                              //checks if ends without )
      double add_value = curr_expr->evaluate(param_values);  // doesn't matter if param_values
      //are empty at this point. It will only call on NumExpr, which ignores the param_values
      param_values.push_back(add_value);
      skipSpace(strp);
      if (**strp == ')') {
        *strp = *strp + 1;
        break;  // breaks the loop
      }
      curr_expr = parseExpression(strp, userDefinedFunc, it, false);
    }
    delete curr_expr;  //Once the deal is done with it -ADDED THIS NOW
    if (userDefinedFunc[func_name].first.size() != param_values.size()) {
      std::cerr << "Provide correct num of parameter values to " << func_name << std::endl;
      exit(EXIT_FAILURE);
    }
    double valuetomakeexpr = userDefinedFunc[func_name].second->evaluate(param_values);
    return new NumExpression(valuetomakeexpr);
  }
  std::cerr << "Reached end of funcCall. Provided more than 2 params for func" << std::endl;
  return NULL;
}
Expression * parseExpression(
    const char ** strp,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it,
    bool param_allowed) {
  skipSpace(strp);  // skip until non-space found
  if (**strp == '\0') {
    std::cerr << "End of line found mid expression!" << std::endl;
    return NULL;
  }
  else if (**strp == '(') {  //func E E (or func id id id ..)
    *strp = *strp + 1;
    return functionCall(strp, userDefinedFunc, it, param_allowed);  // pass to funcCall
  }
  else {  //either param or number (start with num first?
    char * endp;
    double num = strtod(*strp, &endp);
    if (endp == *strp) {            //Param(valid or invalid)
      if (param_allowed == true) {  // if not case param not allowed
        std::string param_name;     //save the given name
        while (**strp != ' ') {     //Add, param name cannot be )
          if (**strp == ')') {      // so stops when reached )
            break;
          }
          param_name.append(1, **strp);
          *strp = *strp + 1;
        }
        //std::cout << "Generated param =" << param_name << "." << std::endl;
        int param_index = -1;  //error if not changed
        for (size_t i = 0; i < it->second.first.size(); i++) {
          if (param_name.compare((it->second.first)[i]) == 0) {  //if found equal
            param_index = i;
            break;
          }
        }
        if (param_index == -1) {  //which means not altered, so not found in list
          std::cerr << "Parameter provided not declared. Error" << std::endl;
          exit(EXIT_FAILURE);
        }
        else {  //found, return proper index.
          return new ParamExpression((size_t)param_index);
        }
      }
      else {
        std::cerr << "Value violating is -" << **strp << "-" << std::endl;
        std::cerr << "Please do not provide any parameters at non param zone" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    *strp = endp;
    return new NumExpression(num);
  }
}

Expression * defineExpression(
    const char * expr_line,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> > & userDefinedFunc,
    std::map<std::string, std::pair<std::vector<std::string>, Expression *> >::iterator it,
    bool param_allowed) {
  const char * temp = expr_line;
  Expression * expr = parseExpression(&temp, userDefinedFunc, it, param_allowed);
  if (expr == NULL) {
    std::cerr << "Error in parseExpression" << std::endl;
    exit(EXIT_FAILURE);
  }
  return expr;
}
