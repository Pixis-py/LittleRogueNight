/**
 * @file file.h
 * @author Clément Lelandais
 * @brief file.h (in french, file=queue) includes every function needed to use queue in an other program
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/// @brief Function initfile initialize a queue
void initfile(void);

/// @brief Function enfiler is used to add an element to the queue
void enfiler(int v);

/// @brief Function defiler is used to un-queue an element
void defiler(int* v);

/// @brief Function filevide is used to check wether the queue is empty or not
int filevide(void);
