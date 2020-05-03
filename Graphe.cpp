#include <iostream>
#include <fstream>
#include<algorithm>
#include <queue>
#include <list>

#include "Graphe.h"

#define MAX 999
///constructeur par défaut
Graphe::Graphe()
{

}
///detrcuteur pour chaque arets et chaque sommet de graphe
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
///methode pour charger le grapge, qui recoit le nom du fichier en parametre
void Graphe::remplirGraphe(std::string nom)
{
    std::ifstream fichier(nom);

    if (fichier)
    {
        fichier >> m_orientation;
        fichier >> m_ordre;

        for (int i=0; i<m_ordre; i++)
        {
            ///creation d'un nouveau sommet a chaque tour de boucle
            Sommet *nouveau;
            nouveau = new Sommet;

            int indice;
            std::string nom;
            int x;
            int y;
            ///en lisant le fichier, on construit petit a petit les caracteritiques des sommets
            fichier >> indice;
            nouveau->setIndice(indice);
            fichier >> nom;
            nouveau->setNom(nom);
            fichier >> x;
            nouveau->setX(x);
            fichier >> y;
            nouveau->setY(y);
            ///on ajoute le nouveau sommet dans le tableau de sommet de graphe
            m_sommets.push_back(nouveau);
        }

        fichier >> m_taille;

        for (int i=0; i<m_taille; i++)
        {
            ///creation d'une nouvelle arrete
            Arete *nouvelle;
            nouvelle = new Arete;

            int indice;
            int ext1;
            int ext2;
            ///etape similaire que pour les sommets
            fichier >> indice;
            nouvelle->setIndice(indice);
            fichier >> ext1;
            nouvelle->setExt1(ext1);
            fichier >> ext2;
            nouvelle->setExt2(ext2);
            ///on fait la meme chose encore que pour les sommets
            m_aretes.push_back(nouvelle);
        }

    }
    else
        std::cout << "Erreur ouverture fichier" << std::endl << std::endl;
}
///methode pour lire le poids dans le fichier de pois a part
void Graphe::lirePoids(std::string nom)
{
    std::ifstream fichier(nom);
    std::vector<int> stockPoids;
    int taille;

    if (fichier)
    {
        fichier>>taille;
        for (unsigned int i=0; i<m_aretes.size(); i++)
        {
            int indice, poids;
            fichier >>indice>> poids;
            ///apres avoir lu le poids on le push back dans un vecteur temporaire de poids
            stockPoids.push_back(poids);
        }
    }
    else
        std::cout << "Erreur";
///double boucle qui permet de parcourir l'ensemble des sommets et des arretes
///puis en comparant les indices et extremites va permettre de remplir le tableau d'adjacence
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
    ///remplis le tableau de poids dans arretes
    for (unsigned int i=0; i<m_aretes.size(); i++)
    {
        m_aretes[i]->setPoids(stockPoids[i]);
    }
}
///methode exactement similaire a lire poids
///mais on en utilise une nouvelle pour pouvoir chager le nouveau fichier correctement
void Graphe::lireNewPoids(std::string nom)
{
    std::ifstream fichier(nom);
    std::vector<int> stockPoids;
    int taille;

    if (fichier)
    {
        fichier>>taille;
        for (unsigned int i=0; i<m_aretes.size(); i++)
        {
            int indice, poids;
            fichier >>indice>> poids;
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
///methode pour trouver le prochain sommet le plus proche
int Graphe::getNextSommet()
{
    ///distance mini tout d'abord initialisé au maximum
    int minim = MAX;
    int nextSommet = 0;
    std::vector<Sommet*>::iterator i;
    ///on parcours la taille de m_sommets
    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        ///on fait le tri dans le tableau pour trouver la plus petite longueur parmis les sommets non visité
        if(m_sommets[i]->getLongueur() < minim && m_sommets[i]->getVisite() == 0)
        {
            ///prochain sommet prends la valeur du sommet au quel on s'est arrete une fois rentré dans le if
            nextSommet = i;
            ///et mini prends donc la nouvelle valeur, au fur et a mesure on trouvera au final la plus petite longueur
            minim = m_sommets[i]->getLongueur();
        }
    }
    ///on retourne le prochain sommet auquel on va se rendre
    return nextSommet;
}
///methode qui recoit en parametre deux sommets, regarde l'arete qu'ils ont en communs puis retourne le poids de cette derniere
int Graphe::retournePoids(int a, int b)
{
    int poids = 0;

    for (unsigned int j=0; j<m_aretes.size(); j++)
    {
        ///test pour verifier si les indices des sommets et les extremites des aretes concordent
        if (m_sommets[a]->getIndice() == m_aretes[j]->getExt1() && m_sommets[b]->getIndice() == m_aretes[j]->getExt2())
        {
            poids = m_aretes[j]->getPoids();
        }
        ///test pour verifier si les indices des sommets et les extremites des aretes concordent
        if (m_sommets[b]->getIndice() == m_aretes[j]->getExt1() && m_sommets[a]->getIndice() == m_aretes[j]->getExt2())
        {
            poids = m_aretes[j]->getPoids();
        }
    }

    return poids;
}
///graphe pour initialiser l'algo de dijkstra qui prend en parametre le debut et la fin
void Graphe::initDijkstra(unsigned int debut, unsigned int fin)
{
    ///on met les diffrents de parametres des sommets au stade initial pour pouvoir recommencer dijkstra
    for (size_t i=0; i<m_sommets.size(); ++i)
    {
        m_sommets[i]->setVisite(0);
        m_sommets[i]->setLongueur(0);
        m_sommets[i]->setPrecedent(-1);
    }
    ///on met le sommet auquel on part a la longueur 0
    m_sommets[debut]->setLongueur(0);
    ///on parcourt en focntion de la taille de m_sommets
    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        ///si c'est different du sommet initiale
        if (i!=debut)
        {
            ///alors on fixe tous les sommets à la longueur infini(max)
            m_sommets[i]->setLongueur(MAX);
        }
    }
    ///appel de la methode pour le parcours algo dijkstra
    dijkstra(debut,fin);
}
///la methode pour le parcours
void Graphe::dijkstra(unsigned int debut, unsigned int fin)
{
    ///sommet le plus proche du sommet auquel on se situe
    int nextSommet;
    bool quitter;


    do
    {
        ///prochain sommet prends la valeur du prochain sommet grace au getter
        nextSommet = getNextSommet();
        ///on dit que le prochain sommet est visite
        m_sommets[nextSommet]->setVisite(true);

        for (int j=0; j<m_sommets[nextSommet]->getNombreVoisins(); j++)
        {
            ///si la longueur de l'adjacent est superieure a la longueur du prochain sommet plus son poids
            if(m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->getLongueur() >
                    m_sommets[nextSommet]->getLongueur() + m_sommets[nextSommet]->getPoids(j))
            {
                ///si les adjacents du prochain sommet n'ont pas ete visites
                if (m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->getVisite() == 0)
                {
                    ///l'adjacent du prochain sommet prends la valeur de la longueur plus le poids
                    m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->setLongueur(m_sommets[nextSommet]->getLongueur() + m_sommets[nextSommet]->getPoids(j));
                    ///on fixe ce somment commme le precedent de ce sommet
                    m_sommets[m_sommets[nextSommet]->getIndiceAdjacence(j)]->setPrecedent(nextSommet);
                }
            }
        }

        quitter=true;

        for(size_t i=0; i<m_sommets.size(); ++i)
        {
            ///tant que tous les sommets n'ont pas ete visite on continue la boucle du do while
            if(m_sommets[i]->getVisite()==0)
            {
                quitter=false;
            }
        }
    }
    while(!quitter);

    ///permet d'afficher le parcours de dijktra
    afficherDijkstra(fin);
}
///methode pour afficher le parcours de dijkstra et compter les poids presents sur les differents chemins
void Graphe::afficherDijkstra(unsigned int sommet)
{
    double poidsTotal = 0;
    int copieFin = sommet;

    std::vector<double> compteur;

    do
    {
        ///on affiche l'indice du somet actuel
        std::cout<<m_sommets[sommet]->getIndice()<<"<---";
        ///sommet prends la valeur du sommet precedet a ce dernier
        sommet = m_sommets[sommet]->getPrecedent();
        ///on ajoute les poids des arretes sur les plus courts chemins dans le tableau compteur
        compteur.push_back(retournePoids(m_sommets[copieFin]->getIndice(),m_sommets[copieFin]->getPrecedent()));

        ///comme pour sommet, copiefin prends la valeur du predecesseur de copiefin actuel
        copieFin = m_sommets[copieFin]->getPrecedent();



    }
    while((m_sommets[sommet]->getPrecedent()!=-1));///tant qu'il existe des predecesseur
    ///on affiche le dernier sommet
    std::cout<<m_sommets[sommet]->getIndice()<<std::endl;
    ///poids total prend la valeur de tous les poids present sur plusieurs plus court chemin
    for (unsigned int i=0; i<compteur.size(); i++)
    {
        poidsTotal += compteur[i];
    }
    ///pour tous les plus court chemin au depart de chaque sommet on ajoute poidstoal dans m_compteur
    m_compteur.push_back(poidsTotal);




}
///methode pour afficher la centralité de degre
void Graphe::afficherCentraliteDegre()
{
    std::cout << "Indice de centralite de degre : " << std::endl << std::endl;


    for (unsigned int i =0; i<m_sommets.size(); ++i)
    {
        ///afficher l'indice de degre revient a afficher son nombre de voisins
        std::cout << "Indice du sommet " << m_sommets[i]->getNom() << " : "<< m_sommets[i]->getIndice() << " de degre " << m_sommets[i]->getNombreVoisins() << std::endl;
    }

    std::cout << std::endl << "Indices de centralite de degre normalise (division par n-1)" << std::endl << std::endl;

    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        ///pour afficher l'indice de degre normalise il suffit de diviser par n-1 avec n, le nombre de sommets du graphe
        std::cout << "Indice du sommet " << m_sommets[i]->getNom() << " : "<< m_sommets[i]->getIndice() << " de norme " << (m_sommets[i]->getNombreVoisins())/(m_sommets.size()-1) << std::endl;
    }
}
///methode pour afficher la centralite de vecteur propre
void Graphe::afficherCentraliteVecteurPropre()
{
    std::cout << "Affichage de l'indice de centralite de vecteur propre : " << std::endl << std::endl;

    std::vector<float> vp;
    float sommeDegreSi = 0;
    float lambda;
    std::vector<float> centraliteVecteur;

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
}
///methode affichage indice de proximité
void Graphe::afficherCentraliteProximite()
{
    std::cout << "Affichage de l'indice de centralite de proximite" << std::endl << std::endl;

    double somme;
    double indiceProximite=0;

    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "Sommet de depart " << i << std::endl << std::endl;

        for (unsigned int j=0; j<m_sommets.size(); ++j)
        {
            if(i!=j)
                initDijkstra(i,j);///permet de faire dijkstra pour chaque sommet du graphe
        }

        for (unsigned int i=0; i<m_compteur.size(); i++)
        {
            somme += m_compteur[i];///somme prends la valeur de chaque poids total d'un chemin pour obtenir le poids total de tous les chemins d'un
            ///sommet i a un sommet j
        }

        std::cout << "Somme des longueurs de tous les plus courts chemins " << somme << std::endl;

        ///l'indice de proximite est egal à k'inverse de la somme des poids sur les plus courts chemins
        indiceProximite = 1/somme;
        std::cout << "Indice de proximite pour le sommet " << i << " : " << indiceProximite << std::endl;
        ///l'indice de proximite normalisé est l'indice de proximité multiplié par n-1
        indiceProximite = (m_sommets.size()-1)*indiceProximite;
        std::cout<< "Indice de proximite normalise pour le sommet " << i << " : " << indiceProximite << std::endl;
        std::cout<< std::endl;

        ///remet le compteur a zero et la somme a zero pour ne pas fausser les sommes sur les autres sommets
        for (unsigned int i=0; i<m_compteur.size(); i++)
        {
            m_compteur[i] = 0;
            somme = 0;
        }
        std::cout << std::endl;
    }
}

void Graphe::afficherCentraliteIntermediarite(int IndiceSommet)
{
    int somme2=0;
    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "Sommet de depart " << i << std::endl << std::endl;

        for (unsigned int j=0; j<m_sommets.size(); ++j)
        {
            if(i!=j)
                NewinitDijkstra(i,j, IndiceSommet);
        }
        for (unsigned int j=0; j<m_stockSommet.size(); j++)
        {
            somme2+=m_stockSommet[j];
        }

        std::cout << "Nombre d'apparence du sommet 2 sur le chemin le plus court est " << somme2 << std::endl;

        for (unsigned int i=0; i<m_stockSommet.size(); i++)
        {
            m_stockSommet[i] = 0;
            somme2 = 0;
        }
        std::cout << std::endl;

//int IndiceInter=0;
        /*{
                std::cout << "Sommet de depart " << i << std::endl << std::endl;

                for (unsigned int j=0; j<m_sommets.size(); ++j)
                {
                    if(i!=j)
                        initDijkstra(i,j);
                }*/
//        initDijkstra(0,1);
//        initDijkstra(0,3);
//        initDijkstra(0,4);
//        initDijkstra(0,2);
        /*     for (size_t i=0; i<m_stockSommet.size(); ++i)
        {
            m_stockSommet[i]=0;
        }
            initDijkstra(1,0);
            initDijkstra(1,3);
            initDijkstra(1,4);
            initDijkstra(1,2);*/
        /*initDijkstra(3,0);
        initDijkstra(3,1);
        initDijkstra(3,2);
        initDijkstra(3,4);*/

        /*for (unsigned int i=0; i<m_sommets.size(); ++i)
        {
        IndiceInter=0;
            for(size_t k=0; k<m_stockSommet.size(); ++k)
            {
                if(m_sommets[i]->getIndice()==m_stockSommet[k]&&m_sommets[i]->getPrecedent()!=-1)
                {
                    IndiceInter++;
                    m_sommets[i]->setInter(IndiceInter);
                }
            }

            std::cout<<m_sommets[i]->getInter()<<std::endl;
        }*/
        //std::cout<<IndiceInter<<std::endl;
        /*for(size_t i=0; i<m_sommets.size(); ++i)
        {
          for(size_t k=0; k<m_stockSommet.size(); ++k)
          {
              if(m_sommets[i]->getIndice()==m_stockSommet[k]&&m_sommets[i]->getPrecedent()!=-1)
                         IndiceInter++;
          }
        }
        std::cout<<IndiceInter;
        //std::cout<<IndiceInter<<std::endl;
        //std::list<int> indince;

        //indice.insert(la connerie oauis);
        //indince.count(2)//balance le i;*/

    }
}


///methode de sauvegarde
void Graphe::sauvegardeCentraliteDegre()
{
    ///ouverture du fichier
    std::ofstream fichier("centraliteDegre.txt");
    ///on verifie que le sommet est bien effectue
    if(fichier)
    {
        fichier<<"Tri par ordre de degres"<<std::endl<<std::endl;

        for (unsigned int i =0; i<m_sommets.size(); ++i)
        {
            ///puis on ecrit toutes les informations à l'interieur
            fichier << "Indice du sommet " << m_sommets[i]->getNom() << " : "<< m_sommets[i]->getIndice()
                    << " de degre " << m_sommets[i]->getNombreVoisins() << std::endl;
        }

        fichier << std::endl << "Indice de centralite des degres normalise (division les degres par n-1)"
                << std::endl << std::endl;

        for (unsigned int i=0; i<m_sommets.size(); i++)
        {
            ///on fait pareil avec la centralité de degre normalisé
            fichier << "Indice du sommet " << m_sommets[i]->getNom() << " : "<< m_sommets[i]->getIndice()
                    << " de norme " << (m_sommets[i]->getNombreVoisins())/(m_sommets.size()-1) << std::endl;
        }
    }
    else
        std::cout<<"ERREUR"<<std::endl;
}
///methode sauvegarde tout a fait similaire a celle precedente,
///on note les informations dans un fichier
void Graphe::sauvegardeCentraliteVecteurPropre()
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
///troisieme methode de sauevgarde similaire aux deux precedentes
void Graphe::sauvegardeCentraliteProximite()
{
    double somme;

    double indiceProximite = 0;

    std::ofstream fichier("centraliteProximite.txt");

    fichier << "Etude de la centralite de proximite " << std::endl << std::endl;

    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        for (unsigned int j=0; j<m_sommets.size(); ++j)
        {
            if(i!=j)
            {
                initDijkstra(i,j);
            }
        }

        for (unsigned int i=0; i<m_compteur.size(); i++)
        {
            somme += m_compteur[i];
        }

        indiceProximite = 1/somme;
        fichier << "Indice de proximite pour le sommet " << i << " : " << indiceProximite << std::endl;
        indiceProximite = (m_sommets.size()-1)*indiceProximite;
        fichier << "Indice de proximite normalise pour le sommet " << i << " : " << indiceProximite << std::endl;
        fichier << std::endl;

        for (unsigned int i=0; i<m_compteur.size(); i++)
        {
            m_compteur[i] = 0;
            somme = 0;
        }
    }
}

void Graphe::sauvegardeCentraliteIntermediarite()
{








}
///methode permettant la supression d'arrete
void Graphe::SuppressionArete()
{
    std::vector<int> indiceArete;
    unsigned int nb =0;
    int indice;
    ///choix du nombre d'arete à supprimer
    do
    {
        std::cout<<"Combien d'aretes voulez vous supprimer ?"<<std::endl;
        std::cin>>nb;
    }
    while(nb<=0 || nb>m_aretes.size());

    ///puis choix de l'arete que l'on souhaite supprimer
    for (unsigned int i =0; i<nb; ++i)
    {
        std::cout<<"Choisir l'arete a supprimer : "<<std::endl;
        std::cin>>indice;
        indiceArete.push_back(indice);
    }
    ///effacage des arretes que l'on a choisit de supprimer
    for (size_t i=0; i<indiceArete.size(); ++i)
    {
        m_aretes.erase(m_aretes.begin()+indiceArete[i]);
    }
    ///on met a jour les tableaux contenant les nouvelles adjacences apres la suppression des aretes
    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        for (unsigned int j=0; j<m_aretes.size(); j++)
        {
            if (m_sommets[i]->getIndice() == m_aretes[j]->getExt1())
            {
                m_sommets[i]->setNewAdja(m_aretes[j]->getExt2());
            }
            if (m_sommets[i]->getIndice() == m_aretes[j]->getExt2())
            {
                m_sommets[i]->setNewAdja(m_aretes[j]->getExt1());
            }
        }
    }
}
///methode pour observer l'impact de ces suppressions sur les differents indices de centralité
void Graphe::vulnerabilite()
{
///pour la comparaison on appel les methodes codées precedemment et on les compares en codant les methodes avec le nouveau ombre de voisins et d'adjacence

    std::vector<float> vp;
    float sommeDegreSi = 0;
    float lambda;
    std::vector<float> centraliteVecteur;

    SuppressionArete();
    std::cout<<"Classement indice degre avant supression d'une arrete: "<<std::endl;
    afficherCentraliteDegre();
    std::cout<<"Classement indice degre apres supression d'une arrete: "<<std::endl;
    for(size_t i=0; i<m_sommets.size(); ++i)
    {
        std::cout<<m_sommets[i]->getNewNombreVoisins()<<std::endl;
    }
    std::cout<<"Centralite vecteur propre avant supression d'une arrete: "<<std::endl;
    afficherCentraliteVecteurPropre();
    std::cout<<"Centralite vecteur propre apres supression d'une arrete: "<<std::endl;
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        vp.push_back(1); //Initialisation a 1
        vp[i] = m_sommets[i]->getNewNombreVoisins(); //Somme des indices de ses voisins

        sommeDegreSi += (vp[i]*vp[i]); //Somme des carre des voisins des sommets
    }

    //Calcul de Lambda

    lambda = sqrt(sommeDegreSi); //Racine carre du carre de la somme des voisins des sommets

    for (unsigned int i =0; i<m_sommets.size(); i++)
    {
        centraliteVecteur.push_back(vp[i]/lambda); //Valeur de la centralite vecteur propre pour chaque sommet
        std::cout << centraliteVecteur[i] << std::endl;
    }
    int depart, depart2;
    std::cout<<"Saisir le sommet de depart du BFS pour trouver les composantes connexes de ce sommet :"<<std::endl;
    std::cin>>depart;
    std::cout<<std::endl;
    parcoursBFS(depart);

    for(size_t i=0; i<m_sommets.size(); ++i)
        m_sommets[i]->setCouleur(0);
    std::cout<<"Saisir le sommet de depart du BFS pour trouver les nouvelles composantes connexes de ce sommet apres suppression :"<<std::endl;
    std::cin>>depart2;
    std::queue <Sommet*> file; ///On créé une file qui va contenir notre parcours BFS
    file.push(m_sommets[depart2]);///On rentre le premier sommet dans notre file
    m_sommets[depart2]->setCouleur(1);
    while(!file.empty())/// Tant que la file n'est pas vide
    {
        for(int i=0; i<file.front()->getNewNombreVoisins(); i++)///boucle qui regarde le degre de chaque sommet en tete de file
        {
            if(m_sommets[file.front()->getNewIndiceAdja(i)]->getCouleur()==0)///Si l'ajacent de du sommet en question n'est pas découvert
            {
                file.push(m_sommets[file.front()->getNewIndiceAdja(i)]);/// On ajoute alors dans la file le numero du sommet adjacent s
                m_sommets[file.front()->getNewIndiceAdja(i)]->setCouleur(1);///Ces sommets S' sont alors découverts on leurs met la couleur gris
                file.front()->ajouterSuivant(m_sommets[file.front()->getNewIndiceAdja(i)]->getIndice());///On ajoute leurs noms à la file
                m_sommets[file.front()->getNewIndiceAdja(i)]->setPrecedent(file.front()->getIndice()); ///On note que s est le predecesseur des S'

            }
        }

        afficherCompoConnexe(file.front());///afficher la chaine a partir du front de la file
        file.front()->setCouleur(2);/// Apres qu'on est découvert tous ses sommets adjacents on le marque noir
        file.pop();///on l'enleve de la file
    }


    // newAfficherCentraliteProxi();



}
///methode pour dessiner en SVG
void Graphe::dessinerSVG()
{
    Svgfile svgout;

    for (unsigned int i=0; i<m_aretes.size(); i++)
    {
        ///si les coordonées sont inferrieurs a 10 dans le fichiers, on les multplies pour pouvoir placer les grpahes correctement
        if(m_sommets[i]->getX()<10 && m_sommets[i]->getY()<10)
        {
            svgout.addLine(m_sommets[m_aretes[i]->getExt1()]->getX()*190,
                           m_sommets[m_aretes[i]->getExt1()]->getY()*190,
                           m_sommets[m_aretes[i]->getExt2()]->getX()*190,
                           m_sommets[m_aretes[i]->getExt2()]->getY()*190,
                           "orange");
        }
    }
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        ///meme conditions pour placer les sommets et avoir la place de dessiner le graphe
        if(m_sommets[i]->getX()<10 && m_sommets[i]->getY()<10)
        {
            svgout.addDisk(m_sommets[i]->getX()*190,m_sommets[i]->getY()*190,20,"red");
            svgout.addCircle(m_sommets[i]->getX()*190,m_sommets[i]->getY()*190,21, 2, "black");
            svgout.addText(m_sommets[i]->getX()*190-5,m_sommets[i]->getY()*190+5,m_sommets[i]->getNom(),"black");
            svgout.addText(m_sommets[i]->getX()*190-15,m_sommets[i]->getY()*190+15,m_sommets[i]->getIndice(),"black");
            svgout.addText(m_sommets[i]->getX()*190-40,m_sommets[i]->getY()*190+40,m_sommets[i]->getNombreVoisins(),"black");
        }
    }
    for (unsigned int i=0; i<m_aretes.size(); i++)
    {
        ///a l'inverse si les coordonées sont superieurs a 10, on multiplie par un coefficient inferieur
        if(m_sommets[i]->getX()>=10 && m_sommets[i]->getY()>=10)
        {
            svgout.addLine(m_sommets[m_aretes[i]->getExt1()]->getX()*20,
                           m_sommets[m_aretes[i]->getExt1()]->getY()*20,
                           m_sommets[m_aretes[i]->getExt2()]->getX()*20,
                           m_sommets[m_aretes[i]->getExt2()]->getY()*20,
                           "orange");
        }
    }
    for(unsigned int i=0; i<m_sommets.size(); i++)
    {
        ///pareil pour placer les sommets
        if(m_sommets[i]->getX()>=10 && m_sommets[i]->getY()>=10)
        {
            svgout.addDisk(m_sommets[i]->getX()*20,m_sommets[i]->getY()*20,20,"yellow");
            svgout.addCircle(m_sommets[i]->getX()*20,m_sommets[i]->getY()*20,21, 2, "black");
            svgout.addText(m_sommets[i]->getX()*20-5,m_sommets[i]->getY()*20+5,m_sommets[i]->getNom(),"black");
            svgout.addText(m_sommets[i]->getX()*20-13,m_sommets[i]->getY()*20+15,m_sommets[i]->getIndice(),"black");
            svgout.addText(10,m_sommets[i]->getY()*10+15,"Centralite de degre du sommet ","black");
            // svgout.addText(160,160,i,"black");
            //svgout.addText(162,m_sommets[i]->getY()*10-15,m_sommets[i]->getNombreVoisins(),"black");
        }
    }
}
///methodes pour afficher tous les sommets et toutes les artes du grpahe
void Graphe::afficherGraphe()
{
    for (unsigned int i=0; i<m_sommets.size(); i++)
    {
        m_sommets[i]->afficherSommet();
    }

    for (unsigned int i=0; i<m_aretes.size(); i++)
    {
        m_aretes[i]->afficherArete();
    }
}

///methode pour stocker les differents compo connexe et les afficher ensuite
///il recoit un sommet en parametre
void Graphe::afficherCompoConnexe(Sommet *sommet)
{
    std::vector<int> stockCC;
    if(sommet->getPrecedent()!=-1)
    {
        stockCC.push_back(sommet->getIndice());
    }

    for(size_t i=0; i<stockCC.size(); ++i)
        std::cout<<stockCC[i]<<" ";

    std::cout<<std::endl;
}
///bfs qui grace a son parcours en largeur, va permetre de conniatre les differents composantes connexes
void Graphe::parcoursBFS(int depart)
{
    std::queue <Sommet*> file; ///On créait une file qui va contenir notre parcours BFS
    file.push(m_sommets[depart]);///On rentre le premier sommet dans notre file
    m_sommets[depart]->setCouleur(1);
    while(!file.empty())/// Tant que la file n'est pas vide
    {
        for(int i=0; i<file.front()->getNombreVoisins(); i++)///boucle qui regarde le degre de chaque sommet en tete de file
        {
            if(m_sommets[file.front()->getIndiceAdjacence(i)]->getCouleur()==0)///Si l'ajacent de du sommet en question n'est pas découvert
            {
                file.push(m_sommets[file.front()->getIndiceAdjacence(i)]);/// On ajoute alors dans la file le numero du sommet adjacent s
                m_sommets[file.front()->getIndiceAdjacence(i)]->setCouleur(1);///Ces sommets S' sont alors découverts on leurs met la couleur gris
                file.front()->ajouterSuivant(m_sommets[file.front()->getIndiceAdjacence(i)]->getIndice());///On ajoute leurs noms à la file
                m_sommets[file.front()->getIndiceAdjacence(i)]->setPrecedent(file.front()->getIndice()); ///On note que s est le predecesseur des S'

            }
        }

        afficherCompoConnexe(file.front());///afficher la chaine a partir du front de la file
        file.front()->setCouleur(2);/// Apres qu'on est découvert tous ses sommets adjacents on le marque noir
        file.pop();///on l'enleve de la file
    }

}
///nouvelle initialisation allant de paire avec le nouveau dijkstra
void Graphe::NewinitDijkstra(unsigned int debut, unsigned int fin, int indiceSommet)
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

    Newdijkstra(debut,fin, indiceSommet);
}
///nouveau dijkstra pour relaiser l'indice d'intermediarité et ne pas interferer avec le dijkstra initial
void Graphe::Newdijkstra(unsigned int debut, unsigned int fin, int indiceSommet)
{
    int nextSommet;
    bool quitter;
    std::list<int> indice;
    int copieFin=fin;
    int mycount=0;

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




    NewafficherDijkstra(fin, indiceSommet);
}
void Graphe::NewafficherDijkstra(unsigned int sommet, int indiceSommet)
{
    double poidsTotal = 0;
    int mycount =0;
    int copieFin = sommet;

    std::vector<double> compteur;
    std::list<int> indice;

    do
    {
        ///on affiche l'indice du somet actuel
        std::cout<<m_sommets[sommet]->getIndice()<<"<---";
        ///sommet prends la valeur du sommet precedet a ce dernier
        sommet = m_sommets[sommet]->getPrecedent();
        ///on ajoute les poids des arretes sur les plus courts chemins dans le tableau compteur
        compteur.push_back(retournePoids(m_sommets[copieFin]->getIndice(),m_sommets[copieFin]->getPrecedent()));


          indice.insert(indice.begin(), m_sommets[copieFin]->getPrecedent());
        ///comme pour sommet, copiefin prends la valeur du predecesseur de copiefin actuel
        copieFin = m_sommets[copieFin]->getPrecedent();
        mycount = std::count (indice.begin(), indice.end(), indiceSommet);


    }
    while((m_sommets[sommet]->getPrecedent()!=-1));///tant qu'il existe des predecesseur
    ///on affiche le dernier sommet
    std::cout<<m_sommets[sommet]->getIndice()<<std::endl;

    m_stockSommet.push_back(mycount);




}



