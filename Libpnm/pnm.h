/**
 * pnm.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * @author: Lorenzen Pierre s203724
 * @date:27/02/2022
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);
/**
 * cree_image
 *
 * alloue de la mémoire pour une image.
 *
 * @param lignes est le nombre de lignes à allouer à l'image.
 * @param colonnes est le nombre de colonnes à allouer à l'image.
 * @param tot_coul est le nombre maximal de couleurs de l'image.
 * @param commentaire est la ligne de commentaire de l'image si il y en a une.
 * @param type est le type de l'image. 
 *
 * @pre: type!= NULL, commentaire != NULL .
 * @post: De la mémoire est allouée.
 *
 * @return:
 *      L'image avec l'espace mémoire alloué
 *      Null si il y a eu un problème
 */
PNM *cree_image(unsigned lignes , unsigned colonnes, unsigned tot_coul, char *commentaire, char *type);
/**
 * detruit_image
 *
 * retire la mémoire allouée
 *
 * @param image est la structure à laquelle on veut retirer la mémoire
 *
 * @pre: image!= NULL.
 * @post: De la mémoire est retirée.
 *
 */
void detruit_image(PNM *image);
/**
 * verification_format
 *
 * vérifie la correspondance d'un format avec un fichier.
 *
 * @param format est le format à retrouver dans un fichier.
 * @param fichier est un fichier avec le format pbm, pgm ou ppm.
 *
 * @pre: format!= NULL, fichier != NULL .
 * @post: La vérification à été éffectuée.
 *
 * @return:
 *      0 Succès
 *     -1 le format est différent du format du fichier
 *
 */
int verification_format(char *format, char *fichier);
/**
 * gestion_option
 *
 * Gère les options introduites à l'execution d'un programme.
 *
 * @param optstring est la chaine de caractères qui défini les paramètres à prendre en compte.
 * @param format est le format du fichier passé en argument.
 * @param entree est l'emplacement du fichier passé en argument.
 * @param sortie est le nom du fichier de sortie.
 * @param argc le premier argument de la fonction main.
 * @param argv le deuxième argument de la fonxtion main.
 *
 * @pre: optstring != NULL, format != NULL, entree != NULL, sortie != NULL.
 * @post: Les options ont été gérées.
 *
 */
void gestion_option(char *optstring, char *format, char *entree, char *sortie, int argc, char *argv[]);
/**
 * verification_sortie
 *
 * Vérifie que la chaine de caratères passée en argument ne contient pas de caratères interdits.
 * Soit  / \ : * ? " < > |
 *
 * @param sortie est la chaine de caratères à vérifier.
 *
 * @pre: sorie!= NULL.
 * @post: La vérification à été éffectuée.
 *
 * @return:
 *      0 Succès
 *     -1 sortie contient au moins un des caratères interdits.
 *
 */
int verifie_sortie(char *sortie);
#endif // __PNM__
