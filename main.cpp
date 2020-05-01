#include <iostream>

#include "Graphe.h"
#include "Svgfile.h"

void menu();

int main()
{
    //int choix;
/*
    do
    {
        menu();

        do
        {
            std::cout << "Votre choix : ";
            std::cin >> choix;
            std::cout << std::endl;
        } while (choix<0 || choix>4);

        switch (choix)
        {
            case 0 :
                std::cout << "Vous avez quitte le programme ! " << std::endl << std::endl;
                break;

            case 1 :
                std::string nom;
                std::cout << "Entrez le nom du fichier que vous souhaitez charger : ";
                std::cin >> nom;
                break;

        }
    } while (choix!=0);

*/

    Graphe a("graphe.txt");
    Svgfile svgout;

    //a.dessinerSVG(svgout);

    //a.test();


    //a.centraliteDijkstra();
      a.centraliteIntermdiariteSimple(2);
    //a.centraliteDegre();
    //a.afficherCentraliteDegre();
    //a.centraliteVecteurPropre();

    return 0;
}

void menu()
{
    std::cout << "Bienvenue dans notre projet de theorie des graphes !" << std::endl << std::endl;

    std::cout << "Notre menu : " << std::endl << std::endl;

    std::cout << "0) Quitter le programme" << std::endl;
    std::cout << "1) Charger un graphe (en entrant le nom du fichier)" << std::endl;
    std::cout << "2) Changer le systeme de ponderation (en chargeant un nouveau fichier avec les ponderations)" << std::endl;
    std::cout << "3) Gestion des indices de centralites (calculs, affichages, sauvergardes)" << std::endl;
    std::cout << "4) Test de la vulnerabilite" << std::endl << std::endl;
}


