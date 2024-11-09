#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vehicule.h"
#include "parc.h"
#include "client.h"
#include "location.h"
//------------------------------------Location---------------------------------------------------
// Fonction pour comparer deux dates
// Retourne 1 si date1 > date2, -1 si date1 < date2, 0 si les dates sont egales
int comparer_dates(struct Date date1, struct Date date2) {
    if (date1.annee > date2.annee) {
        return 1;
    } else if (date1.annee < date2.annee) {
        return -1;
    } else {
        // Les années sont egales, comparez les mois
        if (date1.mois > date2.mois) {
            return 1;
        } else if (date1.mois < date2.mois) {
            return -1;
        } else {
            // Les mois sont egaux, comparez les jours
            if (date1.jour > date2.jour) {
                return 1;
            } else if (date1.jour < date2.jour) {
                return -1;
            } else {
                // Les dates sont egales
                return 0;
            }
        }
    }
}

// Fonction pour saisir les données d'une location
void saisir_location(struct Location *location, struct Parc *parc, struct EnsembleLocation *ensemble_locations) {
  // Afficher les véhicules disponibles dans le parc
  printf("Vehicules disponibles dans le parc :\n");

  // Afficher uniquement les véhicules avec l'etat "disponible"
  for (int i = 0; i < parc->nbr_vehicules; i++) {
    if (strcmp(parc->vehicules[i]->etat, "disponible") == 0) {
      printf("Numero %d\n", i + 1);
      afficher_vehicule(parc->vehicules[i]);
    }
  }

  // Sélectionner un vehicule
  int choix_vehicule;
  printf("Selectionnez le numero du vehicule a louer : ");
  scanf("%d", &choix_vehicule);

  // Vérifier si le numéro de véhicule est valide
  if (choix_vehicule <= 0 || choix_vehicule > parc->nbr_vehicules) {
    printf("Numero de vehicule invalide.\n");
    return;
  }

  // Verifier si le véhicule est disponible
  if (strcmp(parc->vehicules[choix_vehicule - 1]->etat, "disponible") != 0) {
    printf("Le vehicule sélectionne n'est pas disponible.\n");
    return;
  }

  // Copier les donnees du véhicule dans la location
  location->vehicule = parc->vehicules[choix_vehicule - 1];

  // Saisir les autres données de la location
  printf("Numero de CIN du client : ");
  scanf("%d", &location->client->cin);
  printf("Date de debut de la location (jour mois annee) : ");
  scanf("%d %d %d", &location->date_debut.jour, &location->date_debut.mois, &location->date_debut.annee);

  printf("Date de fin de la location (jour mois annee) : ");
  scanf("%d %d %d", &location->date_fin.jour, &location->date_fin.mois, &location->date_fin.annee);

   if (comparer_dates(location->date_debut, location->date_fin) >= 0) {
        printf("Erreur : La date de fin doit etre ulterieure a la date de debut.\n");
        return;
    }
  printf("Prix total : ");
  scanf("%f", &location->prix_total);
  printf("Montant d'avance : ");
  scanf("%f", &location->montant_avance);

  // Ajouter la location à l'ensemble des locations
  ensemble_locations->locations = realloc(ensemble_locations->locations, (ensemble_locations->nbr_locations + 1) * sizeof(struct Location));
  ensemble_locations->locations[ensemble_locations->nbr_locations++] = *location;

  // Mettre à jour l'état du véhicule à "loué"
  mettre_a_jour_etat(parc->vehicules[choix_vehicule - 1], "loue");

  printf("Location ajoutee avec succes.\n");
}

// Fonction pour mettre fin à une location

// Fonction pour terminer une location
void fin_location(struct EnsembleLocation *ensemble_locations) {
  // Afficher les locations en cours
  printf("Locations en cours :\n");
  for (int i = 0; i < ensemble_locations->nbr_locations; i++) {
    printf("Location n°%d\n", i + 1);
    printf("Matricule du vehicule : %s\n", ensemble_locations->locations[i].vehicule->matricule);
    printf("Nom du client (CIN) :  %d\n", ensemble_locations->locations[i].client->cin);
    printf("Date de debut : %s\n", ensemble_locations->locations[i].date_debut);
    printf("Date de fin : %s\n", ensemble_locations->locations[i].date_fin);
    printf("Prix total : %.2f\n", ensemble_locations->locations[i].prix_total);
    printf("Montant d'avance : %.2f\n", ensemble_locations->locations[i].montant_avance);
  }

  // Saisir les informations pour terminer une location
  int cin_client;
  char matricule[100];

  printf("Entrez le CIN du client : ");
  scanf("%d", &cin_client);

  printf("Entrez la matricule du véhicule : ");
  scanf("%s", matricule);

  // Rechercher la location à terminer
  int index_location = -1;
  for (int i = 0; i < ensemble_locations->nbr_locations; i++) {
    if (ensemble_locations->locations[i].client->cin == cin_client &&
        strcmp(ensemble_locations->locations[i].vehicule->matricule, matricule) == 0) {
      index_location = i;
      break;
    }
  }

  // Verifier si la location a été trouvée
  if (index_location == -1) {
    printf("Location non trouvee.\n");
    return;
  }

  // Supprimer la location terminée
  for (int i = index_location; i < ensemble_locations->nbr_locations - 1; i++) {
    ensemble_locations->locations[i] = ensemble_locations->locations[i + 1];
  }
  ensemble_locations->nbr_locations--;

  printf("Location terminee avec succes.\n");
}




// Fonction pour consulter les véhicules actuellement loués
void consulter_vehicules_loues(struct EnsembleLocation *ensemble_locations) {
  // Afficher les véhicules actuellement loués
  printf("Vehicules actuellement loues :\n");
  for (int i = 0; i < ensemble_locations->nbr_locations; i++) {
        printf("-----------------------------\n");
    printf("Matricule du vehicule : %s\n", ensemble_locations->locations[i].vehicule->matricule);
    printf("CIN du client :  %d\n", ensemble_locations->locations[i].client->cin);
    printf("Date de debut : %d/%d/%d\n", ensemble_locations->locations[i].date_debut.jour,
           ensemble_locations->locations[i].date_debut.mois, ensemble_locations->locations[i].date_debut.annee);
    printf("Date de fin : %d/%d/%d\n", ensemble_locations->locations[i].date_fin.jour,
           ensemble_locations->locations[i].date_fin.mois, ensemble_locations->locations[i].date_fin.annee);
    printf("Prix total : %.2f\n", ensemble_locations->locations[i].prix_total);
    printf("Montant d'avance : %.2f\n", ensemble_locations->locations[i].montant_avance);
    printf("-----------------------------\n");
  }
}

// Fonction pour consulter les véhicules loués par un client
void consulter_vehicules_par_client(struct EnsembleLocation *ensemble_locations, int cin_client) {
  // Afficher les véhicules loués par le client
  printf("Véhicules loués par le client (CIN : %d) :\n", cin_client);
  for (int i = 0; i < ensemble_locations->nbr_locations; i++) {
    if (ensemble_locations->locations[i].client->cin == cin_client) {
      printf("Matricule du vehicule : %s\n", ensemble_locations->locations[i].vehicule->matricule);
      printf("Date de debut : %d/%d/%d\n", ensemble_locations->locations[i].date_debut.jour,
             ensemble_locations->locations[i].date_debut.mois, ensemble_locations->locations[i].date_debut.annee);
      printf("Date de fin : %d/%d/%d\n", ensemble_locations->locations[i].date_fin.jour,
             ensemble_locations->locations[i].date_fin.mois, ensemble_locations->locations[i].date_fin.annee);
      printf("Prix total : %.2f\n", ensemble_locations->locations[i].prix_total);
      printf("Montant d'avance : %.2f\n", ensemble_locations->locations[i].montant_avance);
      printf("-----------------------------\n");
    }
  }
}


// Fonction pour afficher le menu de gestion des locations
void menu_gestion_locations(struct EnsembleLocation *ensemble_locations, struct Parc *parc) {
  int choix;
  do {
    printf("\n\n**Menu gestion des locations**\n\n");
    printf("5. Nouvelle location (Ajout d’une location)\n");
    printf("6. Fin de location (Suppression)\n");
    printf("7. Consultation des vehicules actuellement loues\n");
    printf("8. Consultation des vehicules loues par un client\n");
    printf("9. Retour au menu principal\n\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
      case 5: {
        struct Location nouvelle_location;
        nouvelle_location.client = (struct Client *)malloc(sizeof(struct Client));
        saisir_location(&nouvelle_location, parc,ensemble_locations);
        ensemble_locations->locations = realloc(ensemble_locations->locations, (ensemble_locations->nbr_locations + 1) * sizeof(struct Location));
        //ensemble_locations->locations[ensemble_locations->nbr_locations++] = nouvelle_location;
        break;
      }
      case 6:
        fin_location(ensemble_locations);
        break;
      case 7:
        consulter_vehicules_loues(ensemble_locations);
        break;
      case 8: {
        int cin_client;
        printf("Entrez le CIN du client : ");
        scanf("%d", &cin_client);
        consulter_vehicules_par_client(ensemble_locations, cin_client);
        break;
      }
      case 9:
        printf("Retour au menu principal.\n");
        break;
      default:
        printf("Choix invalide.\n");
        break;
    }
  } while (choix != 9);
}
