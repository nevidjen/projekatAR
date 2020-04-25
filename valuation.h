#ifndef VALUATION_H
#define VALUATION_H

#include "atom_set.h"

#include <map>
#include <iostream>

/**
 * @brief The Valuation class - klasa koja predstavlja valuaciju, tj. cuva trenutnu vrednost atoma
 */
class Valuation
{
public:
  Valuation(const AtomSet &aset = {});
  
  /**
   * @brief reset - cisti mapu i postavlja vrednosti svih atoma iz skupa na false
   * @param aset - skup atoma
   */
  void reset(const AtomSet &aset);
  
  /**
   * @brief value - getter za vrednost atoma 'p' pri trenutnoj valuaciji
   * @param p - atom cija se vrednost dohvata
   * @return vrednost atoma 'p'
   */
  bool value(unsigned p) const;
  
  /**
   * @brief value - setter za vrednost atoma 'p'
   * @param p - atom koji se postavlja
   * @return referencu na vrednost atoma koju treba postaviti
   */
  bool& value(unsigned p);
    
  /**
   * @brief next - menja vrednost valuacije na leksikografski sledecu valuaciju
   * @return true ako postoji sledeca valuacija, false inace
   */
  bool next();
  
  /**
   * @brief print - stampa valuaciju u stream
   * @param out - stream u koji se stampa
   * @return referencu na stream
   */
  std::ostream& print(std::ostream &out) const;
  
private:
  std::map<unsigned, bool> m_values;
};

std::ostream& operator<<(std::ostream &out, const Valuation &v);

#endif // VALUATION_H
