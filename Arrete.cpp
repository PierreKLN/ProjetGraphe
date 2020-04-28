#include <iostream>

#include "Arrete.h"

Arrete::Arrete()
{

}

void Arrete::ajouterIndice(int indice)
{
    m_indice = indice;
}

void Arrete::ajouterExtrem1(int un)
{
    m_extre1 = un;
}

void Arrete::ajouterExtrem2(int deux)
{
    m_extre2 = deux;
}

void Arrete::ajouterPoids (int poids)
{
   m_poids.push_back(poids);
}

int Arrete::getExtre1()
{
    return m_extre1;
}

int Arrete::getExtre2()
{
    return m_extre2;
}
int Arrete::getPoids(int i)
{
    return m_poids[i];
}
void Arrete::afficher()
{
    std::cout << "Indice : " << m_indice << std::endl;
    std::cout << "Extremite 1 : " << m_extre1 << std::endl;
    std::cout << "Extremite 2 : " << m_extre2 << std::endl;

    for (size_t i = 0; i<m_poids.size();++i)
    {
        std::cout<<"Poids : "<<m_poids[i]<<std::endl;
    }
}


