#include <string.h>

#include <iostream>
#include <sstream>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 public:
  long num;
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << num;
    return ans.str();
  }
};

class PlusExpression : public Expression {
 public:
  Expression * a;
  Expression * b;
  PlusExpression(Expression * lhs, Expression * rhs) : a(lhs), b(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << a->toString() << " + " << b->toString() << ")";
    return ans.str();
  }
  ~PlusExpression() {
    delete a;
    delete b;
  }
};

class MinusExpression : public Expression {
 public:
  Expression * l;
  Expression * r;
  MinusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << l->toString() << " - " << r->toString() << ")";
    return ans.str();
  }
  ~MinusExpression() {
    delete l;
    delete r;
  }
};

class TimesExpression : public Expression {
 public:
  Expression * l;
  Expression * r;
  TimesExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << l->toString() << " * " << r->toString() << ")";
    return ans.str();
  }

  ~TimesExpression() {
    delete l;
    delete r;
  }
};

class DivExpression : public Expression {
 public:
  Expression * l;
  Expression * r;
  DivExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << l->toString() << " / " << r->toString() << ")";
    return ans.str();
  }

  ~DivExpression() {
    delete l;
    delete r;
  }
};
