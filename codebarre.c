/**
 * \file codebarre.c
 *
 * \brief Ce fichier contient l'implémentation
 * des fonctions de création de code barre au format
 * PNM.
 * 
 * \author: Lorenzen Pierre s203724
 * \date:01/04/2022
 */

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
    assert(fichier!=NULL && dossier_output!= NULL);

    FILE *fp = fopen(fichier,"r");
   
    if(fp==NULL)
        return -1;
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
        borneLigne = 0; 
        
        for(unsigned j =0;j<7;j++){
            for(unsigned i=0;i<7;i++){
                if(i==6)
                    multiplie_matricule(codebarre,parite%2,borneLigne,borneColonne,10);
                else{
                    parite += acces_matrice(codebarre,borneLigne,borneColonne);
                    borneLigne += 10;
                }
            }
            parite = 0;
            borneLigne = 0;
            borneColonne += 10;
        }
        borneColonne = 0;
        borneLigne = 0;
        
        strcpy(nom_fichier,dossier_output);
        strcat(nom_fichier,"/");
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

int corrige_codebarre(char *nom_fichier,char *dossier_output){
    assert(nom_fichier!=NULL);
    PNM *codebarre;

    switch(load_pnm(&codebarre, nom_fichier)){
  
      case -1 : 
        printf("[ERREUR] Impossiblilité d'allouer suffisamment de mémoire pour l'image \n");
        return -1;
        break; 
  
      case -2 :
        printf("[ERREUR] Mauvais format passé en agrument. Le fichier %s n'est pas du type %s \n",nom_fichier ,"PBM");
        return -1;
        break;
  
      case -3 :
        printf("[ERREUR] Le fichier est malformé\n");
        return -1; 
        break;

      default:
        break;
    }// Fin switch
    
    int parite = 0;
    unsigned borneLigne = 0;
    unsigned borneColonne = 0;
    unsigned erreurColonne = 0;
    unsigned compteurErreurC = 0;
    //Cherche les erreurs dans les colonnes
    for(unsigned j =0;j<6;j++){
        for(unsigned i=0;i<7;i++){
            if(i==6){
                if((parite%2)!= acces_matrice(codebarre,borneLigne,borneColonne)){
                    printf("erreur détectée\n");
                    erreurColonne = borneColonne;
                    compteurErreurC++;
                }
                if(compteurErreurC > 1){
                    detruit_image(codebarre);
                    return -2;
                }
            }
            else{
                parite += acces_matrice(codebarre,borneLigne,borneColonne);
                borneLigne += 10;
            }
        }
        parite = 0;
        borneLigne = 0;
        borneColonne += 10;
    }
    
    borneColonne = 0;
    borneLigne = 0;
    unsigned erreurLigne = 0;
    unsigned compteurErreurL = 0;
    //Cherche les erreurs dans les lignes
    for(unsigned j =0;j<6;j++){
        for(unsigned i=0;i<7;i++){
            if(i==6){
                if((parite%2)!= acces_matrice(codebarre,borneLigne,borneColonne)){
                    printf("erreur détectée\n");
                    erreurLigne = borneLigne;
                    compteurErreurL++;
                }
                if(compteurErreurL > 1){
                    detruit_image(codebarre);
                    return -2;
                }
            }
            else{
                parite += acces_matrice(codebarre,borneLigne,borneColonne);
                borneColonne += 10;
            }
        }
        parite = 0;
        borneColonne= 0;
        borneLigne += 10;
    }

    //Si la partité d'une ligne ou d'une colonne sont mauvaises
    if(compteurErreurC || compteurErreurL){
        //Si la partité d'une ligne et d'une colonne sont mauvaises
        if(compteurErreurC && compteurErreurL)
            multiplie_matricule(codebarre,!acces_matrice(codebarre,erreurLigne,erreurColonne),erreurLigne,erreurColonne,10);
        //Si la partité d'une ligne est mauvaise
        if(compteurErreurL && compteurErreurC == 0)
            multiplie_matricule(codebarre,!acces_matrice(codebarre,erreurLigne,60),erreurLigne,60,10);
        //Si la partité d'une colonne est mauvaise
        if(compteurErreurC && compteurErreurL == 0)
            multiplie_matricule(codebarre,!acces_matrice(codebarre,60,erreurColonne),60,erreurColonne,10);
    }
    //Cherche une erreur dans le coin inférieur droit
    compteurErreurL = 0;
    borneLigne = 60;
    borneColonne = 0;
    for(unsigned i=0;i<7;i++){
        if(i==6){
            if((parite%2)!= acces_matrice(codebarre,borneLigne,borneColonne)){
                erreurLigne = borneLigne;
                compteurErreurL++;
            }
            if(compteurErreurL > 1){
                detruit_image(codebarre);
                return -2;
            }
        }
        else{
            parite += acces_matrice(codebarre,borneLigne,borneColonne);
            borneColonne += 10;
        }
    }
    if(compteurErreurL)
        multiplie_matricule(codebarre,!acces_matrice(codebarre,60,60),60,60,10);

    write_pnm(codebarre,dossier_output);
    detruit_image(codebarre);
    return 0;
}