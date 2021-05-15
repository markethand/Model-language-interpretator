#include "LEX.hpp"

type_of_lex  Lex::get_type () const
    {
    return t_lex;
    }

int Lex::get_value () const
    {
    return v_lex;
    }

int Lex::get_string_number () const
    {
    return string_number;
    }

int Lex::get_number_in_string () const
    {
    return number_in_string;
    }

