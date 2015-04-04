#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
using namespace std;
#include "graphe.h"


int main()
{

	graphe G("grUSA_32.ibin");
	cout << "distance : " << G.distance(31,40,-70) << endl;
    return 0;
}


