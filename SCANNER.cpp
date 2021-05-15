#include "SCANNER.hpp"


int Scanner::look ( const string buf, const char ** list )
    {
    int i = 0;
    while ( list[i] )
        {
        if ( buf == list[i] )
            return i;
        ++i;
        }
    return 0;
    }

void Scanner::gc ()
    {
    c = fgetc (fp);
    }

Scanner::Scanner ( const char * program )
    {
    tmp_string_number = 1;
    tmp_number_in_string = 0;
    if ( !(fp = fopen ( program, "r" )) )
        throw  "canТt open file" ;
    }

const char *
Scanner::TW[] = { "", "and", "begin", "boolean", "do", "else", "end", "if", "false", "int", "string", "not", "or", "program",
                      "read", "then", "true", "while", "write", "break", NULL }; //#############################ƒќЅј¬»Ћ BREAK
const char *
Scanner::TD[] = { "", ";", ",", ":", "=", "(", ")", "==", "<", ">", "+", "-", "*", "/", "%", "<=", "!=", ">=", "{", "}", NULL };



ostream & operator<< ( ostream &s, Lex l )
    {
    string t;
    if ( l.t_lex <= LEX_WRITE )
        t = Scanner::TW[l.t_lex];
    else if ( l.t_lex >= LEX_SEMICOLON && l.t_lex <= LEX_CLOSEFBRACKET )
        t = Scanner::TD[ l.t_lex - LEX_SEMICOLON + 1];
    else if ( l.t_lex == LEX_NUM )
        t = "NUMB";
    else if ( l.t_lex == LEX_ID )
        t = TID[l.v_lex].get_name ();
    else if ( l.t_lex == POLIZ_LABEL )
        t = "Label";
    else if ( l.t_lex == POLIZ_ADDRESS )
        t = "Addr";
    else if ( l.t_lex == POLIZ_GO )
        t = "!";
    else if ( l.t_lex == POLIZ_FGO )
        t = "!F";
    else if (l.t_lex == LEX_BREAK)
        t = "break";
    else
        throw l;
    s << '(' << t << ',' << l.v_lex << " " << l.t_lex << ") in line number " << l.string_number << " in position " << l.number_in_string << endl;
    return s;
    }

string & operator<< ( string &s, Lex l )
    {
    string t;
    if ( l.t_lex <= LEX_WRITE )
        t = Scanner::TW[l.t_lex];
    else if ( l.t_lex >= LEX_SEMICOLON && l.t_lex <= LEX_CLOSEFBRACKET )
        t = Scanner::TD[ l.t_lex - LEX_SEMICOLON + 1];
    else if ( l.t_lex == LEX_NUM )
        t = "NUMB";
    else if ( l.t_lex == LEX_ID )
        t = TID[l.v_lex].get_name ();
    else if ( l.t_lex == POLIZ_LABEL )
        t = "Label";
    else if ( l.t_lex == POLIZ_ADDRESS )
        t = "Addr";
    else if ( l.t_lex == POLIZ_GO )
        t = "!";
    else if ( l.t_lex == POLIZ_FGO )
        t = "!F";
    else if (l.t_lex == LEX_BREAK)
        t = "break";
    else
        throw l;
    s = (s + "(" + t + "," + to_string (l.v_lex) + " " + to_string (l.t_lex)
          + ") in line number " + to_string (l.string_number) + " in position " + to_string (l.number_in_string) + "\n");
    return s;
    }




Lex Scanner::get_lex ()
    {
    enum    state { H, PEQ, S_STRING, IDENT, NUMB, PCOM, COM, PECOM, ALE, NEQ };
    int     d, j;
    string  buf;
    state   CS = H;

    //static int tmp_number_in_string = 0;

    string exception_string = "unexpected symbol [";
    do
        {
        gc (); //—читать следующий символ
        tmp_number_in_string++;

        if (c == '\n')
            {
            tmp_string_number++;
            }


        //cout << CS << endl;
        switch ( CS )
            {
            case H:
                if (c == EOF)
                    {
                    buf = "end";
                    j = look ( buf, TW);
                    return Lex ( (type_of_lex) j, j, tmp_string_number, tmp_number_in_string );
                    }

                if (c == '\n')
                    {
                    tmp_number_in_string = 0;
                    }
                else if ( c == ' ' || c== '\r' || c == '\t' ); //игнорируем
                else if ( isalpha (c) )
                    {
                    buf.push_back (c); // buf - тут храним идентификатор
                    CS  = IDENT;
                    }
                else if ( isdigit (c) )
                    {
                    d   = c - '0';     // d - временно хран€щ€€с€ часть числа число.
                    CS  = NUMB;
                    }
                else if ( c == '/' )
                    {
                    CS  = PCOM; //PROBABLY COMMENT
                    }
                else if ( c == '<' || c == '>' )
                    {
                    buf.push_back (c);
                    CS  = ALE;
                    }
                else if (c == '!')
                    {
                    buf.push_back (c);
                    CS  = NEQ;
                    }
                else if (c == '"')
                    {
                    //cout << "CS" << endl;
                    CS = S_STRING;
                    }
                else if (c == '=')
                    {
                    CS = PEQ;//Probably EQ
                    }
                else
                    {
                    //cout << "here";
                    buf.push_back (c);
                    if ( ( j = look ( buf, TD) ) )
                        {
                        return Lex ( (type_of_lex)( j + (int) (LEX_SEMICOLON  - 1) ), j, tmp_string_number, tmp_number_in_string );
                        }
                    else
                        {
                        exception_string.push_back(c);
                        exception_string += "] in string. Unknown lexeme probably operation is not supported ";
                        exception_string += to_string (tmp_string_number);
                        exception_string += "\n";
                        throw exception_string;
                        }
                    }

                break;

            case PEQ:
                 if (c == '=')
                    {
                    //cout << "!!!!!!!";
                    buf = "==";
                    if ( ( j = look ( buf, TD) ) )
                        {
                        //cout << "LEXEM EQ" << endl;
                        return Lex ( (type_of_lex)( j + (int) (LEX_SEMICOLON  - 1) ), j, tmp_string_number, tmp_number_in_string );
                        }
                    }
                ungetc(c, fp ); tmp_number_in_string--;
                buf = "=";
                if ( ( j = look ( buf, TD) ) )
                    {
                    return Lex ( (type_of_lex)( j + (int) (LEX_SEMICOLON  - 1) ), j, tmp_string_number, tmp_number_in_string );
                    }
            break;


            case S_STRING:
                if (c == EOF)
                    {
                    exception_string.push_back(c);
                    exception_string += "undesirable ending of the string in line ";
                    exception_string += to_string (tmp_string_number);
                    exception_string += "\n";
                    throw exception_string;
                    }

                if (c != '"')
                    {
                    buf.push_back (c);
                    break;
                    }

                STRINGS_TABLE.push_back(buf);
                //cout << "!!!" << STRINGS_TABLE[0] << endl;
                return Lex ( LEX_STRING, STRINGS_TABLE.size() - 1, tmp_string_number, tmp_number_in_string);
            break;

            case IDENT:
                if ( isalpha (c) || isdigit (c) )
                    {
                    buf.push_back (c);
                    }
                else
                    {
                    ungetc ( c, fp ); tmp_number_in_string--;
                    if ( (j = look ( buf, TW) ) )
                        {
                        return Lex ( (type_of_lex) j, j, tmp_string_number, tmp_number_in_string);
                        }
                        else
                        {
                        j   = put ( buf ); //¬от тут мы кладем это дело в TID.
                        return Lex ( LEX_ID, j, tmp_string_number, tmp_number_in_string);
                        }
                    }
                break;
            case NUMB:
                if ( isdigit (c) )
                    {
                    d = d * 10 + ( c - '0' );
                    }
                else
                    {
                    ungetc ( c, fp ); tmp_number_in_string--;
                    return Lex ( LEX_NUM, d, tmp_string_number, tmp_number_in_string);
                    }
                break;

            case PCOM:
                if (c == '*') CS = COM;
                else
                    {
                    CS = H;

                    ungetc ( c, fp ); tmp_number_in_string--;
                    //» кладем / куда надо, возвращаем

                    if ( ( j = look ( buf, TD) ) )
                        {
                        return Lex ( (type_of_lex)( j + (int) (LEX_SEMICOLON  - 1) ), j, tmp_string_number,tmp_number_in_string);
                        }
                    }
                break;



            case COM:
                if ( c == '*')
                    {
                    CS  = PECOM;
                    }
                else if ( c == EOF)
                    {
                    exception_string.push_back(c);
                    exception_string += "] undesirable ending of the comment in line ";
                    exception_string += to_string (tmp_string_number);
                    exception_string += "\n";
                    throw exception_string;
                    }
                break;

            case PECOM:
                //probably end of comment
                if ( c == '/' )
                    {
                    CS  = H;
                    }
                else if ( c == EOF)
                    {
                    exception_string.push_back(c);
                    exception_string += "] undesirable comment ending in string in line ";
                    exception_string += to_string (tmp_string_number);
                    exception_string += "\n";
                    throw exception_string;
                    }
                else
                    CS = COM;
                break;

            case ALE:
                if ( c == '=' )
                    {
                    buf.push_back ( c );
                    j   = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) (LEX_SEMICOLON - 1) ), j, tmp_string_number, tmp_number_in_string );
                    }
                else
                    {
                    ungetc ( c, fp ); tmp_number_in_string--;
                    j   = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) (LEX_SEMICOLON  - 1) ), j, tmp_string_number,tmp_number_in_string );
                    }
                break;
            case NEQ:
                if ( c == '=' )
                    {
                    buf.push_back(c);
                    j   = look ( buf, TD );
                    return Lex ( LEX_NEQ, j, tmp_string_number, tmp_number_in_string );
                    }
                else
                    {
                    exception_string.push_back(c);
                    exception_string += "] Unknown state internal error in line  ";
                    exception_string += to_string (tmp_string_number);
                    exception_string += "\n";
                    throw exception_string;
                    }
            break;
            } //end switch
        } while (true);
    }





