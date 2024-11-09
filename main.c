#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicule.h"
#include "parc.h"
#include "client.h"
#include "location.h"
#define MAX_VEHICULES 100



//----------------------------tableau de bord---------------------------------------------

struct TableauDeBord {
  int nbr_total_vehicules;
  int nbr_vehicules_loues;
  int nbr_clients;
};
void afficher_tableau_de_bord(struct TableauDeBord *tableau_de_bord) {
  printf("\n** Tableau de bord **\n");
  printf("Nombre total de vehicules : %d\n", tableau_de_bord->nbr_total_vehicules);
  printf("Nombre de vehicules loues : %d\n", tableau_de_bord->nbr_vehicules_loues);
  printf("Nombre total de clients : %d\n", tableau_de_bord->nbr_clients);
  // Affichez d'autres statistiques
}
void mettre_a_jour_tableau_de_bord(struct EnsembleLocation *ensemble_locations, struct TableauDeBord *tableau_de_bord, struct Parc *parc) {
  tableau_de_bord->nbr_vehicules_loues = ensemble_locations->nbr_locations;
  tableau_de_bord->nbr_total_vehicules = parc->nbr_vehicules;

  // Initialisez le nombre total de clients à 0
  tableau_de_bord->nbr_clients = 0;

  // Parcourez les locations pour compter le nombre total de clients
  for (int i = 0; i < ensemble_locations->nbr_locations; i++) {
    int cin_client = ensemble_locations->locations[i].client->cin;

    // Vérifiez si le client a déjà été compté
    int client_compte = 0;
    for (int j = 0; j < i; j++) {
      if (ensemble_locations->locations[j].client->cin == cin_client) {
        client_compte = 1;
        break;
      }
    }

    // Si le client n'a pas été compté, incrémentez le nombre total de clients
    if (!client_compte) {
      tableau_de_bord->nbr_clients++;
    }
  }

  // Mettez à jour d'autres statistiques selon vos besoins
}


int main() {


  // Initialiser le parc automobile
  struct Parc *parc = (struct Parc *)malloc(sizeof(struct Parc));
  parc->vehicules = (struct Vehicule **)malloc(sizeof(struct Vehicule *) * MAX_VEHICULES);
  parc->nbr_vehicules = 0;
  parc->nbr_emplacements = MAX_VEHICULES;



    //Initialiser le tableau de bord
      struct TableauDeBord tableau_de_bord;
  tableau_de_bord.nbr_total_vehicules = parc->nbr_vehicules;
  tableau_de_bord.nbr_vehicules_loues = 0;
  tableau_de_bord.nbr_clients = 0;

  // Initialiser l'ensemble des locations
  struct EnsembleLocation *ensemble_locations = (struct EnsembleLocation *)malloc(sizeof(struct EnsembleLocation));
  ensemble_locations->locations = NULL;
  ensemble_locations->nbr_locations = 0;

  // Menu principal
  int choix;
  do {
    printf("\n\n**Menu principal**\n\n");
    printf("1. Gerer le parc automobile\n");
    printf("2. Gerer les locations\n");
    printf("3. Tableau de bord\n");
    printf("4. Quitter\n\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
      case 1:
        // Gérer le parc automobile
        menu_gestion_parc(parc);
        break;
      case 2:
        // Gerer les locations
        menu_gestion_locations(ensemble_locations, parc);
        break;
      case 3:
        // Tableau de bord
        mettre_a_jour_tableau_de_bord(ensemble_locations, &tableau_de_bord, parc);
        afficher_tableau_de_bord(&tableau_de_bord);

        break;
      case 4:
          printf("Au revoir !\n");
        break;
      default:
        printf("Choix invalide.\n");
        break;
    }
  } while (choix != 3);

  // Liberer la memoire allouee pour le parc
  for (int i = 0; i < parc->nbr_vehicules; i++) {
    free(parc->vehicules[i]);
  }
  free(parc->vehicules);
  free(parc);

  // Liberer la memoire allouee pour l'ensemble des locations
  for (int i = 0; i < ensemble_locations->nbr_locations; i++) {
    free(ensemble_locations->locations[i].client);
  }
  free(ensemble_locations->locations);
  free(ensemble_locations);

  return 0;
}
