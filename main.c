#include <stdio.h>
#include "codebarre.h"
#include "GestOpt.h"

int main(int argc, char *argv[]) {

    char nom_fichier[4];
    char sortie[120]; 

    gestion_option(":f:o:",nom_fichier, "rien", sortie, argc, argv);

    switch(charge_matricule(nom_fichier,sortie)){
        case 0:
            printf("Tout à bien fonctionné\n");
            break;
        case -1:
            printf("Un problème au chargement des matricules est survenu\n");
            break;
        default:
            break;
    }
}