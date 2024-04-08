/**
 * @file test_pile.c
 * @author Maelig Pesantez
 * @brief File test_pile.c is used to test the whole pile.c file and it's functions to assume it's working
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <CUnit/Basic.h>
#include "../lib/pile.h"


/// @brief Function test_pilevide tests function pilevide, used to check if a stack is empty
/// @param  void
void test_pilevide(void) {
    CU_ASSERT(pilevide() == 1); // La pile doit être vide initialement
    empiler('A');
    CU_ASSERT(pilevide() == 0); // Après l'ajout d'un élément, la pile ne doit plus être vide
    int c;
    depiler(&c);
    CU_ASSERT(pilevide() == 1); // Après avoir dépilé l'élément ajouté, la pile doit être vide à nouveau
}

/// @brief Function test_empiler_depiler_sommetpile tests functions empiler, depiler and sommetpile, used add and pop an element in a stack and to know the top of the stack
/// @param  void
void test_empiler_depiler_sommetpile(void) {
    int c;
    empiler('X');
    empiler('Y');
    empiler('Z');

    sommetpile(&c);
    CU_ASSERT(c == 'Z'); // Test du sommet de pile après ajout de plusieurs éléments

    depiler(&c);
    CU_ASSERT(c == 'Z'); // Test du dépilement du dernier élément ajouté

    sommetpile(&c);
    CU_ASSERT(c == 'Y'); // Test du sommet de pile après un dépilement
}

/// @brief Function main is used to call stack test functions
/// @return 
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Pile Test Suite", NULL, NULL);
    CU_add_test(suite, "test pilevide", test_pilevide);
    CU_add_test(suite, "test empiler/depiler/sommetpile", test_empiler_depiler_sommetpile);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}