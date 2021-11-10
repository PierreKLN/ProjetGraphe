# ProjetGraphe

Projet pisicne réalisé en 5 jours en deuxième année de classe préparatoire intégrée permettant l'étude de la théorie des Graphes. 
Utilisant des .svg pour le rendu graphique.

### Implementation des algorithmes suivant: 

 * Centralité de degrés
 * Centralité de vecteur propre
 * Centralité d'intermédiarité (Theorème de Dijkstra)
 * Centralité de proximité
 
### Fonctionnalités finale du projet: 

* Charger un graphe (donc le fichier de topologie et éventuellement un fichier de pondérations) en demandant les noms de fichiers à l’utilisateur.
* Changer le système de pondérations d’un graphe (en chargeant un nouveau fichier de pondérations)
* Calculer, afficher et sauvegarder les différents indices de centralité.
* Tester la vulnérabilité du graphe en:
      1. permettant de supprimer une ou plusieurs arêtes choisies par l’utilisateur
      * testant la connexité du graphe suite à la suppression de ces arêtes
      * recalculant les indices de centralités pour les comparer avec ceux obtenus avant la suppression.
* Amélioration de l'affichage de départ en console (svg output)
* Système de couleurs permettant de discrimer les sommets en fonction de leur importance mesurée par ces indices
* Calculer les indices de centralité d’intermédiarité des arêtes et pas seulement des sommets.
