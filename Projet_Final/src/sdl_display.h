/**
* @file sdl_display.h
 * @brief Fonctions et variables pour l'affichage graphique avec SDL2.
 *
 * Ce module fournit des fonctions utilitaires pour :
 * - initialiser et nettoyer SDL2
 * - dessiner à l'écran (rectangles, spirales, etc.)
 * - afficher les résultats d'un réseau de neurones en couleurs
 */

#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

//#include <SDL.h>
#include <SDL2/SDL.h>

/**
 * @brief Mélange les couleurs bleu et rouge, avec du vert en cas d'incertitude.
 *
 * Utilisé pour représenter la sortie d’un réseau de neurones binaire.
 *
 * @param p_bleu Probabilité pour la classe bleue (entre 0 et 1)
 * @param p_rouge Probabilité pour la classe rouge (entre 0 et 1)
 * @return Une couleur SDL correspondant au mélange pondéré
 */
SDL_Color melange_couleurs(double p_bleu, double p_rouge);
SDL_Color melange_couleurs_rgb(double sr, double sg, double sb);

/**
 * @brief Affiche les spirales de référence (bleue et rouge) à l’écran.
 *
 * Sert de repère visuel pour comparer les données originales avec la prédiction du réseau.
 *
 * @param renderer Le renderer SDL utilisé pour dessiner
 */
void afficher_spirales(SDL_Renderer *renderer);

/**
 * @brief Initialise SDL2, crée une fenêtre et un renderer.
 *
 * @param title Titre de la fenêtre
 * @param width Largeur de la fenêtre en pixels
 * @param height Hauteur de la fenêtre en pixels
 * @return 1 si tout s’est bien passé, 0 sinon
 */
int init_sdl(const char *title, int width, int height);

/**
 * @brief Libère les ressources SDL (renderer et fenêtre) et quitte SDL.
 */
void cleanup_sdl();

/**
 * @brief Pointeur global vers la fenêtre SDL.
 *
 * Initialisé dans init_sdl() et détruit dans cleanup_sdl().
 */
extern SDL_Window *window;

/**
 * @brief Pointeur global vers le renderer SDL utilisé pour dessiner.
 *
 * Créé dans init_sdl() et détruit dans cleanup_sdl().
 */
extern SDL_Renderer *renderer;

/**
 * @brief Dessine un rectangle plein à l'écran avec une couleur donnée.
 *
 * @param x Coordonnée x du coin supérieur gauche
 * @param y Coordonnée y du coin supérieur gauche
 * @param w Largeur du rectangle
 * @param h Hauteur du rectangle
 * @param color Couleur du rectangle (SDL_Color)
 */
void draw_rectangle(int x, int y, int w, int h, SDL_Color color);

#endif
