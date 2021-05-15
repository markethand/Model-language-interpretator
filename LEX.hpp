#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <unistd.h>
#pragma once


#define DEBUG_MODE 1

using namespace std;

enum type_of_lex
    {
    LEX_NULL,
    LEX_AND, LEX_BEGIN, LEX_BOOL, LEX_DO, LEX_ELSE, LEX_END, LEX_IF, LEX_FALSE, LEX_INT, LEX_STRING,
    LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_THEN, LEX_TRUE, LEX_WHILE, LEX_WRITE, LEX_BREAK,

    LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ, LEX_LSS,
    LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_PERCENT, LEX_LEQ, LEX_NEQ, LEX_GEQ,
    LEX_OPENFBRACKET, LEX_CLOSEFBRACKET,

    LEX_NUM,
    LEX_ID,
    POLIZ_LABEL,
    POLIZ_ADDRESS,
    POLIZ_GO,
    POLIZ_FGO
    };

/////////////////////////  Класс Lex  //////////////////////////

class Lex
    {
    type_of_lex   t_lex;  // Тип лексемы
    int           v_lex;  // номер в таблице лексем соответствующего класса
    int   string_number;  // Номер строки в которой была лексема
    int  number_in_string;


  public:
    //Lex ( type_of_lex t = LEX_NULL, int v = 0, int j = 1): t_lex (t), v_lex (v), string_number (j)  { }
    Lex ( type_of_lex t = LEX_NULL, int v = 0, int j = 1, int n = 1): t_lex (t), v_lex (v), string_number (j), number_in_string(n)  { }
    type_of_lex  get_type () const;
    int get_value () const;
    int get_string_number () const;
    int get_number_in_string () const;

    friend ostream & operator<< ( ostream &s, Lex l );
    friend string & operator<< ( string &s, Lex l );
    };
