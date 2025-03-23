#include "sdl_display.h"
#include <SDL.h>
#include <math.h>

/**
 * Mélange le bleu et le rouge et ajoute du vert en cas d'incertitude.
 */
SDL_Color melange_couleurs(double p_bleu, double p_rouge) {
    /*if (p_bleu < 0)  p_bleu = 0;
    if (p_bleu > 1)  p_bleu = 1;
    if (p_rouge < 0) p_bleu = 0;
    if (p_rouge > 1) p_rouge = 1;*/

    // Calcul de l'incertitude : plus les deux valeurs sont proches, plus c'est incertain (et donc plus vert)
    double incertitude = 1.0 - fabs(p_bleu - p_rouge);

    // Conversion en canaux [0, 255]
    Uint8 r = (Uint8)(p_rouge * 255);
    Uint8 g = (Uint8)(incertitude * 0);
    Uint8 b = (Uint8)(p_bleu * 255);

    SDL_Color color = { r, g, b, 255};
    return color;
}

/**
 * Affiche la spirale bleue et la spirale rouge de référence.
 * (Ces courbes sont calculées avec les équations paramétriques et servent de repère.)
 */
void afficher_spirales(SDL_Renderer *renderer) {
    int pas = 20; // ajuste la densité des points
    for (int i = 0; i < 1000; i += pas) {
        double t = i / 100.0;
        // Spirale bleue : (t*cos(t), t*sin(t))
        int x_bleu = (int)(300 + t * cos(t) * 20);
        int y_bleu = (int)(300 + t * sin(t) * 20);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawPoint(renderer, x_bleu, y_bleu);

        // Spirale rouge : (-t*cos(t), -t*sin(t))
        int x_rouge = (int)(300 - t * cos(t) * 20);
        int y_rouge = (int)(300 - t * sin(t) * 20);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, x_rouge, y_rouge);
    }
}
