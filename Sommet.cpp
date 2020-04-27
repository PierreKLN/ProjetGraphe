#include <iostream>

#include "Sommet.h"

Sommet::Sommet()
{

}

void Sommet::ajouterIndice(int a)
{
    m_indice = a;
}

void Sommet::ajouterNom(char a)
{
    m_nom = a;
}

void Sommet::ajouterX(int x)
{
    m_x = x;
}

void Sommet::ajouterY(int y)
{
    m_y = y;
}

void Sommet::ajouterAdjacence(Sommet *a)
{
    m_adjacence.push_back(a);
}

int Sommet::getIndice()
{
    return m_indice;
}

void Sommet::afficher()
{
    std::cout << "Indice : " << m_indice << std::endl;
    std::cout << "Nom : " << m_nom << std::endl;
    std::cout << "X : " << m_x << std::endl;
    std::cout << "Y : " << m_y << std::endl;
}

void Sommet::afficherAdjacence()
{
    for (unsigned int i=0; i<m_adjacence.size();i++)
    {
        m_adjacence[i]->afficher();
    }
}

int Sommet::getDegre() const
    {
        return (int)m_adjacence.size();
    }
char Sommet::getNom () const
{
    return m_nom;
}
