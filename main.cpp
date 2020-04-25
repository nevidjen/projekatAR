#include "propositional_logic.h"
#include <iostream>

using namespace std;

int main()
{
  Formula p0 = make_shared<Atom>(0);
  Formula p1 = make_shared<Atom>(1);
  Formula p2 = make_shared<Atom>(2);
  Formula f1 = make_shared<And>(p0, p1);
  Formula f2 = make_shared<Not>(f1);
  Formula f3 = make_shared<Imp>(f2, p2);
  Formula f4 = make_shared<Not>(p0);
  Formula f5 = make_shared<Not>(p1);
  Formula f6 = make_shared<Or>(f4, f5);
  Formula f7 = f3->substitute(f2, f6);
  Formula f8 = make_shared<And>(p0, make_shared<True>());
  Formula f9 = make_shared<Or>(f8, make_shared<True>());
  Formula f10 = make_shared<Imp>(f9, p1);
  Formula f11 = f10->simplify();
  
  Formula f12 = make_shared<Iff>(make_shared<False>(), make_shared<False>());
  
  cout << f12->simplify() << endl;
  
  Formula f13 = make_shared<Not>(f3);
  Formula f14= f13->simplify()->nnf();
  
  cout << f13 << endl;
  cout << f14 << endl;
  
  LiteralListList list = f14->listDNF();
  
  cout << list << endl;
  return 0;
}
