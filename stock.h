#pragma once
#define STOCK_H
#define FILENAME "stock.csv"
#define HISTORIQUE_FILE "historique.csv"

//structure
typedef struct {
    int id;
    char nom[100];
    char description[100];
    char categorie[100];
    float prix_unitaire;
    int quantite_stock;
    int seuil_alerte;
    char date_derniere_entree[100];
    char date_derniere_sortie[100];
    int id_fournisseur;
} Produit;

//declaration des foctions
void gererClient();
void gererGerant();
void afficherMenuClient();
void afficherMenuGerant();
int verifierMotDePasse();
void afficherStock();
void acheterProduit(char nom[], int quantite);
void ajouterProduit(Produit p);
void supprimerProduit(int id);
void modifierProduit(int id);
void afficherHistorique();
void ajouterProduitMenu();
