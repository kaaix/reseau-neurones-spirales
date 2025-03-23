#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "neural_network.h"

// Affiche un texte centré dans un bouton
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect button, SDL_Color textColor);

// Affiche une fenêtre avec deux options : Train et Load
void show_train_or_load_window();

// Affiche une fenêtre pour Load (choix Default ou nom de sauvegarde)
void show_load_window(int mode);

// Charge un réseau neuronal et l'affiche dans une nouvelle fenêtre
void load_networkv2(const char *filename,int mode);
void load_network(const char *filename);
// Exécute l'ancien comportement du main pour Train
void show_train_execution_window(const char *filename);

// Affiche une fenêtre pour entrer le nom du fichier de sauvegarde
void show_custom_file_input_window();

// Affiche un bouton avec une bordure et du texte centré
void draw_button(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect button, SDL_Color buttonColor, SDL_Color borderColor, SDL_Color textColor);

// permet de selectionner le nombre de classes
void show_custom_spirals_window();
void show_train_execution_window_custom(int nb_classes,const char *filename);

void show_drawing_window();
void show_training_window_for_drawing();
void show_drawing_choice_window();
#endif // UI_MANAGER_H