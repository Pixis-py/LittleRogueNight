/**
 * @file test_file.c
 * @author Maelig Pesantez
 * @brief File test_file.c is used to test the whole file.c file and it's functions to assume it's working
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <CUnit/Basic.h>
#include "../lib/file.h"

/// @brief Function test_filevide tests function filevide, used to check if a queue is empty
/// @param void
void test_filevide(void) {
    CU_ASSERT(filevide() == 1); // La file doit être vide initialement
    enfiler(5);
    CU_ASSERT(filevide() == 0); // Après l'ajout d'un élément, la file ne doit plus être vide
    int v;
    defiler(&v);
    CU_ASSERT(filevide() == 1); // Après avoir défilé l'élément ajouté, la file doit être vide à nouveau
}

/// @brief Function test_enfiler_defiler tests functions enfiler and defiler, used add and pop an element in a queue
/// @param  void
void test_enfiler_defiler(void) {
    int v;
    enfiler(10);
    enfiler(20);
    enfiler(30);

    defiler(&v);
    CU_ASSERT(v == 10); // Test de défiler le premier élément ajouté
    defiler(&v);
    CU_ASSERT(v == 20); // Test de défiler le deuxième élément ajouté

    enfiler(40);
    defiler(&v);
    CU_ASSERT(v == 30); // Test de défiler après avoir ajouté un autre élément

    defiler(&v);
    CU_ASSERT(v == 40); // Test de défiler le dernier élément ajouté
}

/// @brief Function main is used to call queue test functions
/// @return 
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("File Test Suite", NULL, NULL);
    CU_add_test(suite, "test filevide", test_filevide);
    CU_add_test(suite, "test enfiler/defiler", test_enfiler_defiler);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}