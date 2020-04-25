#include "imp.h"
#include "constant.h"
#include "not.h"
#include "or.h"

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
  GET_OPERANDS(op1, op2);
  
  return !op1->eval(val) || op2->eval(val);
}

Formula Imp::simplify() const
{
  GET_OPERANDS(simplifiedOp1, simplifiedOp2);
  simplifiedOp1 = simplifiedOp1->simplify();
  simplifiedOp2 = simplifiedOp2->simplify();
  
  if (BaseFormula::isOfType<True>(simplifiedOp1))
  {
    return simplifiedOp2;
  }
  else if (BaseFormula::isOfType<True>(simplifiedOp2))
  {
    return simplifiedOp1;
  }
  else if (BaseFormula::isOfType<False>(simplifiedOp1))
  {
    return std::make_shared<True>();
  }
  else if (BaseFormula::isOfType<False>(simplifiedOp2))
  {
    return std::make_shared<Not>(simplifiedOp1)->simplify();
  }
  
  return std::make_shared<Imp>(simplifiedOp1, simplifiedOp2);
}

Formula Imp::nnf() const
{
  GET_OPERANDS(op1, op2);
  return std::make_shared<Or>(std::make_shared<Not>(op1)->nnf(), op2->nnf());
}

LiteralListList Imp::listCNF() const
{
  throw std::runtime_error{"Implikacija se mora eliminisati tokom nnf() procedure"};
}

LiteralListList Imp::listDNF() const
{
  throw std::runtime_error{"Implikacija se mora eliminisati tokom nnf() procedure"};
}
