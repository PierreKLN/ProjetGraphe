#include <iostream>
#include <fstream>

#include "Graphe.h"

#include "svgfile.h"

int main()
{
    Graphe a;
    Svgfile svgout;

    a.dessinerSVG(svgout);

    return 0;
}
