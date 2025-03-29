#include "ui_manager.h"
#include "data.h"
#include "save.h"
#include "sdl_display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "log.h"
int globalRunning = 1; // Variable globale pour gérer la fermeture de la fenêtre


// Affiche un bouton avec une bordure et du texte centré
void draw_button(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect button, SDL_Color buttonColor, SDL_Color borderColor, SDL_Color textColor) {
    // Dessiner la bordure du bouton
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_Rect borderRect = {button.x - 2, button.y - 2, button.w + 4, button.h + 4};
    SDL_RenderFillRect(renderer, &borderRect);

    // Dessiner le fond du bouton
    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &button);

    // Dessiner le texte centré dans le bouton
    render_text(renderer, font, text, button, textColor);
}

// Affiche un texte centré dans un bouton
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Rect button, SDL_Color textColor) {
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);
    if (textSurface) {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {button.x + (button.w - textSurface->w) / 2, button.y + (button.h - textSurface->h) / 2, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void show_train_or_load_window(int mode) {
    log_choix_train_load();
    SDL_Window *choiceWindow = SDL_CreateWindow(
        "Choix : Train ou Load",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 300, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *choiceRenderer = SDL_CreateRenderer(choiceWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    SDL_Color buttonColor = {169, 169, 169, 255}; // Gris clair
    SDL_Color borderColor = {0, 0, 0, 255};       // Noir pour la bordure
    SDL_Color textColor = {0, 0, 0, 255};         // Noir pour le texte

    SDL_Rect trainButton = {50, 100, 300, 50};
    SDL_Rect loadButton = {50, 200, 300, 50};

    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                globalRunning = 0; // Permet de fermer la fenêtre principale
                running = 0; // Permet de fermer la fenêtre
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Vérifier si le clic est sur le bouton Train
                if (x >= trainButton.x && x <= trainButton.x + trainButton.w &&
                    y >= trainButton.y && y <= trainButton.y + trainButton.h) {
                    SDL_DestroyRenderer(choiceRenderer);
                    SDL_DestroyWindow(choiceWindow);

                    if (mode == 1) {
                        // Mode Personnalisé : demander le nombre de classes
                        show_custom_spirals_window();
                    } else {
                        // Mode R/B : exécuter directement l'entraînement
                        show_train_execution_window("");
                    }
                    return;
                }

                // Vérifier si le clic est sur le bouton Load
                if (x >= loadButton.x && x <= loadButton.x + loadButton.w &&
                    y >= loadButton.y && y <= loadButton.y + loadButton.h) {
                    SDL_DestroyRenderer(choiceRenderer);
                    SDL_DestroyWindow(choiceWindow);
                    show_load_window(mode);
                    return;
                }
            }
        }

        SDL_SetRenderDrawColor(choiceRenderer, 240, 240, 240, 255); // Fond gris clair
        SDL_RenderClear(choiceRenderer);

        draw_button(choiceRenderer, font, "Train", trainButton, buttonColor, borderColor, textColor);
        draw_button(choiceRenderer, font, "Load", loadButton, buttonColor, borderColor, textColor);

        SDL_RenderPresent(choiceRenderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(choiceRenderer);
    SDL_DestroyWindow(choiceWindow);
}

// Affiche une fenêtre pour Load (choix Default ou nom de sauvegarde)
void show_load_window(int mode) {
    SDL_Window *loadWindow = SDL_CreateWindow(
        "Choix : Default ou Custom",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 300, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *loadRenderer = SDL_CreateRenderer(loadWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    SDL_Color buttonColor = {169, 169, 169, 255}; // Gris clair
    SDL_Color borderColor = {0, 0, 0, 255};       // Noir pour la bordure
    SDL_Color textColor = {0, 0, 0, 255};         // Noir pour le texte

    SDL_Rect defaultButton = {50, 100, 300, 50};
    SDL_Rect customButton = {50, 200, 300, 50};

    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                globalRunning = 0; // Fermer l'application
                running = 0;
                TTF_CloseFont(font);
                SDL_DestroyRenderer(loadRenderer);
                SDL_DestroyWindow(loadWindow);
                return; 
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Vérifier si le clic est sur le bouton "Default"
                if (x >= defaultButton.x && x <= defaultButton.x + defaultButton.w &&
                    y >= defaultButton.y && y <= defaultButton.y + defaultButton.h) {
                    SDL_DestroyRenderer(loadRenderer);
                    SDL_DestroyWindow(loadWindow);

                    if (mode == 2) {
                        // Charger un modèle par défaut pour "Dessiner"
                        load_network("reseau_dessin.bin");
                    } else if(mode == 1 ) {
                      
                        // Charger un modèle par défaut pour R/B ou Personnalisé
                        load_networkv2("reseau_sauvegarde_custom.bin", mode);
                    }else {
                        load_networkv2("reseau_sauvegarde.bin", mode);
                    }
                    return;
                }

                // Vérifier si le clic est sur le bouton "Custom"
                if (x >= customButton.x && x <= customButton.x + customButton.w &&
                    y >= customButton.y && y <= customButton.y + customButton.h) {
                    SDL_DestroyRenderer(loadRenderer);
                    SDL_DestroyWindow(loadWindow);

                    if (mode == 2) {
                        // Charger un modèle personnalisé pour "Dessiner"
                        show_custom_file_input_window();
                    } else {
                        // Charger un modèle personnalisé pour R/B ou Personnalisé
                        show_custom_file_input_window();
                    }
                    return;
                }
            }
        }

        SDL_SetRenderDrawColor(loadRenderer, 240, 240, 240, 255); // Fond gris clair
        SDL_RenderClear(loadRenderer);

        draw_button(loadRenderer, font, "Default", defaultButton, buttonColor, borderColor, textColor);
        draw_button(loadRenderer, font, "Custom", customButton, buttonColor, borderColor, textColor);

        SDL_RenderPresent(loadRenderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(loadRenderer);
    SDL_DestroyWindow(loadWindow);
}

void load_network(const char *filename) {
    ReseauNeuronal *reseau = charger_reseau(filename);
    if (!reseau) {
        printf("Erreur : impossible de charger le réseau depuis '%s'.\n", filename);
        return;
    }
     log_lancement_load(filename);
    if (strcmp(filename, "reseau_dessin.bin") == 0) {
        // Ouvrir la fenêtre d'entraînement pour "Dessiner"
        show_training_window_for_drawing();
    } else {
        // Ouvrir la fenêtre d'affichage pour R/B ou Personnalisé
        SDL_Window *networkWindow = SDL_CreateWindow(
            "Réseau Chargé",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            600, 600, SDL_WINDOW_SHOWN
        );
        SDL_Renderer *networkRenderer = SDL_CreateRenderer(networkWindow, -1, SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor(networkRenderer, 0, 0, 0, 255);
        SDL_RenderClear(networkRenderer);
        colorier_ecran(networkRenderer, reseau, 600, 600);
        afficher_spirales(networkRenderer);
        SDL_RenderPresent(networkRenderer);

        // Garder la fenêtre ouverte avec gestion de SDL_QUIT
        int running = 1;
        SDL_Event event;
        while (running && globalRunning) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    globalRunning = 0;
                    running = 0;
                }
            }
            SDL_Delay(10);
        }

        SDL_DestroyRenderer(networkRenderer);
        SDL_DestroyWindow(networkWindow);
    }

    detruire_reseau(reseau);
}

void load_networkv2(const char *filename,int mode ) {
    ReseauNeuronal *reseau = charger_reseau(filename);
    if (!reseau) {
        printf("Erreur : impossible de charger le réseau depuis '%s'.\n", filename);
        return;
    } 
    log_lancement_load(filename);
     if( mode == 1) {
       int  x = charger_entier("nb_sauvegarde_custom.bin");
      show_train_execution_window_custom(x,"reseau_sauvegarde_custom.bin");
     }else{
         show_train_execution_window("reseau_sauvegarde.bin");
     }
      
 

  
}
void show_train_execution_window(const char *filename) {
    log_lancement_train();
    // 1) Créer la fenêtre
    SDL_Window *trainWindow = SDL_CreateWindow(
        "Apprentissage Continu (R/B)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        600, 600, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *trainRenderer = SDL_CreateRenderer(trainWindow, -1, SDL_RENDERER_ACCELERATED);

    srand((unsigned)time(NULL));

    // 2) Générer la spirale R/B
    generer_spirales_archimede();

    // 3) Tenter de charger un réseau existant depuis "filename"
    //    Si non trouvé, on crée un nouveau réseau
    ReseauNeuronal *reseau = charger_reseau(filename);
    if (!reseau) {
        printf("Aucun fichier '%s' trouvé. Création d'un nouveau réseau R/B.\n", filename);

        // 2 entrées => 5 couches => 10 neurones par couche cachée => 2 neurones en sortie
        reseau = creer_reseau(2, 5, (int[]){10, 10, 10, 10, 2});
    } else {
        printf("Fichier '%s' chargé. Reprise de l'entraînement R/B.\n", filename);
    }

    double epsilon = 0.001; // Taux d'apprentissage

    // 4) Boucle d’événements + apprentissage en continu
    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        // a) Gérer les événements SDL
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                globalRunning = 0;
            }
        }

        // b) Faire un “batch” d’apprentissage (p. ex. 150 000 itérations)
        for (int i = 0; i < 150000; i++) {
            int idx = rand() % (NB_POINTS_SPIRALE * 2);
            double entree[2] = { dataset[idx].x, dataset[idx].y };
            propagation(reseau, entree);
            backpropagation(reseau, entree, dataset[idx].label, epsilon);
        }

        // c) Afficher la frontière de décision et la spirale
        SDL_SetRenderDrawColor(trainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(trainRenderer);

        colorier_ecran(trainRenderer, reseau, 600, 600);
        afficher_spirales(trainRenderer);

        SDL_RenderPresent(trainRenderer);

        // d) Petite pause (réduit usage CPU + rend l'animation visible)
        SDL_Delay(50);
    }

    // 5) Sauvegarder le réseau sur disque (quand on ferme la fenêtre)
    sauvegarder_reseau(reseau, "reseau_sauvegarde.bin");
    printf("Réseau (R/B) sauvegardé dans '%s'.\n", filename);

    // 6) Libérer
    detruire_reseau(reseau);
    SDL_DestroyRenderer(trainRenderer);
    SDL_DestroyWindow(trainWindow);
}




void show_custom_file_input_window() {
    SDL_Window *inputWindow = SDL_CreateWindow(
        "Entrer le nom du fichier",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        500, 200, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *inputRenderer = SDL_CreateRenderer(inputWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color inputBoxColor = {255, 255, 255, 255}; // Blanc
    SDL_Color borderColor = {0, 0, 0, 255};         // Noir pour la bordure

    SDL_Rect inputBox = {50, 75, 400, 50};
    char customFile[256] = ""; // Buffer pour le nom du fichier
    int cursorPosition = 0;    // Position du curseur dans le champ de texte
    int showCursor = 1;        // Indique si le curseur est visible (pour clignoter)
    Uint32 lastBlinkTime = SDL_GetTicks();

    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                globalRunning = 0; // Permet de fermer la fenêtre principale
                running = 0;
            } else if (event.type == SDL_TEXTINPUT) {
                // Ajouter le texte saisi au buffer
                if (cursorPosition < 255) {
                    strcat(customFile, event.text.text);
                    cursorPosition += strlen(event.text.text);
                }
            } else if (event.type == SDL_KEYDOWN) {
                // Gérer la suppression (backspace)
                if (event.key.keysym.sym == SDLK_BACKSPACE && cursorPosition > 0) {
                    customFile[--cursorPosition] = '\0';
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    // Vérifier si le fichier existe
                    strcat(customFile, ".bin");
                    FILE *file = fopen(customFile, "rb");
                    if (file) {
                        fclose(file);
                        SDL_DestroyRenderer(inputRenderer);
                        SDL_DestroyWindow(inputWindow);
                        // Charger le fichier
                        load_network(customFile);
                        return;
                    } else {
                        printf("Erreur : le fichier '%s' n'existe pas.\n", customFile);
                    }
                }
            }
        }

        // Gérer le clignotement du curseur
        if (SDL_GetTicks() - lastBlinkTime > 500) {
            showCursor = !showCursor;
            lastBlinkTime = SDL_GetTicks();
        }

        SDL_SetRenderDrawColor(inputRenderer, 240, 240, 240, 255); // Fond gris clair
        SDL_RenderClear(inputRenderer);

        // Dessiner la bordure de la zone de texte
        SDL_SetRenderDrawColor(inputRenderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_Rect borderBox = {inputBox.x - 2, inputBox.y - 2, inputBox.w + 4, inputBox.h + 4};
        SDL_RenderFillRect(inputRenderer, &borderBox);

        // Dessiner la zone de texte
        SDL_SetRenderDrawColor(inputRenderer, inputBoxColor.r, inputBoxColor.g, inputBoxColor.b, inputBoxColor.a);
        SDL_RenderFillRect(inputRenderer, &inputBox);

        // Afficher le texte saisi
        render_text(inputRenderer, font, customFile, inputBox, textColor);

        // Dessiner le curseur clignotant
        if (showCursor) {
            int cursorX = inputBox.x + 10 + TTF_SizeText(font, customFile, NULL, NULL); // Position dynamique
            SDL_SetRenderDrawColor(inputRenderer, 0, 0, 0, 255); // Noir
            SDL_Rect cursor = {cursorX, inputBox.y + 10, 2, inputBox.h - 20};
            SDL_RenderFillRect(inputRenderer, &cursor);
        }

        SDL_RenderPresent(inputRenderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(inputRenderer);
    SDL_DestroyWindow(inputWindow);
}

void show_custom_spirals_window() {
    SDL_Window *customWindow = SDL_CreateWindow(
        "Nombre de Classes",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 300, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *customRenderer = SDL_CreateRenderer(customWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color inputBoxColor = {255, 255, 255, 255};
    SDL_Color borderColor = {0, 0, 0, 255};

    SDL_Rect inputBox = {50, 100, 300, 50};
    SDL_Rect infoTextRect = {50, 50, 300, 30};
    char inputText[3] = ""; // Pour stocker le nombre de classes (max 2 chiffres)
    int cursorPosition = 0;
    int showCursor = 1; // Indique si le curseur est visible (pour clignoter)
    Uint32 lastBlinkTime = SDL_GetTicks();

    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                globalRunning = 0; // Permet de fermer la fenêtre principale
                running = 0;
                break; 
            } else if (event.type == SDL_TEXTINPUT) {
                if (cursorPosition < 2 && event.text.text[0] >= '0' && event.text.text[0] <= '9') {
                    inputText[cursorPosition++] = event.text.text[0];
                    inputText[cursorPosition] = '\0';
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && cursorPosition > 0) {
                    inputText[--cursorPosition] = '\0';
                } else if (event.key.keysym.sym == SDLK_RETURN) {
                    int nb_classes = atoi(inputText);
                    if (nb_classes >= 2 && nb_classes <= 10) {
                        running = 0;
                        running = 0;
                        SDL_DestroyRenderer(customRenderer);
                        SDL_DestroyWindow(customWindow);
                        show_train_execution_window_custom(nb_classes, "");
                        return;
                        
                    } else {
                        printf("Erreur : le nombre de classes doit être entre 2 et 10.\n");
                    }
                }
            }
        }

        // Gérer le clignotement du curseur
        if (SDL_GetTicks() - lastBlinkTime > 500) {
            showCursor = !showCursor;
            lastBlinkTime = SDL_GetTicks();
        }

        SDL_SetRenderDrawColor(customRenderer, 240, 240, 240, 255); // Fond gris clair
        SDL_RenderClear(customRenderer);

        // Afficher le texte explicatif
        render_text(customRenderer, font, "Max classes: 10", infoTextRect, textColor);

        // Dessiner la zone de texte
        SDL_SetRenderDrawColor(customRenderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_Rect borderBox = {inputBox.x - 2, inputBox.y - 2, inputBox.w + 4, inputBox.h + 4};
        SDL_RenderFillRect(customRenderer, &borderBox);

        SDL_SetRenderDrawColor(customRenderer, inputBoxColor.r, inputBoxColor.g, inputBoxColor.b, inputBoxColor.a);
        SDL_RenderFillRect(customRenderer, &inputBox);

        // Afficher le texte saisi
        render_text(customRenderer, font, inputText, inputBox, textColor);

        // Dessiner le curseur clignotant
        if (showCursor) {
            int cursorX = inputBox.x + 10 + (cursorPosition * 12); // Position dynamique du curseur
            SDL_SetRenderDrawColor(customRenderer, 0, 0, 0, 255); // Noir
            SDL_Rect cursor = {cursorX, inputBox.y + 10, 2, inputBox.h - 20};
            SDL_RenderFillRect(customRenderer, &cursor);
        }

        SDL_RenderPresent(customRenderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(customRenderer);
    SDL_DestroyWindow(customWindow);
}

void show_train_execution_window_custom(int nb_classes, const char *filename) {
    log_lancement_train();
    // 1) Créer la fenêtre
    SDL_Window *window = SDL_CreateWindow(
        "Spirales Personnalisées - Apprentissage Continu",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        600, 600, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand((unsigned)time(NULL));

    // 2) Générer le dataset multi-classes
    generer_spirales_personnalisees(nb_classes);

    // 3) Charger (ou créer) le réseau
    ReseauNeuronal *reseau = charger_reseau(filename);
    if (!reseau) {
        // Aucun fichier => on crée un réseau neuf
        printf("Aucun fichier sauvegardé '%s'.\n", filename);

        int *taille_couches = malloc((nb_classes + 3) * sizeof(int));
        for (int i = 0; i < nb_classes + 2; i++) {
            taille_couches[i] = 10; // 10 neurones par couche cachée
        }
        taille_couches[nb_classes + 2] = nb_classes; // dernière couche
        reseau = creer_reseau(2, nb_classes + 2, taille_couches);
        free(taille_couches);

    } else {
        // On reprend le réseau chargé
        printf("Fichier '%s' chargé avec succès. Reprise de l'entraînement...\n", filename);
    }

    double epsilon = 0.001; // Taux d'apprentissage

    // 4) Boucle d’événements + apprentissage “en continu”
    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        // a) Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                globalRunning = 0;
            }
        }

        // b) Effectuer un bloc d’entraînement (150k itérations)
        for (int step = 0; step < 150000; step++) {
            int idx = rand() % (nb_classes * NB_POINTS_SPIRALE);
            double entree[2] = { dataset[idx].x, dataset[idx].y };
            propagation(reseau, entree);
            backpropagation(reseau, entree, dataset[idx].label, epsilon);
        }

        // c) Effacer l’écran (fond noir)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // d) Colorier selon la frontière de décision
        colorier_ecran(renderer, reseau, 600, 600);

        // e) Dessiner la spirale
        afficher_spirales(renderer);

        // f) Présenter le rendu
        SDL_RenderPresent(renderer);

        // g) Petite pause
        SDL_Delay(50);
    }

    // 5) Sauvegarder le réseau
    sauvegarder_reseau(reseau, "reseau_sauvegarde_custom.bin");
    sauvegarder_entier(nb_classes, "nb_sauvegarde_custom.bin");
    printf("Réseau multi-classes sauvegardé.\n");

    // 6) Libération
    detruire_reseau(reseau);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void show_drawing_window() {
    SDL_Window *win = SDL_CreateWindow(
        "Dessine tes données",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    // Charger une police
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (!font) {
        printf("Erreur : impossible de charger la police.\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        return;
    }

    nb_dessin = 0; // Réinitialiser les points dessinés
    int running = 1;
    SDL_Event e;

    // Couleur active (par défaut : rouge)
    int r = 255, g = 0, b = 0; // Composantes de la couleur active
    int drawing = 0; // Indique si la souris est en train de dessiner

    // Dimensions initiales de la fenêtre
    int windowWidth = 800, windowHeight = 600;

    while (running && globalRunning) {
        // Récupérer la taille actuelle de la fenêtre
        SDL_GetWindowSize(win, &windowWidth, &windowHeight);

        // Recalculer les zones dynamiquement
        SDL_Rect drawingArea = {20, 20, windowWidth - 240, windowHeight - 40}; // Zone de dessin
        SDL_Rect controlsArea = {windowWidth - 200, 20, 180, windowHeight - 40}; // Zone des contrôles

        SDL_Rect redSlider = {controlsArea.x + 20, controlsArea.y + 50, controlsArea.w - 40, 20};
        SDL_Rect greenSlider = {controlsArea.x + 20, controlsArea.y + 100, controlsArea.w - 40, 20};
        SDL_Rect blueSlider = {controlsArea.x + 20, controlsArea.y + 150, controlsArea.w - 40, 20};

        SDL_Rect validateButton = {controlsArea.x + 20, controlsArea.y + controlsArea.h - 80, controlsArea.w - 40, 40};
        SDL_Rect clearButton = {controlsArea.x + 20, controlsArea.y + controlsArea.h - 140, controlsArea.w - 40, 40};

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
                globalRunning = 0;
                TTF_CloseFont(font);
                SDL_DestroyRenderer(rend);
                SDL_DestroyWindow(win);
                return; 
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                // Vérifier si le clic est sur un curseur
                if (x >= redSlider.x && x <= redSlider.x + redSlider.w && y >= redSlider.y && y <= redSlider.y + redSlider.h) {
                    r = (x - redSlider.x) * 255 / redSlider.w; // Ajuster la composante rouge
                } else if (x >= greenSlider.x && x <= greenSlider.x + greenSlider.w && y >= greenSlider.y && y <= greenSlider.y + greenSlider.h) {
                    g = (x - greenSlider.x) * 255 / greenSlider.w; // Ajuster la composante verte
                } else if (x >= blueSlider.x && x <= blueSlider.x + blueSlider.w && y >= blueSlider.y && y <= blueSlider.y + blueSlider.h) {
                    b = (x - blueSlider.x) * 255 / blueSlider.w; // Ajuster la composante bleue
                }

                // Vérifier si le clic est dans le bouton "Effacer"
                if (x >= clearButton.x && x <= clearButton.x + clearButton.w &&
                    y >= clearButton.y && y <= clearButton.y + clearButton.h) {
                    nb_dessin = 0; // Effacer les points dessinés
                }

                // Vérifier si le clic est dans le bouton "Valider et Entraîner"
                if (x >= validateButton.x && x <= validateButton.x + validateButton.w &&
                    y >= validateButton.y && y <= validateButton.y + validateButton.h) {
                    show_training_window_for_drawing();
                    running = 0; // Fermer la fenêtre après l'entraînement
                }

                // Ajouter un point dans la zone de dessin
                if (x >= drawingArea.x && x <= drawingArea.x + drawingArea.w &&
                    y >= drawingArea.y && y <= drawingArea.y + drawingArea.h &&
                    nb_dessin < MAX_DESSIN) {
                    double nx = (double)(x - drawingArea.x) / drawingArea.w * 2.0 - 1.0; // Normaliser en [-1, 1]
                    double ny = (double)(y - drawingArea.y) / drawingArea.h * 2.0 - 1.0;

                    dessin[nb_dessin] = (DataPoint3){nx, ny, {r / 255.0, g / 255.0, b / 255.0}};
                    nb_dessin++;
                }
                drawing = 1; // Activer le mode dessin
            } else if (e.type == SDL_MOUSEBUTTONUP) {
                drawing = 0; // Désactiver le mode dessin
            } else if (e.type == SDL_MOUSEMOTION && drawing) {
                int x = e.motion.x;
                int y = e.motion.y;

                if (x >= drawingArea.x && x <= drawingArea.x + drawingArea.w &&
                    y >= drawingArea.y && y <= drawingArea.y + drawingArea.h &&
                    nb_dessin < MAX_DESSIN) {
                    double nx = (double)(x - drawingArea.x) / drawingArea.w * 2.0 - 1.0; // Normaliser en [-1, 1]
                    double ny = (double)(y - drawingArea.y) / drawingArea.h * 2.0 - 1.0;

                    dessin[nb_dessin] = (DataPoint3){nx, ny, {r / 255.0, g / 255.0, b / 255.0}};
                    nb_dessin++;
                }
            }
        }

        SDL_SetRenderDrawColor(rend, 240, 240, 240, 255); // Fond gris clair
        SDL_RenderClear(rend);

        // Dessiner la zone de dessin
        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255); // Fond blanc
        SDL_RenderFillRect(rend, &drawingArea);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Bordure noire
        SDL_RenderDrawRect(rend, &drawingArea);

        // Dessiner les points
        for (int i = 0; i < nb_dessin; i++) {
            int px = drawingArea.x + (int)((dessin[i].x + 1.0) / 2.0 * drawingArea.w);
            int py = drawingArea.y + (int)((dessin[i].y + 1.0) / 2.0 * drawingArea.h);

            SDL_SetRenderDrawColor(rend, (Uint8)(dessin[i].label[0] * 255),
                                         (Uint8)(dessin[i].label[1] * 255),
                                         (Uint8)(dessin[i].label[2] * 255), 255);
            SDL_Rect pointRect = {px - 3, py - 3, 6, 6};
            SDL_RenderFillRect(rend, &pointRect);
        }

        // Dessiner la zone des contrôles
        SDL_SetRenderDrawColor(rend, 220, 220, 220, 255); // Fond gris clair
        SDL_RenderFillRect(rend, &controlsArea);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Bordure noire
        SDL_RenderDrawRect(rend, &controlsArea);

        // Dessiner les curseurs
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); // Rouge
        SDL_RenderFillRect(rend, &redSlider);
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); // Vert
        SDL_RenderFillRect(rend, &greenSlider);
        SDL_SetRenderDrawColor(rend, 0, 0, 255, 255); // Bleu
        SDL_RenderFillRect(rend, &blueSlider);

        // Dessiner les indicateurs de position sur les curseurs
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // Noir
        SDL_Rect redCursor = {redSlider.x + (r * redSlider.w / 255) - 5, redSlider.y - 5, 10, 30};
        SDL_Rect greenCursor = {greenSlider.x + (g * greenSlider.w / 255) - 5, greenSlider.y - 5, 10, 30};
        SDL_Rect blueCursor = {blueSlider.x + (b * blueSlider.w / 255) - 5, blueSlider.y - 5, 10, 30};
        SDL_RenderFillRect(rend, &redCursor);
        SDL_RenderFillRect(rend, &greenCursor);
        SDL_RenderFillRect(rend, &blueCursor);

        // Dessiner les indicateurs numériques
        char colorValue[16];
        SDL_Color textColor = {0, 0, 0, 255}; // Noir

        // Indicateur pour le rouge
        SDL_Rect textRect = {redSlider.x - 60, redSlider.y, 50, 20}; // Position à gauche du curseur
        snprintf(colorValue, sizeof(colorValue), "%d", r);
        render_text(rend, font, colorValue, textRect, textColor);

        // Indicateur pour le vert
        textRect.y = greenSlider.y;
        snprintf(colorValue, sizeof(colorValue), "%d", g);
        render_text(rend, font, colorValue, textRect, textColor);

        // Indicateur pour le bleu
        textRect.y = blueSlider.y;
        snprintf(colorValue, sizeof(colorValue), "%d", b);
        render_text(rend, font, colorValue, textRect, textColor);

        // Dessiner les boutons
        SDL_Color buttonColor = {169, 169, 169, 255}; // Gris clair
        SDL_Color borderColor = {0, 0, 0, 255};       // Noir pour la bordure
        SDL_Color buttonTextColor = {0, 0, 0, 255};   // Noir pour le texte
        draw_button(rend, font, "Effacer", clearButton, buttonColor, borderColor, buttonTextColor);
        draw_button(rend, font, "Valider", validateButton, buttonColor, borderColor, buttonTextColor);

        SDL_RenderPresent(rend);
        SDL_Delay(10);
    }

    // Libérer la police
    TTF_CloseFont(font);

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
}


void show_training_window_for_drawing() {
    if (nb_dessin == 0) {
        printf("Aucun point dessiné !\n");
        return;
    }

    // (1) Créer une fenêtre pour l'entraînement
    SDL_Window *trainWindow = SDL_CreateWindow(
        "Entraînement sur les points dessinés (RGB)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        600, 600, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *trainRenderer = SDL_CreateRenderer(trainWindow, -1, SDL_RENDERER_ACCELERATED);

    // (2) Créer un réseau 2 entrées (x, y) -> 3 sorties (R, G, B)
    //     + 3 ou 4 couches cachées de 10 neurones, au choix.
    int taille_couches[] = {10, 10, 10, 10, 3};
    ReseauNeuronal *reseau = creer_reseau(2, 5, taille_couches);

    double epsilon = 0.001;  // Taux d’apprentissage

    // (3) Boucle d’entraînement + affichage
    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        // (a) Gérer les événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                globalRunning = 0; 
                // Sauvegarde (optionnel) si on veut le faire avant de quitter brutalement :
                sauvegarder_reseau(reseau, "reseau_dessin.bin");
                detruire_reseau(reseau);
                SDL_DestroyRenderer(trainRenderer);
                SDL_DestroyWindow(trainWindow);
                return;
            }
        }

        // (b) Effectuer un bloc d’apprentissage
        //     Exemple : 100 000 itérations 
        //     (ou un autre nombre selon votre convenance)
        for (int step = 0; step < 100000; step++) {
            int i = rand() % nb_dessin; // Tirage aléatoire d’un point
            double entree[2] = { dessin[i].x, dessin[i].y };

            // Propagation
            propagation(reseau, entree);

            // Rétropropagation en passant 3 composantes (dessin[i].label[0..2])
            backpropagation(reseau, entree, dessin[i].label, epsilon);
        }

        // (c) Effacer l’écran (noir par ex.)
        SDL_SetRenderDrawColor(trainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(trainRenderer);

        // (d) Colorier selon 3 composantes (R, G, B)
        colorier_ecran_rgb(trainRenderer, reseau, 600, 600);

        // (e) Mettre à jour l’affichage
        SDL_RenderPresent(trainRenderer);

        // (f) Petite pause
        SDL_Delay(50);
    }

    // (4) Quand on sort de la boucle => sauvegarde + libération
    sauvegarder_reseau(reseau, "reseau_dessin.bin");
    printf("Réseau sauvegardé dans 'reseau_dessin.bin'.\n");

    detruire_reseau(reseau);
    SDL_DestroyRenderer(trainRenderer);
    SDL_DestroyWindow(trainWindow);
}


void show_drawing_choice_window() {
    SDL_Window *choiceWindow = SDL_CreateWindow(
        "Choix : Nouveau ou Charger",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 300, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *choiceRenderer = SDL_CreateRenderer(choiceWindow, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    SDL_Color buttonColor = {169, 169, 169, 255}; // Gris clair
    SDL_Color borderColor = {0, 0, 0, 255};       // Noir pour la bordure
    SDL_Color textColor = {0, 0, 0, 255};         // Noir pour le texte

    SDL_Rect newButton = {50, 100, 300, 50}; // Bouton "Nouveau"
    SDL_Rect loadButton = {50, 200, 300, 50}; // Bouton "Charger"

    int running = 1;
    SDL_Event event;

    while (running && globalRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                globalRunning = 0; // Fermer l'application
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Vérifier si le clic est sur le bouton "Nouveau"
                if (x >= newButton.x && x <= newButton.x + newButton.w &&
                    y >= newButton.y && y <= newButton.y + newButton.h) {
                    SDL_DestroyRenderer(choiceRenderer);
                    SDL_DestroyWindow(choiceWindow);
                    show_drawing_window(); // Ouvrir la fenêtre de dessin
                    return;
                }

                // Vérifier si le clic est sur le bouton "Charger"
                if (x >= loadButton.x && x <= loadButton.x + loadButton.w &&
                    y >= loadButton.y && y <= loadButton.y + loadButton.h) {
                    SDL_DestroyRenderer(choiceRenderer);
                    SDL_DestroyWindow(choiceWindow);
                    show_load_window(2); // Charger un modèle (Default ou Custom)
                    return;
                }
            }
        }

        SDL_SetRenderDrawColor(choiceRenderer, 240, 240, 240, 255); // Fond gris clair
        SDL_RenderClear(choiceRenderer);

        draw_button(choiceRenderer, font, "Nouveau", newButton, buttonColor, borderColor, textColor);
        draw_button(choiceRenderer, font, "Charger", loadButton, buttonColor, borderColor, textColor);

        SDL_RenderPresent(choiceRenderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(choiceRenderer);
    SDL_DestroyWindow(choiceWindow);
}