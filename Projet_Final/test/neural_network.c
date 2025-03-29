#include "neural_network.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>



/* Récupère une graine aléatoire depuis /dev/urandom si possible */
unsigned int dev_random_seed() {
    unsigned int seed;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd != -1) {
        ssize_t bytes_read = read(fd, &seed, sizeof(seed));
        if (bytes_read != sizeof(seed)) {
            // En cas d'erreur de lecture, on utilise time(NULL) comme graine
            seed = (unsigned int) time(NULL);
        }
        close(fd);
    } else {
        seed = (unsigned int) time(NULL);
    }
    return seed;
}

/**
 * Crée un réseau avec n_couches.
 * taille_couches[i] = nb de neurones dans la couche i.
 * - couche 0 lit n_entrees
 * - couche i lit la sortie de la couche i-1
 */
ReseauNeuronal* creer_reseau(int n_entrees, int n_couches, const int *taille_couches) {
    
    ReseauNeuronal *reseau = malloc(sizeof(ReseauNeuronal));
    reseau->n_entrees = n_entrees;
    reseau->n_couches = n_couches;

    // Copie du tableau taille_couches
    reseau->taille_couches = malloc(n_couches * sizeof(int));
    memcpy(reseau->taille_couches, taille_couches, n_couches * sizeof(int));

    // Allocation des couches
    reseau->couches = malloc(n_couches * sizeof(Neurone*));

    srand(dev_random_seed());

    for (int i = 0; i < n_couches; i++) {
        int nb_neurones = reseau->taille_couches[i];
        reseau->couches[i] = malloc(nb_neurones * sizeof(Neurone));

        // Nombre d'entrées pour la couche i
        int nb_entrees_precedente = (i == 0) ? n_entrees : reseau->taille_couches[i - 1];

        // Init de chaque neurone
        for (int j = 0; j < nb_neurones; j++) {
            reseau->couches[i][j].n_entrees = nb_entrees_precedente;
            reseau->couches[i][j].poids = malloc(nb_entrees_precedente * sizeof(double));
            // Initialisation aléatoire entre [-1, 1]
            for (int k = 0; k < nb_entrees_precedente; k++) {
                reseau->couches[i][j].poids[k] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            }
            reseau->couches[i][j].sortie = 0.0;
            reseau->couches[i][j].delta = 0.0;
        }
    }
    return reseau;
}

/**
 * Libère la mémoire du réseau
 */
void detruire_reseau(ReseauNeuronal *reseau) {
   

    if (!reseau) return;

    for (int i = 0; i < reseau->n_couches; i++) {
        for (int j = 0; j < reseau->taille_couches[i]; j++) {
            free(reseau->couches[i][j].poids);
        }
        free(reseau->couches[i]);
    }
    free(reseau->couches);
    free(reseau->taille_couches);
    free(reseau);
}

/**
 * Calcule la sortie d'un neurone : somme pondérée + tanh
 */
static double calcul_sortie_neurone(const Neurone *n, const double *entrees) {
    double somme = 0.0;
    for (int i = 0; i < n->n_entrees; i++) {
        somme += n->poids[i] * entrees[i];
    }
    // Activation : tanh
    return tanh(somme);
}

/**
 * Propagation avant : calcule la sortie de chaque couche.
 * - La couche 0 lit 'entrees'
 * - La couche i lit la sortie de la couche i-1
 */
void propagation(ReseauNeuronal *reseau, const double *entrees) {
   
    if (!reseau || !entrees) { 
      
        return;
    }

    // On stocke temporairement les sorties de la couche précédente
    double *sorties_prec = malloc(reseau->n_entrees * sizeof(double));
    // Copie des entrées dans sorties_prec
    for (int i = 0; i < reseau->n_entrees; i++) {
        sorties_prec[i] = entrees[i];
    }

    // Parcours des couches
    for (int couche_idx = 0; couche_idx < reseau->n_couches; couche_idx++) {
        int nb_neurones = reseau->taille_couches[couche_idx];
        double *sorties_cour = malloc(nb_neurones * sizeof(double));

        for (int j = 0; j < nb_neurones; j++) {
            double out = calcul_sortie_neurone(&reseau->couches[couche_idx][j], sorties_prec);
            reseau->couches[couche_idx][j].sortie = out;
            sorties_cour[j] = out;
        }

        free(sorties_prec);
        sorties_prec = sorties_cour; // On utilisera ces sorties pour la couche suivante
    }

    // Libération du dernier buffer
    free(sorties_prec);
}

/**
 * Backprop multi-couches :
 *  1) Calcule delta sur la couche de sortie
 *     delta_i = (1 - sortie_i^2) * (sortie_attendue_i - sortie_i)
 *  2) Pour chaque couche cachée (en remontant) :
 *     delta_i = (1 - sortie_i^2) * somme( delta_k * poids_k_i )
 *  3) Mise à jour des poids :
 *     w_ij += epsilon * delta_i * sortie_j (sortie_j = entrée du neurone i)
 */
void backpropagation(ReseauNeuronal *reseau, const double *entrees,
                     const double *sortie_attendue, double epsilon) {
    
    if (!reseau || !entrees || !sortie_attendue) return;

    int last = reseau->n_couches - 1;

    // 1) Deltas de la couche de sortie
    int nb_out = reseau->taille_couches[last];
    for (int i = 0; i < nb_out; i++) {
        Neurone *neur = &reseau->couches[last][i];
        double s = neur->sortie; // sortie
        double erreur = (sortie_attendue[i] - s);
        double derivee = 1.0 - (s * s); // tanh'(s) = 1 - s^2
        neur->delta = erreur * derivee;
    }

    // 2) Deltas des couches cachées (depuis last-1 jusqu'à 0)
    for (int couche = last - 1; couche >= 0; couche--) {
        int nb_neurones = reseau->taille_couches[couche];
        int nb_neurones_suiv = reseau->taille_couches[couche + 1];

        for (int i = 0; i < nb_neurones; i++) {
            Neurone *neur = &reseau->couches[couche][i];
            double s = neur->sortie;
            double derivee = 1.0 - (s * s);
            // somme des deltas de la couche suivante * poids associés
            double somme = 0.0;
            for (int k = 0; k < nb_neurones_suiv; k++) {
                Neurone *neur_suiv = &reseau->couches[couche + 1][k];
                // neur_suiv->poids[i] relie le neurone i de cette couche
                // au neurone k de la couche suivante
                somme += neur_suiv->delta * neur_suiv->poids[i];
            }
            neur->delta = derivee * somme;
        }
    }

    // 3) Mise à jour des poids
    // Chaque neurone de chaque couche
    for (int couche = 0; couche < reseau->n_couches; couche++) {
        for (int i = 0; i < reseau->taille_couches[couche]; i++) {
            Neurone *neur = &reseau->couches[couche][i];
            double d = neur->delta;

            // Les entrées de ce neurone viennent :
            //  - soit de 'entrees' si couche == 0
            //  - soit de la couche précédente
            for (int w = 0; w < neur->n_entrees; w++) {
                double entree_w;
                if (couche == 0) {
                    entree_w = entrees[w];
                } else {
                    // la sortie du neurone w de la couche (couche-1)
                    entree_w = reseau->couches[couche - 1][w].sortie;
                }

                // w_ij += epsilon * delta_i * x_j
                neur->poids[w] += epsilon * d * entree_w;
            }
        }
    }
}

