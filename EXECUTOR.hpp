#include "PARSER.hpp"
#pragma once


class Executer
    {
    public:
        void execute ( vector<Lex> & poliz );
    };

enum poliz_type {identificator_type, string_type, integer_type, bool_type, another_type};
struct meaning
    {
    poliz_type        meaning_type;
    int                int_meaning;
    string          string_meaning;

    meaning (poliz_type tmp, int a) {int_meaning = a; meaning_type = tmp; }
    meaning (poliz_type tmp, string a) {string_meaning = a; meaning_type = tmp; }


    };
