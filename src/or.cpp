#include "or.h"
#include "constant.h"

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
  GET_OPERANDS(op1, op2);
  
  return op1->eval(val) || op2->eval(val);
}

Formula Or::simplify() const
{
  GET_OPERANDS(simplifiedOp1, simplifiedOp2);
  simplifiedOp1 = simplifiedOp1->simplify();
  simplifiedOp2 = simplifiedOp2->simplify();
  
  if (BaseFormula::isOfType<True>(simplifiedOp1))
  {
    return simplifiedOp1;
  }
  else if (BaseFormula::isOfType<True>(simplifiedOp2))
  {
    return simplifiedOp2;
  }
  else if (BaseFormula::isOfType<False>(simplifiedOp1))
  {
    return simplifiedOp2;
  }
  else if (BaseFormula::isOfType<False>(simplifiedOp2))
  {
    return simplifiedOp1;
  }
  
  return std::make_shared<Or>(simplifiedOp1, simplifiedOp2);
}

Formula Or::nnf() const
{
  GET_OPERANDS(op1, op2);
  return std::make_shared<Or>(op1->nnf(), op2->nnf());
}

LiteralListList Or::listCNF() const
{
  GET_OPERANDS(op1, op2);
  return BaseFormula::cross(op1->listCNF(), op2->listCNF());
}

LiteralListList Or::listDNF() const
{
  GET_OPERANDS(op1, op2);
  return BaseFormula::concatenate(op1->listDNF(), op2->listDNF());
}
