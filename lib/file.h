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
/// @param  void
void initfile(void);

/// @brief Function enfiler is used to add an element to the queue
/// @param v 
void enfiler(int v);

/// @brief Function enfiler is used to add an element to the queue
/// @param v 
void defiler(int* v);

/// @brief Function filevide is used to verify if a queue is empty
/// @param  void
/// @return true or false, wether the queue is empty or not
int filevide(void);
