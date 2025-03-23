#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "sdl_display.h"
#include "ui_manager.h"
/*
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [train|load] [fichier_sauvegarde]\n", argv[0]);
        return 1;
    }

    const char *mode = argv[1];
    const char *fichier_sauvegarde = (argc >= 3) ? argv[2] : "reseau_sauvegarde.bin";
     //const char *fichier_sauvegarde = argv[2] : "reseau_sauvegarde.bin";
    //int nb_classes = (argc >= 4) ? atoi(argv[3]) : 2;

    // 1) Génération du dataset en spirale
    generer_spirales_archimede();

    //generer_spirales_personnalisees(nb_classes);

    ReseauNeuronal *reseau = NULL;

    if (strcmp(mode, "load") == 0) {
        // Charger un réseau depuis un fichier
        reseau = charger_reseau(fichier_sauvegarde);
        if (!reseau) {
            printf("Erreur : impossible de charger le réseau depuis '%s'.\n", fichier_sauvegarde);
            return 1;
        }
        printf("Réseau chargé avec succès depuis '%s'.\n", fichier_sauvegarde);
    } else if (strcmp(mode, "train") == 0) {
        // Créer un nouveau réseau
        int taille_couches[] = {10, 10, 10, 10, 2};
        reseau = creer_reseau(2, 5, taille_couches);
    } else {
        printf("Mode inconnu : %s. Utilisez 'train' ou 'load'.\n", mode);
        return 1;
    }

    // pour les classes personnalisées
    
        if (strcmp(mode, "load") == 0) {
        // Charger un réseau depuis un fichier
        reseau = charger_reseau(fichier_sauvegarde);
        if (!reseau) {
            printf("Erreur : impossible de charger le réseau depuis '%s'.\n", fichier_sauvegarde);
            return 1;
        }
        printf("Réseau chargé avec succès depuis '%s'.\n", fichier_sauvegarde);
    } else if (strcmp(mode, "train") == 0) {
        // Créer un nouveau réseau
        int *taille_couches = malloc((nb_classes + 3) * sizeof(int));
        for (int i = 0; i < nb_classes + 2; i++) {
            taille_couches[i] = 10; // Exemple : 10 neurones par couche cachée
        }
        taille_couches[nb_classes + 2] = nb_classes; // Dernière couche = nb_classes

        reseau = creer_reseau(2, nb_classes + 2, taille_couches);
        free(taille_couches);
    } else {
        printf("Mode inconnu : %s. Utilisez 'train' ou 'load'.\n", mode);
        return 1;
    }

    // 2) Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Spirales - Apprentissage continu",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          600, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand((unsigned)time(NULL));
    double epsilon = 0.001; // Taux d'apprentissage plus faible pour une convergence progressive

    // 3) Boucle d’événements + apprentissage en continu
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

    // Sauvegarde du réseau si en mode 'train'
    if (strcmp(mode, "train") == 0) {
        sauvegarder_reseau(reseau, fichier_sauvegarde);
        printf("Réseau sauvegardé dans '%s'.\n", fichier_sauvegarde);
    }

    // Libération
    detruire_reseau(reseau);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    // Initialiser SDL
    if (!init_sdl("Interface Graphique", 800, 600)) {
        return 1;
    }

    // Initialiser SDL_ttf
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        cleanup_sdl();
        return 1;
    }

    // Charger une police
    const char *fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
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

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Vérifier si le clic est dans le bouton "R/B"
                if (x >= buttonRB.x && x <= buttonRB.x + buttonRB.w &&
                    y >= buttonRB.y && y <= buttonRB.y + buttonRB.h) {
                    show_train_or_load_window(0); // Mode R/B
                    running = 0; // Fermer la fenêtre actuelle
                }

                // Vérifier si le clic est dans le bouton "Personnalisé"
                if (x >= buttonCustom.x && x <= buttonCustom.x + buttonCustom.w &&
                    y >= buttonCustom.y && y <= buttonCustom.y + buttonCustom.h) {
                    show_train_or_load_window(1); // Mode Personnalisé
                    running = 0; // Fermer la fenêtre actuelle
                }

                // Vérifier si le clic est dans le bouton "Dessiner"
                if (x >= buttonDraw.x && x <= buttonDraw.x + buttonDraw.w &&
                    y >= buttonDraw.y && y <= buttonDraw.y + buttonDraw.h) {
                    show_drawing_choice_window(); // Afficher le choix entre "Nouveau" et "Charger"
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

    return 0;
}