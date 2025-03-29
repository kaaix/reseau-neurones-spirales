#include "CuTest.h"
#include "neural_network.h"
#include <stdlib.h>

void TestNeuralNetwork_Creation(CuTest* tc) {
    int layers[] = {3, 3, 1};
    ReseauNeuronal* r = creer_reseau(2, 3, layers);
    CuAssert(tc, "Le réseau ne doit pas être NULL", r != NULL);
    detruire_reseau(r);
}

void TestNeuralNetwork_Propagation(CuTest* tc) {
    int layers[] = {3, 3, 1};
    ReseauNeuronal* r = creer_reseau(2, 3, layers);
    double input[] = {0.5, -0.5};
    propagation(r, input);

    int last_layer = r->n_couches - 1;
    for (int i = 0; i < r->taille_couches[last_layer]; i++) {
        double s = r->couches[last_layer][i].sortie;
        CuAssert(tc, "La sortie doit être comprise entre 0 et 1", s >= 0.0 && s <= 1.0);
    }

    detruire_reseau(r);
}

void TestNeuralNet_AddTests(CuSuite* suite) {
    SUITE_ADD_TEST(suite, TestNeuralNetwork_Creation);
    SUITE_ADD_TEST(suite, TestNeuralNetwork_Propagation);
}
