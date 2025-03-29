
#include "ubench.h"
#include "src/neural_network.h"
#include "data.h"
#include <stdlib.h>
#include <string.h>

static double entree_2[2] = {0.1, 0.2};
static double sortie_2[2] = {1.0, 0.0};
static double entree_4[3] = {0.4, 0.2, 0.7};
static double sortie_4[4] = {0.0, 1.0, 0.0, 0.0};

// --- BENCHMARKS propagation / backpropagation 2→2 ---

UBENCH_EX(neural_network, propagation_2_2) {
    int layers[] = {5, 2};
    ReseauNeuronal *r = creer_reseau(2, 2, layers);
    UBENCH_DO_BENCHMARK() {
        propagation(r, entree_2);
    }
    detruire_reseau(r);
}

UBENCH_EX(neural_network, backpropagation_2_2) {
    int layers[] = {5, 2};
    ReseauNeuronal *r = creer_reseau(2, 2, layers);
    UBENCH_DO_BENCHMARK() {
        propagation(r, entree_2);
        backpropagation(r, entree_2, sortie_2, 0.01);
    }
    detruire_reseau(r);
}

// --- GENERATION DE DONNEES ---

UBENCH_EX(data_generation, generer_spirales_archimede) {
    UBENCH_DO_BENCHMARK() {
        generer_spirales_archimede();
    }
}

UBENCH_EX(data_generation, generer_spirales_personnalisees_3_classes) {
    UBENCH_DO_BENCHMARK() {
        generer_spirales_personnalisees(3);
    }
}

// --- Autres architectures (propagation / backpropagation) ---

UBENCH_EX(neural_network, creer_reseau_2_3) {
    int layers[] = {4, 3};
    UBENCH_DO_BENCHMARK() {
        ReseauNeuronal *r = creer_reseau(2, 2, layers);
        detruire_reseau(r);
    }
}

UBENCH_EX(neural_network, propagation_3_entrees_4_sorties) {
    int layers[] = {5, 4};
    ReseauNeuronal *r = creer_reseau(3, 2, layers);
    UBENCH_DO_BENCHMARK() {
        propagation(r, entree_4);
    }
    detruire_reseau(r);
}

UBENCH_EX(neural_network, backpropagation_3_entrees_4_sorties) {
    int layers[] = {5, 4};
    ReseauNeuronal *r = creer_reseau(3, 2, layers);
    UBENCH_DO_BENCHMARK() {
        propagation(r, entree_4);
        backpropagation(r, entree_4, sortie_4, 0.01);
    }
    detruire_reseau(r);
}

UBENCH_EX(neural_network, creer_reseau_3_4) {
    int couches[] = {12, 12, 12, 4};
    UBENCH_DO_BENCHMARK() {
        ReseauNeuronal *reseau = creer_reseau(3, 4, couches);
        detruire_reseau(reseau);
    }
}

UBENCH_EX(neural_network, propagation_3_4) {
    int couches[] = {12, 12, 12, 4};
    double entree[] = {0.1, -0.2, 0.3};
    ReseauNeuronal *reseau = creer_reseau(3, 4, couches);
    UBENCH_DO_BENCHMARK() {
        propagation(reseau, entree);
    }
    detruire_reseau(reseau);
}

UBENCH_EX(neural_network, backpropagation_3_4) {
    int couches[] = {12, 12, 12, 4};
    double entree[] = {0.1, -0.2, 0.3};
    double sortie_attendue[] = {0.0, 1.0, 0.0, 0.0};
    double epsilon = 0.01;
    ReseauNeuronal *reseau = creer_reseau(3, 4, couches);
    UBENCH_DO_BENCHMARK() {
        backpropagation(reseau, entree, sortie_attendue, epsilon);
    }
    detruire_reseau(reseau);
}

// --- MAIN ---

UBENCH_MAIN();
