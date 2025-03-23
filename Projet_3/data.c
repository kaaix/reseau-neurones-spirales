#include "data.h"
#include <math.h>

DataPoint dataset[NB_POINTS_SPIRALE * 2];

void generer_spirales() {
    int index = 0;
    // Définir la valeur maximale de t pour normaliser les données (par exemple, t_max = NB_POINTS_SPIRALE * 0.1)
   double scale = NB_POINTS_SPIRALE * 0.1; // Par exemple, 500 * 0.1 = 50
    for (int i = 0; i < NB_POINTS_SPIRALE; i++) {
        double t = i * 0.1;
        // Spirale bleue (classe 1)
        dataset[index].x = (t * cos(t)) / scale;
        dataset[index].y = (t * sin(t)) / scale;
        dataset[index].label[0] = 1.0; // bleu
        dataset[index].label[1] = 0.0;
        index++;

        // Spirale rouge (classe 2)
        dataset[index].x = (-t * cos(t)) / scale;
        dataset[index].y = (-t * sin(t)) / scale;
        dataset[index].label[0] = 0.0;
        dataset[index].label[1] = 1.0; // rouge
        index++;
    }
}

void colorier_ecran(SDL_Renderer *renderer, ReseauNeuronal *reseau, int width, int height) {
    // Ici, on suppose que les entrées du réseau sont dans [-1, 1]
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
            double p_bleu  = (s_bleu  + 1.0) ;/// 2.0;
            double p_rouge = (s_rouge + 1.0) ;/// 2.0;

            SDL_Color col = melange_couleurs(p_bleu, p_rouge);
            SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, 255);
            SDL_RenderDrawPoint(renderer, px, py);
        }
    }
}
