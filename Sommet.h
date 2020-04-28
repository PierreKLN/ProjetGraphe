#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>

#include <string>


class Sommet
{
    private :

        int m_indice;

        std::string m_nom;


        int m_x;
        int m_y;
        int m_precedent;
        std::vector<Sommet*> m_adjacence;

    public :

        Sommet();

        void ajouterIndice(int a);
        void ajouterNom(char a);
        void ajouterX(int x);
        void ajouterY(int y);
        void ajouterAdjacence(Sommet *a);

        int getIndice();

        int getX();
        int getY();
        std::string getNom()const;
        int getPrecedent() const;

        void afficherAdjacence();
        void setPrecedent(int precedent);
        int getDegre()const;
        std::vector<Sommet*> getAdja(int i);

        void afficher();
};

#endif // SOMMET_H_INCLUDED
