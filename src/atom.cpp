#include "atom.h"

Atom::Atom(unsigned p)
  : AtomicFormula (), m_p(p)
{
  
}

std::ostream &Atom::print(std::ostream &out) const
{
  return out << "p" << m_p;
}

bool Atom::eval(const Valuation &val) const
{
  return val.value(m_p);
}

void Atom::getAtoms(AtomSet &aset) const
{
  aset.insert(m_p);
}

bool Atom::equalTo(const Formula &f) const
{
  if (BaseFormula::equalTo(f))
  {
    const Atom *pF = static_cast<const Atom*>(f.get());
    return pF->m_p == m_p;
  }
  
  return false;
}

LiteralListList Atom::listCNF() const
{
  return {{std::const_pointer_cast<BaseFormula>(shared_from_this())}};
}

LiteralListList Atom::listDNF() const
{
  return {{std::const_pointer_cast<BaseFormula>(shared_from_this())}};
}


