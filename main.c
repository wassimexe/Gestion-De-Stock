#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"

int main() {
    int choix;
    while (1) {
        printf("\nBienvenue dans le gestionnaire de stock. Veuillez choisir votre role:\n");
        printf("1. Client\n");
        printf("2. Gerant\n");
        printf("3. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);
        getchar();

        if (choix == 1) {
            gererClient();
        } else if (choix == 2) {
            if (!verifierMotDePasse()) continue;
            gererGerant();
        } else if (choix == 3) {
            printf("Merci d'avoir utilise le gestionnaire de stock. Au revoir!\n");
            break;
        } else {
            printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
    return 0;
}
