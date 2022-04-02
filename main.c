/**
 * main.c
 *
 * Ce fichier contient la fonction main du projet 2
 *
 * @author: Lorenzen Pierre s203724
 * @date: 02/04/2022
 * @projet: INFO0030 Projet 2
**/
#include <stdio.h>
#include "codebarre.h"
#include "GestOpt.h"

int main(int argc, char *argv[]) {

    char nom_fichier[200];
    char sortie[120];
    char corriger[200]; 

    gestion_option(":f:c:o:",nom_fichier, "rien", sortie,corriger, argc, argv);

    printf("---------------------CHARGEMENT MATRICULE---------------------\n");
    switch(charge_matricule(nom_fichier,sortie)){
        case 0:
            printf("La création à fonctionné\n");
            break;
        case -1:
            printf("[ERREUR] Un problème au chargement des matricules est survenu\n");
            break;
        default:
            break;
    }
    printf("---------------------CORRECTION D'IMAGE---------------------\n");
    switch(corrige_codebarre(corriger,sortie)){
        case 0:
            printf("La correction à fonctionné\n");
            break;
        case -1:
            printf("[ERREUR] Un problème au chargement de l'image\n");
            break;
        case -2:
            printf("[ERREUR] Trop d'erreur dans l'image\n");
            break;
        default:
            break;
    }
}