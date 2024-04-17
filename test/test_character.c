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

#include <CUnit/Basic.h>
#include "../lib/character.h"

void test_create() {
    character_t * character;
    create(&character, 100);
    CU_ASSERT_PTR_NOT_NULL(character);
    CU_ASSERT_EQUAL(character->pv, 100);
    CU_ASSERT_EQUAL(character->damage, 25);
    CU_ASSERT_EQUAL(character->x, 0);
    CU_ASSERT_EQUAL(character->y, 0);
    destruct(character);
}

void test_pv_loss() {
    character_t * character;
    create(&character, 100);
    pv_loss(&character, 50);
    CU_ASSERT_EQUAL(character->pv, 50);
    destruct(character);
}

void test_pv_gain() {
    character_t * character;
    create(&character, 100);
    pv_gain(&character, 50);
    CU_ASSERT_EQUAL(character->pv, 150);
    destruct(character);
}

/// @brief Function that tests attack on character's structure
void test_attack() {
   character_t * c;
   character_t * e;
   create(&c,100);
   create(&e,100);
   attack(&c, &e);
   CU_ASSERT_EQUAL((c)->pv, 75);
   destruct(c);
   destruct(e);
}


int main() {
   CU_initialize_registry();

   CU_pSuite suite = CU_add_suite("Character Tests", NULL, NULL);
   CU_add_test(suite, "Test Creation", test_create);
   CU_add_test(suite, "Test Pv Loss", test_pv_loss);
   CU_add_test(suite, "Test Attack", test_attack);
   CU_add_test(suite, "Test Pv Gain", test_pv_gain);

   CU_basic_run_tests();
   CU_cleanup_registry();

   return 0;
}
