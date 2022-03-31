/**
 * pnm.c
 *
 * Ce fichier contient les définitions de types et
 * les fonctions de manipulation d'images PNM.
 *
 * @author: Lorenzen Pierre s203724
 * @date: 31/03/2022
 * @projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"
#include "GestOpt.h"

/**
 * 
 * Définition du type opaque PNM
 *
 */
struct PNM_t {

   char *type;/*** Le format du fichier ***/
   char *commentaire;/*** Les commentaires du fichier ***/
   unsigned tot_coul;/*** Le nombre total de couleurs d'un pixel ***/
   unsigned colonnes;/*** Le nombre de colonnes de la matrice de l'image ***/
   unsigned lignes;/*** Le nombre de lignes de la matrice de l'image ***/
   unsigned **matrice;/*** La matrice de l'image ***/
};

void detruit_image(PNM *image){
  assert(image !=NULL);

  for ( unsigned i = 0; i < image->lignes; i++)
    free(image->matrice[i]);
  
  free(image->matrice);
  free(image);
}//Fin detruit_image() 

PNM *cree_image(unsigned lignes , unsigned colonnes, unsigned tot_coul, char *commentaire, char *type){
  assert(type !=NULL && commentaire != NULL);

  PNM *image = malloc(sizeof(PNM));

  if(image==NULL){
    printf("Impossible d'allouer de la mémoire pour cette image\n");
    return NULL;
  }
  
  unsigned taille_type = strlen(type)+1;
  image->type = malloc(taille_type*sizeof(char));

  if(image->type == NULL){
    free(image);
    return NULL;
  }

  unsigned taille_commentaire = strlen(commentaire)+1;
  image->commentaire = malloc(taille_commentaire*sizeof(char));

  if(image->commentaire == NULL){
    free(image);
    return NULL;
  }

  memcpy(image->type, type, taille_type);
  image->tot_coul = tot_coul;
  image->lignes = lignes;
  image->colonnes = colonnes;
  memcpy(image->commentaire, commentaire, taille_commentaire);

  image->matrice = malloc(lignes*sizeof(unsigned*));
  
  if(image->matrice == NULL){
    free(image);
    return NULL;
  }

  for(unsigned i=0; i < lignes; i++){
      image->matrice[i] = calloc(colonnes,sizeof(unsigned));

      if(!image->matrice[i])
        detruit_image(image);
  }
  return image;
}//Fin cree_image()

int verification_format(char *format , char *fichier){
  assert(format!= NULL && fichier != NULL);
  char sortie[4];
  for(unsigned i=0; format[i] !=0; i++){
    switch(format[i]){

      case 'P': 
        sortie[i]='p';
        break;

      case 'M':
        sortie[i]='m';
        break;

      case 'B':
        sortie[i]='b';
        break;

      case 'G':
        sortie[i]='g';
        break;
      
      default:
        return -1;
    }
  }
  if(strncmp(sortie,fichier,strlen(sortie-1)) == 0){ return 0; }
  else{ return -1; }
}//Fin verification_format()

int load_pnm(PNM **image, char* filename) {
  assert(filename != NULL && (image) != NULL);
  
  ///////////////////////////////// Ouverture du fichier de nom "filename" /////////////////////////////////
  
  FILE *fp;
  fp = fopen(filename,"r");
   
  if(fp==NULL)
    return -1;

  //contient la taille de la chaine de caractères filename
  unsigned taille_filename = strlen(filename);
  //contient la taille de la chaine de caractères filename sans l'extension ex:".pbm"
  unsigned taille_extension = strlen(filename)-4;
  //contient l'extention du fichier de nom filename 
  char extension[4];
  // contient le nombre magique du fichier
  char nb_mag[3];

  for(unsigned i=0; taille_extension < taille_filename && i<4; i++){
    extension[i]=filename[taille_extension];
    taille_extension++;
  }//fin boucle extension
  ///////////////////////////////// Si Fichier PBM /////////////////////////////////
  if(strncmp(".pbm",extension,4) == 0){
    // Vérifie que le nombre magique est bien P1 //   
    fgets (nb_mag, 3, fp);

    if(strcmp(nb_mag,"P1") != 0)
      return -2;
  }
  ///////////////////////////////// Si Fichier PGM /////////////////////////////////
  if(strncmp(".pgm",extension,4) == 0){  
    // Vérifie que le nombre magique est bien P2 //   
    fgets (nb_mag, 3, fp);

    if(strcmp(nb_mag,"P2") != 0)
      return -2;
  }
  ///////////////////////////////// Si Fichier PPM /////////////////////////////////
  if(strncmp(".ppm",extension,4) == 0){
    // Vérifie que le nombre magique est bien P3 //
    fgets (nb_mag, 3, fp);

    if(strcmp(nb_mag,"P3") != 0)
      return -2;
  }

  //contient les commentaires du fichier
  char commentaire[200];
  //contient temporairement des chaines de caractères
  char tmp[200]; 
  //1er case du tableau : nbr colonnes , 2ème case du tableau : nbr de lignes
  unsigned taille_image[2];
  //variable temporaire qui contient des valeurs entières positives
  unsigned valeur;
  
  for( unsigned i = 0 ; i < 2 && !feof(fp);){ 

    if(fscanf (fp, "%s", tmp)==0)
      return -3;
    // enregistre dans la variable commentaire la ligne de commentaire //
    if(strncmp("#",tmp, 1 )==0){
          
      fgets(commentaire, 200, fp);
      strcat(tmp, commentaire);
      memcpy(commentaire, tmp, strlen(tmp)-1);
    }//fin If

    // Enregistre la taille de la matrice dans taille_image //

    else{
      if(strcmp(nb_mag,"P3") == 0){
        
        if(i==0){ // car la couleur est définie par 3 nombres donc je triple le nombre de colonnes
          sscanf(tmp, "%u", &valeur);
          taille_image[i]=3*valeur; 
          i++;
        }

        else{
          sscanf(tmp, "%u", &valeur);
          taille_image[i]=valeur; 
          i++;
        }
      }//fin si fichier PPM
      else{
        sscanf(tmp, "%u", &valeur);
        taille_image[i]=valeur; 
        i++;
      }//si fichier PBM ou PGM
    }//Fin else
  }//Fin for
    
  if(strcmp("P1",nb_mag)==0)
    valeur = 1;
  else{
    if(!feof(fp)){
      if(fscanf (fp, "%s", tmp)==0)
        return -3;
      sscanf(tmp, "%u", &valeur);
    }
  }
  *image = cree_image(taille_image[1], taille_image[0], valeur, commentaire, nb_mag);

  if (*image ==NULL)
    return -1;
      
  for(unsigned i=0 ; i < taille_image[1] ; i++){

    for(unsigned j=0 ; j < taille_image[0] && !feof(fp) ; j++){
          
      if(fscanf(fp,"%s", tmp)==0)
        return -3;
      sscanf(tmp, "%u", &valeur);
      if(valeur > (*image)->tot_coul)
        return -3;
      (*image)->matrice[i][j] = valeur; 
    }
  }      
  fclose(fp);  
  return 0;
}//Fin load_pnm()

int write_pnm(PNM *image, char* filename) {
  assert(image!= NULL && filename != NULL);

  if(verifie_sortie(filename)==-1)
    return -1;
  ///////////////////////////////// Ouverture du fichier de nom "filename" /////////////////////////////////
  
  FILE *fp;
  fp = fopen(filename,"w");

  if(fp==NULL)
    return -2;

  // Inscrit le nombre magique dans le fichier de nom filename
  fprintf(fp, "%s\n", image->type);

  // Inscrit un commentaire dans le fichier de nom filename si il y en a un
  if(strncmp("#",image->commentaire, 1 )==0) 
  fprintf(fp, "%s\n", image->commentaire); 

  // Inscrit la taille de l'image dans le fichier de nom filename
  if(strcmp("P3",image->type)==0)
    fprintf(fp, "%u %u\n",image->colonnes/3,image->lignes);
  else
    fprintf(fp, "%u %u\n",image->colonnes,image->lignes);

  //Inscrit le nombre maximal de couleur dans le fichier de nom filename
  if(strcmp("P2",image->type)==0 || strcmp("P3",image->type)==0)
    fprintf(fp,"%u\n",image->tot_coul);

  // Inscrit les valeurs de l'image dans le fichier de nom filename
  for(unsigned i=0 ; i < image->lignes ; i++){

    for(unsigned j=0 ; j < image->colonnes ; j++){
      fprintf(fp, "%u ",image->matrice[i][j]);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
  return 0;
}//Fin write_pnm

int verifie_sortie(char *sortie){
  assert(sortie !=NULL);

  int erreur = 0;

  for(unsigned i=0; sortie[i]!=0 && erreur!= -1; i++){

    switch(sortie[i]){
    
      case ':' : 
        erreur =-1;
        break; 
  
      case '*' :
        erreur =-1;
        break;

      case '?' :
        erreur =-1;
        break;
      
      case '"' :
        erreur =-1;
        break;

      case '<' :
        erreur =-1;
        break;

      case '>' :
        erreur =-1;
        break;

      case '|' :
        erreur =-1;
        break;

      case '\\' :
        erreur =-1;
        break;

      default:
        break;
    }
  }
  return erreur;
}//Fin verifie_sortie()

char* acces_type(PNM *image){
  assert(image !=NULL);
  return image->type;
}

char* acces_commentaire(PNM *image){
  assert(image !=NULL);
  return image->commentaire;
}

int acces_tot_coul(PNM *image){
  assert(image !=NULL);
  return image->tot_coul;
}

int acces_colonnes(PNM *image){
  assert(image !=NULL);
  return image->colonnes;
}

int acces_lignes(PNM *image){
  assert(image !=NULL);
  return image->lignes;
}

int acces_matrice(PNM *image, unsigned ligne, unsigned colonne){
  assert(image != NULL);
  return image->matrice[ligne][colonne];
}

void defini_matrice(PNM *image, unsigned ligne, unsigned colonne, unsigned val){
  assert(image != NULL);
  image->matrice[ligne][colonne] = val;
}