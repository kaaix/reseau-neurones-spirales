#ifndef SAVE_H
#define SAVE_H

#include "neural_network.h"

// Sauvegarde un réseau neuronal dans un fichier
void sauvegarder_reseau(ReseauNeuronal *reseau, const char *nom_fichier);

// Charge un réseau neuronal depuis un fichier
ReseauNeuronal* charger_reseau(const char *nom_fichier);

#endif // SAVE_H