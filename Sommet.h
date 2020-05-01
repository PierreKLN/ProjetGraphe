#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>

class Sommet
{
    private :

        int m_indice;
        std::string m_nom;
        int m_x;
        int m_y;

        int m_longueur;
        int m_precedent;
        bool m_visite;

        std::vector<int> m_adjacents;
        std::vector<int> m_poids;


    public :

        Sommet();

        int getIndice();
        std::string getNom();
        int getX();
        int getY();
        int getLongueur();
        int getPrecedent();
        bool getVisite();
        int getPoids(int i);
        float getNombreVoisins();
        int getIndiceAdjacence(int i);
        void ajouterAdjacence(Sommet *a, double poids);

        void setIndice(int indice);
        void setNom(std::string nom);
        void setX(int x);
        void setY(int y);

        void setLongueur(int longueur);
        void setPrecedent(int precedent);
        void setVisite(bool visite);

        void setAdjacent(int indice);
        void setPoids(int poids);

        void afficher();
        void afficherSommet();

};

#endif // SOMMET_H_INCLUDED
