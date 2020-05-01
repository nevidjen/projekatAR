#ifndef AND_H
#define AND_H

#include "binary_connective.h"

class And : public BinaryConnective
{
public:
  And(const Formula &op1, const Formula &op2);
  
  virtual std::string symbol() const;
  
  virtual Formula substitute(const Formula &what, const Formula &with) const;
  
  virtual bool eval(const Valuation &val) const;
  
  virtual Formula simplify() const;
  
  virtual Formula nnf() const;
  
  virtual LiteralListList listCNF() const;
  
  virtual LiteralListList listDNF() const;
};

#endif // AND_H
