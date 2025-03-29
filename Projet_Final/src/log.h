/**
 * @file log.h
 * @brief Gestion des messages de log pour le projet.
 *
 * Ce module fournit des fonctions pour afficher et enregistrer des messages
 * de log à différents niveaux (INFO, WARNING, ERROR). Il permet aussi de
 * suivre les étapes importantes d'entraînement, de chargement et de
 * sauvegarde du réseau de neurones, ainsi que la génération de structures
 * spécifiques (spirale, coloration, propagation...).
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

/**
 * @enum LogLevel
 * @brief Niveaux de log disponibles.
 */
typedef enum {
    LOG_LEVEL_INFO,     /**< Message d'information générale */
    LOG_LEVEL_WARNING,  /**< Message d'avertissement */
    LOG_LEVEL_ERROR     /**< Message d'erreur critique */
} LogLevel;

/**
 * @brief Niveau de log actuel.
 *
 * Seuls les messages avec un niveau >= à ce niveau seront affichés.
 */
extern LogLevel CURRENT_LOG_LEVEL;

/**
 * @brief Affiche un message de log selon le niveau donné.
 *
 * @param level Le niveau de gravité du message.
 * @param format Format du message (comme printf).
 * @param ... Arguments associés au format.
 */
void log_message(LogLevel level, const char *format, ...);

/**
 * @brief Convertit un niveau de log en chaîne de caractères.
 *
 * @param level Le niveau de log.
 * @return Chaîne de caractères correspondant au niveau.
 */
const char* log_level_to_string(LogLevel level);

/**
 * @brief Définit le niveau de log courant.
 *
 * @param level Nouveau niveau à définir.
 */
void log_set_level(LogLevel level);

/**
 * @brief Log la génération d'une spirale selon le mode utilisé.
 *
 * @param mode Le mode de génération (ex : "train" ou "test").
 */
void log_generation_spirale(const char *mode);

/**
 * @brief Log la sauvegarde du réseau de neurones dans un fichier.
 *
 * @param filename Nom du fichier de sauvegarde.
 */
void log_save_network(const char *filename);

/**
 * @brief Log le chargement d’un réseau de neurones depuis un fichier.
 *
 * @param filename Nom du fichier à charger.
 */
void log_load_network(const char *filename);

/**
 * @brief Log la sauvegarde d’une valeur entière dans un fichier.
 *
 * @param filename Nom du fichier.
 * @param value Valeur entière à sauvegarder.
 */
void log_save_int(const char *filename, int value);

/**
 * @brief Log le chargement d’une valeur entière depuis un fichier.
 *
 * @param filename Nom du fichier.
 * @param value Valeur entière attendue (ou clé d'identification).
 */
void log_load_int(const char *filename, int value);

/**
 * @brief Log la coloration (classification) des données une seule fois selon un mode.
 *
 * @param mode Le mode utilisé (ex : "test", "évaluation").
 */
void log_colorier_once(const char *mode);

/**
 * @brief Log une exécution de la propagation (forward pass) une seule fois.
 */
void log_propagation_once();

/**
 * @brief Log une exécution de la rétropropagation (backward pass).
 */
void log_retropropagation();

/**
 * @brief Log le choix entre les modes d'entraînement et de chargement.
 */
void log_choix_train_load();

/**
 * @brief Log le lancement du chargement des données.
 *
 * @param nom_fichier Nom du fichier chargé.
 */
void log_lancement_load(const char* nom_fichier);

/**
 * @brief Log le lancement de l'entraînement du réseau.
 */
void log_lancement_train();

#endif // LOG_H
