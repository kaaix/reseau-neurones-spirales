#include "data.h"
#include <math.h>

DataPoint dataset[NB_POINTS_SPIRALE * 2];
DataPoint dataset_P[NB_POINTS_SPIRALE * MAX_CLASSES];

void generer_spirales_archimede() {
    int index = 0;
    double a = 0.0, b = 0.5, scale = 10.0;

    for (int i = 0; i < NB_POINTS_SPIRALE; i++) {
        double t = i * 0.05;
        double r = a + b * t;

        dataset[index].x = (r * cos(t)) / scale;
        dataset[index].y = (r * sin(t)) / scale;
        dataset[index].label[0] = 1.0;
        dataset[index].label[1] = 0.0;
        index++;

        dataset[index].x = (r * cos(t + M_PI)) / scale;
        dataset[index].y = (r * sin(t + M_PI)) / scale;
        dataset[index].label[0] = 0.0;
        dataset[index].label[1] = 1.0;
        index++;
    }
}

void generer_spirales_personnalisees(int nb_classes) {
    int index = 0;
    double a = 0.0, b = 0.5, scale = 10.0;

    for (int i = 0; i < NB_POINTS_SPIRALE; i++) {
        double t = i * 0.05;
        double r = a + b * t;

        for (int classe = 0; classe < nb_classes; classe++) {
            double angle = (2 * M_PI / nb_classes) * classe;
            dataset_P[index].x = (r * cos(t + angle)) / scale;
            dataset_P[index].y = (r * sin(t + angle)) / scale;

            for (int k = 0; k < nb_classes; k++) {
                dataset_P[index].label[k] = (k == classe) ? 1.0 : 0.0;
            }
            index++;
        }
    }
}
