#include <stdio.h>
#include <getopt.h>
#include "GestOpt.h"
#include <string.h>
#include <assert.h>

void gestion_option(char *optstring, char *format, char *entree, char *sortie, char *c, int argc, char *argv[]){
  assert(optstring != NULL && format != NULL && entree != NULL && sortie != NULL);

  printf("\n");

  int val;

  while((val=getopt(argc, argv, optstring))!=EOF){
    switch(val){
      case 'f':
        printf("format: %s\n",optarg);  
        memcpy(format, optarg, strlen(optarg)+1);
        break;
      case 'i':
        printf("entree: %s\n", optarg);
        memcpy(entree, optarg, strlen(optarg)+1);
        break;
      case 'o':
        printf("sortie: %s\n", optarg); 
        memcpy(sortie, optarg, strlen(optarg)+1);
        break;
      case 'c':
        printf("à corriger: %s\n", optarg); 
        memcpy(c, optarg, strlen(optarg)+1);
        break;
      case '?':
        printf("unknown option: %c\n", optopt); break;
      case ':':
        printf("missing arg: %c\n", optopt); break;
    }//fin switch
  }//fin while

  printf("\n");
}//Fin gestion_option()