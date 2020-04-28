#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>


#include "svgfile.h"


class Sommet;
class Arrete;

class Graphe
{
    private :

        int m_orientation;
        int m_ordre;
        int m_taille;
        std::vector<Sommet*> m_sommets;
        std::vector<Arrete*> m_arretes;

    public :

        Graphe();
        void afficher();

        void dessinerSVG(Svgfile &svgout);
        void lecturePoids();
        void VerifAdja();

        void IndiceDegre();

        void CentraliteProximite(int debut, int fin);
        int getProchainSommet();

        void vecteurPropre();

};

#endif // GRAPHE_H_INCLUDED
