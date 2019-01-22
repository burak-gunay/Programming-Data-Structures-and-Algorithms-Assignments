#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>  //MOST ARE TAKEN FROM THE EVAL ASSIGNMENT COURSE- CITATION DREW HILTON
class Expression
{
 public:
  Expression() {}
  virtual ~Expression() {}
  //evaluate is not constant, as the ParamExpression
  virtual double evaluate(std::vector<double> & paramvalues) const = 0;
};
class NumExpression : public Expression
{
 protected:
  double value;

 public:
  NumExpression(double num) : value(num) {
    //std::cout << "Val is= " << num << std::endl;
  }
  //Only case where paramvalues is not used, to be honest cannot find a way around this
  virtual double evaluate(std::vector<double> & paramvalues) const {
    paramvalues[0];  //suppress the warning(FULL HONESTY)
    return value;
  }
  virtual ~NumExpression() {}
};
class ParamExpression : public Expression
{
 protected:
  size_t param_index;

 public:
  ParamExpression(size_t p_index) : param_index(p_index) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    return paramvalues[param_index];  //Just pick corresponding value, simple as that
  }
};
class PlusExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * E1, Expression * E2) : lhs(E1), rhs(E2) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = lhs->evaluate(paramvalues);
    double val2 = rhs->evaluate(paramvalues);
    return val1 + val2;
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * E1, Expression * E2) : lhs(E1), rhs(E2) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = lhs->evaluate(paramvalues);
    double val2 = rhs->evaluate(paramvalues);
    return val1 - val2;
  }
  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * E1, Expression * E2) : lhs(E1), rhs(E2) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = lhs->evaluate(paramvalues);
    double val2 = rhs->evaluate(paramvalues);
    return val1 * val2;
  }
  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * E1, Expression * E2) : lhs(E1), rhs(E2) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = lhs->evaluate(paramvalues);
    double val2 = rhs->evaluate(paramvalues);
    return val1 / val2;
  }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};

class ModExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  ModExpression(Expression * E1, Expression * E2) : lhs(E1), rhs(E2) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = lhs->evaluate(paramvalues);
    double val2 = rhs->evaluate(paramvalues);
    return fmod(val1, val2);
  }
  virtual ~ModExpression() {
    delete lhs;
    delete rhs;
  }
};

class PowExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  PowExpression(Expression * E1, Expression * E2) : lhs(E1), rhs(E2) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = lhs->evaluate(paramvalues);
    double val2 = rhs->evaluate(paramvalues);
    return pow(val1, val2);
  }
  virtual ~PowExpression() {
    delete lhs;
    delete rhs;
  }
};

class SinExpression : public Expression
{
 protected:
  Expression * param;

 public:
  SinExpression(Expression * p_param) : param(p_param) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = param->evaluate(paramvalues);
    return sin(val1);
  }
  virtual ~SinExpression() { delete param; }
};

class CosExpression : public Expression
{
 protected:
  Expression * param;

 public:
  CosExpression(Expression * p_param) : param(p_param) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = param->evaluate(paramvalues);
    return cos(val1);
  }
  virtual ~CosExpression() { delete param; }
};

class SqrtExpression : public Expression
{
 protected:
  Expression * param;

 public:
  SqrtExpression(Expression * p_param) : param(p_param) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = param->evaluate(paramvalues);
    return sqrt(val1);
  }
  virtual ~SqrtExpression() { delete param; }
};

class LnExpression : public Expression
{
 protected:
  Expression * param;

 public:
  LnExpression(Expression * p_param) : param(p_param) {}
  virtual double evaluate(std::vector<double> & paramvalues) const {
    double val1 = param->evaluate(paramvalues);
    return log(val1);
  }
  virtual ~LnExpression() { delete param; }
};
