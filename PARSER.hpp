#include "SCANNER.hpp"
#pragma once


template <class T, class T_EL>
void from_st ( T & st, T_EL & i )
    {
    //if (st.empty()) cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    //cout << st.top() << endl;
    i = st.top(); st.pop();
    }

class Parser
    {
    Lex          curr_lex;
    type_of_lex  c_type;
    int          c_val;
    int          c_string_number;
    int          c_number_in_string;
    Scanner      scan;

    string exception_string;

    stack < type_of_lex >   st_lex;
    void  P();
    void  D1();
    void  D();
    void  B();
    void  S();
    void  E1();
    void  E2();
    void  E3();
    void  E4();
    void  E5();
    void  E6();
    void  E7();



    void  dec ( type_of_lex type);
    void  check_id ();
    void  check_op ();
    void  check_not ();
    void  eq_type ();
    void  eq_bool ();
    void  check_id_in_read ();
    void  gl ()
        {
        curr_lex  = scan.get_lex ();
        c_type    = curr_lex.get_type ();
        c_val     = curr_lex.get_value ();
        c_string_number = curr_lex.get_string_number();
        c_number_in_string = curr_lex.get_number_in_string();
        }
public:
    vector <Lex> poliz;
    Parser ( const char *program ) : scan (program) { }
    void  analyze();
    };




