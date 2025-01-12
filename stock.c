#include "stock.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//choix client
void afficherMenuClient() {

    printf("\n------------*************Menu Client**************------------\n");
    printf("1. Afficher le stock\n");
    printf("2. Acheter un produit\n");
    printf("3. Rechercher un produit par nom\n");
    printf("4. Afficher les produits tries par prix croissant\n");
    printf("5. Afficher les produits tries par prix decroissant\n");
    printf("6. Quitter\n");
    printf("-----------*************************************----------------\n");
}

//choix gerant
void afficherMenuGerant(){

    printf("\n-----------*********Menu Gerant******************------------\n");
    printf("1. Ajouter un produit\n");
    printf("2. Modifier un produit\n");
    printf("3. Supprimer un produit\n");
    printf("4. Afficher le stock\n");
    printf("5. Historique des achats\n");
    printf("6. Quitter\n");
}

//verifier si le mot de passe est correct
int verifierMotDePasse()
{
    char mot_de_passe[100];
    printf("Veuillez entrer le mot de passe : ");
    fgets(mot_de_passe, sizeof(mot_de_passe), stdin);
    mot_de_passe[strcspn(mot_de_passe, "\n")] = 0;
    if (strcmp(mot_de_passe, "1234") == 0)
    {
        printf("Mot de passe correct.\n");
        return 1;
    }
    else
    {
        printf("Mot de passe incorrect. Acces refuse.\n");
        return 0;
    }
}

//affichage du stock
void afficherStock()
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char buffer[256];
    Produit p;
    printf("\nStock de produits:\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| ID     | Nom             | Description           | Categorie       | Prix         | Quantite    | Seuil   |\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), fp))
    {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f;%d;%d;%d", &p.id, p.nom, p.description, p.categorie, &p.prix_unitaire,
               &p.quantite_stock, &p.seuil_alerte, &p.id_fournisseur);
        printf("| %-3d    | %-12s    | %-18s    | %-12s    | %-9.2f    | %-8d    | %-5d   |\n", p.id, p.nom, p.description, p.categorie, p.prix_unitaire,
               p.quantite_stock, p.seuil_alerte);
    }

    printf("-------------------------------------------------------------------------------------------------------------\n");
    fclose(fp);
}

//affichage d'historique
void afficherHistorique()
{
    FILE *fp;
    char buffer[256];

    fp = fopen(HISTORIQUE_FILE, "r");
    if (fp == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier historique.\n");
        return;
    }

    printf("\nHistorique des achats:\n");
    printf("---------------------------------------\n");
    printf("| ID  | Nom            | Quantite     |\n");
    printf("---------------------------------------\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        int id, quantite;
        char nom[100];
        sscanf(buffer, "%d;%[^;];%d", &id, nom, &quantite);
        printf("| %-3d | %-14s | %-10d   |\n", id, nom, quantite);
    }
    printf("---------------------------------------\n");

    fclose(fp);
}

//si le choix est "2" afficher le menu "client"
void gererClient(){

    int choixClient;
    do {
        afficherMenuClient();
        printf("Choisissez une option : ");
        scanf("%d", &choixClient);
        getchar();

        switch (choixClient) {
        case 1:
            afficherStock();
            break;
        case 2: {
            char nomProduit[100];
            int quantite;
            printf("Entrez le nom du produit a acheter : ");
            fgets(nomProduit, sizeof(nomProduit), stdin);
            nomProduit[strcspn(nomProduit, "\n")] = 0;

            printf("Entrez la quantite a acheter : ");
            scanf("%d", &quantite);
            getchar();

            acheterProduit(nomProduit, quantite);
            break;
        }

        case 3: {
            char nomRecherche[100];
            printf("Entrez le nom du produit a rechercher : ");
            fgets(nomRecherche, sizeof(nomRecherche), stdin);
            nomRecherche[strcspn(nomRecherche, "\n")] = 0;

            rechercherProduitParNom(nomRecherche);
            break;
        }

        case 4:
            afficherProduitsTriesParPrixCroissant();
            break;
        case 5:
            afficherProduitsTriesParPrixDecroissant();
            break;
        case 6:
            printf("Retour au menu principal.\n");
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choixClient != 6);
}

//si le choix est "2" afficher le menu "gerant"
void gererGerant(){

    int choixGerant;
    do
    {
        afficherMenuGerant();
        printf("Choisissez une option: ");
        scanf("%d", &choixGerant);
        getchar();

        switch (choixGerant)
        {
        case 1:
            ajouterProduitMenu();
            break;
        case 2:
        {
            int id;
            printf("Entrez l'ID du produit a modifier : ");
            scanf("%d", &id);
            getchar();
            modifierProduit(id);
            break;
        }

        case 3:
        {
            int id;
            printf("Entrez l'ID du produit a supprimer : ");
            scanf("%d", &id);
            supprimerProduit(id);
            break;
        }
        case 4:
            afficherStock();
            break;
        case 5:
            afficherHistorique();
            break;
        case 6:
            printf("Retour au menu principal.\n");
            break;
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
    while (choixGerant != 6);
}

//formule
void ajouterProduitMenu(){
    Produit p;
    printf("\nEntrez les informations du produit :\n");

    printf("Nom du produit : ");
    fgets(p.nom, sizeof(p.nom), stdin);
    p.nom[strcspn(p.nom, "\n")] = 0;

    printf("Description du produit : ");
    fgets(p.description, sizeof(p.description), stdin);
    p.description[strcspn(p.description, "\n")] = 0;

    printf("Categorie du produit : ");
    fgets(p.categorie, sizeof(p.categorie), stdin);
    p.categorie[strcspn(p.categorie, "\n")] = 0;

    printf("Prix unitaire du produit : ");
    if (scanf("%f", &p.prix_unitaire) != 1)
    {
        printf("Erreur : Entree invalide pour le prix.\n");
        return;
    }
    getchar();

    printf("Quantite en stock : ");
    if (scanf("%d", &p.quantite_stock) != 1)
    {
        printf("Erreur : Entree invalide pour la quantité.\n");
        return;
    }
    getchar();

    printf("Seuil d'alerte de quantite : ");
    if (scanf("%d", &p.seuil_alerte) != 1)
    {
        printf("Erreur : Entre invalide pour le seuil.\n");
        return;
    }
    getchar();

    FILE *fp = fopen(FILENAME, "r");
    if (fp)
    {
        char buffer[256];
        int dernierId = 0;
        while (fgets(buffer, sizeof(buffer), fp))
        {
            int id;
            sscanf(buffer, "%d", &id);
            if (id > dernierId)
            {
                dernierId = id;
            }
        }
        fclose(fp);
        p.id = dernierId + 1;
    }
    else
    {
        p.id = 1;
    }

    ajouterProduit(p);
}

//ajout produit
void ajouterProduit(Produit p)
{
    FILE *fp = fopen(FILENAME, "a");
    if (!fp)
    {
        printf("Erreur : Impossible d'ouvrir ou de créer le fichier %s\n", FILENAME);
        return;
    }

    fprintf(fp, "%d;%s;%s;%s;%.2f;%d;%d;%d\n",
            p.id,
            p.nom,
            p.description,
            p.categorie,
            p.prix_unitaire,
            p.quantite_stock,
            p.seuil_alerte,
            p.id_fournisseur);

    fclose(fp);
    printf("Produit ajoute avec succes.\n");
}

//suppression
void supprimerProduit(int id)
{
    FILE *fp = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.csv", "w");
    char buffer[256];
    Produit produit;
    int produitSupprime = 0;

    if (fp == NULL || tempFile == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f;%d;%d;%d", &produit.id, produit.nom, produit.description,
               produit.categorie, &produit.prix_unitaire, &produit.quantite_stock, &produit.seuil_alerte,
               &produit.id_fournisseur);

        if (produit.id != id)
        {
            fprintf(tempFile, "%d;%s;%s;%s;%.2f;%d;%d;%d\n", produit.id, produit.nom, produit.description,
                    produit.categorie, produit.prix_unitaire, produit.quantite_stock, produit.seuil_alerte,
                    produit.id_fournisseur);
        }
        else
        {
            produitSupprime = 1;
        }
    }

    fclose(fp);
    fclose(tempFile);
    remove(FILENAME);
    rename("temp.csv", FILENAME);

    if (produitSupprime)
    {
        printf("Produit avec l'ID %d supprime avec succes.\n", id);
    }
    else
    {
        printf("Aucun produit trouve avec l'ID %d.\n", id);
    }
}

//modification
void modifierProduit(int id)
{
    FILE *fp = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.csv", "w");
    char buffer[256];
    Produit produit;
    int produitModifie = 0;

    if (fp == NULL || tempFile == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f;%d;%d;%d", &produit.id, produit.nom, produit.description,
               produit.categorie, &produit.prix_unitaire, &produit.quantite_stock, &produit.seuil_alerte,
               &produit.id_fournisseur);

        if (produit.id == id)
        {
            produitModifie = 1;
            printf("Modification du produit avec ID %d :\n", id);

            printf("Nom actuel (%s) : ", produit.nom);
            fgets(produit.nom, sizeof(produit.nom), stdin);
            produit.nom[strcspn(produit.nom, "\n")] = 0;

            printf("Description actuelle (%s) : ", produit.description);
            fgets(produit.description, sizeof(produit.description), stdin);
            produit.description[strcspn(produit.description, "\n")] = 0;

            printf("Categorie actuelle (%s) : ", produit.categorie);
            fgets(produit.categorie, sizeof(produit.categorie), stdin);
            produit.categorie[strcspn(produit.categorie, "\n")] = 0;

            printf("Prix unitaire actuel (%.2f) : ", produit.prix_unitaire);
            scanf("%f", &produit.prix_unitaire);
            getchar();

            printf("Quantite en stock actuelle (%d) : ", produit.quantite_stock);
            scanf("%d", &produit.quantite_stock);
            getchar();

            printf("Seuil d'alerte actuel (%d) : ", produit.seuil_alerte);
            scanf("%d", &produit.seuil_alerte);
            getchar();
        }

        fprintf(tempFile, "%d;%s;%s;%s;%.2f;%d;%d;%d\n", produit.id, produit.nom, produit.description,
                produit.categorie, produit.prix_unitaire, produit.quantite_stock, produit.seuil_alerte,
                produit.id_fournisseur);
    }

    fclose(fp);
    fclose(tempFile);
    remove(FILENAME);
    rename("temp.csv", FILENAME);

    if (produitModifie)
    {
        printf("Produit avec l'ID %d modifie avec succes.\n", id);
    }
    else
    {
        printf("Aucun produit trouve avec l'ID %d.\n", id);
    }
}

/*------Client------*/

//achat produit
void acheterProduit(char nom[], int quantite) {
    FILE *fp = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.csv", "w");
    FILE *historiqueFile = fopen(HISTORIQUE_FILE, "a");
    char buffer[256];
    Produit produit;
    int achatEffectue = 0;

    if (fp == NULL || tempFile == NULL || historiqueFile == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f;%d;%d;%d", &produit.id, produit.nom, produit.description,
               produit.categorie, &produit.prix_unitaire, &produit.quantite_stock, &produit.seuil_alerte,
               &produit.id_fournisseur);

        if (strcmp(produit.nom, nom) == 0) {
            if (produit.quantite_stock >= quantite) {
                produit.quantite_stock -= quantite;
                fprintf(historiqueFile, "%d;%s;%d\n", produit.id, produit.nom, quantite);
                printf("Achat effectue avec succes ! %d unite(s) de %s achetee(s).\n", quantite, produit.nom);
                achatEffectue = 1;
            } else {
                printf("Stock insuffisant pour %s. Disponible : %d.\n", produit.nom, produit.quantite_stock);
            }
        }

        fprintf(tempFile, "%d;%s;%s;%s;%.2f;%d;%d;%d\n", produit.id, produit.nom, produit.description,
                produit.categorie, produit.prix_unitaire, produit.quantite_stock, produit.seuil_alerte,
                produit.id_fournisseur);
    }

    fclose(fp);
    fclose(tempFile);
    fclose(historiqueFile);

    remove(FILENAME);
    rename("temp.csv", FILENAME);

    if (!achatEffectue) {
        printf("Produit %s introuvable dans le stock.\n", nom);
    }
}

//recherche produit
void rechercherProduitParNom(char nom[]) {
    FILE *fp = fopen(FILENAME, "r");
    char buffer[256];
    Produit produit;
    int produitTrouve = 0;

    if (fp == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", FILENAME);
        return;
    }

    printf("\nRésultats de la recherche pour \"%s\" :\n", nom);
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| ID     | Nom             | Description           | Categorie       | Prix         | Quantite    | Seuil   |\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    while (fgets(buffer, sizeof(buffer), fp)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f;%d;%d;%d", &produit.id, produit.nom, produit.description,
               produit.categorie, &produit.prix_unitaire, &produit.quantite_stock, &produit.seuil_alerte,
               &produit.id_fournisseur);

        // Vérifier si le nom du produit contient la chaîne recherchée
        if (strstr(produit.nom, nom) != NULL) {
            produitTrouve = 1;
            printf("| %-3d    | %-12s    | %-18s    | %-12s    | %-9.2f    | %-8d    | %-5d   |\n",
                   produit.id, produit.nom, produit.description, produit.categorie, produit.prix_unitaire,
                   produit.quantite_stock, produit.seuil_alerte);
        }
    }

    printf("-------------------------------------------------------------------------------------------------------------\n");

    if (!produitTrouve) {
        printf("Aucun produit trouve pour \"%s\".\n", nom);
    }

    fclose(fp);
}

//affichage par ordrecroissant
void afficherProduitsTriesParPrixCroissant() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", FILENAME);
        return;
    }

    Produit produits[100]; // Tableau pour stocker les produits (100 est une taille maximale arbitraire)
    int nombreProduits = 0;
    char buffer[256];

    // Charger les produits depuis le fichier
    while (fgets(buffer, sizeof(buffer), fp)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f;%d;%d;%d",
               &produits[nombreProduits].id,
               produits[nombreProduits].nom,
               produits[nombreProduits].description,
               produits[nombreProduits].categorie,
               &produits[nombreProduits].prix_unitaire,
               &produits[nombreProduits].quantite_stock,
               &produits[nombreProduits].seuil_alerte,
               &produits[nombreProduits].id_fournisseur);
        nombreProduits++;
    }
    fclose(fp);

    // Trier les produits par prix croissant (tri à bulles)
    for (int i = 0; i < nombreProduits - 1; i++) {
        for (int j = 0; j < nombreProduits - i - 1; j++) {
            if (produits[j].prix_unitaire > produits[j + 1].prix_unitaire) {
                Produit temp = produits[j];
                produits[j] = produits[j + 1];
                produits[j + 1] = temp;
            }
        }
    }

    // Afficher les produits triés
    printf("\nProduits tries par prix croissant :\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| ID     | Nom             | Description           | Categorie       | Prix         | Quantite    | Seuil   |\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < nombreProduits; i++) {
        printf("| %-3d    | %-12s    | %-18s    | %-12s    | %-9.2f    | %-8d    | %-5d   |\n",
               produits[i].id, produits[i].nom, produits[i].description, produits[i].categorie,
               produits[i].prix_unitaire, produits[i].quantite_stock, produits[i].seuil_alerte);
    }

    printf("-------------------------------------------------------------------------------------------------------------\n");
}

//affichage par ordre décroissant
void afficherProduitsTriesParPrixDecroissant() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", FILENAME);
        return;
    }

    Produit produits[100]; // Tableau pour stocker les produits
    int nombreProduits = 0;
    char buffer[256];

    // Charger les produits depuis le fichier
    while (fgets(buffer, sizeof(buffer), fp)) {
        sscanf(buffer, "%d;%[^;];%[^;];%[^;];%f;%d;%d;%d",
               &produits[nombreProduits].id,
               produits[nombreProduits].nom,
               produits[nombreProduits].description,
               produits[nombreProduits].categorie,
               &produits[nombreProduits].prix_unitaire,
               &produits[nombreProduits].quantite_stock,
               &produits[nombreProduits].seuil_alerte,
               &produits[nombreProduits].id_fournisseur);
        nombreProduits++;
    }
    fclose(fp);

    // Trier les produits par prix décroissant (tri à bulles)
    for (int i = 0; i < nombreProduits - 1; i++) {
        for (int j = 0; j < nombreProduits - i - 1; j++) {
            if (produits[j].prix_unitaire < produits[j + 1].prix_unitaire) {
                Produit temp = produits[j];
                produits[j] = produits[j + 1];
                produits[j + 1] = temp;
            }
        }
    }

    // Afficher les produits triés
    printf("\nProduits tries par prix decroissant :\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| ID     | Nom             | Description           | Categorie       | Prix         | Quantite    | Seuil   |\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < nombreProduits; i++) {
        printf("| %-3d    | %-12s    | %-18s    | %-12s    | %-9.2f    | %-8d    | %-5d   |\n",
               produits[i].id, produits[i].nom, produits[i].description, produits[i].categorie,
               produits[i].prix_unitaire, produits[i].quantite_stock, produits[i].seuil_alerte);
    }

    printf("-------------------------------------------------------------------------------------------------------------\n");
}
