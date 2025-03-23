#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include <SDL.h>

/**
 * Mélange le bleu et le rouge en ajoutant du vert quand le réseau hésite.
 * p_bleu et p_rouge sont des valeurs dans [0, 1].
 */
SDL_Color melange_couleurs(double p_bleu, double p_rouge);

/**
 * Affiche les spirales (de référence) sur l'écran.
 */
void afficher_spirales(SDL_Renderer *renderer);

#endif
