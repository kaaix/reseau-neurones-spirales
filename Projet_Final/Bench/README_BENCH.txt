README - Benchmark UBENCH

Ce projet contient deux implémentations de benchmarks utilisant la bibliothèque ubench.h
pour mesurer les performances de différentes opérations sur un réseau de neurones.

Fichiers principaux :
---------------------
- benchmark.c        : Contient les benchmarks UBENCH (version simple ou avec fixtures)
- neural_network.c/h : Implémentation du réseau de neurones
- data.c/h           : Fonctions de génération de données (spirales)
- ubench.h           : Bibliothèque de benchmark utilisée
- Makefile           : Fichier de compilation

Compilation :
-------------
Pour compiler le projet :
    make

Cela génère un exécutable nommé :
    run_bench

Utilisation :
-------------
Pour exécuter les benchmarks :
    ./run_bench

Résultat :
----------
L'exécution affiche les résultats des benchmarks dans la console :
- Nom du test
- Temps moyen d'exécution
- Intervalle de confiance

Format de sortie :
    [  OK   ] nom_du_test (mean X.XXXus, confidence interval +- Y.YY%)

Structure :
-----------
- Version 1 : benchmark avec FIXTURE (UBENCH_F), setup/teardown structuré
- Version 2 : benchmark simple (UBENCH_EX), instanciation locale des réseaux

Encadrant : M. Nicolas Courilleau
Auteurs   : El Mahdi Benfdal & Ewen Croizier
Université de Poitiers — Licence Informatique 2024/2025
