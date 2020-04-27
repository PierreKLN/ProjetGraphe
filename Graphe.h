#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>

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
        void VerifAdja();
        void IndiceDegre();
};

#endif // GRAPHE_H_INCLUDED