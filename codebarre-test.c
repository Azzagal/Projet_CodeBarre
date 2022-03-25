#include "seatest.h"
#include "codebarre.h"

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

 static void test_fixture(){
    test_fixture_start();

    run_test(test_int_vers_binaire);

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