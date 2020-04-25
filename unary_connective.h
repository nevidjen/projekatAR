#ifndef UNARYCONNECTIVE_H
#define UNARYCONNECTIVE_H

#include "base_formula.h"

class UnaryConnective : public BaseFormula
{
public:
  UnaryConnective(const Formula &op);
  
  unsigned complexity() const;
  
  void getAtoms(AtomSet &aset) const;
  
  bool equalTo(const Formula &f) const;
  
  Formula operand() const;
private:
  Formula m_op;
};

#endif // UNARYCONNECTIVE_H
