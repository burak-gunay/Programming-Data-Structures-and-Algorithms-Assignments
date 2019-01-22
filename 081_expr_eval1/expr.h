#include <iostream>
#include <sstream>
#include <string>
class Expression
{
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
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
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
