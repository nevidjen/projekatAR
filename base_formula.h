#ifndef BASEFORMULA_H
#define BASEFORMULA_H

#include "atom_set.h"
#include "valuation.h"

#include <memory>
#include <iostream>
#include <vector>
#include <experimental/optional>

/**
 * Forward declaration klase BaseFormula zbog upotrebe za definisanje tipa Formula
 */
class BaseFormula;

/**
 * Definisanje tip
 */
using Formula = std::shared_ptr<BaseFormula>;
using OptionalValuation = std::experimental::optional<Valuation>;

using LiteralList = std::vector<Formula>;
using LiteralListList = std::vector<LiteralList>;

/**
 * @brief The BaseFormula class - bazna klasa hijerarhije za formiranje iskaznih formula.
 */
class BaseFormula : public std::enable_shared_from_this<BaseFormula>
{
public:
  BaseFormula();
  
  /**
   * @brief print - stampa sadrzaj formule u C++ stream
   * @param out - stream u koji se stampa
   * @return referenca na stream (slicno kao kod operatora <<)
   */
  virtual std::ostream& print(std::ostream &out) const = 0;
  
  /**
   * @brief complexity - racuna slozenost formule koja je jednaka broju logickih veznika koji formula sadrzi
   * @return slozenost formule
   */
  virtual unsigned complexity() const = 0;
  
  /**
   * @brief substitute - menja u tekucoj formuli sva pojavljivanja potformule 'what' sa 'with'
   * @param what - potformula koja se menja
   * @param with - potformula kojom se menja
   * @return modifikovana formula
   */
  virtual Formula substitute(const Formula &what, const Formula &with) const = 0;
  
  /**
   * @brief eval - racuna istinitosnu vrednost formule za datu valuaciju 'val'
   * @param val - tekuca valuacija
   * @return true ukoliko je 'val' model za tekucu formulu, false inace
   */
  virtual bool eval(const Valuation &val) const = 0;
  
  /**
   * @brief getAtoms - dodaje sve atome koji se javljaju u okviru formule u skup atoma 'aset'
   * @param aset - skup atoma u koji se dodaje
   */
  virtual void getAtoms(AtomSet &aset) const;
  
  /**
   * @brief equalTo - proverava da li su dve formule sintaksno jednake
   * @param f - formula sa kojom se poredi tekuca formula
   * @return true ako su formule sintaksno jednake, false inace
   */
  virtual bool equalTo(const Formula &f) const;
  
  /**
   * @brief ~BaseFormula - podsecanje, kad god je klasa bazna destruktor treba da bude virtualan
   */
  virtual ~BaseFormula();
  
  /**
   * @brief isSatisfiable - ispituje da li je formula zadovoljiva
   * @return valuacija koja je model za formulu ili nista
   */
  OptionalValuation isSatisfiable() const;
  
  /**
   * @brief isNotTautology - ispituje da li je formula tautologija
   * @return valuacija koja nije model za fomulu ili nista
   */
  OptionalValuation isNotTautology() const;
  
  /**
   * @brief isConsequence - ispituje da li je prosledjena formula 'f' posledica tekuce formule
   * @param f - formula za koju se ispituje da li je posledica
   * @return true ako je 'f' posledica tekuce formule, false inace
   */
  bool isConsequence(const Formula &f) const;
  
  /**
   * @brief isEquivalent - ispituje logicku jednakost formula
   * @param f - formula za koju se ispituje logicka jednakost sa tekucom formulom
   * @return true ako su formule logicki ekvivalentne, false inace
   */
  bool isEquivalent(const Formula &f) const;
  
  /**
   * @brief printTruthTable - ispisuje istinitosnu tablicu u C++ stream
   * @param out - stream u koji se ispisuje tablica
   */
  void printTruthTable(std::ostream &out) const;
  
  virtual Formula simplify() const = 0;
  
  virtual Formula nnf() const = 0;
  
  virtual LiteralListList listCNF() const = 0;
  
  virtual LiteralListList listDNF() const = 0;
  
  template <typename ListType>
  static ListType concatenate(const ListType &l1, const ListType &l2);
  
  static LiteralListList cross(const LiteralListList &l1, const LiteralListList &l2);
  
  template <typename Derived>
  static const Derived* isOfType(const Formula &f);
};

template <typename ListType>
ListType BaseFormula::concatenate(const ListType &l1, const ListType &l2)
{
  ListType result;
  result.reserve(l1.size() + l2.size());
  std::copy(l1.cbegin(), l1.cend(), std::back_inserter(result));
  std::copy(l2.cbegin(), l2.cend(), std::back_inserter(result));
  return result;
}

template <typename Derived>
const Derived* BaseFormula::isOfType(const Formula &f)
{
  return dynamic_cast<const Derived *>(f.get());
}

/**
 * @brief operator == ispituje sintaksnu jednakost dve formule
 * 
 * @details Implementacija se svodi na pozivanje virtuelnog equalsTo() metoda.
 * 
 * @param lhs - prva formula
 * @param rhs - druga formula
 * @return true ako su formule sintaksno jednake, false inace
 */
bool operator==(const Formula &lhs, const Formula &rhs);

/**
 * @brief operator != ispituje sintaksnu razlicitost dve formule, svodi se na !(lhs == rhs)
 * @param lhs
 * @param rhs
 * @return 
 */
bool operator!=(const Formula &lhs, const Formula &rhs);

/**
 * @brief operator << sluzi za ispis u C++ stream
 * @param out - stream u koji se pise
 * @param f - formula koja se pise u stream
 * @return  referenca na stream kako bi pozivi '<<' mogli da se ulancaju
 */
std::ostream& operator<<(std::ostream &out, const Formula &f);

std::ostream& operator<<(std::ostream &out, const LiteralListList &l);

#endif // BASEFORMULA_H
