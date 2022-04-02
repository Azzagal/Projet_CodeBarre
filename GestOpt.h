/**
 * \file Gestopt.h
 *
 * \brief Ce fichier contient la déclaration d'une fonction qui gère les options passées en arguments
 *
 * \author Lorenzen Pierre s203724
 * \date 24/03/2022
 * 
 */
#ifndef __GESTOPT__
#define __GESTOPT__

/**
 * \fn void gestion_option(char *optstring, char *format, char *entree, char *sortie, int argc, char *argv[])
 *
 * \brief Gère les options introduites à l'execution d'un programme.
 *
 * \param optstring est la chaine de caractères qui défini les paramètres à prendre en compte.
 * \param format est le format du fichier passé en argument.
 * \param entree est l'emplacement du fichier passé en argument.
 * \param sortie est le nom du fichier de sortie.
 * \param c est le nom du fichier à corriger.
 * \param argc le premier argument de la fonction main.
 * \param argv le deuxième argument de la fonxtion main.
 *
 */
void gestion_option(char *optstring, char *format, char *entree, char *sortie, char *c, int argc, char *argv[]);
#endif