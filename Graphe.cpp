#include <iostream>
#include <fstream>
#include<algorithm>

#include "Graphe.h"

#define MAX 999

Graphe::Graphe(std::string nom)
{
    std::ifstream fichier(nom);

    if (fichier)
    {
        fichier >> m_orientation;
        fichier >> m_ordre;

        for (int i=0; i<m_ordre; i++)
        {
            Sommet *nouveau;
            nouveau = new Sommet;

            int indice;
            std::string nom;
            int x;
            int y;

            fichier >> indice;
            nouveau->setIndice(indice);
            fichier >> nom;
            nouveau->setNom(nom);
            fichier >> x;
            nouveau->setX(x);
            fichier >> y;
            nouveau->setY(y);

            m_sommets.push_back(nouveau);
        }

        fichier >> m_taille;

        for (int i=0; i<m_taille; i++)
        {
            Arete *nouvelle;
            nouvelle = new Arete;

            int indice;
            int ext1;
            int ext2;

            fichier >> indice;
            nouvelle->setIndice(indice);
            fichier >> ext1;
            nouvelle->setExt1(ext1);
            fichier >> ext2;
            nouvelle->setExt2(ext2);

            m_aretes.push_back(nouvelle);
        }

    }
    else
        std::cout << "Erreur ouverture fichier";

    lirePoids();
}

Graphe::~Graphe()
{
    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        delete m_sommets[i];
    }
    for (unsigned int i=0; i<m_aretes.size(); i++)
    {
        delete m_aretes[i];
    }
}

void Graphe::lirePoids()
{
    std::ifstream fichier("poids.txt");
    std::vector<int> stockPoids;

    if (fichier)
    {
        for (unsigned int i=0; i<m_aretes.size(); i++)
        {
            int poids;
            fichier >> poids;
            stockPoids.push_back(poids);
        }
    }
    else
        std::cout << "Erreur";

    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        for (unsigned int j=0; j<m_aretes.size(); j++)
        {
            if (m_sommets[i]->getIndice() == m_aretes[j]->getExt1())
            {
                m_sommets[i]->setAdjacent(m_aretes[j]->getExt2());
                m_sommets[i]->setPoids(stockPoids[j]);
            }
            if (m_sommets[i]->getIndice() == m_aretes[j]->getExt2())
            {
                m_sommets[i]->setAdjacent(m_aretes[j]->getExt1());
                m_sommets[i]->setPoids(stockPoids[j]);
            }
        }
    }
    for (unsigned int i=0; i<m_aretes.size(); i++)
    {
        m_aretes[i]->setPoids(stockPoids[i]);
    }
}

int Graphe::getOrientation()
{
    return m_orientation;
}

int Graphe::getOrdre()
{
    return m_ordre;
}

int Graphe::getTaille()
{
    return m_taille;
}

void Graphe::centraliteDegre()
{
    std::ofstream fichier("centraliteDegre.txt");

    std::sort(m_sommets.begin(), m_sommets.end(), [](Sommet *s1, Sommet *s2)
    {
        return s1->getNombreVoisins() > s2->getNombreVoisins();
    });

    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        std::cout<<m_sommets[i]->getNombreVoisins()<<std::endl;
    }

    if(fichier)
    {
        fichier<<"Tri par ordre de degres"<<std::endl<<std::endl;

        for (unsigned int i =0; i<m_sommets.size(); ++i)
        {

            fichier << "Indice du sommet " << m_sommets[i]->getNom() << " : "<< m_sommets[i]->getIndice()
                    << " de degre " << m_sommets[i]->getNombreVoisins() << std::endl;
        }

        fichier << std::endl << "Indice de centralite des degres normalise (division les degres par n-1)"
                << std::endl << std::endl;

        for (unsigned int i=0; i<m_sommets.size(); i++)
        {
            fichier << "Indice du sommet " << m_sommets[i]->getNom() << " : "<< m_sommets[i]->getIndice()
                    << " de norme " << (m_sommets[i]->getNombreVoisins())/(m_sommets.size()-1) << std::endl;
        }
    }
    else
        std::cout<<"ERREUR"<<std::endl;
}

void Graphe::centraliteVecteurPropre()
{
    std::vector<float> vp;
    float sommeDegreSi = 0;
    float lambda;
    std::vector<float> centraliteVecteur;

    std::ofstream fichier("centraliteVecteurPropre.txt");

    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        vp.push_back(1); //Initialisation a 1
        vp[i] = m_sommets[i]->getNombreVoisins(); //Somme des indices de ses voisins

        sommeDegreSi += (vp[i]*vp[i]); //Somme des carre des voisins des sommets
    }

    //Calcul de Lambda

    lambda = sqrt(sommeDegreSi); //Racine carre du carre de la somme des voisins des sommets

    for (unsigned int i =0; i<m_sommets.size(); i++)
    {
        centraliteVecteur.push_back(vp[i]/lambda); //Valeur de la centralite vecteur propre pour chaque sommet
        std::cout << centraliteVecteur[i] << std::endl;
    }

    if(fichier)
    {
        fichier << "Etude de la centralite de vecteur propre : " << std::endl << std::endl;

        for (unsigned int i=0; i<m_sommets.size(); i++)
        {
            fichier << "Sommet " << m_sommets[i]->getNom() << " d'indice " << i
                    << " : Coefficient centralite VP " << centraliteVecteur[i] << std::endl;
        }
    }
}

int Graphe::getNextSommet()
{
    int minim = MAX;
    int nextSommet = 0;
    std::vector<Sommet*>::iterator i;

    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        if(m_sommets[i]->getLongueur() < minim && m_sommets[i]->getVisite() == 0)
        {
            nextSommet = i;
            minim = m_sommets[i]->getLongueur();
        }
    }

    return nextSommet;
}

void Graphe::initDijkstra(unsigned int debut, unsigned int fin)
{
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->setVisite(0);
        m_sommets[i]->setLongueur(0);
        m_sommets[i]->setPrecedent(-1);
    }

    m_sommets[debut]->setLongueur(0);

    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        if (i!=debut)
        {
            m_sommets[i]->setLongueur(MAX);
        }
    }

    dijkstra(debut,fin);
}

void Graphe::dijkstra(unsigned int debut, unsigned int fin)
{
    int nextSommet;
    bool quitter;

    do
    {
        nextSommet = getNextSommet();

        m_sommets[nextSommet]->setVisite(true);

        for (int j=0; j<m_sommets[nextSommet]->getNombreVoisins(); j++)
        {
            if(m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->getLongueur() >
                    m_sommets[nextSommet]->getLongueur() + m_sommets[nextSommet]->getPoids(j))
            {
                if (m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->getVisite() == 0)
                {
                    m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->setLongueur(m_sommets[nextSommet]->getLongueur() + m_sommets[nextSommet]->getPoids(j));

                    m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->setPrecedent(nextSommet);
                }
            }
        }

        quitter=true;

        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            if(m_sommets[i]->getVisite()==0)
            {
                quitter=false;
            }
        }

    }
    while(!quitter);

    afficherTout(fin);
}

void Graphe::afficherTout(unsigned int sommet)
{
    double poidsTotal = 0;
    int copieFin = sommet;

    std::vector<double> compteur;

    do
    {
        std::cout<<m_sommets[sommet]->getIndice()<<"<---";
        sommet = m_sommets[sommet]->getPrecedent();

        compteur.push_back(retournePoids(m_sommets[copieFin]->getIndice(),m_sommets[copieFin]->getPrecedent()));
        copieFin = m_sommets[copieFin]->getPrecedent();

    }
    while((m_sommets[sommet]->getPrecedent()!=-1));

    std::cout<<m_sommets[sommet]->getIndice()<<std::endl;

    for (unsigned int i=0; i<compteur.size(); i++)
    {
        poidsTotal += compteur[i];
    }

    m_compteur.push_back(poidsTotal);
}

void Graphe::centraliteDijkstra()
{
    double somme;

    double indiceProximite = 0;

    std::ofstream fichier("centraliteProximite.txt");

    fichier << "Etude de la centralite de proximite " << std::endl << std::endl;

    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "Sommet de depart " << i << std::endl << std::endl;

        for (unsigned int j=0; j<m_sommets.size(); ++j)
        {
            if(i!=j)
            {
                initDijkstra(i,j);
            }
        }

        for (int i=0; i<m_compteur.size(); i++)
        {
            somme += m_compteur[i];
        }

        std::cout << "Somme des longueurs de tous les plus courts chemins " << somme << std::endl;

        indiceProximite = 1/somme;
        fichier << "Indice de proximite pour le sommet " << i << " : " << indiceProximite << std::endl;
        indiceProximite = (m_sommets.size()-1)*indiceProximite;
        fichier << "Indice de proximite normalise pour le sommet " << i << " : " << indiceProximite << std::endl;
        fichier << std::endl;

        for (int i=0; i<m_compteur.size(); i++)
        {
            m_compteur[i] = 0;
            somme = 0;
        }

        std::cout << std::endl;
    }
}

void Graphe::afficherCentraliteDegre()
{
    std::cout << "Affichage de l'indice de centralite de degre : " << std::endl << std::endl;

    for (unsigned int i =0; i<m_sommets.size(); ++i)
    {
        std::cout << "Le sommet " << m_sommets[i]->getNom() << " d'indice " << m_sommets[i]->getIndice() << " possede ";
        std::cout<<m_sommets[i]->getNombreVoisins()<< " sommets adjacents" <<std::endl;
    }
}

void Graphe::afficherCentraliteVecteurPropre()
{
    std::cout << "Affichage de l'indice de centralite de vecteur propre" << std::endl << std::endl;
}

void Graphe::afficherCentraliteProximite()
{
    std::cout << "Affichage de l'indice de centralite de proximite" << std::endl << std::endl;
}

int Graphe::CalculIndice(int &courtChemin, int num)
{
    if (m_sommets[num]->getPrecedent()!=-1)
    {
        courtChemin+=retournePoids(num, m_sommets[num]->getPrecedent());
        CalculIndice(courtChemin, m_sommets[num]->getPrecedent());
    }

    return courtChemin;

}

void Graphe::dessinerSVG(Svgfile &svgout)
{
    for (unsigned int i=0; i<m_aretes.size(); i++)
    {
        svgout.addLine(m_sommets[m_aretes[i]->getExt1()]->getX()*100,
                       m_sommets[m_aretes[i]->getExt1()]->getY()*100,
                       m_sommets[m_aretes[i]->getExt2()]->getX()*100,
                       m_sommets[m_aretes[i]->getExt2()]->getY()*100,
                       "orange");
    }

    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        svgout.addDisk(m_sommets[i]->getX()*100,m_sommets[i]->getY()*100,20,"red");
        svgout.addText(m_sommets[i]->getX()*100-5,m_sommets[i]->getY()*100+5,m_sommets[i]->getNom(),"black");
    }
}

int Graphe::retournePoids(int a, int b)
{
    int poids = 0;

    for (unsigned int j=0; j<m_aretes.size(); j++)
    {
        if (m_sommets[a]->getIndice() == m_aretes[j]->getExt1() && m_sommets[b]->getIndice() == m_aretes[j]->getExt2())
        {
            poids = m_aretes[j]->getPoids();
        }
        if (m_sommets[b]->getIndice() == m_aretes[j]->getExt1() && m_sommets[a]->getIndice() == m_aretes[j]->getExt2())
        {
            poids = m_aretes[j]->getPoids();
        }
    }

    return poids;
}

void Graphe::setCompteur(double i)
{
    m_compteur.push_back(i);
}

void Graphe::centraliteIntermdiariteSimple(int indice)
{
    int centraliteInter=0;
    for (size_t i=0; i<m_sommets.size();++i)
    {
        for (size_t j=0; j<m_sommets.size(); ++j)
        {
            if(i!=j)
                initDijkstra(i,j);
        }
      if(m_sommets[indice]->getPrecedent()!=-1)
      {
          if(m_sommets[i]->getPrecedent()==m_sommets[indice]->getIndice())
                std::cout<<"test";
      }



    }
   // std::cout<<"Inter vaut : "<<centraliteInter<<std::endl;
}

void Graphe::SuppressionArete(int indice)
{
    delete m_aretes[indice];
}

void Graphe::Vulnerabilite()
{
    int indice;
    centraliteDegre();
    std::cout<<"Choisissez le numero de l'arrete à supprimer"<<std::endl;
    std::cin>>indice;
    SuppressionArete(indice);
    std::sort(m_sommets.begin(), m_sommets.end(), [](Sommet *s1, Sommet *s2)
    {
        return s1->getNombreVoisins() > s2->getNombreVoisins();
    });
    std::cout<<"Classement indice degre apres supression d'une arrete: "<<std::endl;
    for(size_t i=0; i<m_sommets.size();++i)
    {
        std::cout<<m_sommets[i]->getNombreVoisins()<<std::endl;
    }
}






