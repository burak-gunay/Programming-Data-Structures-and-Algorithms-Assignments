#include <iostream>
#include <sstream>
#include <string>
class Expression
{
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
  virtual long evaluate() const = 0;
};
class NumExpression : public Expression
{
 protected:
  long value;

 public:
  NumExpression(long num) : value(num) {}
  virtual std::string toString() const {
    std::string out;
    std::stringstream ss;
    ss << value;
    out = ss.str();
    return out;
  }
  virtual long evaluate() const { return value; }
  virtual ~NumExpression() {}
};
class PlusExpression : public Expression
{
 protected:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * E1, Expression * E2) : lhs(E1), rhs(E2) {}
  virtual std::string toString() const {
    std::string out;
    std::stringstream ss;
    ss << "(";
    ss << lhs->toString();
    ss << " + ";
    ss << rhs->toString();
    ss << ")";
    out = ss.str();
    return out;
  }
  virtual long evaluate() const {
    long val1 = lhs->evaluate();
    long val2 = rhs->evaluate();
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
  virtual std::string toString() const {
    std::string out;
    std::stringstream ss;
    ss << "(";
    ss << lhs->toString();
    ss << " - ";
    ss << rhs->toString();
    ss << ")";
    out = ss.str();
    return out;
  }
  virtual long evaluate() const {
    long val1 = lhs->evaluate();
    long val2 = rhs->evaluate();
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
  virtual std::string toString() const {
    std::string out;
    std::stringstream ss;
    ss << "(";
    ss << lhs->toString();
    ss << " * ";
    ss << rhs->toString();
    ss << ")";
    out = ss.str();
    return out;
  }

  virtual long evaluate() const {
    long val1 = lhs->evaluate();
    long val2 = rhs->evaluate();
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
  virtual std::string toString() const {
    std::string out;
    std::stringstream ss;
    ss << "(";
    ss << lhs->toString();
    ss << " / ";
    ss << rhs->toString();
    ss << ")";
    out = ss.str();
    return out;
  }
  virtual long evaluate() const {
    long val1 = lhs->evaluate();
    long val2 = rhs->evaluate();
    return val1 / val2;
  }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
