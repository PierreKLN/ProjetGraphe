#include <iostream>

#include "Sommet.h"

Sommet::Sommet():m_precedent{-1}, m_couleur{0}
{

}

int Sommet::getIndice()
{
    return m_indice;
}

std::string Sommet::getNom()
{
    return m_nom;
}
int Sommet::getX()
{
    return m_x;
}

int Sommet::getY()
{
    return m_y;
}

int Sommet::getLongueur()
{
    return m_longueur;
}

int Sommet::getPrecedent()
{
    return m_precedent;
}

bool Sommet::getVisite()
{
    return m_visite;
}

int Sommet::getPoids(int i)
{
    return m_poids[i];
}

float Sommet::getNombreVoisins()
{
    return m_adjacents.size();
}

float Sommet::getNewNombreVoisins()
{
    return m_NewAdja.size();
}

int Sommet::getIndiceAdjacence(int i)
{
    return m_adjacents[i];
}
int Sommet::getNewIndiceAdja(int i)
{
    return m_NewAdja[i];
}

void Sommet::setIndice(int indice)
{
    m_indice = indice;
}

void Sommet::setNom(std::string nom)
{
    m_nom = nom;
}

void Sommet::setX(int x)
{
    m_x = x;
}
void Sommet::setY(int y)
{
    m_y = y;
}

void Sommet::setLongueur(int longueur)
{
    m_longueur = longueur;
}

void Sommet::setPrecedent(int precedent)
{
    m_precedent = precedent;
}
void Sommet::ajouterSuivant(int indice)
{
    m_suivant.push_back(indice);
}

void Sommet::setVisite(bool visite)
{
    m_visite = visite;
}

void Sommet::setAdjacent(int indice)
{
    m_adjacents.push_back(indice);
}
void Sommet::setNewAdja (int indice)
{
    m_NewAdja.push_back(indice);
}

void Sommet::setPoids(int poids)
{
    m_poids.push_back(poids);
}

void Sommet::afficher()
{
    std::cout << m_indice << std::endl;
}

void Sommet::afficherSommet()
{
    for (unsigned int i=0;i<m_adjacents.size();i++)
    {
        std::cout << m_adjacents[i] << std::endl;
    }
    std::cout << std::endl;
}

void Sommet::setCouleur(int couleur)
{
    m_couleur=couleur;
}
int Sommet::getCouleur()
{
    return m_couleur;
}
void Sommet::setInter(int inter)
{
    m_inter=inter;
}
int Sommet::getInter()
{
    return m_inter;
}

