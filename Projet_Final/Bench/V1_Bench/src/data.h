/**
* @file data.h
 * @brief Module de génération des jeux de données pour l'entraînement du réseau de neurones.
 *
 * Ce fichier contient les structures et fonctions permettant de générer
 * des jeux de données sous forme de spirales. Ces jeux sont utilisés
 * pour tester la capacité de classification du réseau de neurones.
 */

#ifndef DATA_H
#define DATA_H

#include "neural_network.h"

/// Nombre de points générés pour chaque spirale.
#define NB_POINTS_SPIRALE 500

/// Nombre maximal de classes pour les spirales personnalisées.
#define MAX_CLASSES 10

/// Nombre maximal de dessins (réservé pour d'autres types de données).
#define MAX_DESSIN 10000

/**
 * @struct DataPoint
 * @brief Représente un point de données avec coordonnées et étiquette.
 *
 * Chaque point contient :
 * - ses coordonnées `x` et `y` dans le plan,
 * - une étiquette vectorielle `label` (souvent [1, 0] ou [0, 1] pour la classification binaire).
 */
typedef struct {
    double x;              /**< Coordonnée x du point */
    double y;              /**< Coordonnée y du point */
    double label[2];       /**< Étiquette associée (vectorisée) */
} DataPoint;

/// Jeu de données pour deux spirales (classification binaire).
extern DataPoint dataset[NB_POINTS_SPIRALE * 2];

/// Jeu de données pour spirales avec plusieurs classes.
extern DataPoint dataset_P[NB_POINTS_SPIRALE * MAX_CLASSES];

/**
 * @brief Génère deux spirales d'Archimède entrelacées pour la classification binaire.
 *
 * Les points sont générés aléatoirement et stockés dans le tableau global `dataset`.
 */
void generer_spirales_archimede();

/**
 * @brief Génère des spirales personnalisées pour un nombre variable de classes.
 *
 * Les points sont générés et stockés dans le tableau global `dataset_P`.
 *
 * @param nb_classes Nombre de classes à générer (maximum : MAX_CLASSES).
 */
void generer_spirales_personnalisees(int nb_classes);

#endif // DATA_H
