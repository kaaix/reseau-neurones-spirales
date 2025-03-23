#include "save.h"
#include <stdio.h>
#include <stdlib.h>

// Sauvegarde un réseau neuronal dans un fichier
void sauvegarder_reseau(ReseauNeuronal *reseau, const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "wb");
    if (!f) {
        perror("Erreur lors de l'ouverture du fichier pour sauvegarde");
        return;
    }

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
}

// Charge un réseau neuronal depuis un fichier
ReseauNeuronal* charger_reseau(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "rb");
    if (!f) {
        perror("Erreur lors de l'ouverture du fichier pour chargement");
        return NULL;
    }

    // Lecture des métadonnées
    int n_entrees, n_couches;
    if (fread(&n_entrees, sizeof(int), 1, f) != 1 ||
        fread(&n_couches, sizeof(int), 1, f) != 1) {
        perror("Erreur lors de la lecture des métadonnées");
        fclose(f);
        return NULL;
    }

    int *taille_couches = malloc(n_couches * sizeof(int));
    if (fread(taille_couches, sizeof(int), n_couches, f) != (size_t)n_couches) {
        perror("Erreur lors de la lecture des tailles des couches");
        free(taille_couches);
        fclose(f);
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
                return NULL;
            }
        }
    }

    free(taille_couches);
    fclose(f);
    return reseau;
}