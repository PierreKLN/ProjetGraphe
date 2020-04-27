#ifndef ARRETE_H_INCLUDED
#define ARRETE_H_INCLUDED

class Arrete
{
    private :

        int m_indice;
        int m_extre1;
        int m_extre2;

    public :

        Arrete();

        void ajouterIndice(int indice);
        void ajouterExtrem1(int un);
        void ajouterExtrem2(int deux);

        int getExtre1();
        int getExtre2();

        void afficher();

};

#endif // ARRETE_H_INCLUDED
