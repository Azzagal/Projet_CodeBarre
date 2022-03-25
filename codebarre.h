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

#endif // __CODEBARRE__