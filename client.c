#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicule.h"
#include "parc.h"
#include "client.h"
#include "location.h"

//------------------------------------Client---------------------------------------------------
// Fonction pour mettre à jour le nom d'un client
void mettre_a_jour_nom(struct Client *client, const char *nouveau_nom) {
  strcpy(client->nom, nouveau_nom);
}

// Fonction pour mettre a jour le prenom d'un client
void mettre_a_jour_prenom(struct Client *client, const char *nouveau_prenom) {
  strcpy(client->prenom, nouveau_prenom);
}

// Fonction pour mettre à jour l'adresse d'un client
void mettre_a_jour_adresse(struct Client *client, const char *nouvelle_adresse) {
  strcpy(client->adresse, nouvelle_adresse);
}

// Fonction pour saisir les données d'un client
void saisir_client(struct Client *client) {
  printf("Numero de CIN : ");
  scanf("%d", &client->cin);
  printf("Nom : ");
  scanf("%s", client->nom);
  printf("Prenom : ");
  scanf("%s", client->prenom);
  printf("Adresse : ");
  scanf("%s", client->adresse);
}

// Fonction pour afficher les données d'un client
void afficher_client(const struct Client *client) {
  printf("Numero de CIN : %d\n", client->cin);
  printf("Nom : %s\n", client->nom);
  printf("Prenom : %s\n", client->prenom);
  printf("Adresse : %s\n", client->adresse);
}

