#include <iostream>

#include "Arete.h"

Arete::Arete()
{

}

void Arete::setIndice(int indice)
{
    m_indice = indice;
}

void Arete::setExt1(int ext1)
{
    m_ext1 = ext1;
}

void Arete::setExt2(int ext2)
{
    m_ext2 = ext2;
}

void Arete::setPoids(int poids)
{
    m_poids = poids;
}

int Arete::getIndice()
{
    return m_indice;
}

int Arete::getExt1()
{
    return m_ext1;
}

int Arete::getExt2()
{
    return m_ext2;
}

int Arete::getPoids()
{
    return m_poids;
}

void Arete::afficherArete()
{
    std::cout << m_indice << m_ext1 << m_ext2 << std::endl;
}
