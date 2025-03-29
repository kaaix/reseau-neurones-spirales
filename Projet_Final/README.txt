Projet : Réseau de Neurones Spirales
====================================

Ce document décrit comment utiliser le Makefile contenu dans le dossier "src" afin de compiler et gérer le projet.

Prérequis
---------
- Un compilateur C/C++ (comme gcc ou g++) installé sur votre machine.
- L'utilitaire GNU Make installé.

Utilisation
-----------
1. **Se placer dans le dossier src**  
   Ouvrez un terminal et rendez-vous dans le répertoire "src" du projet :
   > cd chemin/vers/le/projet/src

2. **Compiler le projet**  
   Pour compiler le projet, exécutez simplement la commande :
   > make  
   Cette commande va compiler tous les fichiers sources et générer l'exécutable du projet.

3. **Nettoyer le projet**  
   Pour supprimer les fichiers objets et l'exécutable généré, utilisez la commande :
   > make clean

4. **Commandes additionnelles**  
   Le Makefile peut contenir d'autres cibles. Par exemple :  
   - *make run* : Pour lancer l'exécutable généré (si cette cible est définie).  
   - *make test* : Pour lancer des tests automatiques (si une cible "test" est prévue).

Remarques
---------
- Si vous apportez des modifications aux fichiers sources, il est conseillé d'exécuter `make clean` avant de recompiler afin d'éviter d'éventuels conflits.
- En cas d'erreur de compilation, vérifiez que toutes les dépendances nécessaires sont bien installées et consultez les messages d'erreur pour identifier le problème.

Conclusion
----------
Le Makefile facilite la gestion et la compilation du projet. Pour toute question supplémentaire ou en cas de problème, n'hésitez pas à consulter la documentation complète du projet ou à contacter le responsable.

Bonne utilisation !
