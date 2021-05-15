#include "INTERPRETATOR.hpp"
void Interpretator::interpretation () {
    pars.analyze ();

    cout << "=========================" << endl;
    cout << "=========================" << endl;

    E.execute ( pars.poliz );
}

