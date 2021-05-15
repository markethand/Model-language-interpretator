#include "GLOBAL.hpp"


vector<Ident> TID;
vector <string> STRINGS_TABLE;
int put ( const string & buf ) //Добавить идентификатор, если его не было вернуть позицию
    {
    vector<Ident>::iterator k;

    if ( ( k = find ( TID.begin (), TID.end (), buf ) ) != TID.end () )
        {
        return k - TID.begin();;
        }
    TID.push_back ( Ident(buf) );
    return TID.size () - 1;
    }
