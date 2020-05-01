#include "valuation.h"

#include <iterator>
#include <algorithm>

Valuation::Valuation(const AtomSet &aset)
{
  reset(aset);
}

void Valuation::reset(const AtomSet &aset)
{
  m_values.clear();
  for (unsigned atom : aset)
  {
    m_values[atom] = false;
  }
}

bool Valuation::value(unsigned p) const
{
  return m_values.at(p);
}

bool &Valuation::value(unsigned p)
{
  return m_values.at(p);
}

bool Valuation::next()
{
  auto first = m_values.rbegin();
  auto last = m_values.rend();
  while (first != last)
  {
    first->second = !first->second;
    if (first->second)
    {
      return true;
    }
    ++first;
  }
  
  return false;
}

std::ostream &Valuation::print(std::ostream &out) const
{
  for (const auto &atomValue : m_values)
  {
    out << atomValue.second << " ";
  }
  return out;
}


std::ostream &operator<<(std::ostream &out, const Valuation &v)
{
  return v.print(out);
}
#include "base_formula.h"

#include <typeinfo>

BaseFormula::BaseFormula()
{
  
}

void BaseFormula::getAtoms(AtomSet &aset) const
{
  UNUSED_VARIABLE(aset);
}

bool BaseFormula::equalTo(const Formula &f) const
{
  const BaseFormula *base = f.get();
  return typeid (*this) == typeid (*base);
}

BaseFormula::~BaseFormula()
{
  
}

OptionalValuation BaseFormula::isSatisfiable() const
{
  AtomSet aset;
  getAtoms(aset);
  Valuation val{aset};
  do {
    if (eval(val))
    {
      return val;
    }
  } while (val.next());
  
  return {};
}

OptionalValuation BaseFormula::isNotTautology() const
{
  AtomSet aset;
  getAtoms(aset);
  Valuation val{aset};
  do {
    if (!eval(val))
    {
      return val;
    }
  } while (val.next());
  return {};
}

bool BaseFormula::isEquivalent(const Formula &f) const
{
  AtomSet aset;
  getAtoms(aset);
  f->getAtoms(aset);
  Valuation val{aset};
  do {
    if (eval(val) != f->eval(val))
    {
      return false;
    }
  } while (val.next());
  return true;
}

void BaseFormula::printTruthTable(std::ostream &out) const
{
  AtomSet aset;
  getAtoms(aset);
  Valuation v{aset};
  out << std::noboolalpha;
  do {
    out << v << " | " << eval(v) << '\n'; 
  } while (v.next());
}

bool BaseFormula::isConsequence(const Formula &f) const
{
  AtomSet aset;
  getAtoms(aset);
  f->getAtoms(aset);
  Valuation val{aset};
  do {
    if (eval(val) && !f->eval(val))
    {
      return false;
    }
  } while (val.next());
  return true;
}

bool operator==(const Formula &lhs, const Formula &rhs)
{
  return lhs->equalTo(rhs);
}

bool operator!=(const Formula &lhs, const Formula &rhs)
{
  return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &out, const Formula &f)
{
  return f->print(out);
}
#include "atomic_formula.h"

AtomicFormula::AtomicFormula()
  : BaseFormula ()
{
  
}

unsigned AtomicFormula::complexity() const
{
  return 0;
}

Formula AtomicFormula::substitute(const Formula &what, const Formula &with) const
{
  if (equalTo(what))
  {
    return with;
  }
  
  return std::const_pointer_cast<BaseFormula>(shared_from_this());
}
#include "binary_connective.h"

BinaryConnective::BinaryConnective(const Formula &op1, const Formula &op2)
  : BaseFormula (), m_op1(op1), m_op2(op2)
{
  
}

std::ostream &BinaryConnective::print(std::ostream &out) const
{
  out << "(";
  m_op1->print(out);
  out << symbol();
  m_op2->print(out);
  return out << ")";
}

unsigned BinaryConnective::complexity() const
{
  return 1 + m_op1->complexity() + m_op2->complexity();
}

void BinaryConnective::getAtoms(AtomSet &aset) const
{
  m_op1->getAtoms(aset);
  m_op2->getAtoms(aset);
}

bool BinaryConnective::equalTo(const Formula &f) const
{
  if (BaseFormula::equalTo(f))
  {
    const BinaryConnective *pF = static_cast<const BinaryConnective*>(f.get());
    return m_op1 == pF->m_op1 && m_op2 == pF->m_op2;
  }
  
  return false;
}

std::pair<Formula, Formula> BinaryConnective::operands() const
{
  return {m_op1, m_op2};
}

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


#include "constant.h"


True::True()
  : AtomicFormula ()
{
  
}

std::ostream &True::print(std::ostream &out) const
{
  return out << "TRUE";
}

bool True::eval(const Valuation &val) const
{
  UNUSED_VARIABLE(val);
  return true;
}

False::False()
  : AtomicFormula ()
{
  
}

std::ostream &False::print(std::ostream &out) const
{
  return out << "FALSE";
}

bool False::eval(const Valuation &val) const
{
  UNUSED_VARIABLE(val);
  return false;
}
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


#include "not.h"

Not::Not(const Formula &op)
  : UnaryConnective (op)
{
  
}

std::ostream &Not::print(std::ostream &out) const
{
  out << "~";
  return operand()->print(out);
}

Formula Not::substitute(const Formula &what, const Formula &with) const
{
  if (equalTo(what))
  {
    return with;
  }
  
  return std::make_shared<Not>(operand()->substitute(what, with));
}

bool Not::eval(const Valuation &val) const
{
  return !operand()->eval(val);
}
#include "and.h"

And::And(const Formula &op1, const Formula &op2)
  :BinaryConnective (op1, op2)
{
  
}

std::string And::symbol() const
{
  return "/\\";
}

Formula And::substitute(const Formula &what, const Formula &with) const
{
  return substituteImpl<And>(what, with);
}

bool And::eval(const Valuation &val) const
{
  Formula op1, op2;
  std::tie(op1, op2) = operands();
  
  return op1->eval(val) && op2->eval(val);
}
#include "or.h"

Or::Or(const Formula &op1, const Formula &op2)
  : BinaryConnective (op1, op2)
{
  
}

std::string Or::symbol() const
{
  return "\\/";
}

Formula Or::substitute(const Formula &what, const Formula &with) const
{
  return substituteImpl<Or>(what, with);
}

bool Or::eval(const Valuation &val) const
{
  Formula op1, op2;
  std::tie(op1, op2) = operands();
  
  return op1->eval(val) || op2->eval(val);
}




#include "imp.h"

Imp::Imp(const Formula &op1, const Formula &op2)
  :BinaryConnective (op1, op2)
{
  
}

std::string Imp::symbol() const
{
  return "=>";
}

Formula Imp::substitute(const Formula &what, const Formula &with) const
{
  return substituteImpl<Imp>(what, with);
}

bool Imp::eval(const Valuation &val) const
{
  Formula op1, op2;
  std::tie(op1, op2) = operands();
  
  return !op1->eval(val) || op2->eval(val);
}
#include "iff.h"

Iff::Iff(const Formula &op1, const Formula &op2)
  :BinaryConnective (op1, op2)
{
  
}

std::string Iff::symbol() const
{
  return "<=>";
}

Formula Iff::substitute(const Formula &what, const Formula &with) const
{
  return substituteImpl<Iff>(what, with);
}

bool Iff::eval(const Valuation &val) const
{
  Formula op1, op2;
  std::tie(op1, op2) = operands();
  
  return op1->eval(val) == op2->eval(val);
}
