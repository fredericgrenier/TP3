#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <chrono>
#include <stdint.h>
#include "graphe.h"

using std::string;
using std::cout;
using std::endl;

void Two_Way_Test(std::string path, uint32_t from, uint32_t to)
{
	graphe graph(path);

	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::duration<double> dur;
	double duration;

	start = std::chrono::high_resolution_clock::now();
	graph.afficher_chemin(graph.trouver_chemin(from, to));
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Duration A: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << endl;

	start = std::chrono::high_resolution_clock::now();
	graph.afficher_chemin(graph.trouver_chemin(to, from));
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Duration B: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << endl;
}

void findDistance(string filePath, uint32_t numreoNoeud, float latitude, float longitude)
{
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	graphe G(filePath);

	cout << "point : " << numreoNoeud << " distance : " << G.distance(numreoNoeud, latitude, longitude) << endl << endl;
	start = std::chrono::high_resolution_clock::now();
	numreoNoeud = G.localiser(latitude, longitude);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Duree de la localisation du noeud: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << endl;
	cout << "point : " << numreoNoeud << endl
		 << "distance : " << G.distance(numreoNoeud, latitude, longitude) << endl
		 << "noeuds lus : " << G.size_map() << endl
		 << endl;
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

int main()
{
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\exemple.ibin", 0, 9);
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\grUSA_32.ibin", 27, 12);
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\grUSA_1024.ibin", 316, 554);
	//Two_Way_Test("F:\\Travaux\\BAC Informatique\\Session1\\IFT339\\TP2\\Fichiers test\\grUSA_32768.ibin", 0, 32767);
	//Two_Way_Test("C:\\Tests\\grUSA_32768.ibin", 3489, 6666);
	//Two_Way_Test("C:\\Tests\\grUSA_1048576.ibin", 320694, 910366);

	//findDistance("C:\\Tests\\grUSA_32.ibin", 31, 40.0F, -70.0F); //  (d=234.21) 8 noeuds lus
	//findDistance("C:\\Tests\\grUSA_1024.ibin", 841, 40.0F, -70.0F); //  (d=191.314) 25 noeuds lus
	//findDistance("C:\\Tests\\grUSA_32768.ibin", 18499, 40.0F, -70.0F); //  (d=138.913) 29 noeuds lus
	//findDistance("C:\\Tests\\grUSA_1048576.ibin", 631097, 40.0F, -70.0F); //  (d=71.6312) 143 noeuds lus

	// Test des petites fonctions
	graphe G("C:\\Tests\\grUSA_32.ibin");
	//cout << "Size_map depart : " << G.size_map() << endl;
	uint32_t noeud;
	noeud = G.localiser(40.0F, -70.0F);
	cout << "point : " << noeud << endl
		<< "distance : " << G.distance(noeud, 40.0F, -70.0F) << endl
		<< "noeuds lus : " << G.size_map() << endl
		<< endl;
	G.vider();
	noeud = G.localiser(41.792F, -92.8338F);
	cout << "point : " << noeud << endl
		<< "distance : " << G.distance(noeud, 41.792F, -92.8338F) << endl
		<< "noeuds lus : " << G.size_map() << endl
		<< endl;
	G.vider();
	noeud = G.localiser(37.6264F, -77.6058F);
	cout << "point : " << noeud << endl
		<< "distance : " << G.distance(noeud, 37.6264F, -77.6058F) << endl
		<< "noeuds lus : " << G.size_map() << endl
		<< endl;
	G.vider();
	noeud = G.localiser(37.6264F, -70.8559F);
	cout << "point : " << noeud << endl
		<< "distance : " << G.distance(noeud, 37.6264F, -70.8559F) << endl
		<< "noeuds lus : " << G.size_map() << endl
		<< endl;
	//cout << "Size_map apres localiser : " << G.size_map() << endl;
	//cout << "Nom du noeud 0 : " << G[0] << endl;
	//cout << "Nom du noeud 631097 : " << G[631097] << endl;
	//G.vider();
	//cout << "Size_map apres vider : " << G.size_map() << endl;
	
	return 0;
}

