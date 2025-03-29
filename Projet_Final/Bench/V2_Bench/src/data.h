/**
* @file data.h
 * @brief Génération des jeux de données pour l'entraînement du réseau de neurones.
 *
 * Ce module permet de créer des ensembles de points organisés en spirales, utiles pour tester
 * les capacités de classification d’un réseau de neurones.
 */

#ifndef DATA_H
#define DATA_H

#include "neural_network.h"

/// Nombre de points par spirale.
#define NB_POINTS_SPIRALE 500

/// Nombre maximum de classes pour les spirales personnalisées.
#define MAX_CLASSES 10

/// Nombre maximum de dessins (utilisé dans d'autres jeux de données).
#define MAX_DESSIN 10000

/**
 * @struct DataPoint
 * @brief Structure représentant un point de données pour l'entraînement.
 *
 * Un point est défini par :
 * - ses coordonnées (x, y)
 * - son label sous forme de tableau de doubles (2 dimensions ici).
 */
typedef struct {
    double x;             /**< Coordonnée x */
    double y;             /**< Coordonnée y */
    double label[2];      /**< Label du point (vectorisé pour classification binaire) */
} DataPoint;

/// Jeu de données de spirales à 2 classes.
extern DataPoint dataset[NB_POINTS_SPIRALE * 2];

/// Jeu de données de spirales personnalisées à plusieurs classes.
extern DataPoint dataset_P[NB_POINTS_SPIRALE * MAX_CLASSES];

/**
 * @brief Génère deux spirales d'Archimède pour un problème de classification binaire.
 *
 * Les points générés sont stockés dans `dataset`.
 */
void generer_spirales_archimede();

/**
 * @brief Génère des spirales personnalisées pour plusieurs classes.
 *
 * Les points générés sont stockés dans `dataset_P`.
 *
 * @param nb_classes Nombre de classes à générer (maximum : MAX_CLASSES).
 */
void generer_spirales_personnalisees(int nb_classes);

#endif // DATA_H
