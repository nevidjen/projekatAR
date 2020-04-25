#ifndef ATOMICFORMULA_H
#define ATOMICFORMULA_H

#include "base_formula.h"

class AtomicFormula : public BaseFormula
{
public:
  AtomicFormula();
  
  virtual unsigned complexity() const;
  
  virtual Formula substitute(const Formula &what, const Formula &with) const;
  
  virtual Formula simplify() const;
  
  virtual Formula nnf() const;
};

#endif // ATOMICFORMULA_H
