/**
 * @file test_character.c
 * @author Maelig Pesantez
 * @brief test_character.c is used to test the whole character.c file and it's functions to assume it's working
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#include "../src/character.c"

/// @brief Function main is the only function here, it's used to check every function of character.c, from creation to destruction
int main(){

   printf("**************** Character structures test initialisation ****************\n\n");

   printf("**************** Creation test ****************\n\n");

   character_t * c;
   create(&c);

   if(c != NULL){
      printf("--- OK\n\n");
   }else{
      printf("--- KO\n\n");
   }

   printf("**************** Pv loss test ****************\n\n");

   pv_loss(&c, 10);
      
   if((c->pv) == 90){
      printf("--- OK\n\n");
   }else{
      printf("--- KO\n\n");
   }

   printf("**************** Pv gain test ****************\n\n");

   pv_gain(&c, 10);
      
   if((c->pv) == 100){
      printf("--- OK\n\n");
   }else{
      printf("--- KO\n\n");
   }

   printf("**************** Desctruction test ****************\n\n");

   destruct(c);
   if(c == NULL){
      printf("--- KO\n\n");
   }else{
      printf("--- OK\n\n");
   }

   return 0;

}