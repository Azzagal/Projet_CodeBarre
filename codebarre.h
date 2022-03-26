/**
 * codebarre.h
 *
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions de création de code barre au format
 * PNM.
 * 
 * @author: Lorenzen Pierre s203724
 * @date:27/02/2022
 * @projet: INFO0030 Projet 2
 */

#ifndef __CODEBARRE__
#define __CODEBARRE__

/**
 * \fn void int_vers_binaire(int entree, unsigned n,int *sortie)
 * 
 * \brief Transforme un nombre entier vers un nombre binaire
 * 
 * \param entree un nombre entier.
 * \param n le nombre de bit du nombre en binaire.
 * \param sortie un tableau d'entier contenant le nombre bianire de sortie
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
 *      -2 Le matricule est trop long.
 */
int verifie_matricule(char *entree);

/**
 * \fn int charge_matricule(char* fichier)
 * 
 * \brief Charge les matricules depuis un fichier
 * 
 * \param fichier Le nom du fichier où se trouve les matricules
 * 
 * \return
 *      0 Succès
 *      -1 Problème au chargement des matricules
 * 
 */
int charge_matricule(char* fichier);

#endif // __CODEBARRE__