
#include "INTERPRETATOR.hpp"
#define MAX_FILE_NAME_LENGTH 20

int main (int argc, char* argv[])
    {
    try
        {
        char FILE_NAME [20] = {};

        if (argc > 1)
            {
            Interpretator I ( argv [1] );

            I.interpretation ();
            }
        else
            {
            string FILE_NAME_STRING = "";
            cin >> FILE_NAME_STRING;

            if (FILE_NAME_STRING.size() < MAX_FILE_NAME_LENGTH)
                {
                for (int i = 0; i < FILE_NAME_STRING.size(); i++)
                    {
                    FILE_NAME[i] = FILE_NAME_STRING[i];

                    Interpretator I (FILE_NAME);

                    I.interpretation ();
                    }
                }
            else
                throw "bad filename, too long";

            }
        return 0;
        }
    catch ( string  s )
        {
        cout << s << endl;
        return 1;
        }
    catch ( Lex l )
        {
        cout << "unexpected lexeme" << l << endl;
        return 1;
        }
    catch ( const char *source )
        {
        cout << source << endl;
        return 1;
        }
    }
