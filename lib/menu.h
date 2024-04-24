/**
 * @file menu.h
 * @author Enzo Desfaudais
 * @brief menu.h contains functions prototype's used in menu.c
 * @version 1.0
 * @date 2024-03-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/// @brief menu is used to show the first menu and choose the character for the game
/// @param argc 
/// @param argv 
/// @param choix_perso 
/// @return the choice of the player to play the game or quit the game.
int menu(int argc, char** argv,int *choix_perso);
