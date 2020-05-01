#include "unary_connective.h"

UnaryConnective::UnaryConnective(const Formula &op)
  :BaseFormula (), m_op{op}
{  
}

unsigned UnaryConnective::complexity() const
{
  return m_op->complexity() + 1;
}

void UnaryConnective::getAtoms(AtomSet &aset) const
{
  m_op ->getAtoms(aset);
}

bool UnaryConnective::equalTo(const Formula &f) const
{
  if (BaseFormula::equalTo(f))
  {
    const UnaryConnective *pF = static_cast<const UnaryConnective *>(f.get());
    return pF->m_op == m_op;
  }
  
  return false;
}

Formula UnaryConnective::operand() const
{
  return m_op;
}


