/**
* @file ui_manager.h
 * @brief Gestion des interfaces graphiques de l'application.
 *
 * Ce module gère toutes les fenêtres interactives de l'application, telles que :
 * - les choix entre entraînement et chargement,
 * - les interfaces de dessin personnalisé,
 * - l'entraînement en live des réseaux,
 * - le chargement de fichiers personnalisés.
 */

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "neural_network.h"

/**
 * @brief Affiche un texte centré dans un bouton.
 *
 * @param renderer Le renderer SDL utilisé pour dessiner.
 * @param font La police utilisée.
 * @param text Le texte à afficher.
 * @param button La zone du bouton.
 * @param textColor La couleur du texte.
 */
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect button, SDL_Color textColor);

/**
 * @brief Affiche une fenêtre avec deux boutons : "Train" et "Load".
 *
 * @param mode 0 pour R/B, 1 pour personnalisé.
 */
void show_train_or_load_window();

/**
 * @brief Affiche une fenêtre "Load" avec choix entre "Default" et "Custom".
 *
 * @param mode 0, 1 ou 2 selon le contexte (R/B, personnalisé ou dessin).
 */
void show_load_window(int mode);

/**
 * @brief Variante de chargement avec exécution en mode entraînement personnalisé.
 *
 * @param filename Nom du fichier réseau.
 * @param mode 0 (R/B), 1 (personnalisé), 2 (dessin).
 */
void load_networkv2(const char *filename,int mode);

/**
 * @brief Charge un réseau neuronal et affiche le résultat selon le mode.
 *
 * @param filename Nom du fichier contenant le réseau.
 */
void load_network(const char *filename);

/**
 * @brief Lance l'entraînement continu en mode R/B à partir d'un fichier.
 *
 * @param filename Nom du fichier réseau. Si non trouvé, un nouveau réseau est créé.
 */
void show_train_execution_window(const char *filename);

/**
 * @brief Affiche une boîte de saisie pour entrer un nom de fichier personnalisé.
 */
void show_custom_file_input_window();

/**
 * @brief Dessine un bouton avec bordure et texte centré.
 *
 * @param renderer Renderer SDL.
 * @param font Police pour le texte.
 * @param text Texte à afficher.
 * @param button Zone du bouton.
 * @param buttonColor Couleur de fond.
 * @param borderColor Couleur de la bordure.
 * @param textColor Couleur du texte.
 */
void draw_button(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect button, SDL_Color buttonColor, SDL_Color borderColor, SDL_Color textColor);

/**
 * @brief Affiche une interface pour choisir le nombre de classes personnalisées.
 */
void show_custom_spirals_window();

/**
 * @brief Lance l'entraînement avec un nombre de classes personnalisées.
 *
 * @param nb_classes Nombre de classes souhaité.
 * @param filename Nom du fichier réseau à charger ou sauvegarder.
 */
void show_train_execution_window_custom(int nb_classes,const char *filename);

/**
 * @brief Affiche la fenêtre de dessin pour créer un dataset personnalisé.
 */
void show_drawing_window();

/**
 * @brief Entraîne un réseau sur les données dessinées par l'utilisateur.
 */
void show_training_window_for_drawing();

/**
 * @brief Affiche une interface avec deux boutons : "Nouveau" et "Charger".
 */
void show_drawing_choice_window();
#endif // UI_MANAGER_H