#include "and.h"
#include "constant.h"

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
  GET_OPERANDS(op1, op2);
  
  return op1->eval(val) && op2->eval(val);
}

Formula And::simplify() const
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
    return std::make_shared<False>();
  }
  else if (BaseFormula::isOfType<False>(simplifiedOp2))
  {
    return std::make_shared<False>();
  }
  
  return std::make_shared<And>(simplifiedOp1, simplifiedOp2);
}

Formula And::nnf() const
{
  GET_OPERANDS(op1, op2);
  return std::make_shared<And>(op1->nnf(), op2->nnf());
}

LiteralListList And::listCNF() const
{
  GET_OPERANDS(op1, op2);
  return BaseFormula::concatenate(op1->listCNF(), op2->listCNF());
}

LiteralListList And::listDNF() const
{
  GET_OPERANDS(op1, op2);
  return BaseFormula::cross(op1->listDNF(), op2->listDNF());
}
