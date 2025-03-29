/**
* @file main.c
 * @brief Point d'entrée pour exécuter les tests unitaires avec CuTest.
 *
 * Ce fichier initialise et exécute la suite de tests définie dans le projet.
 */

#include <stdio.h>
#include "CuTest.h"

/**
 * @brief Déclaration de la fonction qui rassemble tous les tests.
 *
 * Cette fonction doit être définie dans un autre fichier (par ex. `test_example.c`)
 * et retourner une suite contenant tous les tests à exécuter.
 *
 * @return Pointeur vers la suite de tests.
 */
extern CuSuite* AllTests(void);

/**
 * @brief Fonction principale qui exécute les tests unitaires.
 *
 * Elle exécute les tests, affiche un résumé global et les détails
 * des échecs éventuels.
 *
 * @return Code de retour (toujours 0).
 */
int main(void) {
    CuSuite* suite = AllTests();       /**< Création et récupération des tests */
    CuSuiteRun(suite);                 /**< Exécution des tests */
    CuSuiteDetails(suite);            /**< Affichage des détails */
    return 0;
}
