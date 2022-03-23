#include "seatest.h"
#include "pnm.h"

/**
 * 
 * Test de la fonction cree_image
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
/*
static void test_verification_format(){

    char *s0 ="/home/pierre/Documents/Projet/PNM/exemples_images/washington.pbm";
    char *s1 ="home/cake/bunny/file.pgmm";
    char *s2 ="home/cake/bunny/file.ppmm";

    assert_int_equal(0,verification_format("PBM",s0));
    assert_int_equal(0,verification_format("PGM",s1));
    assert_int_equal(0,verification_format("PPM",s2));

}// fin test_verification_format()
*/
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
    assert_int_equal(-1,verifie_sortie(s1));
    assert_int_equal(-1,verifie_sortie(s2));
    assert_int_equal(-1,verifie_sortie(s3));
    assert_int_equal(-1,verifie_sortie(s4));
    assert_int_equal(-1,verifie_sortie(s5));
    assert_int_equal(-1,verifie_sortie(s6));
    assert_int_equal(-1,verifie_sortie(s7));

}// fin test_verifie_sortie()


static void test_fixture(){
    test_fixture_start();

    run_test(test_cree_image);
    //run_test(test_verification_format);
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