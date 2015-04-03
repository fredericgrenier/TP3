#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
using namespace std;
#include "graphe.h"


int main()
{
	cout << "Hello world!" << endl;
	graphe G("grUSA_32.ibin");
	G.afficher_noeud(6);
    return 0;
}


