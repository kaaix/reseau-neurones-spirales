#include "sdl_display.h"
//#include <SDL.h>
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;



SDL_Color melange_couleurs(double p_bleu, double p_rouge) {
    // S'assurer que les valeurs sont dans [0, 1]
    if (p_bleu < 0) p_bleu = 0;
    if (p_bleu > 1) p_bleu = 1;
    if (p_rouge < 0) p_rouge = 0;
    if (p_rouge > 1) p_rouge = 1;

    // Calcul de l'incertitude : plus p_bleu et p_rouge sont proches, plus le vert est présent.
    double incertitude = 1.0 - fabs(p_bleu - p_rouge);

    // Conversion des valeurs en canaux [0, 255]
    Uint8 r = (Uint8)(p_rouge * 255);
    Uint8 g = (Uint8)(incertitude * 0);  // Ajoute du vert proportionnellement à l'incertitude
    Uint8 b = (Uint8)(p_bleu * 255);

    SDL_Color color = { r, g, b, 255 };
    return color;
}
SDL_Color melange_couleurs_rgb(double sr, double sg, double sb)
{
    // 1) Convertir [-1..1] en [0..1]
    double rr = (sr + 1.0) * 0.5;  
    double gg = (sg + 1.0) * 0.5;
    double bb = (sb + 1.0) * 0.5;

    // 2) (Facultatif) saturer pour éviter d’éventuels débordements hors de [0..1]
    if (rr < 0.0) rr = 0.0;
    else if (rr > 1.0) rr = 1.0;

    if (gg < 0.0) gg = 0.0;
    else if (gg > 1.0) gg = 1.0;

    if (bb < 0.0) bb = 0.0;
    else if (bb > 1.0) bb = 1.0;

    // 3) Convertir en [0..255]
    Uint8 R = (Uint8)(rr * 255.0);
    Uint8 G = (Uint8)(gg * 255.0);
    Uint8 B = (Uint8)(bb * 255.0);

    // 4) Créer la couleur SDL
    SDL_Color color = { R, G, B, 255 };
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



int init_sdl(const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

void cleanup_sdl() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void draw_rectangle(int x, int y, int w, int h, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}