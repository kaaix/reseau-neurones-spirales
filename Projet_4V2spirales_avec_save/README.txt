
🚀 Solution rapide pour résoudre l'avertissement "Clock skew detected" :

Si cette erreur est détectée :

make: Warning: File 'Makefile' has modification time 457 s in the future

gcc main.o neural_network.o data.o sdl_display.o save.o -o spirales -lSDL2 -lm
make: warning:  Clock skew detected.  Your build may be incomplete

1. Mettre à jour l'heure de ton système :

- Sur Linux, tu peux synchroniser la date avec cette commande :
  
  sudo ntpdate -u pool.ntp.org

- Ou, si tu n’as pas ntpdate :
  
  sudo timedatectl set-ntp true

2. Mettre à jour la date des fichiers (pour éviter immédiatement les messages d'avertissement) :
  
  find . -exec touch {} +

Cette commande met à jour les timestamps des fichiers du dossier courant.

3. Recompiler ton projet :
  
  make clean
  make

✅ Résultat attendu :
Après avoir appliqué ces commandes, relance la compilation, et le message d'avertissement devrait disparaître.

----

⚙️ Compilation du projet :

- Pour compiler, utilisez simplement :
  
  make

- Pour supprimer les fichiers de compilation et nettoyer l'environnement :
  
  make clean

⚠️ **Important** :  
Avant de lancer cette version avec les binaires, lancez toujours :

  ./spirales

Vous verrez un message d'usage qui indique comment lancer correctement l'exécutable :

Usage: ./spirales [train|load] [fichier_sauvegarde]

----

📌 **Exemple de compilation et d'exécution :**

1. Nettoyez l'environnement de compilation :
   
   make clean

2. Compilez votre projet :
   
   make

3. Lancez votre exécutable avec l'option appropriée :
   
   ./spirales [train ou load] [nom_du_fichier_sauvegarde (facultatif)]

Exemple concret :

- Entraîner un nouveau réseau neuronal et le sauvegarder dans "chahca" :
  
  ./spirales train chahca

- Charger un réseau neuronal existant :
  
  ./spirales load chahca

ou biens 
    ./spirale train 

- Charger un réseau neuronal existant :
  
  ./spirales load 
 

Si vous faites une erreur dans la commande (ex : `lead` au lieu de `load`), le programme affiche clairement ce que vous devez utiliser :

Mode inconnu : lead. Utilisez 'train' ou 'load'.

----

📍 **Commande finale pour tout nettoyer (y compris les fichiers parasites)** :

make clean

Si vous tapez mal (`make celan`), vous aurez une erreur. Veillez à bien taper.

----

💡 **Astuce :**  
Utilisez la commande suivante pour lister les fichiers présents après nettoyage, afin de vérifier que tout est propre :

ls
