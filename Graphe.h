#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include <string>
#include <list>

#include "Sommet.h"
#include "Arete.h"

#include "Svgfile.h"

class Svgfile;

class Graphe
{
    private :

        int m_orientation;
        int m_ordre;
        int m_taille;

        std::vector<Sommet*> m_sommets;
        std::vector<Arete*> m_aretes;
        std::vector <double> m_compteur;
        std::vector <int> m_stockSommet;
        std::list<int> m_indice;

    public :

        Graphe();
        ~Graphe();
        ///methode pour charger les differents poids et graphes
        void remplirGraphe(std::string nom);
        void lirePoids(std::string nom);
        void lireNewPoids(std::string nom);
        ///methodes pour faire fonctionner les differents dijkstra
        void initDijkstra(unsigned int debut, unsigned int fin);
        void NewinitDijkstra(unsigned int debut, unsigned int fin, int IndiceSommet);
        void dijkstra(unsigned int debut, unsigned int fin);
        void Newdijkstra(unsigned int debut, unsigned int fin, int IndiceSommet);
        void afficherDijkstra(unsigned int sommet);
        void NewafficherDijkstra(unsigned int sommet, int IndiceSommet);
        int getNextSommet();
        int newgetNextSommet();
        ///methode pour l'affichage des differentes centralités
        void afficherCentraliteDegre();
        void afficherCentraliteVecteurPropre();
        void afficherCentraliteProximite();
        void afficherCentraliteIntermediarite(int IndiceSommet);
        ///methode pour la sauvegarde des differentes centralités
        void sauvegardeCentraliteDegre();
        void sauvegardeCentraliteVecteurPropre();
        void sauvegardeCentraliteProximite();
        void sauvegardeCentraliteIntermediarite();


        int retournePoids(int a, int b);
        void vulnerabilite();
        void SuppressionArete();
        void parcoursBFS(int depart);
        void afficherCompoConnexe(Sommet *sommet);
        void dessinerSVG();
        void afficherGraphe();


};

#endif // GRAPHE_H_INCLUDED
