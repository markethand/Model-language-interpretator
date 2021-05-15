#include "GLOBAL.hpp"
#pragma once


class Scanner
    {
    FILE * fp;
    char   c;

    int tmp_string_number;
    int tmp_number_in_string;

    int look ( const string buf, const char ** list );
    void gc ();
  public:
    static const char * TW [], * TD [];
    Scanner ( const char * program );
    Lex get_lex ();
};

