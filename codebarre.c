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
#include "pnm.h"

void int_vers_binaire(int entree, unsigned n,int *sortie){
    assert(sortie !=NULL);

    for(int i=0; n>0 ;i++){
        sortie[i] = entree %2;
        entree/=2;
        n--;
    }
}//Fin int_vers_binaire()

int verifie_matricule(char *entree){
    assert(entree!=NULL);

    // compte le nombre de chiffre du matricule
    unsigned compteur=0;
    for(unsigned i = 0; entree[i]!= 0;i++){

        switch(entree[i]){

            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                break;
            case '7':
                break;
            case '8':
                break;
            case '9':
                break;
            default:
                return -1;            
        }
        compteur++;
    }
    if(compteur!=7)
        return -2;
    return 0;
}//Fin int verifie_matricule()

void multiplie_matricule(PNM *image, unsigned valeur ,unsigned borneLigne, unsigned borneColonne, unsigned taille){
    assert(image!=NULL);
    
    unsigned finL = borneLigne + taille;
    unsigned finC = borneColonne + taille;
    for(unsigned i = borneLigne; i< finL;i++){

        for(unsigned j = borneColonne;j< finC;j++){
            defini_matrice(image,i,j,valeur);
        }
    }
}

int charge_matricule(char* fichier){
    assert(fichier!=NULL);

    FILE *fp;
    fp = fopen(fichier,"r");
   
    if(fp==NULL)
        return -1;

    char *tmp;
    int matriculeDec;
    int matriculeBi[36];
    PNM *codebarre = cree_image(700,700,1,"","PBM");
    
    for(;!feof(fp);){
        // Vérification de la validité du matricule
        if(fscanf (fp, "%s", tmp)==0 || verifie_matricule(tmp)!=0)
            return -1;
        // Récupération du matricule et conversion en bianire
        sscanf(tmp, "%u", &matriculeDec);
        int_vers_binaire(matriculeDec,36,matriculeBi);
        
        for(unsigned i=0;matriculeBi[i]!=NULL;i++){

        }
    }
    return 0;
}//Fin int charge_matricule()