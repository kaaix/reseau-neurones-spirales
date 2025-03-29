/**
* @file neural_network.h
 * @brief Définition des structures et fonctions pour les réseaux de neurones.
 *
 * Ce module permet de créer, entraîner et évaluer un réseau de neurones à propagation avant
 * avec rétropropagation du gradient. Il est utilisé dans le cadre de la classification
 * de points en 2D (par exemple, des spirales).
 */

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdlib.h>
#include <math.h>
#include <SDL.h>

/**
 * @brief Structure représentant un neurone.
 */
typedef struct {
    int n_entrees;      ///< Nombre d’entrées du neurone
    double *poids;      ///< Poids associés aux entrées
    double sortie;      ///< Dernière sortie activée du neurone
    double delta;       ///< Valeur de delta utilisée pour la rétropropagation
} Neurone;

/**
 * @brief Structure représentant un réseau de neurones multicouches.
 */
typedef struct {
 int n_entrees;           ///< Nombre d’entrées globales (ex: 2 pour x et y)
 int n_couches;           ///< Nombre total de couches
 int *taille_couches;     ///< Tableau contenant le nombre de neurones par couche
 Neurone **couches;       ///< Tableau 2D contenant tous les neurones du réseau
} ReseauNeuronal;

/**
 * @brief Crée un réseau de neurones multicouches.
 *
 * @param n_entrees Nombre d’entrées (par exemple : 2 pour x et y)
 * @param n_couches Nombre total de couches (hors entrée)
 * @param taille_couches Tableau contenant le nombre de neurones pour chaque couche
 * @return Un pointeur vers un réseau de neurones initialisé
 */
ReseauNeuronal* creer_reseau(int n_entrees, int n_couches, const int *taille_couches);

/**
 * @brief Libère la mémoire allouée pour un réseau de neurones.
 *
 * @param reseau Le réseau à libérer
 */
void detruire_reseau(ReseauNeuronal *reseau);

/**
 * @brief Effectue la propagation avant dans le réseau.
 *
 * Cette fonction calcule la sortie de chaque couche du réseau
 * à partir des entrées fournies.
 *
 * @param reseau Le réseau de neurones
 * @param entrees Les entrées du réseau (de taille n_entrees)
 */
void propagation(ReseauNeuronal *reseau, const double *entrees);

/**
 * @brief Effectue une rétropropagation du gradient et met à jour les poids.
 *
 * @param reseau Le réseau de neurones à entraîner
 * @param entrees Les entrées du réseau
 * @param sortie_attendue Le vecteur de sortie attendu (cible)
 * @param epsilon Le taux d’apprentissage
 */
void backpropagation(ReseauNeuronal *reseau, const double *entrees,
                     const double *sortie_attendue, double epsilon);

/**
 * @brief Renvoie une graine aléatoire issue de /dev/urandom si possible, sinon time(NULL).
 *
 * @return Une graine aléatoire (unsigned int)
 */
unsigned int dev_random_seed();

#endif
