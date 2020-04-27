#include <iostream>
#include <fstream>

#include "Graphe.h"


#include "svgfile.h"

int main()
{
    Graphe a;
    Svgfile svgout;

    a.dessinerSVG(svgout);
    a.afficher();

    return 0;
}
