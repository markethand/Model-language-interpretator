#include "PARSER.hpp"

void Parser::analyze ()
    {
    gl ();
    P ();
    gl ();
    if (c_type != LEX_END)
        {
        exception_string = "Inappropriate ending of the program. Should be end, but it is ";
        exception_string << curr_lex;
        throw exception_string;
        }

    cout << endl << "------------Syntax stage completed------------" << endl;
    for ( Lex l : poliz )
        cout << l;
    cout << endl << "------------POLIZ output completed------------" << endl;

    }

void Parser::P ()
    {
    //cout << "-P-" << endl;
    if ( c_type == LEX_PROGRAM )
        {
        gl ();
        }
    else
        {
        exception_string = "Inappropriate beginning of the program. Should be PROGRAM lexeme, but it is ";
        exception_string << curr_lex;
        throw exception_string;
        }

    if ( c_type == LEX_OPENFBRACKET )
        {
        gl ();
        }
    else
        {
        exception_string = "Inappropriate beginning of the program. Should be { lexeme after PROGRAM, but it is ";
        exception_string << curr_lex;
        throw exception_string;
        }

    //D1-  описания
    D1 (); //Текущая лексема - int/boolean/string должна быть

    S (); //текущая лексема - оператор либо идентификатор либо константа..
    //gl();

    while (c_type != LEX_CLOSEFBRACKET)
        {
        S();
        //if (c_type == LEX_SEMICOLON) gl();
        }




    if ( c_type == LEX_CLOSEFBRACKET )
        {
        gl ();
        }
    else
        {
        exception_string = "Inappropriate ending of the program. Should be } lexeme after PROGRAM BLOCK, but it is ";
        exception_string << curr_lex;
        throw exception_string;
        }
    }


void Parser::D1 ()
    {
    //cout << "-D1-" << endl;

    //Если описание существует (его может и не быть)

    while ( (c_type == LEX_INT) || (c_type == LEX_STRING) || (c_type == LEX_BOOL))
        {
        D ();

        //Должны стоять на ;, иначе ошибка
        if (c_type == LEX_SEMICOLON)
            {
            gl (); //Если были на на ;, перешли бы на начало следующего описания
            }
        else
            {
            exception_string = "Inappropriate ending of the declatation. SEMicolon is needed, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        }

    }

void Parser::D ()
    {
    //cout << "-D-" << endl;

    type_of_lex description_type = c_type;
    int tmp_identificator_id  = 0;
    int i = 0;

    gl ();

    if ( c_type != LEX_ID )
        {
        exception_string = "Inappropriate declarationa. Should be indentificator but it is ";
        exception_string << curr_lex;
        throw exception_string;
        }
    else
        {
        if ( TID[c_val].get_declare () )
            {
            exception_string = "Double declaration in ";
            exception_string << curr_lex;
            throw exception_string;
            }
        //throw "twice";

        tmp_identificator_id = c_val;
        TID[tmp_identificator_id].put_declare ();
        TID[tmp_identificator_id].put_type ( description_type );
        cout << "c_val = " << tmp_identificator_id << endl;

        gl ();

        if (c_type == LEX_ASSIGN)
            {
            gl (); //Мы на переменной

            cout << "c_val = " << tmp_identificator_id << endl;


            //TID[tmp_identificator_id].put_declare ();
            //TID[tmp_identificator_id].put_type ( description_type );

            if (c_type == LEX_NUM && TID[tmp_identificator_id].get_type() != LEX_INT)
                {
                exception_string = "Wrong declaration in ";
                exception_string << curr_lex;
                throw exception_string;
                }
            if (c_type == LEX_STRING && TID[tmp_identificator_id].get_type() != LEX_STRING)
                {
                exception_string = "Wrong declaration in ";
                exception_string << curr_lex;
                throw exception_string;
                }
            /*if (c_type == LEX_BOOL && !( (TID[tmp_identificator_id].get_type() != LEX_TRUE)
                                    ||   (TID[tmp_identificator_id].get_type() != LEX_FALSE) ) )*/
            if ((c_type == LEX_TRUE || c_type == LEX_FALSE) && (TID[tmp_identificator_id].get_type() != LEX_BOOL))
                {
                exception_string = "Wrong bool declaration in ";
                exception_string << curr_lex;
                throw exception_string;
                }


            if (c_type == LEX_NUM)
                TID[tmp_identificator_id].put_value (c_val);
            else if (c_type == LEX_STRING)
                TID[tmp_identificator_id].put_value (c_val);
            else if (c_type == LEX_TRUE || c_type == LEX_FALSE)
                TID[tmp_identificator_id].put_value (c_val);
            else
                {
                exception_string = "Wrong declaration in ";
                exception_string << curr_lex;
                throw exception_string;
                }

            TID[tmp_identificator_id].put_assign();

            gl(); // Возможно на запятой
            }

        while ( c_type == LEX_COMMA )
            {
            gl ();
            if ( c_type != LEX_ID )
                {
                exception_string = "Not an identificator. Wrong declaration in ";
                exception_string << curr_lex;
                throw exception_string;
                }
            else
                {
                if ( TID[c_val].get_declare () )
                    {
                    exception_string = "Double declaration in ";
                    exception_string << curr_lex;
                    throw exception_string;
                    }

                tmp_identificator_id = c_val;
                TID[tmp_identificator_id].put_declare ();
                TID[tmp_identificator_id].put_type ( description_type );
                cout << "c_val = " << tmp_identificator_id << endl;

                gl ();

                if (c_type == LEX_ASSIGN)
                    {
                    gl ();

                    cout << "c_val = " << tmp_identificator_id << endl;

                    //TID[tmp_identificator_id].put_declare ();
                    //TID[tmp_identificator_id].put_type ( description_type );

                if (c_type == LEX_NUM && TID[tmp_identificator_id].get_type() != LEX_INT)
                    {
                    exception_string = "Wrong declaration in ";
                    exception_string << curr_lex;
                    throw exception_string;
                    }
                if (c_type == LEX_STRING && TID[tmp_identificator_id].get_type() != LEX_STRING)
                    {
                    exception_string = "Wrong declaration in ";
                    exception_string << curr_lex;
                    throw exception_string;
                    }
                /*if (c_type == LEX_BOOL && !( (TID[tmp_identificator_id].get_type() != LEX_TRUE)
                                        ||   (TID[tmp_identificator_id].get_type() != LEX_FALSE) ) )*/
                if ((c_type == LEX_TRUE || c_type == LEX_FALSE) && (TID[tmp_identificator_id].get_type() != LEX_BOOL))
                    {
                    exception_string = "Wrong bool declaration in ";
                    exception_string << curr_lex;
                    throw exception_string;
                    }


                if (c_type == LEX_NUM)
                    TID[tmp_identificator_id].put_value (c_val);
                else if (c_type == LEX_STRING)
                    TID[tmp_identificator_id].put_value (c_val);
                //else if (c_type == LEX_BOOL)
                else if (c_type == LEX_TRUE || c_type == LEX_FALSE)
                    TID[tmp_identificator_id].put_value (c_val);
                else
                    {
                    exception_string = "Wrong declaration in ";
                    exception_string << curr_lex;
                    throw exception_string;
                    }

                    TID[tmp_identificator_id].put_assign();

                    gl();
                    }
                }
            }
        /*if ( c_type != LEX_SEMICOLON )
            throw curr_lex;*/
        }
    }




void Parser::S ()
    {
    cout << "-S- " << curr_lex << endl;

    int pl0, pl1, pl2, pl3;


    if ( c_type == LEX_IF )
        {
        cout << "-if-" << endl;
        gl();
        if (c_type != LEX_LPAREN)
            {
            exception_string = "Inappropriate IF condition bracketing. ( required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl ();
        E1 ();

        eq_bool ();

        pl2 = poliz.size();
        poliz.push_back ( Lex(LEX_NULL, 0, c_string_number, c_number_in_string ));
        poliz.push_back ( Lex(POLIZ_FGO, 0, c_string_number, c_number_in_string ));

        if (c_type != LEX_RPAREN)
            {
            exception_string = "Inappropriate IF condition bracketing. ) required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl();

        cout << "STILLLLLLLLLLLLLLLLLLLLLLLLLLL";
        cout << curr_lex;
        cout << endl;
        cout << endl;

        S();

            if(c_type == LEX_SEMICOLON) gl();

            cout << "ELSE CHECKING " << curr_lex << endl;
            if (c_type == LEX_ELSE)
                {
                pl3 = poliz.size ();
                poliz.push_back ( Lex (LEX_NULL, 0, c_string_number, c_number_in_string ));

                poliz.push_back ( Lex ( POLIZ_GO, 0, c_string_number, c_number_in_string  ));
                poliz[pl2] = Lex ( POLIZ_LABEL, poliz.size(), c_string_number, c_number_in_string );

                gl ();
                S ();
                poliz[pl3] = Lex ( POLIZ_LABEL, poliz.size(), c_string_number, c_number_in_string  );

                int tmp_size = poliz.size();
                /*for (int i = pl2 + 2; i < tmp_size; i++)
                    {
                    if (poliz[i].get_type() == LEX_BREAK) //Если были бряки
                        {
                        poliz[i] = Lex (POLIZ_LABEL, tmp_size, c_string_number );
                        }
                    }*/
                }
            else
                {
                poliz[pl2] = Lex ( POLIZ_LABEL, poliz.size() );

                int tmp_size = poliz.size();
                /*for (int i = pl2 + 2; i < tmp_size; i++)
                    {
                    if (poliz[i].get_type() == LEX_BREAK) //Если были бряки
                        {
                        poliz[i] = Lex (POLIZ_LABEL, tmp_size, c_string_number );
                        }
                    }*/
                }
        cout << "ENDIF" << endl;
        }//end if


    else if ( c_type == LEX_WHILE )
        {
        cout << "-while-" << endl;

        pl0 = poliz.size ();
        gl ();

        if (c_type != LEX_LPAREN)
            {
            exception_string = "Inappropriate WHILE condition bracketing. ( required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl ();

        E1 ();
        eq_bool ();

        if (c_type != LEX_RPAREN)
            {
            exception_string = "Inappropriate IF condition bracketing. ) required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl ();

        pl1 = poliz.size ();
        poliz.push_back ( Lex (LEX_NULL, 0, c_string_number, c_number_in_string ));
        poliz.push_back ( Lex (POLIZ_FGO, 0, c_string_number, c_number_in_string ) );


        S();
        poliz.push_back ( Lex ( POLIZ_LABEL, pl0, c_string_number, c_number_in_string ) );
        poliz.push_back ( Lex ( POLIZ_GO, 0, c_string_number, c_number_in_string ));
        poliz[pl1] = Lex ( POLIZ_LABEL, poliz.size(), c_string_number, c_number_in_string );

        int tmp_size = poliz.size();
        cout << "TMP SIZE" << tmp_size << endl;
        cout << "<><><><><><><><><><><><><><><><>" << endl;
        for (int i = pl0; i < tmp_size; i++)
            {
            cout << i << " ";
            cout << poliz[i];
            if (poliz[i].get_type() == LEX_BREAK) //Если были break
                {
                poliz[i] = Lex (POLIZ_LABEL, tmp_size, c_string_number, c_number_in_string);
                cout << poliz[i].get_value() << endl;
                }
            }

        cout << "<><><><><><><><><><><><><><><><>" << endl;
        }//end while
    else if (c_type == LEX_DO)
        {
        pl0 = poliz.size ();
        gl ();

        S();

        if (c_type != LEX_WHILE)
            {
            exception_string = "Inappropriate DO-WHILE cycle ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl();


        if (c_type != LEX_LPAREN)
            {
            exception_string = "Inappropriate DO WHILE bracketing. ( required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl ();

        E1();
        eq_bool ();

        if (c_type != LEX_RPAREN)
            {
            exception_string = "Inappropriate DO WHILE bracketing. ) required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl ();

        //Если неверно
        poliz.push_back ( Lex ( POLIZ_LABEL, poliz.size() + 4, c_string_number, c_number_in_string ) );
        poliz.push_back ( Lex ( POLIZ_FGO, 0, c_string_number, c_number_in_string ));
        //Если верно
        poliz.push_back ( Lex ( POLIZ_LABEL, pl0, c_string_number ) );
        poliz.push_back ( Lex ( POLIZ_GO, 0, c_string_number, c_number_in_string ));

        if (c_type != LEX_SEMICOLON)
            {
            exception_string = "Inappropriate DO WHILE bracketing. ) required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        gl();
        }

    else if (c_type == LEX_BREAK)
        {
        cout << "-break- " << poliz.size() << endl;
        poliz.push_back ( Lex (LEX_BREAK, 0, c_string_number, c_number_in_string ));
        poliz.push_back ( Lex (POLIZ_GO, 0, c_string_number, c_number_in_string ));
        gl();
        if (c_type == LEX_SEMICOLON) gl();
        }

    else if ( c_type == LEX_READ )
        {
        gl ();
        if ( c_type == LEX_LPAREN )
            {
            gl ();
            if ( c_type == LEX_ID )
                {
                check_id_in_read ();
                poliz.push_back ( Lex( POLIZ_ADDRESS, c_val, c_string_number, c_number_in_string) );
                gl();
                }
            else
                {
                exception_string = "Inappropriate READ condition bracketing. IDENT required, but it is ";
                exception_string << curr_lex;
                throw exception_string;
                }
            if ( c_type == LEX_RPAREN )
                {
                gl ();
                poliz.push_back ( Lex (LEX_READ, 0, c_string_number, c_number_in_string ));
                }
            else
                {
                exception_string = "Inappropriate READ condition bracketing. ) required, but it is ";
                exception_string << curr_lex;
                throw exception_string;
                }
            }
        else
            {
            exception_string = "Inappropriate READ condition bracketing. ( required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        if (c_type == LEX_SEMICOLON) gl();
        }//end read
    else if ( c_type == LEX_WRITE )
        {
        int number_to_be_written = 0;
        cout << "WRITE";
        gl ();
        if ( c_type == LEX_LPAREN )
            {
            gl ();
            E1 ();

            number_to_be_written++;
            while ( c_type == LEX_COMMA )
                {
                gl();
                E1();

                number_to_be_written++;
                }

            if ( c_type == LEX_RPAREN )
                {
                gl ();
                poliz.push_back ( Lex ( LEX_NUM, number_to_be_written, c_string_number, c_number_in_string ));
                poliz.push_back ( Lex ( LEX_WRITE, 0, c_string_number, c_number_in_string ) );
                }
            else
                {
                exception_string = "Inappropriate WRITE condition bracketing. ) required, but it is ";
                exception_string << curr_lex;
                throw exception_string;
                }

            cout << "WRITTEN" << endl;
            cout << curr_lex;
            if (c_type == LEX_SEMICOLON) gl();
            }
        else
            {
            exception_string = "Inappropriate WRITE condition bracketing. ( required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        }//end write

    else if (c_type == LEX_OPENFBRACKET)
            {
            pl0 = poliz.size();

            gl();

            do
                {
                cout << curr_lex;
                cout << "IN OPENFBRACKET" << endl;
                S ();

                cout << "operator S in {} ended" << endl;
                if (c_type == LEX_SEMICOLON) gl();
                }
            while (c_type != LEX_CLOSEFBRACKET);

            cout << "ended complex operator {}" << endl;
            gl();

            /*int tmp_size = poliz.size();
            for (int i = pl0; i < tmp_size; i++)
                {
                if (poliz[i].get_type() == LEX_BREAK) //Если были бряки
                    {
                    poliz[i] = Lex (POLIZ_LABEL, tmp_size, c_string_number );
                    }
                }*/
            }
    else
        {
        /* Здесь будет оператор вида выражение и точка с запятой */

        pl0 = poliz.size();

        E1 ();

        if (poliz.size() > pl0)
            {
            if (c_type == LEX_SEMICOLON)
                {
                gl();
                poliz.push_back ( Lex ( LEX_SEMICOLON, 0, c_string_number, c_number_in_string ) ); //Для зачистки стэка
                }
            }
        }
    }



void Parser::E1 ()
    {
    int p0 = poliz.size();
    E2();

    while ( c_type == LEX_ASSIGN)
        {
        cout << "ASSIGN" << endl;

        poliz [poliz.size() - 1] = Lex (POLIZ_ADDRESS, poliz [poliz.size() - 1].get_value());

        gl();

        st_lex.push(LEX_ASSIGN);
        E2();

        cout << "HERE CHECKOP ASSIGN" << endl;
        check_op();
        }

    }

void Parser::E2 ()
    {
    E3();

    while ( c_type == LEX_OR)
        {
        gl();
        st_lex.push(LEX_OR);
        E3();
        check_op();
        }
    }



void Parser::E3 ()
    {
    E4();

    while( c_type == LEX_AND)
        {
        gl();
        st_lex.push(LEX_AND);
        E4();
        check_op();
        }
    }


void Parser::E4 ()
    {
    E5();

    while ( c_type == LEX_EQ  || c_type == LEX_LSS || c_type == LEX_GTR ||
         c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ )
        {
        st_lex.push ( c_type );
        gl ();
        E5 ();
        check_op ();
        }
    }

void Parser::E5 ()
    {
    E6();

    while ( c_type == LEX_PLUS  || c_type == LEX_MINUS )
        {
        st_lex.push ( c_type );
        gl ();
        E6 ();
        check_op ();
        }
    }


void Parser::E6 ()
    {
    E7();

    while ( c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_PERCENT)
        {
        st_lex.push ( c_type );
        gl ();
        E7 ();
        check_op ();
        }
    }




void Parser::E7 ()
    {
    if ( c_type == LEX_ID ) //Check id вызовет проверку декларированности и положит в стек st_lex ТИП.
        {                   //Но нам не нужен ТИП. Нам нужна и информация о том идентификатор это или нет
                            //А тип при проверке операции мы сможем достать и сами.

                            //INTEGER нам теперь не подходит.
                            //Будем хранить сразу два значения - тип IDENT и сам IDENT
        cout << "F:lex" << endl;
        check_id ();

        poliz.push_back ( Lex ( LEX_ID, c_val, c_string_number, c_number_in_string  ) );
        gl ();
        }
    else if ( c_type == LEX_NUM )
        {
        st_lex.push ( LEX_INT );
        poliz.push_back ( Lex ( c_type , c_val,  c_string_number, c_number_in_string ) );
        gl ();
        }
    else if ( c_type == LEX_STRING )
        {
        st_lex.push ( LEX_STRING );
        poliz.push_back ( Lex ( c_type , c_val,  c_string_number, c_number_in_string ) );
        gl ();
        }
    else if ( c_type == LEX_TRUE )
        {
        st_lex.push ( LEX_BOOL );
        poliz.push_back ( Lex (LEX_TRUE, 1,  c_string_number, c_number_in_string) );
        gl ();
        }
    else if ( c_type == LEX_FALSE)
        {
        st_lex.push ( LEX_BOOL );
        poliz.push_back ( Lex (LEX_FALSE, 0,  c_string_number, c_number_in_string) );
        gl ();
        }
    else if ( c_type == LEX_NOT )
        {
        gl ();
        E7 ();
        check_not ();
        }
    else if ( c_type == LEX_LPAREN )
        {
        gl ();
        E1 ();
        if ( c_type == LEX_RPAREN) gl ();
        else
            {
            exception_string = "Inappropriate () condition bracketing. ) required, but it is ";
            exception_string << curr_lex;
            throw exception_string;
            }
        }
    else
        {
        exception_string = "Inappropriate symbol in the expression ";
        exception_string << curr_lex;
        throw exception_string;
        }
    }



void Parser::check_id ()
    {
    //cout << "c_val = " << c_val << " " << TID[c_val].get_value_string() << endl;

    if ( TID[c_val].get_declare() )
        {
        st_lex.push ( TID[c_val].get_type () );
        st_lex.push (LEX_ID);
        }
    else
        {
        exception_string = "Undeclared IDENT ";
        exception_string << curr_lex;
        throw exception_string;
        }
    }


void Parser::check_op ()
    {
    type_of_lex t1 = LEX_NULL, t2 = LEX_NULL, op = LEX_NULL;
    type_of_lex t1_real = LEX_NULL, t2_real = LEX_NULL;

    from_st ( st_lex, t1 );
    if (t1 == LEX_ID) from_st (st_lex, t1_real);
    from_st ( st_lex, op );
    from_st ( st_lex, t2 );
    if (t2 == LEX_ID) from_st (st_lex, t2_real);



    cout << t1 << " " << t1_real << " " << op << " "<< t2 << " " << t2_real << " " << endl;
    cout << "CHEKOP OPERATION IS" << op << endl;


    type_of_lex tmp1 = LEX_NULL;
    type_of_lex tmp2 = LEX_NULL;
    if (t1_real) tmp1 = t1_real;
    else tmp1 = t1;
    if (t2_real) tmp2 = t2_real;
    else tmp2 = t2;
    if  (tmp1 == LEX_NUM ) tmp1 = LEX_INT;
    if  (tmp2 == LEX_NUM ) tmp2 = LEX_INT;


    switch (op)
        {
        case LEX_ASSIGN:
            {
            if (t2_real && (t2_real == t1 || t2_real == t1_real ))
                {
                st_lex.push (t2_real);
                st_lex.push (t2);
                }
            else
                {
                cout << t1 << " " << t1_real << " " << t2 << " " << t2_real << endl;
                exception_string = "Wrond assignment, left part is not an assignment";
                exception_string << curr_lex;
                throw exception_string;
                }
            }
        break;


        case LEX_OR: case LEX_AND:
            {
            if (!(t1 == LEX_BOOL || t1_real == LEX_BOOL )) //tmp1 = BOOL;
                {
                exception_string = "Wrond OR operation";
                exception_string << curr_lex;
                throw exception_string;
                }
            if (!(t2 == LEX_BOOL || t2_real == LEX_BOOL )) //tmp2 = BOOL;
                {
                exception_string = "Wrong OR operation";
                exception_string << curr_lex;
                throw exception_string;
                }

            if (t2_real)  st_lex.push (t2_real);
            else if (t2)       st_lex.push (t2);
            }
        break;

        case LEX_EQ: case LEX_LSS: case LEX_GTR: case LEX_LEQ: case LEX_GEQ: case LEX_NEQ:
            {
            if ((tmp1 == tmp2) && (tmp1 == LEX_INT || tmp1 == LEX_STRING))
                {
                st_lex.push (LEX_BOOL);
                }
            else
                {
                exception_string = "Not equal types in comparison operation";
                exception_string << curr_lex;
                throw exception_string;
                }
            }
        break;



        case LEX_PLUS:
            {
            if ((tmp1 == tmp2) && (tmp1 == LEX_STRING || tmp1 == LEX_INT))
                {
                if (tmp1 == LEX_STRING) st_lex.push (LEX_STRING);
                else if (tmp1 == LEX_INT) st_lex.push (LEX_INT);
                }
            else
                {
                exception_string = "Not equal types in addition operation";
                exception_string << curr_lex;
                throw exception_string;
                }
            }
        break;


        case LEX_MINUS:
        case LEX_TIMES: case LEX_SLASH: case LEX_PERCENT:
            {
            if ((tmp1 == tmp2) && (tmp1 == LEX_INT))
                {
                st_lex.push (LEX_INT);
                }
            else
                {
                exception_string = "Not integer in - * / % operation";
                exception_string << curr_lex;
                throw exception_string;
                }
            }
        break;

        default:
            {
            exception_string = "Unknown operation";
            exception_string << curr_lex;
            throw exception_string;
            }
        }

    cout << "POLIZ OPERATION" << Lex(op) << endl;
    poliz.push_back (Lex (op, 0,  c_string_number, c_number_in_string));
    }



void Parser::check_not ()
    {
    type_of_lex t1 = LEX_NULL;
    type_of_lex t1_real = LEX_NULL;

    from_st ( st_lex, t1 );
    if (t1 == LEX_ID) from_st (st_lex, t1_real);

    if (!(t1 == LEX_BOOL || t1_real == LEX_BOOL )) //tmp1 = BOOL;
        {
        exception_string = "operation NOT does not suit for NOT BOOLEAN type";
        exception_string << curr_lex;
        throw exception_string;
        }
    else
        {
        cout << "####################################################################" << endl;
        poliz.push_back ( Lex (LEX_NOT, 0,  c_string_number, c_number_in_string ));
        st_lex.push (LEX_BOOL);
        }

    //Ничего не делаем т.к нам нужно чтобы наверху остался boolean
    }


void Parser::eq_bool ()
    {
    type_of_lex t1 = LEX_NULL;
    type_of_lex t1_real = LEX_NULL;

    from_st ( st_lex, t1 );
    if (t1 == LEX_ID) from_st (st_lex, t1_real);

    if (!(t1 == LEX_BOOL || t1_real == LEX_BOOL )) //tmp1 = BOOL;
        {
        exception_string = "operation NOT does not suit for NOT BOOLEAN type";
        exception_string << curr_lex;
        throw exception_string;
        }
    else
        {
        ; //poliz.push_back ( Lex (LEX_NOT, 0,  c_string_number, c_number_in_string ));
        //if (t1_real) st_lex.push (t1_real);
        //else if st_lex.push (t1);
        //st_lex.push (LEX_BOOL);
        }
    }

void Parser::check_id_in_read ()
    {
    if ( !TID [c_val].get_declare() )
        {
        exception_string = "Undeclared variable";
        exception_string += TID[c_val].get_name();
        exception_string << curr_lex;
        throw exception_string;
        }
    }
