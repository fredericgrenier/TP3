//
//  graphe.cpp
//
//  Jean Goulet on 15-02-09.
//  Copyleft 2015
//  Maxime Boulay, Fr�d�ric Grenier 15-03-16

#include <fstream>
#include "graphe.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <stdint.h>
#include <unordered_map>
using namespace std;

void graphe::lire(uint32_t& v) {
    DATA.read(reinterpret_cast<char*> (&v), 4);
}


void graphe::lire(uint16_t& v) {
    DATA.read(reinterpret_cast<char*> (&v), 2);
}


void graphe::lire(float& k) {
    DATA.read(reinterpret_cast<char*> (&k), 4);
}


void graphe::lire(string& n) {
    DATA >> n;
}

size_t graphe::size()const{return NBNOEUDS;}


void graphe::lire_noeud(uint32_t i) {
    if(lesNoeuds.count(i)==0) {
        char * buffer = new char [2];
        noeud x;
        char y;
        uint32_t num;
        float poids;
        uint32_t variable;
        uint16_t size_nom;
        uint32_t fixe = i*28+DEBUT_PARTIE_FIXE;
        DATA.seekg(fixe);
        lire(variable);
        lire(x.lattitude);
        lire(x.longitude);
		lire(x.QT[0]);
		lire(x.QT[1]);
		lire(x.QT[2]);
		lire(x.QT[3]);
        DATA.seekg(variable);
        uint16_t nbr;
        lire(nbr);
        for(int l=0;l<nbr;++l) {
            lire(num);
            lire(poids);
            x.lesArcs.insert(pair<uint32_t,float>(num,poids));
        }
        DATA.read(buffer,2);
        lire(x.nom);
        lesNoeuds.insert(pair<uint32_t,noeud>(i,x));
        delete [] buffer;
    }
}


graphe::graphe(string fichier) {
    char * buffer = new char [3];
    DATA.open(fichier,ios::binary);
    DATA >> NOM;
    DATA >> NBNOEUDS;
    DATA.read(buffer,3);
    DEBUT_PARTIE_FIXE = DATA.tellg();
    delete [] buffer;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void graphe::afficher_noeud(uint32_t numero) {
    lire_noeud(numero);
    cout << "nom:" << lesNoeuds[numero].nom << endl;
    cout << "lattitude:" << lesNoeuds[numero].lattitude << endl;
    cout << "longitude:" << lesNoeuds[numero].longitude << endl;
    cout << "nbr_darc:" << lesNoeuds[numero].lesArcs.size() << endl;
    for(auto& it : lesNoeuds[numero].lesArcs) {
        cout << it.first << " " << it.second << endl;
        }
}

/////////////////////////////////////////////////////////////////////////////////////////////
void graphe::afficher_chemin(list<uint32_t> chemin){
    float total = 0;
    list<uint32_t>::iterator it = chemin.begin();
    cout << lesNoeuds[(*it)].nom << " (" << lesNoeuds[(*it)].lattitude << "," << lesNoeuds[(*it)].longitude  << ") " << endl;
    ++it;
    for(; it != chemin.end();++it){
        cout << "=> " << lesNoeuds[(*it)].nom << " (" << lesNoeuds[(*it)].lattitude << "," << lesNoeuds[(*it)].longitude  << ") ";
        list<uint32_t>::iterator it2=it;
        (--it2);
        if ((it)!=chemin.end())
        cout << lesNoeuds[(*it2)].lesArcs[*it] << " ";
        total += lesNoeuds[(*it2)].lesArcs[*it];
        cout << endl;
        }
    cout << endl;
    cout << "Total : " << total << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
list<uint32_t> graphe::trouver_chemin(uint32_t DEP,uint32_t ARR) {
    unordered_map<uint32_t,float> TOTAL;
    multimap<float,uint32_t> LATOT;
    unordered_map<uint32_t,uint32_t> PRED;
    list<uint32_t> RESULTAT;
    uint32_t us = DEP;
    float max_a_date=1;
    float max_a_venir;

    LATOT.insert(pair<float,uint32_t>(0,DEP));
    TOTAL[DEP] = 0;

    lire_noeud(ARR);

    map<float,uint32_t>::iterator i = LATOT.begin();
    while((*i).second != ARR){
        if((TOTAL.count((*i).second)==1)&&((*i).first>TOTAL[(*i).second])){  //Regarder si le noeud de LATOT est d�j� explor� avec un plus court chemin
            ++i;
            us = (*i).second;
            continue;
            }
        lire_noeud(us);
        for(auto n : lesNoeuds[us].lesArcs){
            max_a_venir = TOTAL[us]+n.second;
            if(TOTAL.count(n.first)==1){
                max_a_date = TOTAL[n.first];
                if(max_a_date<=max_a_venir)continue;
                }
            TOTAL[n.first] = max_a_venir;
            LATOT.insert(pair<float,uint32_t>(max_a_venir,n.first));
            PRED[n.first] = us;
            }
        ++i;
        us = (*i).second;
        if(i==LATOT.end()) break; //S'il n'y a pas de chemin possible, on sort de la boucle
        }

    if(us==ARR){while(us != DEP){
        RESULTAT.push_front(us);
        us = PRED[us];
        }
    }
    else{cout << "Il n'y a pas de chemin possible" << endl;}
    RESULTAT.push_front(DEP);
    return RESULTAT;
}

void graphe::clear(){
    lesNoeuds.clear();
    DATA.close();
    DEBUT_PARTIE_FIXE=NBNOEUDS=0;
    NOM = "";
}

graphe::~graphe(){
    clear();
}

void graphe::localiser(float LAT, float LON, uint32_t& point_final, uint32_t& point, float& Mdistance){
	lire_noeud(point);
	size_t z, z1, z2;
	float Ndistance = distance(point,LAT,LON);
	if (Ndistance < Mdistance)
	{
		cout << "distance : " << Mdistance << endl;
		Mdistance = Ndistance;
		point_final = point;
	}
	noeud noeudCourant = lesNoeuds[point];
	float point_LAT = noeudCourant.lattitude;
	float point_LON = noeudCourant.longitude;
	// Determiner dans quel zone est le point x(LAT,LON)
	if ((LAT > point_LAT) && (LON > point_LON))z = 0;
	else if ((LAT > point_LAT) && (LON <= point_LON))z = 1;
	else if ((LAT <= point_LAT) && (LON > point_LON))z = 2;
	else z = 3;
	z1 = (z + 2) % 4;
	z2 = 3 - z1;
	int test = lesNoeuds[point].QT[z];
	if (noeudCourant.QT[z] != 0)localiser(LAT, LON, point_final, noeudCourant.QT[z], Mdistance);
	if (noeudCourant.QT[z1] != 0)localiser(LAT, LON, point_final, noeudCourant.QT[z1], Mdistance);
	if (noeudCourant.QT[z2] != 0)localiser(LAT, LON, point_final, noeudCourant.QT[z2], Mdistance);
}

uint32_t graphe::localiser(float LAT, float LON){
	uint32_t point = 0;	// Ne fonctionne pas si le noeud initial n'est pas 0
	uint32_t point_final = 0;
	float Mdistance = std::numeric_limits<float>::max();
	localiser(LAT, LON,point_final, point, Mdistance);
	return point_final;
}

void graphe::vider(){
	lesNoeuds.clear();
}

size_t graphe::size_map()const{
	return lesNoeuds.size();
}

string graphe::operator[](uint32_t noeud){
	return lesNoeuds[noeud].nom;
}

float graphe::distance(uint32_t noeud, float LAT, float LON){
	lire_noeud(noeud);
	float Mdistance, x, y,c;
	float pi = 3.141592653589793238462643;
	
	float noeud_LAT = lesNoeuds[noeud].lattitude;
	float noeud_LON = lesNoeuds[noeud].longitude;

	x = pow((LON - noeud_LON), 2);
	y = pow((LAT - noeud_LAT), 2);
	c = pow(cos((noeud_LAT + LAT) / 2 * pi / 180), 2);
	Mdistance = sqrt(y + x*c)*111;
	return Mdistance;
}