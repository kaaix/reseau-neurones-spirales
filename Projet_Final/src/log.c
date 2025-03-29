#include "log.h"

LogLevel CURRENT_LOG_LEVEL = LOG_LEVEL_INFO; // par défaut : INFO

// Convertit le niveau en string lisible
const char* log_level_to_string(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_INFO:    return "INFO";
        case LOG_LEVEL_WARNING: return "WARNING";
        case LOG_LEVEL_ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}

// Fonction principale de log
void log_message(LogLevel level, const char *format, ...) {
    if (level < CURRENT_LOG_LEVEL)
        return;

    // Récupérer l'heure courante
    time_t rawtime;
    struct tm *timeinfo;
    char time_str[20];
    
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", timeinfo);

    // Affichage du log formaté
    fprintf(stderr, "[%s][%s] ", time_str, log_level_to_string(level));

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
}

// Permet de changer dynamiquement le niveau de log
void log_set_level(LogLevel level) {
    CURRENT_LOG_LEVEL = level;
}
void log_generation_spirale(const char *mode) {
    log_message(LOG_LEVEL_INFO, "Génération des spirales en mode %s.", mode);
}
void log_save_network(const char *filename) {
    log_message(LOG_LEVEL_INFO, "Sauvegarde du réseau dans '%s'.", filename);
}

void log_load_network(const char *filename) {
    log_message(LOG_LEVEL_INFO, "Chargement du réseau depuis '%s'.", filename);
}

void log_save_int(const char *filename, int value) {
    log_message(LOG_LEVEL_INFO, "Sauvegarde de l'entier %d dans '%s'.", value, filename);
}

void log_load_int(const char *filename, int value) {
    log_message(LOG_LEVEL_INFO, "Chargement de l'entier %d depuis '%s'.", value, filename);
}
void log_colorier_once(const char *mode) {
    static int deja_fait = 0;
    if (!deja_fait) {
        log_message(LOG_LEVEL_INFO, "Coloriage de l'écran (%s) en cours...", mode);
        deja_fait = 1;
    }
}
// ==================================================
// ===           GESTION DU RÉSEAU DE NEURONES    ===
// ==================================================

 void log_propagation_once() {
    static int already_logged = 0;
    if (!already_logged) {
        log_message(LOG_LEVEL_INFO, "Propagation des données à travers le réseau.");
        already_logged = 1;
    }
}
void log_retropropagation() {
    static int already_logged1= 0;
    if (!already_logged1) {
        log_message(LOG_LEVEL_INFO, "Rétropropagation en cours.");
        already_logged1 = 1;
    }
}
// ========== LOGGING UTILS ==========
void log_choix_train_load() {
    static int already_logged = 0;
    if (!already_logged) {
        log_message(LOG_LEVEL_INFO, "Fenêtre affichée : Choix Train / Load.");
        already_logged = 1;
    }
}

 void log_lancement_train() {
    log_message(LOG_LEVEL_INFO, "Lancement de l'entraînement du réseau neuronal.");
}

void log_lancement_load(const char* nom_fichier) {
    log_message(LOG_LEVEL_INFO, "Chargement d'un réseau depuis : %s", nom_fichier);
}