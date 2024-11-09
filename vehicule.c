
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicule.h"
#include "parc.h"
#include "client.h"
#include "location.h"


// Fonction pour mettre à jour le constructeur d'un véhicule
void mettre_a_jour_constructeur(struct Vehicule *vehicule, const char *nouveau_constructeur) {
  strcpy(vehicule->constructeur, nouveau_constructeur);
}

// Fonction pour mettre à jour la marque d'un véhicule
void mettre_a_jour_marque(struct Vehicule *vehicule, const char *nouvelle_marque) {
  strcpy(vehicule->marque, nouvelle_marque);
}

// Fonction pour mettre à jour l'état d'un véhicule
void mettre_a_jour_etat(struct Vehicule *vehicule, const char *nouvel_etat) {
  strcpy(vehicule->etat, nouvel_etat);
}

// Fonction pour saisir les donnees d'un vehicule
void saisir_vehicule(struct Vehicule *vehicule) {
  printf("Numero d'immatriculation : ");
  scanf("%s", vehicule->matricule);
  printf("Constructeur : ");
  scanf("%s", vehicule->constructeur);
  printf("Marque : ");
  scanf("%s", vehicule->marque);
  printf("Etat : ");
  scanf("%s", vehicule->etat);
}


// Fonction pour afficher les donnees d'un vehicule
void afficher_vehicule(const struct Vehicule *vehicule) {
  printf("Numero d'immatriculation : %s\n", vehicule->matricule);
  printf("Constructeur : %s\n", vehicule->constructeur);
  printf("Marque : %s\n", vehicule->marque);
  printf("Etat : %s\n", vehicule->etat);
}
