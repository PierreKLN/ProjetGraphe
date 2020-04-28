#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED

#include <vector>
class Arrete
{
    private :

        int m_indice;
        int m_extre1;
        int m_extre2;
        int m_longueur;
        bool m_visite;
        std::vector<int> m_poids;

    public :

        Arrete();

        void ajouterIndice(int indice);
        void ajouterExtrem1(int un);
        void ajouterExtrem2(int deux);
        void ajouterPoids(int poids);

        int getExtre1();
        int getExtre2();
        int getLongueur() const;
        bool getVisite() const;
        std::vector<int> getPoids();

         void setCouleur(int couleur);
         void setLongueur(int longueur);

         void afficher();

};

#endif // ARRETE_H_INCLUDED
