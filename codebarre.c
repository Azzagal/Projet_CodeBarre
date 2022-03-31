/**
 * codebarre.c
 *
 * Ce fichier contient les définitions de types et
 * les fonctions de création de code barre au format
 * PNM.
 *
 * @author: Lorenzen Pierre s203724
 * @date: 31/03/2022
 * @projet: INFO0030 Projet 2
**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

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
    if(compteur!=8){
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
    PNM *codebarre = cree_image(70,70,1,"","P1");
    unsigned parite = 0;
    unsigned borneLigne = 0;
    unsigned borneColonne = 0;
    char nom_fichier[200];
    mkdir(dossier_output,0777);

    for(;!feof(fp);){
        // Vérification de la validité du matricule
        if(fscanf (fp, "%s", tmp)==0 || verifie_matricule(tmp)!=0)
            return -1;
        // Récupération du matricule et conversion en bianire
        sscanf(tmp, "%d", &matriculeDec);
        int_vers_binaire(matriculeDec,36,matriculeBi);
        
        for(unsigned i=0;i<36;i++){
            if(i%6==0 && i!=0){
                multiplie_matricule(codebarre,parite%2,borneLigne,borneColonne,10);
                borneLigne += 10;
                borneColonne = 0;
                parite = 0;
                multiplie_matricule(codebarre,matriculeBi[i],borneLigne,borneColonne,10);
                borneColonne += 10;
                parite += matriculeBi[i];
            }
            else{
                multiplie_matricule(codebarre,matriculeBi[i],borneLigne,borneColonne,10);
                borneColonne += 10;
                parite += matriculeBi[i];
            }
        }
        parite = 0;
        borneColonne = 0;
        borneLigne = 60; 
        
        for(unsigned j =0;j<6;j++){
            for(unsigned i=0;i<=41;i++){
                if((i-j)%6==0 && (i-j)!=36)
                    parite += matriculeBi[i];
                if(i-j==36){
                    multiplie_matricule(codebarre,parite%2,borneLigne,borneColonne,10);
                    borneColonne+=10;
                    parite =0;
                }

            }
        }
        borneLigne = 0;
        borneColonne = 0;
        
        strcpy(nom_fichier,dossier_output);
        strcat(nom_fichier,"/Matricule_");
        strcat(nom_fichier,tmp);
        strcat(nom_fichier,".pbm");
        switch(write_pnm(codebarre,nom_fichier)){

            case -1:
                printf("[ERREUR] Nom de fichier malformé\n");
                break;
            case -2:
                printf("[ERREUR] lors de la création de l'image\n");
        }
    }
    detruit_image(codebarre);
    fclose(fp);
    return 0;
}//Fin int charge_matricule()