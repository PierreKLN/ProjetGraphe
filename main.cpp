#include <iostream>

#include "Graphe.h"
#include "Svgfile.h"

void menu();
void menuCentralite();
void menuActionCentralite();

int main()
{
    Graphe a;

    int choix;
    int choixCentralite;
    int choixActionCentralite;
    int indiceSommet;
    std::string nom;
    std::string Newnom;

    std::cout << "Bienvenue dans notre projet de theorie des graphes !" << std::endl << std::endl;

    do
    {
        menu();

        do
        {
            std::cout << "Votre choix : ";
            std::cin >> choix;
            std::cout << std::endl;
        }
        while (choix<0 || choix>5);

        switch (choix)
        {
        case 0 :
            std::cout << "Vous avez quitte le programme ! " << std::endl << std::endl;
            break;

        case 1 :
            system("cls");
            std::cout << "Entrez le nom du fichier que vous souhaitez charger : ";
            std::cin >> nom;
            std::cout << std::endl;
            a.remplirGraphe(nom);
            break;

        case 2 :
            system("cls");
            std::cout << "Entrez le nom du fichier contenant les ponderations : ";
            std::cin >> nom;
            std::cout << std::endl;
            a.lirePoids(nom);
            break;

        case 3 :
            system("cls");
            std::cout << "Calculer, afficher et sauvegarder les differents indices de centralitee : " << std::endl << std::endl;
            menuCentralite();
            do
            {
                std::cout << "Quel indice de centralite voulez vous etudier : ";
                std::cin >> choixCentralite;
                std::cout << std::endl;
            }
            while (choixCentralite<1 || choixCentralite>5);

            switch (choixCentralite)
            {
            case 1 :
                system("cls");
                menuActionCentralite();
                do
                {
                    std::cout << "Que souhaitez vous faire : ";
                    std::cin >> choixActionCentralite;
                    std::cout << std::endl;
                }
                while (choixActionCentralite<1 || choixActionCentralite>3);

                switch(choixActionCentralite)
                {
                case 1 :
                    system("cls");
                    a.afficherCentraliteDegre();
                    break;

                case 2 :
                    system("cls");
                    a.dessinerSVGDegre();
                    break;

                case 3 :
                    std::cout << "Vos indices de centralite de degre ont ete sauvegardes dans le fichier \"centraliteDegre.txt\" " << std::endl << std::endl;
                    a.sauvegardeCentraliteDegre();
                    break;
                }
                break;

            case 2 :
                system("cls");
                menuActionCentralite();
                do
                {
                    std::cout << "Que souhaitez vous faire : ";
                    std::cin >> choixActionCentralite;
                    std::cout << std::endl;
                }
                while (choixActionCentralite<1 || choixActionCentralite>3);

                switch(choixActionCentralite)
                {
                case 1 :
                    system("cls");
                    a.afficherCentraliteVecteurPropre();
                    break;

                case 2 :
                    system("cls");
                    a.dessinerSVGVecteur();
                    break;

                case 3 :
                    std::cout << "Vos indices de centralite de degre ont ete sauvegardes dans le fichier \"centraliteVecteurPropre.txt\" " << std::endl << std::endl;
                    a.sauvegardeCentraliteVecteurPropre();
                    break;
                }
                break;

            case 3 :
                system("cls");
                menuActionCentralite();
                do
                {
                    std::cout << "Que souhaitez vous faire : ";
                    std::cin >> choixActionCentralite;
                    std::cout << std::endl;
                }
                while (choixActionCentralite<1 || choixActionCentralite>3);

                switch(choixActionCentralite)
                {
                case 1 :
                    system("cls");
                    a.afficherCentraliteProximite();
                    break;

                case 2 :
                    system("cls");
                    a.dessinerSVGProximite();
                    break;

                case 3 :
                    std::cout << "Vos indices de centralite de degre ont ete sauvegardes dans le fichier \"centraliteProximite.txt\" " << std::endl << std::endl;
                    a.sauvegardeCentraliteProximite();
                    system("cls");
                    break;
                }
                break;

            case 4 :
                system("cls");
                menuActionCentralite();
                do
                {
                    std::cout << "Que souhaitez vous faire : ";
                    std::cin >> choixActionCentralite;
                    std::cout << std::endl;
                }
                while (choixActionCentralite<1 || choixActionCentralite>3);
                switch(choixActionCentralite)
                {
                case 1 :
                    system("cls");
                    std::cout<<"Sommet pour lequel vous voulez voir la centralité d'intermediarité : "<<std::endl;
                    std::cin>>indiceSommet;
                    a.afficherCentraliteIntermediarite(indiceSommet);
                    break;

                case 2 :
                    a.dessinerSVG();
                    break;

                case 3 :
                    a.sauvegardeCentraliteIntermediarite();
                    break;
                }
                break;
            }
            break;

        case 4 :
            a.vulnerabilite();
            std::cout << std::endl << std::endl;
            break;

        case 5 :
            std::cout << "Entrez le nom du fichier contenant les ponderations : ";
            std::cin >> Newnom;
            std::cout << std::endl;
            a.lireNewPoids(Newnom);
            break;
        }


    }
    while (choix!=0);

    return 0;
}

void menu()
{
    std::cout << "Menu : " << std::endl << std::endl;

    std::cout << "0) Quitter le programme" << std::endl;
    std::cout << "1) Charger un graphe (en entrant le nom du fichier)" << std::endl;
    std::cout << "2) Charger le systeme de ponderation initiale (en entrant le nom du fichier)" << std::endl;
    std::cout << "3) Gestion des indices de centralites (calculs, affichages, sauvergardes)" << std::endl;
    std::cout << "4) Test de la vulnerabilite" << std::endl;
    std::cout << "5) Changement du fichier de ponderation"<<std::endl<<std::endl;
}

void menuCentralite()
{
    std::cout << "1) Centralite de degre" << std::endl;
    std::cout << "2) Centralite de vecteur propre" << std::endl;
    std::cout << "3) Centralite de proximite" << std::endl;
    std::cout << "4) Centralite d'intermediarite" << std::endl << std::endl;
}

void menuActionCentralite()
{
    std::cout << "1) Afficher en console" << std::endl;
    std::cout << "2) Afficher dans un fichier SVG" << std::endl;
    std::cout << "3) Sauvegarde" << std::endl << std::endl;
}
