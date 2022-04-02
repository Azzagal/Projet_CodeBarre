/**
 * \file codebarre-test.c
 *
 * \brief Ce fichier contient les fonctions de test des fichiers pnm.c et codebarre.c.
 *
 * \author: Lorenzen Pierre s203724
 * \date: 02/04/2022
**/

#include "seatest.h"
#include "codebarre.h"
#include "pnm.h"

/**
 * 
 * \brief Test de la fonction cree_image
 * 
**/
static void test_cree_image(){

    PNM *image = cree_image(15,25,255,"Ceci n'est pas une image","PBM");

    assert_int_equal(15,acces_lignes(image));
    assert_int_equal(25,acces_colonnes(image));
    assert_int_equal(255,acces_tot_coul(image));
    assert_string_equal("Ceci n'est pas une image",acces_commentaire(image));
    assert_string_equal("PBM",acces_type(image));

    detruit_image(image);
 }// Fin test_cree_image()

/**
 * 
 * \brief Test de la fonction verification_format
 * 
**/
static void test_verification_format(){

    char *s0 ="/home/pierre/Documents/Projet/PNM/exemples_images/washington.pbm";
    char *s1 ="home/cake/bunny/file.pgm";
    char *s2 ="home/cake/bunny/file.ppm";

    assert_int_equal(0,verification_format("PBM",s0));
    assert_int_equal(0,verification_format("PGM",s1));
    assert_int_equal(0,verification_format("PPM",s2));

}// fin test_verification_format()

/**
 * 
 * \brief Test de la fonction verifie_sortie
 * 
**/
static void test_verifie_sortie(){

    char *s0 ="Ce dossier ci";
    char *s1 ="Ce dossier ci/";
    char *s2 ="Ce dossier| ci";
    char *s3 ="Ce dossier: ci";
    char *s4 ="Ce dossier* ci";
    char *s5 ="Ce dossier? ci";
    char *s6 ="Ce dossier <ci";
    char *s7 ="Ce dossier> ci";

    assert_int_equal(0,verifie_sortie(s0));
    assert_int_equal(-1,verifie_sortie(s2));
    assert_int_equal(-1,verifie_sortie(s3));
    assert_int_equal(-1,verifie_sortie(s4));
    assert_int_equal(-1,verifie_sortie(s5));
    assert_int_equal(-1,verifie_sortie(s6));
    assert_int_equal(-1,verifie_sortie(s7));

}// fin test_verifie_sortie()

/**
 * 
 * \brief Test de la fonction int_vers_binaire
 * 
**/

static void test_int_vers_binaire(){

    int sortie1[32];
    int_vers_binaire(20100749,32,sortie1);
    int attendu1[32] ={1,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0};
    int sortie2[32];
    int_vers_binaire(20111182,32,sortie2);
    int attendu2[32] ={0,1,1,1,0,0,1,0,1,1,1,1,1,0,1,1,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0};
    int sortie3[32];
    int_vers_binaire(20100749,32,sortie3);
    int attendu3[32] ={1,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0};

    assert_n_array_equal(attendu1,sortie1,32);
    assert_n_array_equal(attendu2,sortie2,32);
    assert_n_array_equal(attendu3,sortie3,32);

 }// Fin test_cree_image()

/**
 * 
 * \brief Test de la fonction verifie_matricule
 * 
**/
static void test_verifie_matricule(){

    char *f1 ="20100749";
    char *f2 ="2010074954641";
    char *f3 ="Salut tout le monde";

    assert_int_equal(0,verifie_matricule(f1));
    assert_int_equal(-2,verifie_matricule(f2));
    assert_int_equal(-1,verifie_matricule(f3));
}

static void test_fixture(){
    test_fixture_start();

    run_test(test_int_vers_binaire);
    run_test(test_verifie_matricule);
    run_test(test_cree_image);
    run_test(test_verification_format);
    run_test(test_verifie_sortie);
    test_fixture_end();
}

void all_tests( void )
{
        test_fixture();   
}

int main( int argc, char** argv )
{
        return run_tests(all_tests);
}