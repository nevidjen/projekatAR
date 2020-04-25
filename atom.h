#ifndef ATOM_H
#define ATOM_H

#include "atomic_formula.h"

class Atom : public AtomicFormula
{
public:
  Atom(unsigned p);
  
  virtual std::ostream& print(std::ostream &out) const;
  
  virtual bool eval(const Valuation &val) const;
  
  virtual void getAtoms(AtomSet &aset) const;
  
  virtual bool equalTo(const Formula &f) const;
  
  virtual LiteralListList listCNF() const;
  
  virtual LiteralListList listDNF() const;
private:
  unsigned m_p;
};

#endif // ATOM_H
