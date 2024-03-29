/**
 * @file pile.c
 * @author Clément Lelandais
 * @brief Pile.c (in french, pile=stack) includes every function needed to use stacks in an other program 
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/// @brief Function initpile is used to initialize a stack 
/// @param void
void initpile(void);

/// @brief Function epmiler is used to add an element to the stack
/// @param c 
void empiler(int c);

/// @brief Function depiler is used to unstack an element from a stack
/// @param c 
void depiler(int * c);

/// @brief Function pilevide is used to know if a stack is empty
/// @param  void
int pilevide(void);

/// @brief Function sommetpile is used to know stack's top
/// @param c 
void sommetpile(int *c);
