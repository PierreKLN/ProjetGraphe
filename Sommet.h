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
        int m_inter;

        int m_longueur;
        int m_precedent;
        int m_couleur;
        bool m_visite;

        std::vector<int> m_adjacents;
        std::vector<int> m_NewAdja;
        std::vector<int> m_poids;
        std::vector <int> m_suivant;


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
        float getNewNombreVoisins();
        int getIndiceAdjacence(int i);
        int getNewIndiceAdja(int i);
        int getCouleur();
        int getInter();

        void setIndice(int indice);
        void setNom(std::string nom);
        void setX(int x);
        void setY(int y);

        void setLongueur(int longueur);
        void setPrecedent(int precedent);
        void ajouterSuivant(int indice);
        void setVisite(bool visite);
        void setNewAdja(int indice);
        void setCouleur(int couleur);
        void setInter(int inter);

        void setAdjacent(int indice);
        void setPoids(int poids);

        void afficher();
        void afficherSommet();

};

#endif // SOMMET_H_INCLUDED
