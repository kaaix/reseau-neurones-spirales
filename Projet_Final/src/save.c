#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

// Sauvegarde un réseau neuronal dans un fichier
void sauvegarder_reseau(ReseauNeuronal *reseau, const char *nom_fichier) {
    log_message(LOG_LEVEL_INFO, "Tentative de sauvegarde du réseau dans '%s'...", nom_fichier);
    FILE *f = fopen(nom_fichier, "wb");
    if (!f) {
        log_message(LOG_LEVEL_ERROR, "Erreur ouverture fichier '%s' pour écriture.", nom_fichier);
        perror("Erreur lors de l'ouverture du fichier pour sauvegarde");
        return;
    }
    log_message(LOG_LEVEL_INFO, "Fichier ouvert pour écriture : %s", nom_fichier);
    // Sauvegarde des métadonnées
    fwrite(&reseau->n_entrees, sizeof(int), 1, f);
    fwrite(&reseau->n_couches, sizeof(int), 1, f);
    fwrite(reseau->taille_couches, sizeof(int), reseau->n_couches, f);

    // Sauvegarde des poids et des biais
    for (int i = 0; i < reseau->n_couches; i++) {
        for (int j = 0; j < reseau->taille_couches[i]; j++) {
            Neurone *neurone = &reseau->couches[i][j];
            fwrite(neurone->poids, sizeof(double), neurone->n_entrees, f);
        }
    }

    fclose(f);
    log_message(LOG_LEVEL_INFO, "Réseau sauvegardé avec succès dans '%s'.", nom_fichier);
}


// Charge un réseau neuronal depuis un fichier
ReseauNeuronal* charger_reseau(const char *nom_fichier) {
    log_message(LOG_LEVEL_INFO, "Chargement du réseau depuis '%s'...", nom_fichier);
    FILE *f = fopen(nom_fichier, "rb");
    if (!f) {
        log_message(LOG_LEVEL_ERROR, "Erreur ouverture fichier '%s' pour lecture.", nom_fichier);
        perror("Erreur lors de l'ouverture du fichier pour chargement");
        return NULL;
    }
    log_message(LOG_LEVEL_INFO, "Fichier ouvert pour lecture : %s", nom_fichier);
    // Lecture des métadonnées
    int n_entrees, n_couches;
    if (fread(&n_entrees, sizeof(int), 1, f) != 1 ||
        fread(&n_couches, sizeof(int), 1, f) != 1) {
        perror("Erreur lors de la lecture des métadonnées");
        fclose(f);
        log_message(LOG_LEVEL_INFO, "Réseau sauvegardé avec succès dans '%s'.", nom_fichier);
        return NULL;
    }

    int *taille_couches = malloc(n_couches * sizeof(int));
    if (fread(taille_couches, sizeof(int), n_couches, f) != (size_t)n_couches) {
        perror("Erreur lors de la lecture des tailles des couches");
        free(taille_couches);
        fclose(f);
        log_message(LOG_LEVEL_INFO, "Réseau sauvegardé avec succès dans '%s'.", nom_fichier);
        return NULL;
    }

    // Création du réseau
    ReseauNeuronal *reseau = creer_reseau(n_entrees, n_couches, taille_couches);

    // Chargement des poids et des biais
    for (int i = 0; i < reseau->n_couches; i++) {
        for (int j = 0; j < reseau->taille_couches[i]; j++) {
            Neurone *neurone = &reseau->couches[i][j];
            if (fread(neurone->poids, sizeof(double), neurone->n_entrees, f) != (size_t)neurone->n_entrees) {
                perror("Erreur lors de la lecture des poids");
                free(taille_couches);
                detruire_reseau(reseau);
                fclose(f);
                 log_message(LOG_LEVEL_INFO, "Réseau sauvegardé avec succès dans '%s'.", nom_fichier);
                return NULL;
            }
        }
    }

    free(taille_couches);
    fclose(f);
    return reseau;
}


void sauvegarder_entier(int nombre, const char *nomFichier) {
    FILE *f = fopen(nomFichier, "wb");
    if (!f) {
        perror("Erreur lors de l'ouverture du fichier pour sauvegarde");
        return;
    }

    // Écriture de l'entier
    fwrite(&nombre, sizeof(int), 1, f);

    fclose(f);
    log_message(LOG_LEVEL_INFO, "Réseau sauvegardé avec succès dans '%s'.", nomFichier);
    printf("Entier %d sauvegardé dans '%s'\n", nombre, nomFichier);
}

// Relit un entier depuis un fichier binaire
int charger_entier(const char *nomFichier) {
    FILE *f = fopen(nomFichier, "rb");
    if (!f) {
        perror("Erreur lors de l'ouverture du fichier pour chargement");
        return -1; // indique une erreur
    }

    int nombre;
    if (fread(&nombre, sizeof(int), 1, f) != 1) {
        perror("Erreur lors de la lecture de l'entier");
        fclose(f);
        log_message(LOG_LEVEL_INFO, "Réseau sauvegardé avec succès dans '%s'.", nomFichier);
        return -1;
    }

    fclose(f);
    log_message(LOG_LEVEL_INFO, "Réseau sauvegardé avec succès dans '%s'.",nomFichier);
    return nombre;
}