#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>

class Sommet
{
    private :

        int m_indice;
        char m_nom;
        int m_x;
        int m_y;
        std::vector<Sommet*> m_adjacence;

    public :

        Sommet();

        void ajouterIndice(int a);
        void ajouterNom(char a);
        void ajouterX(int x);
        void ajouterY(int y);
        void ajouterAdjacence(Sommet *a);

        int getIndice();
        int getDegre()const;
        char getNom()const;

        void afficherAdjacence();
        void afficher();
};

#endif // SOMMET_H_INCLUDED