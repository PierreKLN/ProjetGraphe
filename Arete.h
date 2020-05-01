#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"

class Arete
{
    private :

        int m_indice;
        int m_ext1;
        int m_ext2;
        int m_poids;

    public :

        Arete();

        void setIndice(int indice);
        void setExt1(int ext1);
        void setExt2(int ext2);
        void setPoids(int poids);

        int getIndice();
        int getExt1();
        int getExt2();
        int getPoids();

        void afficherArete();
};

#endif // ARETE_H_INCLUDED
