
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicule.h"
#include "parc.h"
#include "client.h"
#include "location.h"
//------------------------------------PARC---------------------------------------------------


// Fonction pour ajouter un vehicule au parc
void ajouter_vehicule(struct Parc *parc) {
  // Verifier que le parc n'est pas plein
  if (parc->nbr_emplacements <= parc->nbr_vehicules) {
    printf("Le parc est plein.\n");
    return;
  }

  // Allouer la memoire necessaire pour le nouveau vehicule
  struct Vehicule *vehicule = (struct Vehicule *)malloc(sizeof(struct Vehicule));

  // Saisir les données du véhicule
  printf("Numero d'immatriculation : ");
  scanf("%s", vehicule->matricule);
  printf("Constructeur : ");
  scanf("%s", vehicule->constructeur);
  printf("Marque : ");
  scanf("%s", vehicule->marque);
  printf("Etat : ");
  scanf("%s", vehicule->etat);

  // Ajouter le véhicule au tableau de vehicules
  parc->vehicules[parc->nbr_vehicules++] = vehicule;
}
// Fonction pour modifier l'état d'un véhicule
void modifier_etat_vehicule(struct Parc *parc, char *matricule, char *nouvel_etat) {
  // Trouver le véhicule à modifier
  int i;
  for (i = 0; i < parc->nbr_vehicules; i++) {
    // Comparer en ignorant les caractères de nouvelle ligne
    if (strncmp(parc->vehicules[i]->matricule, matricule, strlen(matricule)) == 0) {
      // Modifier l'etat du vehicule
      strcpy(parc->vehicules[i]->etat, nouvel_etat);
      printf("Etat du vehicule modifie avec succes.\n");
      return;
    }
  }

  // Le véhicule n'a pas été trouvé
  printf("Le vehicule avec la matricule %s n'existe pas.\n", matricule);
}


// Fonction pour supprimer un véhicule du parc
void supprimer_vehicule(struct Parc *parc, char *matricule) {
  // Trouver le vehicule à supprimer
  int i;
  for (i = 0; i < parc->nbr_vehicules; i++) {
    if (strcmp(parc->vehicules[i]->matricule, matricule) == 0) {
      // Supprimer le véhicule du tableau
      free(parc->vehicules[i]);
      parc->vehicules[i] = parc->vehicules[parc->nbr_vehicules - 1];
      parc->nbr_vehicules--;
      return;
    }
  }

  // Le véhicule n'a pas été trouvé
  printf("Le vehicule avec la matricule %s n'existe pas.\n", matricule);
}

// Fonction pour afficher le parc automobile
void afficher_parc(struct Parc *parc) {
  // Afficher le nombre de véhicules
  printf("Nombre de vehicules : %d\n", parc->nbr_vehicules);

  // Afficher les données de chaque véhicule
  for (int i = 0; i < parc->nbr_vehicules; i++) {
    printf("Vehicule n°%d\n", i + 1);
    // Appeler la fonction pour afficher les détails du véhicule
    afficher_vehicule(parc->vehicules[i]);
  }
}


// Fonction pour afficher le menu de gestion du parc
void menu_gestion_parc(struct Parc *parc) {
  int choix;
  do {
    printf("\n\n**Menu gestion du parc**\n\n");
    printf("1. Ajouter un véhicule\n");
    printf("2. Modifier l'etat d'un vehicule\n");
    printf("3. Supprimer un vehicule\n");
    printf("4. Afficher le parc\n");
    printf("5. Retour au menu principal\n\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
      case 1:
        ajouter_vehicule(parc);
        break;
      case 2: {
        char matricule[10];
        char nouvel_etat[10];
        printf("Matricule du vehicule : ");
        scanf("%s", matricule);
        printf("Nouvel etat : ");
        scanf("%s", nouvel_etat);
        modifier_etat_vehicule(parc, matricule, nouvel_etat);
        break;
      }
      case 3: {
        char matricule[10];
        printf("Matricule du vehicule a supprimer : ");
        scanf("%s", matricule);
        supprimer_vehicule(parc, matricule);
        break;
      }
      case 4:
        afficher_parc(parc);
        break;
      case 5:
        printf("Retour au menu principal.\n");
        break;
      default:
        printf("Choix invalide.\n");
        break;
    }
  } while (choix != 5);
}
