#include "data.h"
#include <math.h>
#include "sdl_display.h"
#include "log.h"


//DataPoint dataset[NB_POINTS_SPIRALE * MAX_CLASSES];
DataPoint dataset_P[NB_POINTS_SPIRALE * MAX_CLASSES];
// Le dataset contiendra 2*NB_POINTS_SPIRALE points (une spirale pour chaque classe)
DataPoint dataset[NB_POINTS_SPIRALE * 2]; // 2 classes (bleu et rouge)

int nb_dessin = 0; // Compteur pour le nombre de points dessinés
DataPoint3 dessin[MAX_DESSIN]; // Tableau pour stocker les points à dessiner

// Génère les points des spirales d'Archimède (normalisés dans [-1, 1])
void generer_spirales_archimede() {
    log_generation_spirale("R/B");
    int index = 0;
    double a = 0.0;        // Décalage initial (tu peux ajuster)
    double b = 0.5;        // Contrôle l'espacement entre les spires
    // Choisis un facteur de normalisation pour ramener les points dans [-1,1]
    double scale = 10.0 ; // Ajuste cette valeur si besoin

    for (int i = 0; i < NB_POINTS_SPIRALE; i++) {
        double t = i * 0.05;          // Paramètre angulaire
        double r = a + b * t;        // Rayon selon la spirale d'Archimède

        // Génération de la spirale bleue (classe 1)
        dataset[index].x = (r * cos(t)) / scale;
        dataset[index].y = (r * sin(t)) / scale;
        dataset[index].label[0] = 1.0;   // bleu
        dataset[index].label[1] = 0.0;
        index++;

        // Génération de la spirale rouge (classe 2)
        // On décale l'angle de PI pour obtenir l'opposée
        dataset[index].x = (r * cos(t + M_PI)) / scale;
        dataset[index].y = (r * sin(t + M_PI)) / scale;
        dataset[index].label[0] = 0.0;
        dataset[index].label[1] = 1.0;   // rouge
        index++;
    }
}


void colorier_ecran(SDL_Renderer *renderer, ReseauNeuronal *reseau, int width, int height) {
    // Ici, on suppose que les entrées du réseau sont dans [-1, 1]
    log_colorier_once("R/B");
    double range = 0.8;
    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            double x = ((double)px / (width - 1)) * (2 * range) - range;  // x ∈ [-1, 1]
            double y = ((double)py / (height - 1)) * (2 * range) - range;  // y ∈ [-1, 1]
            double input[2] = { x, y };

            propagation(reseau, input);
            int last = reseau->n_couches - 1;
            double s_bleu  = reseau->couches[last][0].sortie;  // neurone 0 pour la classe bleu
            double s_rouge = reseau->couches[last][1].sortie;  // neurone 1 pour la classe rouge

            // On convertit la sortie de tanh (∈[-1,1]) en probabilité ∈[0,1]
            double p_bleu  = (s_bleu  + 1.0) / 2.0;
            double p_rouge = (s_rouge + 1.0) / 2.0;

            SDL_Color col = melange_couleurs(p_bleu, p_rouge);
            SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 255);
            SDL_RenderDrawPoint(renderer, px, py);
        }
    }
}
void colorier_ecran_rgb(SDL_Renderer *renderer, ReseauNeuronal *reseau, int width, int height)
{ 
    log_colorier_once("RGB");
    // On suppose tanh => sortie dans [-1,1].
    // range=1.0 (ou 0.8) c’est vous qui voyez
    double range = 1.0;
    int last = reseau->n_couches - 1;

    for(int py = 0; py < height; py++) {
        for(int px = 0; px < width; px++) {

            // 1) Convertir (px,py) en (x,y) dans [-range..+range]
            double x = ((double)px / (width - 1)) * (2.0 * range) - range;
            double y = ((double)py / (height - 1)) * (2.0 * range) - range;
            double entree[2] = { x, y };

            // 2) Propagation
            propagation(reseau, entree);

            // 3) Récupérer la sortie R, G, B
            double sr = reseau->couches[last][0].sortie;  // [-1..1]
            double sg = reseau->couches[last][1].sortie;
            double sb = reseau->couches[last][2].sortie;

            // 4) Passer dans melange_couleurs_rgb
            SDL_Color col = melange_couleurs_rgb(sr, sg, sb);

            // 5) Dessiner le pixel
            SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
            SDL_RenderDrawPoint(renderer, px, py);
        }
    }
}

// Génère des spirales personnalisées avec un nombre arbitraire de classes
void generer_spirales_personnalisees(int nb_classes) {
    log_generation_spirale("multi-classes");
    int index = 0;
    double a = 0.0;        // Décalage initial
    double b = 0.5;        // Contrôle l'espacement entre les spires
    double scale = 10.0;   // Facteur de normalisation

    for (int i = 0; i < NB_POINTS_SPIRALE; i++) {
        double t = i * 0.05;          // Paramètre angulaire
        double r = a + b * t;        // Rayon selon la spirale d'Archimède

        for (int classe = 0; classe < nb_classes; classe++) {
            double angle = (2 * M_PI / nb_classes) * classe; // Décalage angulaire pour chaque classe
            dataset[index].x = (r * cos(t + angle)) / scale;
            dataset[index].y = (r * sin(t + angle)) / scale;

            // Initialiser les labels pour chaque classe
            for (int k = 0; k < nb_classes; k++) {
                dataset[index].label[k] = (k == classe) ? 1.0 : 0.0;
            }
            index++;
        }
    }
}