#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdlib.h>
#include <math.h>
#include <SDL.h>

typedef struct {
    int n_entrees;   // Nombre d’entrées (sans compter éventuellement le biais)
    double *poids;   // Tableau de poids [n_entrees]
    double sortie;   // Dernière sortie calculée (après activation)
    double delta;    // Delta pour la rétropropagation
} Neurone;

typedef struct {
    int n_entrees;      // Nombre d’entrées globales (x, y, etc.)
    int n_couches;      // Nombre de couches
    int *taille_couches;// Tableau : taille_couches[i] = nb neurones dans la couche i
    Neurone **couches;  // Tableau 2D [n_couches][taille_couches[i]]
} ReseauNeuronal;

// Crée un réseau de n_couches, avec n_entrees en entrée
// et taille_couches[i] neurones dans la couche i.
ReseauNeuronal* creer_reseau(int n_entrees, int n_couches, const int *taille_couches);

// Libère la mémoire allouée pour le réseau de neurones.
void detruire_reseau(ReseauNeuronal *reseau);

// Calcule la sortie de chaque neurone du réseau, couche par couche.
void propagation(ReseauNeuronal *reseau, const double *entrees);

/**
 * Effectue la rétropropagation sur toutes les couches :
 * - Calcule les deltas de la couche de sortie
 * - Calcule les deltas dans les couches cachées en remontant
 * - Met à jour les poids
 */
void backpropagation(ReseauNeuronal *reseau, const double *entrees,
                     const double *sortie_attendue, double epsilon);

/**
 * Renvoie une graine aléatoire issue de /dev/urandom si possible,
 * sinon basée sur time(NULL).
 */
unsigned int dev_random_seed();

#endif
