#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Graphe.h"
#include "Sommet.h"
#include "Arrete.h"

#include "svgfile.h"

Graphe::Graphe()
{
    std::ifstream fichier ("graphe2.txt");

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
    std::ofstream fichier("centraliteDegre.txt");

    ///tri de monsieur Fercoq utilisé lors du tp1
    std::sort(m_sommets.begin(), m_sommets.end(), [](Sommet* s1, Sommet* s2)
    {
        return s1->getDegre() > s2->getDegre();
    });

    for (size_t i =0; i<m_sommets.size(); ++i)
    {
        std::cout<<m_sommets[i]->getDegre()<<std::endl;
    }

    if(fichier)
    {
        fichier<<"Tri par ordre de degres"<<std::endl<<std::endl;
        for (size_t i =0; i<m_sommets.size(); ++i)
        {

            fichier<<"Indice sommet "<<m_sommets[i]->getNom()<<": "<<m_sommets[i]->getIndice()
            <<" et de degre "<<m_sommets[i]->getDegre()<<std::endl;
        }
    }
    else
        std::cout<<"ERREUR"<<std::endl;
}

void Graphe::vecteurPropre()
{
    std::vector<float> vp;
    float sommeDegreSi = 0;
    float lambda;
    std::vector<float> centraliteVecteur;

    std::ofstream fichier("centraliteVecteurPropre.txt");

    for(unsigned int i=0;i<m_sommets.size();i++)
    {
        vp.push_back(1); //Initialisation a 1
        vp[i] = m_sommets[i]->getAdjacence().size(); //Somme des indices de ses voisins

        sommeDegreSi += vp[i]*vp[i]; //Somme de tous les sommes vecteurs voisins
    }

    //Calcul de Lambda

    lambda = sqrt(sommeDegreSi*sommeDegreSi); //Racine carre du carre de la somme des indices des sommets

    for (unsigned int i =0;i<m_sommets.size();i++)
    {
        centraliteVecteur.push_back(vp[i]/lambda); //Valeur de la centralite vecteur propre pour chaque sommet
        std::cout << centraliteVecteur[i] << std::endl;
    }

    if(fichier)
    {
        fichier << "Etude de la centralite de vecteur propre : " << std::endl << std::endl;

        for (unsigned int i=0;i<m_sommets.size();i++)
        {
            fichier << "Sommet " << m_sommets[i]->getNom() << " d'indice " << i
            << " : Coefficient centralite VP " << centraliteVecteur[i] << std::endl;
        }
    }
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

void Graphe::dessinerSVG(Svgfile &svgout)
{
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        svgout.addDisk(m_sommets[i]->getX()*100,m_sommets[i]->getY()*100,20,"red");
        svgout.addText(m_sommets[i]->getX()*100-5,m_sommets[i]->getY()*100+5,m_sommets[i]->getNom(),"black");
    }

    for (unsigned int i=0;i<m_arretes.size();i++)
    {
        svgout.addLine(m_sommets[m_arretes[i]->getExtre1()]->getX()*100,
                       m_sommets[m_arretes[i]->getExtre1()]->getY()*100,
                       m_sommets[m_arretes[i]->getExtre2()]->getX()*100,
                       m_sommets[m_arretes[i]->getExtre2()]->getY()*100,
                       "red");
    }
}
