//
//  graphe.h
//
//  Jean Goulet on 15-02-09.
//  Copyleft 2015
//  Maxime Boulay, Frédéric Grenier 15-03-16

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include <stdint.h>
#ifndef FichiersBinaires_graphe_h
#define FichiersBinaires_graphe_h
using namespace std;

class graphe{
private:
    struct noeud{
        float lattitude,longitude;
        string nom;
        uint32_t QT[4];
        map <uint32_t,float> lesArcs;
    };
    ifstream DATA;
    string NOM;
    uint32_t NBNOEUDS;
    uint32_t DEBUT_PARTIE_FIXE;
    map<uint32_t,noeud> lesNoeuds;
    void lire(void* adresse,size_t octets);
    void lire(uint16_t&);
    void lire(uint32_t&);
    void lire(float&);
    void lire(string&);
    void lire_noeud(uint32_t);

public:
    graphe(string);
    ~graphe();
    void clear();
    size_t size()const;
    void afficher_noeud(uint32_t numero);
    list<uint32_t> trouver_chemin(uint32_t,uint32_t);
    void afficher_chemin(list<uint32_t> chemin);
};


#endif
