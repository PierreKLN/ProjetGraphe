#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include <string>

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

    public :

        Graphe(std::string nom);

        ~Graphe();

        void lirePoids();

        int getOrientation();
        int getOrdre();
        int getTaille();

        int retournePoids(int a, int b);

        int getNextSommet();
        void initDijkstra(unsigned int debut, unsigned int fin);
        void dijkstra(unsigned int debut, unsigned int fin);
        void afficherTout(unsigned int sommet);
        void recupSommePoids(unsigned int i);

        void centraliteDegre();
        void centraliteVecteurPropre();
        void centraliteDijkstra();

        void afficherCentraliteDegre();
        void afficherCentraliteVecteurPropre();
        void afficherCentraliteProximite();

        void dessinerSVG(Svgfile &svgout);

        void setCompteur(double i);
        int CalculIndice(int &courtChemin, int num);

        void centraliteIntermdiariteSimple(int indice);

        void SuppressionArete(int indice);
        void Vulnerabilite();


};

#endif // GRAPHE_H_INCLUDED
