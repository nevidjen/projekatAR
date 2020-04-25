#ifndef NOT_H
#define NOT_H

#include "unary_connective.h"

class Not : public UnaryConnective
{
public:
  Not(const Formula &op);
  
  virtual std::ostream& print(std::ostream &out) const;
  
  virtual Formula substitute(const Formula &what, const Formula &with) const;
  
  virtual bool eval(const Valuation &val) const;
  
  virtual Formula simplify() const;
  
  virtual Formula nnf() const;
  
  virtual LiteralListList listCNF() const;
  
  virtual LiteralListList listDNF() const;
};

#endif // NOT_H
