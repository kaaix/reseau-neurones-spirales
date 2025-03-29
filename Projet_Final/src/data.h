/**
* @file data.h
 * @brief Fonctions et structures pour la génération de données (spirales) et la visualisation.
 *
 * Ce module gère :
 * - La génération de jeux de données en forme de spirales pour l'entraînement des réseaux de neurones
 * - La génération personnalisée pour un nombre variable de classes
 * - La coloration de l'écran selon les sorties du réseau
 * - Le stockage des points dessinés manuellement
 */

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

/**
 * @brief Représente un point avec deux coordonnées et un label à deux classes.
 */
typedef struct {
    double x;               ///< Coordonnée x du point
    double y;               ///< Coordonnée y du point
    double label[2];        ///< Label sous forme one-hot (ex: [1,0] ou [0,1])
} DataPoint;

/**
 * @brief Représente un point dessiné manuellement (jusqu'à 3 classes possibles).
 */
typedef struct {
    double x;               ///< Coordonnée x
    double y;               ///< Coordonnée y
    double label[3];        ///< Label one-hot
} DataPoint3;

/**
 * @brief Nombre de points dessinés manuellement.
 */
extern int nb_dessin;

/**
 * @brief Tableau contenant les points dessinés à la main.
 */
extern DataPoint3 dessin[MAX_DESSIN];

/**
 * @brief Jeu de données personnalisé pour plusieurs classes.
 *
 * Chaque classe possède une spirale. Contient jusqu'à MAX_CLASSES spirales.
 */
extern DataPoint dataset_P[NB_POINTS_SPIRALE * MAX_CLASSES];

/**
 * @brief Jeu de données de base pour deux classes (rouge et bleu).
 *
 * Contient 2 spirales opposées (2 * NB_POINTS_SPIRALE points).
 */
extern DataPoint dataset[NB_POINTS_SPIRALE * 2]; // 2 classes (bleu et rouge)

/**
 * @brief Génère deux spirales opposées (bleu et rouge), normalisées dans [-1, 1].
 *
 * Stocke les points dans le tableau global `dataset`.
 */
void generer_spirales_archimede();

/**
 * @brief Génère un ensemble de spirales pour un nombre arbitraire de classes.
 *
 * Chaque spirale est décalée angulairement pour représenter une classe différente.
 * Les points sont normalisés dans [-1, 1] et stockés dans `dataset`.
 *
 * @param nb_classes Nombre de classes (spirales) à générer.
 */
void generer_spirales_personnalisees(int nb_classes);

/**
 * @brief Colore l'écran selon la sortie du réseau de neurones.
 *
 * Chaque pixel est évalué par le réseau pour estimer sa classe, puis colorié en conséquence.
 *
 * @param renderer Renderer SDL utilisé pour dessiner.
 * @param reseau Réseau de neurones utilisé pour la classification.
 * @param width Largeur de l’écran.
 * @param height Hauteur de l’écran.
 */
void colorier_ecran(SDL_Renderer *renderer, ReseauNeuronal *reseau, int width, int height);

/**
 * @brief Colore l'écran en RGB pour les réseaux multi-classes.
 *
 * Utilisé lorsqu’il y a plus de deux classes. Chaque classe est associée à une couleur distincte.
 * Le rendu final utilise un mélange RGB basé sur la sortie du réseau pour chaque pixel.
 *
 * @param renderer Renderer SDL utilisé pour dessiner.
 * @param reseau Réseau de neurones utilisé pour la classification.
 * @param width Largeur de l’écran.
 * @param height Hauteur de l’écran.
 */
void colorier_ecran_rgb(SDL_Renderer *renderer, ReseauNeuronal *reseau, int width, int height);

#endif
