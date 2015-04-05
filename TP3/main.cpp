#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <ctime>
#include "graphe.h"

using namespace std;

void Two_Way_Test(std::string path, uint32_t from, uint32_t to)
{
	graphe graph(path);

	std::clock_t start;
	double duration;

	start = std::clock();
	graph.afficher_chemin(graph.trouver_chemin(from, to));
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration A: " << duration << '\n';

	start = std::clock();
	graph.afficher_chemin(graph.trouver_chemin(to, from));
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Duration B: " << duration << '\n';
}

void askNode()
{
	std::string path;
	uint32_t nodeA, nodeB;
	std::cout << "Gives the path the file to open:" << std::endl;
	std::getline(std::cin, path);
	std::cout << "Node from:" << std::endl;
	std::cin >> nodeA;
	std::cout << "Node to:" << std::endl;
	std::cin >> nodeB;
	Two_Way_Test(path, nodeA, nodeB);
}

void Test2()
{
	uint32_t noeud;
	graphe G("grUSA_1024.ibin");
	cout << "point : 841 distance : " << G.distance(841, 40, -70) << endl;
	noeud = G.localiser(40, -70);
	cout << "point : "
		 << noeud
		 << " distance : "
		 << G.distance(noeud, 40, -70)
		 << " noeuds lus : "
		 << G.size_map()
		 << endl;
}

int main()
{
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\exemple.ibin", 0, 9);
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\grUSA_32.ibin", 27, 12);
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\grUSA_1024.ibin", 316, 554);
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\grUSA_32768.ibin", 0, 32767);
	Two_Way_Test("C:\\Tests\\grUSA_1048576.ibin", 320694, 910366);
	//Two_Way_Test("C:\\Tests\\grUSA_32768.ibin", 3489, 6666);

	return 0;
}

