/**
 * codebarre.c
 *
 * Ce fichier contient les définitions de types et
 * les fonctions de création de code barre au format
 * PNM.
 *
 * @author: Lorenzen Pierre s203724
 * @date: 27/02/2022
 * @projet: INFO0030 Projet 2
**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "codebarre.h"


void int_vers_binaire(int entree, unsigned n,int *sortie){
    assert(sortie !=NULL);

    for(int i=0; n>0 ;i++){
        sortie[i] = entree %2;
        entree/=2;
        n--;
    }
}//Fin int_vers_binaire()