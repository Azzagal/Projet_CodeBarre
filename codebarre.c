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
                printf("[ERREUR]: Matricule contenant un caractère différent d'un chiffre\n");
                return -1;            
        }
        compteur++;
    }
    if(compteur!=7){
        printf("[ERREUR]: Matricule trop long ou trop petit\n");
        return -2;
    }
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

int charge_matricule(char* fichier, char* dossier_output){
    assert(fichier!=NULL);

    FILE *fp = fopen(fichier,"r");
   
    if(fp==NULL){
        printf("ici\n");
        return -1;
}
    char tmp[100];
    int matriculeDec;
    int matriculeBi[36];
    PNM *codebarre = cree_image(700,700,1,"","PBM");
    unsigned partite = 0;
    unsigned borneLigne = 0;
    unsigned borneColonne = 0;
    char *nom_fichier = "Matricule_";
    
    for(;!feof(fp);){
        // Vérification de la validité du matricule
        if(fscanf (fp, "%s", tmp)==0 || verifie_matricule(tmp)!=0)
            return -1;
        // Récupération du matricule et conversion en bianire
        sscanf(tmp, "%d", &matriculeDec);
        int_vers_binaire(matriculeDec,36,matriculeBi);
        
        for(unsigned i=0;matriculeBi[i]!=NULL;i++){
            if(!i%7 && i!=0){
                multiplie_matricule(codebarre,partite%2,borneLigne,borneColonne,10);
                borneLigne = 0;
                borneColonne += 10;
                partite = 0;
            }
            multiplie_matricule(codebarre,matriculeBi[i],borneLigne,borneColonne,10);
            borneLigne += 10;
            partite += matriculeBi[i];
        }
        strcat(dossier_output,nom_fichier);
        strcat(dossier_output,(char *)matriculeDec);
        write_pnm(codebarre,dossier_output);
    }
    detruit_image(codebarre);
    fclose(fp);
    return 0;
}//Fin int charge_matricule()