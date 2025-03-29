/**
* @file main.c
 * @brief Point d'entrée de l'application graphique utilisant SDL2.
 *
 * @details
 * Ce programme initialise une interface graphique contenant trois boutons :
 * - **"R/B"** : permet d’entraîner ou de charger un réseau binaire (deux classes, rouge et bleu).
 * - **"Personnalisé"** : permet de gérer plusieurs classes (jusqu’à 10), entraînement ou chargement.
 * - **"Dessiner"** : permet à l’utilisateur de dessiner lui-même les données et d’entraîner le réseau à partir de celles-ci.
 *
 * Il utilise SDL2 pour la gestion graphique, SDL_ttf pour l’affichage du texte,
 * et appelle des fonctions définies dans `sdl_display.h` et `ui_manager.h`.
 *
 * L’interface principale attend des clics de l’utilisateur sur les boutons, et redirige ensuite
 * vers les fenêtres spécifiques correspondantes.
 *
 * La fenêtre principale est blanche avec trois boutons centrés verticalement.
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "sdl_display.h"
#include "ui_manager.h"
extern int globalRunning;
#include "log.h"

/**
 * @brief Fonction principale de l'application.
 *
 * Initialise SDL2 et SDL_ttf, charge une police de caractères, crée une fenêtre principale
 * avec trois boutons. Gère les événements utilisateurs (clics) pour ouvrir les différentes
 * interfaces d'entraînement ou de dessin. Nettoie les ressources à la fin.
 *
 * @param argc Nombre d’arguments de la ligne de commande (non utilisé)
 * @param argv Arguments de la ligne de commande (non utilisé)
 * @return 0 en cas de succès, 1 en cas d’erreur d’initialisation
 */
int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    log_message(LOG_LEVEL_INFO, "Lancement de l'application graphique SDL2...");


    // Initialiser SDL
    log_message(LOG_LEVEL_INFO, "Initialisation de SDL...");

    if (!init_sdl("Interface Graphique", 800, 600)) {
        return 1;
    }

    // Initialiser SDL_ttf
    log_message(LOG_LEVEL_INFO, "Initialisation de SDL_ttf...");

    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        cleanup_sdl();
        return 1;
    }

    // Charger une police
    const char *fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    log_message(LOG_LEVEL_INFO, "Chargement de la police depuis %s", fontPath);

    TTF_Font *font = TTF_OpenFont(fontPath, 24);
    if (!font) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
        TTF_Quit();
        cleanup_sdl();
        return 1;
    }

    // Définir les couleurs et les boutons
    SDL_Color buttonColor = {169, 169, 169, 255}; // Gris clair
    SDL_Color borderColor = {0, 0, 0, 255};       // Noir pour la bordure
    SDL_Color textColor = {0, 0, 0, 255};         // Noir pour le texte
    SDL_Rect buttonRB = {300, 150, 200, 100};     // Bouton "R/B"
    SDL_Rect buttonCustom = {300, 300, 200, 100}; // Bouton "Personnalisé"
    SDL_Rect buttonDraw = {300, 450, 200, 100};   // Bouton "Dessiner"

    int running = 1;
   SDL_Event event;
   log_message(LOG_LEVEL_INFO, "Interface prête. Attente des interactions utilisateur...");

    while (running && globalRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                globalRunning = 0; // Fermer toutes les fenêtres
                running = 0;       // Fermer cette fenêtre
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= buttonRB.x && x <= buttonRB.x + buttonRB.w &&
                    y >= buttonRB.y && y <= buttonRB.y + buttonRB.h) {
                    log_message(LOG_LEVEL_INFO, "Bouton 'R/B' cliqué : ouverture de la fenêtre d'entraînement binaire.");
                    show_train_or_load_window(0); // Mode R/B
                    if (!globalRunning) running = 0;
                }

                if (x >= buttonCustom.x && x <= buttonCustom.x + buttonCustom.w &&
                    y >= buttonCustom.y && y <= buttonCustom.y + buttonCustom.h) {
                    log_message(LOG_LEVEL_INFO, "Bouton 'Personnalisé' cliqué : ouverture de la fenêtre multi-classes.");
                    show_train_or_load_window(1); // Mode Personnalisé
                    if (!globalRunning) running = 0;
                }

                if (x >= buttonDraw.x && x <= buttonDraw.x + buttonDraw.w &&
                    y >= buttonDraw.y && y <= buttonDraw.y + buttonDraw.h) {
                    log_message(LOG_LEVEL_INFO, "Bouton 'Dessiner' cliqué : ouverture de l'interface de dessin.");
                    show_drawing_choice_window(); // Dessiner
                    if (!globalRunning) running = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fond blanc
        SDL_RenderClear(renderer); 

        // Dessiner les boutons
        draw_button(renderer, font, "R/B", buttonRB, buttonColor, borderColor, textColor);
        draw_button(renderer, font, "Personnalise", buttonCustom, buttonColor, borderColor, textColor);
        draw_button(renderer, font, "Dessiner", buttonDraw, buttonColor, borderColor, textColor);

        SDL_RenderPresent(renderer);
    }


    // Nettoyer les ressources
    TTF_CloseFont(font);
    TTF_Quit();
    cleanup_sdl();
    log_message(LOG_LEVEL_INFO, "Fermeture de l'application et libération des ressources.");
    return 0;
}