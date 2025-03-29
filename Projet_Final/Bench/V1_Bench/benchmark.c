#include "ubench.h"
#include "src/neural_network.h"
#include "src/data.h"
#include <stdlib.h>
#include <string.h>
#include"benchmark.h"

static ReseauNeuronal *reseau_2_2 = NULL;
static ReseauNeuronal *reseau_3_4 = NULL;

static double entree_2[2] = {0.1, 0.2};
static double sortie_2[2] = {1.0, 0.0};

static double entree_4[3] = {0.4, 0.2, 0.7};
static double sortie_4[4] = {0.0, 1.0, 0.0, 0.0};

// ---------------------- BENCHMARKS POUR RESEAUX 2→2 ----------------------

UBENCH_F_SETUP(neural_network_propagation_2_2) {
    (void)ubench_fixture;
    int layers[] = {5, 2};
    reseau_2_2 = creer_reseau(2, 2, layers);
}

UBENCH_F_TEARDOWN(neural_network_propagation_2_2) {
    (void)ubench_fixture;
    detruire_reseau(reseau_2_2);
}

UBENCH_EX_F(neural_network_propagation_2_2, propagation_only) {
    (void)ubench_fixture;
    UBENCH_DO_BENCHMARK() {
        propagation(reseau_2_2, entree_2);
    }
}

UBENCH_EX_F(neural_network_propagation_2_2, backpropagation) {
    (void)ubench_fixture;
    UBENCH_DO_BENCHMARK() {
        propagation(reseau_2_2, entree_2);
        backpropagation(reseau_2_2, entree_2, sortie_2, 0.01);
    }
}

// ---------------------- GENERATION DE DONNEES ----------------------

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

// ---------------------- BENCHMARKS POUR RESEAUX 2→3 ----------------------

UBENCH_EX(neural_network, creer_reseau_2_3) {
    int layers[] = {4, 3};
    UBENCH_DO_BENCHMARK() {
        ReseauNeuronal *r = creer_reseau(2, 2, layers);
        detruire_reseau(r);
    }
}

UBENCH_EX(neural_network, propagation_3_entrees_4_sorties) {
    int layers[] = {5, 4};
    reseau_3_4 = creer_reseau(3, 2, layers);
    UBENCH_DO_BENCHMARK() {
        propagation(reseau_3_4, entree_4);
    }
    detruire_reseau(reseau_3_4);
}

UBENCH_EX(neural_network, backpropagation_3_entrees_4_sorties) {
    int layers[] = {5, 4};
    reseau_3_4 = creer_reseau(3, 2, layers);
    UBENCH_DO_BENCHMARK() {
        propagation(reseau_3_4, entree_4);
        backpropagation(reseau_3_4, entree_4, sortie_4, 0.01);
    }
    detruire_reseau(reseau_3_4);
}

// ---------------------- BENCHMARKS POUR RESEAUX 3→4 ----------------------

UBENCH_EX(neural_network, creer_reseau_3_4) {
    int couches[] = {12, 12, 12, 4};
    UBENCH_DO_BENCHMARK() {
        ReseauNeuronal *reseau = creer_reseau(3, 4, couches);
        detruire_reseau(reseau);
    }
}

UBENCH_EX(neural_network, propagation_3_4) {
    int couches[] = {12, 12, 12, 4};
    ReseauNeuronal *reseau = creer_reseau(3, 4, couches);
    double entree[] = {0.1, -0.2, 0.3};

    UBENCH_DO_BENCHMARK() {
        propagation(reseau, entree);
    }
    detruire_reseau(reseau);
}

UBENCH_EX(neural_network, backpropagation_3_4) {
    int couches[] = {12, 12, 12, 4};
    ReseauNeuronal *reseau = creer_reseau(3, 4, couches);
    double entree[] = {0.1, -0.2, 0.3};
    double sortie_attendue[] = {0.0, 1.0, 0.0, 0.0};
    double epsilon = 0.01;

    UBENCH_DO_BENCHMARK() {
        backpropagation(reseau, entree, sortie_attendue, epsilon);
    }
    detruire_reseau(reseau);
}

// ---------------------- MAIN ----------------------

UBENCH_MAIN();