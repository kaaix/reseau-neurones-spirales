/**
* @file benchmark.h
 * @brief Fichier d'en-tête pour les benchmarks de performance du réseau de neurones.
 *
 * Ce module regroupe les dépendances nécessaires à l'exécution de benchmarks
 * sur les fonctions critiques comme la propagation, la rétropropagation,
 * ou la génération des données d'entraînement.
 *
 * Il inclut :
 * - `ubench.h` : micro-framework pour les benchmarks.
 * - `neural_network.h` : logique du réseau de neurones.
 * - `data.h` : génération des jeux de données.
 * - `<stdlib.h>` et `<time.h>` : pour la mémoire et la mesure de temps.
 */

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "ubench.h"
#include "src/neural_network.h"
#include "src/data.h"
#include <stdlib.h>
#include <time.h>

/**
 * @struct neural_network_propagation_2_2
 * @brief Fixture pour les benchmarks de propagation d’un réseau 2-2.
 *
 * Cette structure est destinée à contenir les données ou objets nécessaires
 * à la mise en place d’un test de performance spécifique à une architecture
 * de réseau de neurones 2 entrées / 2 sorties.
 *
 * Elle peut être utilisée pour initialiser un réseau, charger des données,
 * ou conserver des états intermédiaires utilisés dans un benchmark.
 */
typedef struct neural_network_propagation_2_2 {
    // Fixture vide pour l’instant. À remplir avec :
    // NeuralNetwork net;
    // DataPoint* input;
    // etc.
} neural_network_propagation_2_2;

#endif // BENCHMARK_H
