#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
using namespace std;
#include "graphe.h"


int main()
{
    list<uint32_t> chemin;
    graphe G("exemple.ibin");
    /*
    for(int i = 0; i < 10; ++i)
    G.afficher(i);
    */
    chemin.push_back(0);
    chemin.push_back(1);
    chemin.push_back(2);
    //chemin.push_back(3);
    G.afficher_chemin(chemin);
    return 0;
}


