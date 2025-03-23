#ifndef DATA_H
#define DATA_H
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "neural_network.h"
#include <SDL.h>
#include "sdl_display.h"

#define NB_POINTS_SPIRALE 500
#define MAX_CLASSES 10
#define MAX_DESSIN 10000

typedef struct {
    double x;
    double y;
    double label[2];
} DataPoint;

typedef struct {
    double x;
    double y;
    double label[3];
} DataPoint3;

extern int nb_dessin;
extern DataPoint3 dessin[MAX_DESSIN];

// le dataset_p contiendra MAX_CLASSES spirales
// (une spirale pour chaque classe)
extern DataPoint dataset_P[NB_POINTS_SPIRALE * MAX_CLASSES];

// Le dataset contiendra 2*NB_POINTS_SPIRALE points (une spirale pour chaque classe)
extern DataPoint dataset[NB_POINTS_SPIRALE * 2]; // 2 classes (bleu et rouge)

// Génère les points des spirales (normalisés dans [-1, 1])
void generer_spirales_archimede();

// Génère des spirales personnalisées avec un nombre arbitraire de classes
void generer_spirales_personnalisees(int nb_classes);

// Colorie l'écran en fonction des sorties du réseau
void colorier_ecran(SDL_Renderer *renderer, ReseauNeuronal *reseau, int width, int height);


#endif
