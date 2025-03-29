/**
* @file save.h
 * @brief Fonctions pour la sauvegarde et le chargement de données.
 *
 * Ce module permet de sauvegarder et charger :
 * - des réseaux de neurones (poids, structure)
 * - des entiers (par exemple pour stocker un nombre de classes)
 *
 * Il utilise des fichiers binaires pour un format compact et rapide.
 */
#ifndef SAVE_H
#define SAVE_H

#include "neural_network.h"

/**
 * @brief Sauvegarde un réseau de neurones dans un fichier binaire.
 *
 * Écrit le nombre d’entrées, le nombre de couches, les tailles de chaque couche
 * puis tous les poids du réseau.
 *
 * @param reseau Le réseau à sauvegarder
 * @param nom_fichier Le nom du fichier binaire de destination
 */
void sauvegarder_reseau(ReseauNeuronal *reseau, const char *nom_fichier);

/**
 * @brief Charge un réseau de neurones depuis un fichier binaire.
 *
 * Reconstruit un réseau complet à partir des données lues (structure + poids).
 *
 * @param nom_fichier Le fichier binaire contenant le réseau sauvegardé
 * @return Un pointeur vers le réseau chargé, ou NULL en cas d’erreur
 */
ReseauNeuronal* charger_reseau(const char *nom_fichier);

/**
 * @brief Sauvegarde un entier dans un fichier binaire.
 *
 * Utile pour enregistrer des paramètres simples comme un nombre de classes.
 *
 * @param nombre L’entier à sauvegarder
 * @param nomFichier Le nom du fichier de destination
 */
void sauvegarder_entier(int nombre, const char *nomFichier);

/**
 * @brief Charge un entier depuis un fichier binaire.
 *
 * @param nomFichier Le fichier contenant l’entier sauvegardé
 * @return L’entier lu, ou -1 en cas d’erreur
 */
int charger_entier(const char *nomFichier);
#endif // SAVE_H