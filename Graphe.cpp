#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"

Graphe::Graphe()
{
    std::ifstream fichier ("graphe.txt");

    fichier >> m_orientation;
    fichier >> m_ordre;

    for (int i=0; i<m_ordre; i++)
    {
        Sommet *a;
        a = new Sommet;

        int indice;
        char nom;
        int x;
        int y;

        fichier >> indice;
        fichier >> nom;
        fichier >> x;
        fichier >> y;

        a->ajouterIndice(indice);
        a->ajouterNom(nom);
        a->ajouterX(x);
        a->ajouterY(y);

        m_sommets.push_back(a);
    }

    fichier >> m_taille;

    for (int i=0; i<m_taille; i++)
    {
        Arrete *a;
        a = new Arrete;

        int indice;
        int un;
        int deux;

        fichier >> indice;
        fichier >> un;
        fichier >> deux;

        a->ajouterIndice(indice);
        a->ajouterExtrem1(un);
        a->ajouterExtrem2(deux);

        m_arretes.push_back(a);
    }

    VerifAdja();

}

void Graphe::VerifAdja()
{
    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        for (unsigned int j=0; j<m_arretes.size(); j++)
        {
            if (m_sommets[i]->getIndice()==m_arretes[j]->getExtre1())
            {
                m_sommets[i]->ajouterAdjacence(m_sommets[m_arretes[j]->getExtre2()]);
            }

            if (m_sommets[i]->getIndice()==m_arretes[j]->getExtre2())
            {
                m_sommets[i]->ajouterAdjacence(m_sommets[m_arretes[j]->getExtre1()]);
            }
        }
    }
}

void Graphe::IndiceDegre()
{
    std::ofstream SaveIndice1("C:/Users/Pierr/OneDrive/Documents/Cours ING2/Projet/SaveIndice1.txt");
    ///tri de monsieur Fercoq utilisé lors du tp1
    std::sort(m_sommets.begin(), m_sommets.end(), [](Sommet* s1, Sommet* s2)
    {
        return s1->getDegre() > s2->getDegre();
    });

    for (size_t i =0; i<m_sommets.size(); ++i)
    {
        std::cout<<m_sommets[i]->getDegre()<<std::endl;
    }

    if(SaveIndice1)
    {
        SaveIndice1<<"Tri par ordre de degres"<<std::endl;
        for (size_t i =0; i<m_sommets.size(); ++i)
        {

            SaveIndice1<<"Indice sommet "<<m_sommets[i]->getNom()<<": "<<m_sommets[i]->getIndice()
            <<" et de degre "<<m_sommets[i]->getDegre()<<std::endl;
        }
    }
    else
        std::cout<<"ERREUR"<<std::endl;

}
void Graphe::afficher()
{
    std::cout << "Orientation : " << m_orientation << std::endl;
    std::cout << "Ordre : " << m_ordre << std::endl << std::endl;

    std::cout << "Liste et caracteristiques de nos sommets : " << std::endl << std::endl;

    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->afficher();
    }

    std::cout << std::endl;

    std::cout << "Liste et caracteristiques de nos arretes : " << std::endl << std::endl;

    for (unsigned int i=0; i<m_arretes.size(); i++)
    {
        m_arretes[i]->afficher();
    }

    std::cout << std::endl;

    std::cout << "Liste d'adjacence : " << std::endl << std::endl;

    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        std::cout << "Adjacent au sommet " << i << std::endl;
        m_sommets[i]->afficherAdjacence();
    }
    std::cout<<"Tri des degres par ordre decroissant"<<std::endl;
    IndiceDegre();
}
