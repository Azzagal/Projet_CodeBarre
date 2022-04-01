/**
 * codebarre.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions de création de code barre au format
 * PNM.
 * 
 * @author: Lorenzen Pierre s203724
 * @date:01/04/2022
 * @projet: INFO0030 Projet 2
 */
#include"pnm.h"
#ifndef __CODEBARRE__
#define __CODEBARRE__

/**
 * \fn void int_vers_binaire(int entree, unsigned n,int *sortie)
 * 
 * \brief Transforme un nombre entier vers un nombre binaire
 * 
 * \param entree un nombre entier.
 * \param n le nombre de bit du nombre en binaire.
 * \param sortie un tableau d'entier contenant le nombre bianire de sortie.
 * 
 */
void int_vers_binaire(int entree, unsigned n,int *sortie);

/**
 * \fn int verifie_matricule(char *entree)
 * 
 * \brief Vérifie que la chaine de caractère est bien une suite de 8 chiffres.
 * 
 * \param entree le matricule à vérifié.
 * 
 * \return 
 *      0 Succès.
 *      -1 Le matricule est maformé.
 *      -2 Le matricule n'a pas la bonne taille.
 */
int verifie_matricule(char *entree);

/**
 * \fn void multiplie_matricule(PNM *image, unsigned valeur ,unsigned borneInf, unsigned taille)
 * 
 * \brief Donne la forme d'un matrice taille x taille à la valeur dans la matrice de l'image depuis
 *        borneInf comme départ.
 * 
 * \param image un pointeur sur PNM.
 * \param valeur la valeur à recopié dans la matrice.
 * \param borneLigne l'indice de ligne où commencer la matrice.
 * \param borneColonne l'indice de ligne où commencer la matrice.
 * \param taille la taille de la matrice carrée.
 * 
 */
void multiplie_matricule(PNM *image, unsigned valeur ,unsigned borneLigne, unsigned borneColonne ,unsigned taille);

/**
 * \fn int charge_matricule(char* fichier)
 * 
 * \brief Charge les matricules depuis un fichier
 * 
 * \param fichier Le nom du fichier où se trouve les matricules
 * \param dossier_output Le nom du dossier où doivent se trouver les codebarres
 * 
 * \return
 *      0 Succès
 *      -1 Problème au chargement des matricules
 */
int charge_matricule(char* fichier,char* dossier_output);
/**
 * \fn int corrige_codebarre(char *nom_fichier)
 * 
 * \brief Corrige une erreur sur un code barre de nom "nom_fichier" 
 * 
 * \param nom_fichier Le nom du fichier où se trouve l'image
 * \param dossier_output  le fichier où écrire le résultat de la correction
 * 
 * \return
 *       0 Succès
 *      -1 Problème au chargement de l'image
 *      -2 Trop d'erreur dans l'image
 */
int corrige_codebarre(char *nom_fichier,char *dossier_output);

#endif // __CODEBARRE__