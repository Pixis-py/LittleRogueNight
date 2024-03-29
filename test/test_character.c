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

/// @brief Function that tests cration on character's structure
void test_creation() {
   character_t * c;
   create(&c);
   CU_ASSERT_PTR_NOT_NULL(c);
   destruct(&c);
}

/// @brief Function that tests pv loss on character's structure
void test_pv_loss() {
   character_t * c;
   create(&c);
   pv_loss(&c, 10);
   CU_ASSERT_EQUAL(c->pv, 90);
   destruct(&c);
}

/// @brief Function that tests attack on character's structure
void test_attack() {
   character_t * c;
   character_t * e;
   create(&c);
   create(&e);
   attack(c, e);
   CU_ASSERT_EQUAL(c->pv, 90);
   destruct(&c);
   destruct(&e);
}

/// @brief Function that tests pv gain on character's structure
void test_pv_gain() {
   character_t * c;
   create(&c);
   pv_gain(&c, 20);
   CU_ASSERT_EQUAL(c->pv, 120);
   destruct(&c);
}

/// @brief Function that tests destruction on character's structure
void test_destruction() {
   character_t * c;
   create(&c);
   destruct(&c);
   CU_ASSERT_PTR_NULL(c);
}


/// @brief 
/// @return 
int main() {
   CU_initialize_registry();

   CU_pSuite suite = CU_add_suite("Character Tests", NULL, NULL);
   CU_add_test(suite, "Test Creation", test_creation);
   CU_add_test(suite, "Test Pv Loss", test_pv_loss);
   CU_add_test(suite, "Test Attack", test_attack);
   CU_add_test(suite, "Test Pv Gain", test_pv_gain);
   CU_add_test(suite, "Test Destruction", test_destruction);

   CU_basic_run_tests();
   CU_cleanup_registry();

   return 0;
}
