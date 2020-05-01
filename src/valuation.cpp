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
