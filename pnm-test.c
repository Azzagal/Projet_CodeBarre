#include "seatest.h"
#include "pnm.h"

/**
 * 
 * Test de la fonction cree_image
 * 
**/
 
static void test_cree_image(){

    PNM *image = cree_image(15,25,255,"Ceci n'est pas une image","PBM");

    assert_int_equal(15,image->lignes);
    assert_int_equal(25,image->colonnes);
    assert_int_equal(255,image->tot->coul);
    assert_string_equal("Ceci n'est pas une image",image->commentaire);
    assert_string_equal("PBM",image->type);

    detruit_image(image);
 }// Fin test_cree_image()






static void test_fixture(){
    test_fixture_start();

    run_test(test_cree_image);

    test_fixture_end();
}