#include "EXECUTOR.hpp"


void change_meaning (meaning & tmp1)
    {
    int id_meaning = tmp1.int_meaning;
    int arg_type = 0;
    arg_type = TID[id_meaning].get_type();

    if (arg_type == LEX_STRING)
        {
        tmp1 = meaning (string_type, STRINGS_TABLE [ TID[id_meaning].get_value() ]);
        }
    else if (arg_type == LEX_BOOL)
        {
        tmp1 = meaning (bool_type, TID[id_meaning].get_value() );
        }
    else if (arg_type == LEX_INT)
        {
        tmp1 = meaning (integer_type, TID[id_meaning].get_value() );
        }
    }

void args_to_meanings (stack < meaning >  & args)
    {
    meaning tmp1 (another_type, 0);
    meaning tmp2 (another_type, 0);

    from_st ( args, tmp1 );
    from_st ( args, tmp2 );

    if (tmp1.meaning_type == identificator_type)
        {
        change_meaning (tmp1);
        }

    if (tmp2.meaning_type == identificator_type)
        {
        change_meaning (tmp2);
        }

    args.push (tmp2);
    args.push (tmp1);
    }


void Executer::execute ( vector<Lex> & poliz ) {
    cout << "STARTED EXECUTING" << endl;
    Lex pc_el;
    stack < meaning > args;
    //vector <meaning> args;
    int i, j, index = 0, size = poliz.size();

    meaning tmp1( another_type, 0);
    meaning tmp2( another_type, 0);
    int k;
    string tmp_string;


    while ( index < size )
        {
        //cout << "$" << endl;
        //cout << "SIZE = " << args.size() << " INDEX = " << index << endl;
        pc_el = poliz [ index ];
        //cout << poliz [index];

        //cout << "~" << endl;

        switch ( pc_el.get_type () )
            {
            case LEX_TRUE: case LEX_FALSE:
                args.push ( meaning (identificator_type, pc_el.get_value ()) );
            break;


            case LEX_NUM:
            case POLIZ_LABEL:
                args.push ( meaning (integer_type, pc_el.get_value ()) );
            break;


            case POLIZ_ADDRESS:
                args.push ( meaning (identificator_type, pc_el.get_value ()) );
            break;


            case LEX_STRING:
                args.push ( meaning (string_type, STRINGS_TABLE [pc_el.get_value ()]) );
            break;



            case LEX_ID:
                //cout << "LEX ID" << endl;

                tmp1.int_meaning = pc_el.get_value ();

                if (TID[pc_el.get_value()].get_assign())
                    {
                    int lex_type = 0;
                    lex_type = TID[pc_el.get_value()].get_type();

                    if (lex_type == LEX_STRING)
                        {
                        tmp1 = meaning (string_type, STRINGS_TABLE [ TID[pc_el.get_value()].get_value() ]);
                        //tmp1.meaning_type = string_type;
                        }
                    else if (lex_type == LEX_BOOL)
                        {
                        tmp1 = meaning (bool_type, TID[pc_el.get_value()].get_value() );
                        //tmp1.meaning_type = bool_type;
                        }
                    else if (lex_type == LEX_INT)
                        {
                        //cout << " I W H" << endl;
                        tmp1 = meaning (integer_type, TID[pc_el.get_value()].get_value() );
                        //tmp1.meaning_type = integer_type;
                        }
                    else ;

                    args.push(tmp1);

                    //cout << "LEX_ID SIZE = " << args.size() << " INDEX = " << index << endl;
                    }
                else
                    {
                    string exception_string;
                    exception_string = "Error: UNINITIALIZED VALUE USE ";
                    exception_string << pc_el;
                    throw (exception_string);
                    }
            break;




            case LEX_NOT:
                from_st ( args, tmp1 );

                if (tmp1.meaning_type == identificator_type)
                    {
                    tmp1 = meaning (bool_type, TID[tmp1.int_meaning].get_value() );
                    }

                args.push (meaning (bool_type, !tmp1.int_meaning));
            break;

            case LEX_OR:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );
                args.push (meaning (bool_type, tmp1.int_meaning || tmp2.int_meaning));
            break;

            case LEX_AND:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );
                args.push (meaning (bool_type, tmp1.int_meaning && tmp2.int_meaning));
            break;




            case POLIZ_GO:
                //cout << "#GO" << endl;
                from_st ( args, tmp1 );
                index = tmp1.int_meaning - 1;
            break;

            case POLIZ_FGO:
                //cout << "#FGO" << endl;
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );


                //cout << "TMP1 " << tmp1.int_meaning;
                //cout << "TMP2 " << tmp2.int_meaning;

                if ( !tmp2.int_meaning )
                    {
                    //cout << "FGO SUCCEEDED" << endl;
                    index = tmp1.int_meaning - 1;
                    }
            break;



            case LEX_WRITE:
                {
                cout << "WRITE |";

                //cout << "DEBUG\n";
                //cout << args.top().meaning_type << " "<< args.empty() <<endl;
                //cout << "DEBUG\n";
                //cout << endl;

                from_st ( args, tmp2 ); //Количество аргументов

                stack < meaning > reverse_args;
                int               args_q = tmp2.int_meaning;
                while (tmp2.int_meaning > 0)
                    {
                    //cout << "E" << args.empty() <<endl;
                    from_st ( args, tmp1 );
                    reverse_args.push (tmp1);
                    tmp2.int_meaning = (tmp2.int_meaning - 1);

                    //cout << "&" << endl;
                    //cout << endl;
                    //cout << endl;
                    }

                //cout << "var to be written " << args_q << endl;
                while (args_q > 0)
                    {
                    from_st ( reverse_args, tmp1 );

                    //cout << "var to be written " << tmp1.int_meaning << endl;

                    if (tmp1.meaning_type == identificator_type)
                        {
                        if (TID[tmp1.int_meaning].get_type() == LEX_STRING)
                            {
                            cout << STRINGS_TABLE [TID[tmp1.int_meaning].get_value()];
                            }
                        else if (TID[tmp1.int_meaning].get_type() == LEX_BOOL)
                            {
                            if (TID [tmp1.int_meaning].get_value()) cout << "true";
                            else cout << "false";
                            }
                        else if (TID[tmp1.int_meaning].get_type() == LEX_INT)
                            cout << TID[tmp1.int_meaning].get_value();
                        }
                    else if (tmp1.meaning_type == string_type)
                        {
                        cout << tmp1.string_meaning;
                        }
                    else if (tmp1.meaning_type == bool_type)
                        {
                        if (tmp1.int_meaning) cout << "true";
                        else cout << "false";
                        }
                    else if (tmp1.meaning_type == integer_type)
                        cout << tmp1.int_meaning;

                    args_q--;
                    cout << "|";
                    }
                cout << endl;
                cout << endl;

                cout << "ended WRITE" << endl;


                }
            break;

            case LEX_READ:
                from_st ( args, tmp1 );

                cout << "TO BE READ :: " << tmp1.int_meaning << endl;
                i = tmp1.int_meaning;

                if ( TID[i].get_type () == LEX_INT )
                    {
                    cout << "Input int value for " << TID[i].get_name () << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;

                    int TMP_TO_INPUT = 0;
                    cin >> TMP_TO_INPUT;


                    cout << "input succeeded";

                    TID[i].put_value (TMP_TO_INPUT);
                    TID[i].put_assign ();

                    cout << "output succeeded";
                    }
                else if (TID[i].get_type() == LEX_STRING)
                    {
                    cout << "Input string value for " << TID[i].get_name () << endl;
                    cin >> tmp_string;
                    if (TID[i].get_assign())
                        {
                        STRINGS_TABLE [TID[i].get_value()] = tmp_string;
                        }
                    else
                        {
                        STRINGS_TABLE.push_back(tmp_string);
                        TID[i].put_value(STRINGS_TABLE.size() - 1);
                        TID[i].put_assign ();
                        }
                    }
                else
                    {
                    string j;
                    while (1)
                        {
                        cout << "Input boolean value (true or false) for" << TID[i].get_name() << endl;
                        cin >> j;
                        if ( j != "true" && j != "false" )
                            {
                            cout << "Error in input:true/false" << endl;
                            continue;
                            }
                        k = ( j == "true" ) ? 1 : 0;
                        break;
                        }

                    TID[i].put_value (k);
                    TID[i].put_assign ();
                    }
            break;

            case LEX_PLUS:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (tmp1.meaning_type == string_type)
                    {
                    tmp1.string_meaning = tmp1.string_meaning;
                    tmp2.string_meaning = tmp2.string_meaning;
                    args.push ( meaning (string_type, tmp2.string_meaning + tmp1.string_meaning) );
                    }
                else
                    { //Ingeger
                    tmp1.int_meaning = tmp1.int_meaning;
                    tmp2.int_meaning = tmp2.int_meaning;
                    args.push ( meaning (integer_type, tmp2.int_meaning + tmp1.int_meaning) );
                    }
            break;

            case LEX_TIMES:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );
                args.push ( meaning (integer_type, tmp2.int_meaning * tmp1.int_meaning) );
            break;

            case LEX_MINUS:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );
                args.push ( meaning (integer_type, tmp2.int_meaning - tmp1.int_meaning) );
            break;

            case LEX_SLASH:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (! ((tmp1.int_meaning == 0)   ))
                    {
                    args.push (meaning (integer_type, tmp2.int_meaning / tmp1.int_meaning ));
                    break;
                    }
                else
                    throw "POLIZ:divide by zero";
            break;

            case LEX_PERCENT:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (tmp1.int_meaning == 0 || tmp1.int_meaning == 1) throw "bad %";
                args.push ( meaning (integer_type,tmp2.int_meaning % tmp1.int_meaning) );
            break;


            case LEX_EQ:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (tmp1.meaning_type == string_type)
                    args.push ( meaning (string_type, tmp2.string_meaning == tmp1.string_meaning) );
                else
                    args.push ( meaning (integer_type, tmp2.int_meaning == tmp1.int_meaning) );
            break;

            case LEX_LSS:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                cout << "TMP2 " << tmp2.int_meaning << endl;
                cout << "TMP1 " << tmp1.int_meaning << endl;

                cout << "RESULT TMP2 < TMP1 " << (tmp2.int_meaning < tmp1.int_meaning) << endl;

                if (tmp1.meaning_type == string_type)
                    args.push ( meaning (string_type, tmp2.string_meaning < tmp1.string_meaning) );
                else
                    args.push ( meaning (integer_type, tmp2.int_meaning < tmp1.int_meaning) );
            break;

            case LEX_GTR:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (tmp1.meaning_type == string_type)
                    args.push ( meaning (string_type, tmp2.string_meaning > tmp1.string_meaning) );
                else
                    args.push ( meaning (integer_type, tmp2.int_meaning > tmp1.int_meaning) );
            break;

            case LEX_LEQ:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (tmp1.meaning_type == string_type)
                    args.push ( meaning (string_type, tmp2.string_meaning <= tmp1.string_meaning) );
                else
                    args.push ( meaning (integer_type, tmp2.int_meaning <= tmp1.int_meaning) );
            break;

            case LEX_GEQ:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );


                if (tmp1.meaning_type == string_type)
                    args.push ( meaning (string_type, tmp2.string_meaning >= tmp1.string_meaning) );
                else
                    args.push ( meaning (integer_type, tmp2.int_meaning >= tmp1.int_meaning) );
            break;

            case LEX_NEQ:
                args_to_meanings (args);
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (tmp1.meaning_type == string_type)
                    args.push ( meaning (string_type, tmp1.string_meaning != tmp2.string_meaning) );
                else
                    args.push ( meaning (integer_type, tmp1.int_meaning != tmp2.int_meaning) );
            break;

            case LEX_ASSIGN:
                from_st ( args, tmp1 );
                from_st ( args, tmp2 );

                if (tmp1.meaning_type == string_type)
                    {
                    //cout << "assign strings " << endl;

                    if (tmp1.meaning_type == identificator_type)
                        {
                        STRINGS_TABLE [TID[tmp2.int_meaning].get_value()] = STRINGS_TABLE [TID[tmp1.int_meaning].get_value()];
                        }
                    else
                        {
                        STRINGS_TABLE [TID[tmp2.int_meaning].get_value()] = tmp1.string_meaning;
                        }

                    TID[tmp2.int_meaning].put_assign ();

                    args.push (tmp2);
                    }
                else
                    {
                    if (tmp1.meaning_type == identificator_type)
                        {
                        TID [tmp2.int_meaning].put_value(TID [tmp1.int_meaning].get_value());
                        }
                    else
                        {
                        TID[tmp2.int_meaning].put_value (tmp1.int_meaning);
                        }

                    TID[tmp2.int_meaning].put_assign ();

                    args.push (tmp2);
                    }
                //TID[tmp2.int_meaning].put_assign();
            break;


            case LEX_SEMICOLON:
                if (!args.empty()) from_st ( args, tmp1 );
            break;

            default:
                cout << "DEFAULT" << pc_el.get_type() << " " << pc_el.get_value() << endl;
                throw "POLIZ: unexpected elem";
            }//end of switch
        ++index;
        };//end of while
    cout << "Finish of executing!!!" << endl;
    }
