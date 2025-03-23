#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

//#include <SDL.h>
#include <SDL2/SDL.h>
/**
 * Mélange le bleu et le rouge en ajoutant du vert quand le réseau hésite.
 * p_bleu et p_rouge sont des valeurs dans [0, 1].
 */
SDL_Color melange_couleurs(double p_bleu, double p_rouge);

/**
 * Affiche les spirales (de référence) sur l'écran.
 */
void afficher_spirales(SDL_Renderer *renderer);

/**
 * Colorie l'écran en fonction des sorties du réseau.
 * Le réseau doit être déjà propagé avec les entrées correspondantes.
 */
int init_sdl(const char *title, int width, int height);

/// Libère les ressources SDL
void cleanup_sdl();

/// Variables globales pour la fenêtre et le renderer
/// Ces variables sont initialisées dans init_sdl() et libérées dans cleanup_sdl()
extern SDL_Window *window;

/// Le renderer est utilisé pour dessiner sur la fenêtre
/// Il est créé dans init_sdl() et détruit dans cleanup_sdl()
extern SDL_Renderer *renderer;

/// Dessine un rectangle avec la couleur spécifiée
void draw_rectangle(int x, int y, int w, int h, SDL_Color color);

#endif
