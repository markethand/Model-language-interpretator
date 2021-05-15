#include "IDENT.hpp"


Ident::Ident()
    {
    declare = false;     //ѕо умолчанию ни объ€вление, ни инициализаци€
    assign  = false;
    }

bool Ident::operator== ( const string& s ) const //дл€ сравнени€ ==
    {
    return name == s;
    }

Ident::Ident ( const string n )                  //дл€ инициализации через строку
    {
    name    = n;
    declare = false;
    assign  = false;
    }

