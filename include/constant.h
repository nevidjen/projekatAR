#ifndef CONSTANT_H
#define CONSTANT_H

#include "atomic_formula.h"

class True : public AtomicFormula
{
public:
  True();
  
  virtual std::ostream& print(std::ostream &out) const;
  
  virtual bool eval(const Valuation &val) const;
  
  virtual LiteralListList listCNF() const;
  
  virtual LiteralListList listDNF() const;
};

class False : public AtomicFormula
{
public:
  False();
  
  virtual std::ostream& print(std::ostream &out) const;
  
  virtual bool eval(const Valuation &val) const;
  
  virtual LiteralListList listCNF() const;
  
  virtual LiteralListList listDNF() const;
};

#endif // CONSTANT_H
