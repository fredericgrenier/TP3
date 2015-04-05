#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
using namespace std;
#include "graphe.h"


int main()
{
	uint32_t noeud;
	graphe G("grUSA_1024.ibin");
	cout << "point : 841 distance : " << G.distance(841,40,-70) << endl;
	noeud = G.localiser(40, -70);
	cout << "point : "
		<< noeud
		<< " distance : "
		<< G.distance(noeud, 40, -70)
		<< " noeuds lus : "
		<< G.size_map()
		<< endl;
    return 0;
}


