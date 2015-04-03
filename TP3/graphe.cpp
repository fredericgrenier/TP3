//
//  graphe.cpp
//
//  Jean Goulet on 15-02-09.
//  Copyleft 2015
//  Maxime Boulay, Frédéric Grenier 15-03-16

#include <fstream>
#include "graphe.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
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
        if((TOTAL.count((*i).second)==1)&&((*i).first>TOTAL[(*i).second])){  //Regarder si le noeud de LATOT est déjà exploré avec un plus court chemin
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

void graphe::localiser(uint32_t& point, float& distance){

}

graphe::vider(){

}

size_t graphe::size_map()const{

}

uint32_t graphe::localiser(float LAT, float LON){

}

string graphe::operator[](uint32_t){

}

float graphe::distance(uint32_t, float, float){

}