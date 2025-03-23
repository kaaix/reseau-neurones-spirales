#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neural_network.h"
#include "sdl_display.h"
#include "data.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    // 1) Génération du dataset en spirale
   // 1) Génération du dataset en spirale d'Archimède
   generer_spirales_archimede();


    // 2) Création du réseau
    // Ici, nous choisissons 5 couches cachées de 10 neurones et une couche de sortie de 2 neurones (total 5 couches)
    int taille_couches[] = {10, 10, 10, 10, 2};
    ReseauNeuronal *reseau = creer_reseau(2, 5, taille_couches);

    // 3) Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Spirales - Apprentissage continu",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          600, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand((unsigned)time(NULL));
    double epsilon = 0.001; // Taux d'apprentissage plus faible pour une convergence progressive

    // 4) Boucle d’événements + apprentissage en continu
    SDL_Event event;
    int running = 1;
    while (running) {
        // Traitement des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Effectuer quelques itérations d'entraînement (batch de 1000 itérations)
        for (int step = 0; step < 50000; step++) {
            int idx = rand() % (NB_POINTS_SPIRALE * 2);
            double entree[2] = { dataset[idx].x, dataset[idx].y };
            propagation(reseau, entree);
            backpropagation(reseau, entree, dataset[idx].label, epsilon);
        }

        // Effacer l'écran (fond noir)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Colorier l'écran selon la sortie du réseau (affichage de la frontière de décision)
        colorier_ecran(renderer, reseau, 600, 600);

        // Dessiner en surimpression la spirale de référence (les données d'origine)
        afficher_spirales(renderer);

        // Présenter le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    // Libération
    detruire_reseau(reseau);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
