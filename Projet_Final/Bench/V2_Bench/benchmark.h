/**
* @file benchmark.h
 * @brief Fichier d'en-tête pour les benchmarks de performance.
 *
 * Ce fichier regroupe les dépendances nécessaires à l'exécution
 * de benchmarks sur le réseau de neurones du projet.
 *
 * Il inclut :
 * - `ubench.h` : micro-framework de benchmarking.
 * - `neural_network.h` : logique du réseau de neurones.
 * - `data.h` : gestion des données d’entrée.
 * - `<stdlib.h>` et `<time.h>` : bibliothèques standards pour la génération aléatoire et la mesure de temps.
 *
 * Ce fichier est destiné à centraliser les éléments utiles à
 * l'écriture de tests de performance, comme ceux que l'on trouve dans `bench/`.
 */

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "ubench.h"
#include "src/neural_network.h"
#include "src/data.h"
#include <stdlib.h>
#include <time.h>

#endif // BENCHMARK_H
