/**
 * \file pnm.h
 *
 * \brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 *
 * \author Lorenzen Pierre s203724
 * \date 23/03/2022
 * \brief projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * \brief Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * \fn char* acces_type(PNM *image)
 * 
 * \brief Donne accès au champ type de la structure de donnée PNM
 * 
 * \param image un pointeur sur PNM.
 * 
 * \return la fonction retourne le type de l'image
 */
char* acces_type(PNM *image);

/**
 * \fn char* acces_commentaire(PNM *image)
 * 
 * \brief Donne accès au champ commentaire de la structure de donnée PNM
 * 
 * \param image un pointeur sur PNM.
 * 
 * \return la fonction retourne le commentaire de l'image
 */
char* acces_commentaire(PNM *image);

/**
 * \fn int acces_tot_coul(PNM *image)
 * 
 * \brief Donne accès au champ tot_coul de la structure de donnée PNM
 * 
 * \param image un pointeur sur PNM.
 * 
 * \return la fonction retourne le nombre totale de couleur de l'image
 */
int acces_tot_coul(PNM *image);

/**
 * \fn int acces_colonnes(PNM *image)
 * 
 * \brief Donne accès au champ colonnes de la structure de donnée PNM
 * 
 * \param image un pointeur sur PNM.
 * 
 * \return la fonction retourne le nombre de colonnes de l'image
 */
int acces_colonnes(PNM *image);

/**
 * \fn int acces_lignes(PNM *image)
 * 
 * \brief Donne accès au champ lignes de la structure de donnée PNM
 * 
 * \param image un pointeur sur PNM.
 * 
 * \return la fonction retourne le nombre de lignes de l'image
 */
int acces_lignes(PNM *image);

/**
 * \fn int load_pnm(PNM **image, char* filename)
 *
 * \brief Charge une image PNM depuis un fichier.
 *
 * \param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * \param filename le chemin vers le fichier contenant l'image.
 *
 * \return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * \fn int write_pnm(PNM *image, char* filename)
 *
 * \brief Sauvegarde une image PNM dans un fichier.
 *
 * \param image un pointeur sur PNM.
 * \param filename le chemin vers le fichier de destination.
 *
 * \return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

/**
 * \fn PNM *cree_image(unsigned lignes , unsigned colonnes, unsigned tot_coul, char *commentaire, char *type)
 *
 * \brief alloue de la mémoire pour une image.
 *
 * \param lignes est le nombre de lignes à allouer à l'image.
 * \param colonnes est le nombre de colonnes à allouer à l'image.
 * \param tot_coul est le nombre maximal de couleurs de l'image.
 * \param commentaire est la ligne de commentaire de l'image si il y en a une.
 * \param type est le type de l'image. 
 *
 * \return:
 *      L'image avec l'espace mémoire alloué
 *      Null si il y a eu un problème
 */
PNM *cree_image(unsigned lignes , unsigned colonnes, unsigned tot_coul, char *commentaire, char *type);
/**
 * \fn void detruit_image(PNM *image)
 *
 * \brief retire la mémoire allouée pour la structure PNM
 *
 * \param image est la structure à laquelle on veut retirer la mémoire
 *
 */
void detruit_image(PNM *image);
/**
 * \fn int verification_format(char *format, char *fichier)
 *
 * \brief vérifie la correspondance d'un format avec un fichier.
 *
 * \param format est le format à retrouver dans un fichier.
 * \param fichier est un fichier avec le format pbm, pgm ou ppm.
 *
 * \return:
 *      0 Succès
 *     -1 le format est différent du format du fichier
 *
 */
int verification_format(char *format, char *fichier);
/**
 * \fn void gestion_option(char *optstring, char *format, char *entree, char *sortie, int argc, char *argv[])
 *
 * \brief Gère les options introduites à l'execution d'un programme.
 *
 * \param optstring est la chaine de caractères qui défini les paramètres à prendre en compte.
 * \param format est le format du fichier passé en argument.
 * \param entree est l'emplacement du fichier passé en argument.
 * \param sortie est le nom du fichier de sortie.
 * \param argc le premier argument de la fonction main.
 * \param argv le deuxième argument de la fonxtion main.
 *
 */
void gestion_option(char *optstring, char *format, char *entree, char *sortie, int argc, char *argv[]);
/**
 * \fn int verifie_sortie(char *sortie)
 *
 * \brief Vérifie que la chaine de caratères passée en argument ne contient pas de caratères interdits.
 *        Soit  / \ : * ? " < > |
 *
 * \param sortie est la chaine de caratères à vérifier.
 * \return:
 *      0 Succès
 *     -1 sortie contient au moins un des caratères interdits.
 *
 */
int verifie_sortie(char *sortie);
#endif // __PNM__
