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

LiteralListList True::listCNF() const
{
    /* 
     * Klauze su ogranicenja - prazna lista klauza je uvek zadovoljiva 
     * tj. (nema nezadovoljenih ogranicenja) - ovo je konvencija. 
     */
    return {};
}

LiteralListList True::listDNF() const
{
    /*
     * DNF je tacna ako ima bar jednu listu literala koja je zadovoljena,
     * a lista je konjukncija za koju vazi da je zadovoljena jer nema
     * nijedan nezadovoljeni literal - ovo je konvencija.
     */
    return {{}};
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

LiteralListList False::listCNF() const
{
    /*
     * Prazna klauza je uvek nezadovoljena (potsetiti se rezolucije) - ovo je
     * konvencija.
     */
    return {{}};
}

LiteralListList False::listDNF() const
{
    /*
     * Prazna lista listi literala je nezadovoljena jer ne postoji nijedna 
     * lista literala koja je zadovoljena - ovo je konvencija.
     */
    return {};
}
